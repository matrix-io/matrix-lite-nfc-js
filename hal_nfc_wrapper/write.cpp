#include "write.h"
#include <nan.h>
#include "nfc.h"
#include "data/page.h"
#include "data/ndef.h"
#include<iostream>// TODO remove
using namespace std;// TODO remove

class AsyncWriter : public Nan::AsyncWorker {
public:
  writeOptions options;

  AsyncWriter(Nan::Callback *callback, writeOptions options)
    : Nan::AsyncWorker(callback) {
      this->options = options;
    }

  // Execute non-blocking code. **DO NOT MAKE V8 CALLS HERE!**
  void Execute() {
    if (options.tag == writeType::page){
      cout << "DOING PAGE WRITE..." << endl;

    }

    else if (options.tag == writeType::ndef){
      cout << "DOING NDEF WRITE..." << endl;
    }
  }

  void HandleOKCallback() {

  }
};

NAN_METHOD(page_write){
  writeOptions options = {.tag = writeType::page};

  // Grab JS page index
  if (!info[0]->IsNumber()) {Nan::ThrowTypeError("Argument 1 must be a number");return;}
  options.page_index = info[0];

  // Grab new JS page byte
  if (!info[1]->IsArray()) {Nan::ThrowTypeError("Argument 2 must be an array of 4 ints");return;}
  options.page_data = v8::Local<v8::Array>::Cast(info[1]);

  // Grab callback
  if (!info[2]->IsFunction()) {Nan::ThrowTypeError("Argument 3 must be a function");return;}
  Nan::Callback *callback = new Nan::Callback(Nan::To<v8::Function>(info[2]).ToLocalChecked());

  // Run async function
  Nan::AsyncQueueWorker(new AsyncWriter(callback, options));
}

NAN_METHOD(ndef_write){
  writeOptions options {
    .tag = writeType::ndef,
  };

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

  // Nan::Set(obj, Nan::New("ndef").ToLocalChecked(),
  // Nan::GetFunction(Nan::New<v8::FunctionTemplate>(ndef_write)).ToLocalChecked());

  info.GetReturnValue().Set(obj);
}