#include "write.h"
#include <nan.h>
#include "../nfc.h"
#include<iostream>// TODO remove
using namespace std;// TODO remove

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
      cout << "DOING NDEF WRITE... not finished yet...." << endl;
      nfc.Deactivate();
    }
    else if (options.tag == writeType::erase){
      nfc_status = nfc.Activate();
      erase_status = nfc.ndef.Erase();
      nfc.Deactivate();
    }

    // Allow other threads to use NFC
    nfc_usage.unlock();
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
    v8::Local<v8::Value> argv[] = {
      Nan::New(nfc_status),
      Nan::New(write_status)
    };

    // Start callback
    Nan::Call(callback->GetFunction(), Nan::GetCurrentContext()->Global(), argCount, argv);
  }
};

// Writes a buffer (array of ints) to an NFC page
NAN_METHOD(page_write){
  writeOptions options = {.tag = writeType::page};

  // Grab JS page index
  if (!info[0]->IsNumber()) {Nan::ThrowTypeError("Argument 1 must be a number");return;}
  options.page.index = Nan::To<int>(info[0]).FromJust();;

  // Grab new JS page
  if (!info[1]->IsArray()) {Nan::ThrowTypeError("Argument 2 must be an array of 4 ints");return;}
  v8::Local<v8::Array> content = v8::Local<v8::Array>::Cast(info[1]);
  
  // Create vector from JS array
  std::vector<uint8_t> new_page;
  for (int i = 0; i < content->Length(); i++){
    new_page.push_back(Nan::To<int>(Nan::Get(content, i).ToLocalChecked()).FromJust());
  }

  options.page.data = new_page;

  // Grab callback
  if (!info[2]->IsFunction()) {Nan::ThrowTypeError("Argument 3 must be a function");return;}
  Nan::Callback *callback = new Nan::Callback(Nan::To<v8::Function>(info[2]).ToLocalChecked());

  // Run async function
  Nan::AsyncQueueWorker(new AsyncWriter(callback, options));
}

// Erases all NDEF data on an NFC tag
NAN_METHOD(erase_write){
  writeOptions options = {.tag = writeType::erase};

  // Grab callback
  if (!info[0]->IsFunction()) {Nan::ThrowTypeError("Argument 3 must be a function");return;}
  Nan::Callback *callback = new Nan::Callback(Nan::To<v8::Function>(info[0]).ToLocalChecked());

  // Run async function
  Nan::AsyncQueueWorker(new AsyncWriter(callback, options));
}

// Writes NDEF data, from NDEF parser, to an NFC tag
NAN_METHOD(ndef_write){
  writeOptions options = {.tag = writeType::ndef};

  Nan::Callback *callback = new Nan::Callback(Nan::To<v8::Function>(info[0]).ToLocalChecked());

  // Run async function
  Nan::AsyncQueueWorker(new AsyncWriter(callback, options));
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