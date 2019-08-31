#include "write.h"
#include <iostream>
#include <nan.h>
#include "../nfc.h"
#include "../ndef_types/ndef_parser.h"

class AsyncWriter : public Nan::AsyncWorker {
public:
  int nfc_status, page_status, ndef_status, erase_status;
  writeOptions options;

  AsyncWriter(Nan::Callback *callback, writeOptions options)
    : Nan::AsyncWorker(callback) {
      this->options = options;
    }

  // Execute non-blocking code. **DO NOT MAKE V8 CALLS HERE!**
  void Execute() {
    // Prevent NFC from being used by another thread
    nfc_usage.lock();

    // Write Desired NFC data //
    if (options.tag == writeType::page){
      nfc_status = nfc.Activate();
      page_status = nfc.mful.WritePage(options.page.index, options.page.data);
      nfc.Deactivate();
    }
    else if (options.tag == writeType::ndef){
      nfc_status = nfc.Activate();
      ndef_status = nfc.ndef.Write(&options.ndef.parser);
      nfc.Deactivate();
    }
    else if (options.tag == writeType::erase){
      nfc_status = nfc.Activate();
      erase_status = nfc.ndef.Erase();
      nfc.Deactivate();
    }

    // Allow other threads to use NFC
    nfc_usage.unlock();
    
    // If nonexistant, avoid calling Callback
    if (callback == nullptr){
      this->SetErrorMessage("No Callback Given");
      return;
    }
  }

  void HandleOKCallback() {
    // Prevent V8 objects from being garbage collected
    Nan::HandleScope scope;

    // Get status from the used write function //
    int write_status;
    
    switch(options.tag){
      case writeType::page:
        write_status = page_status;
        break;
      case writeType::ndef:
        write_status = ndef_status;
        break;
      case writeType::erase:
        write_status = erase_status;
        break;
    }

    // Callback Parameters
    int argCount = 2;
    v8::Local<v8::Value> argValues[] = {
      Nan::New(nfc_status),
      Nan::New(write_status)
    };

    // Start callback
    Nan::Call(callback->GetFunction(), Nan::GetCurrentContext()->Global(), argCount, argValues);
  }

  // Called if no callback given
  void HandleErrorCallback() {/*no need to do anything*/}
};

// Writes a buffer (array of ints) to an NFC page
NAN_METHOD(page_write){
  writeOptions options = {.tag = writeType::page};

  // Grab JS page index
  if (!info[0]->IsNumber()) {Nan::ThrowTypeError("Argument 1 must be a number");return;}
  options.page.index = Nan::To<int>(info[0]).FromJust();

  // Grab new JS page
  if (!info[1]->IsArray()) {Nan::ThrowTypeError("Argument 2 must be an array of 4 ints");return;}
  v8::Local<v8::Array> content = v8::Local<v8::Array>::Cast(info[1]);
  
  // Create vector from JS array
  std::vector<uint8_t> new_page;
  for (int i = 0; i < content->Length(); i++){
    new_page.push_back(Nan::To<int>(Nan::Get(content, i).ToLocalChecked()).FromJust());
  }

  options.page.data = new_page;

  // Run async write without callback
  if (!info[2]->IsFunction())
    Nan::AsyncQueueWorker(new AsyncWriter(nullptr, options));

  // Run async write with callback
  else {
    Nan::Callback *callback = new Nan::Callback(Nan::To<v8::Function>(info[2]).ToLocalChecked());
    Nan::AsyncQueueWorker(new AsyncWriter(callback, options));
  }
}

// Erases all NDEF data on an NFC tag
NAN_METHOD(erase_write){
  writeOptions options = {.tag = writeType::erase};

  // Run async write without callback
  if (!info[0]->IsFunction())
    Nan::AsyncQueueWorker(new AsyncWriter(nullptr, options));

  // Run async write with callback
  else {
    Nan::Callback *callback = new Nan::Callback(Nan::To<v8::Function>(info[0]).ToLocalChecked());
    Nan::AsyncQueueWorker(new AsyncWriter(callback, options));
  }
}

// Writes NDEF data, from NDEF parser, to an NFC tag
NAN_METHOD(ndef_write){
  writeOptions options = {.tag = writeType::ndef};

  // Check if valid JS NDEF parser
  Nan::MaybeLocal<v8::Object> maybe_obj = Nan::To<v8::Object>(info[0]);
  if (maybe_obj.IsEmpty()) {Nan::ThrowTypeError("Argument must be an ndefParser");return;}
  
  // Unwrap JS NDEF parser for C++
  ndef_parser* obj = Nan::ObjectWrap::Unwrap<ndef_parser>(maybe_obj.ToLocalChecked());
  options.ndef.parser = obj->Self();

  // Run async write without callback
  if (!info[1]->IsFunction())
    Nan::AsyncQueueWorker(new AsyncWriter(nullptr, options));

  // Run async write with callback
  else {
    Nan::Callback *callback = new Nan::Callback(Nan::To<v8::Function>(info[1]).ToLocalChecked());
    Nan::AsyncQueueWorker(new AsyncWriter(callback, options));
  }
}

// ** EXPORTED NFC WRITE OBJECT ** //
NAN_METHOD(write){
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  // Set Object Properties //
  Nan::Set(obj, Nan::New("page").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(page_write)).ToLocalChecked());

  Nan::Set(obj, Nan::New("ndef").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(ndef_write)).ToLocalChecked());

  Nan::Set(obj, Nan::New("erase").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(erase_write)).ToLocalChecked());

  info.GetReturnValue().Set(obj);
}