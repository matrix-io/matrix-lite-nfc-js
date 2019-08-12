#include "read.h"
#include <nan.h>
#include "nfc.h"
#include "data/info.h"
#include "data/page.h"
#include "data/ndef.h"

#include <iostream>

class MyAsyncWorker : public Nan::AsyncWorker {
public:

  int info_status, pages_status;

  MyAsyncWorker(Nan::Callback *callback, readOptions options )
    : Nan::AsyncWorker(callback) {}

  // Execute non-blocking code
  void Execute() {
    // Read NFC tag
    nfc.Activate();
    info_status = nfc.ReadInfo(&nfc_data.info);
    nfc.Deactivate();

    nfc.Activate();
    pages_status = nfc.mful.ReadPages(&nfc_data.pages);
    nfc.Deactivate();
  }

  void HandleOKCallback() {
    // Prevent V8 objects from being garbage collected
    Nan::HandleScope scope;

    // Return scanned NFC data
    v8::Local<v8::Object> tag_data = Nan::New<v8::Object>();

    // Create NFC data & add read status code to each object
    v8::Local<v8::Object> info_data = data_info_js();
    Nan::Set(info_data, Nan::New("status").ToLocalChecked(), Nan::New(info_status));
    Nan::Set(tag_data, Nan::New("info").ToLocalChecked(), info_data);

    v8::Local<v8::Object> pages_data = data_pages_js();
    Nan::Set(pages_data, Nan::New("status").ToLocalChecked(), Nan::New(pages_status));
    Nan::Set(tag_data, Nan::New("pages").ToLocalChecked(), pages_data);

    // Callback Parameters
    int argCount = 1;

    v8::Local<v8::Value> argv[] = {
      tag_data
    };

    // Start callback
    Nan::Call(callback->GetFunction(), Nan::GetCurrentContext()->Global(), argCount, argv);
  }
};

NAN_METHOD(read){
  std::cout << "HELLOO" << std::endl;



  Nan::Callback *callback = new Nan::Callback(
    Nan::To<v8::Function>(info[0]).ToLocalChecked()
  );

  Nan::AsyncQueueWorker(new MyAsyncWorker(callback, readOptions{true,true,0,true}));
}