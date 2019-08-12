#include "read.h"
#include <nan.h>
#include "nfc.h"
#include "data/info.h"
#include "data/page.h"
#include "data/ndef.h"

#include <iostream>

class MyAsyncWorker : public Nan::AsyncWorker {
public:

  int nfc_status, info_status, pages_status, page_status, ndef_status;

  MyAsyncWorker(Nan::Callback *callback, readOptions options )
    : Nan::AsyncWorker(callback) {}

  // Execute non-blocking code
  void Execute() {
    // Prevent async calls overlapping NFC
    if (!nfc_active){
      nfc_active = true;

      // Read Info
      nfc_status = nfc.Activate();
      info_status = nfc.ReadInfo(&nfc_data.info);
      nfc.Deactivate();

      // Read Pages
      nfc_status = nfc.Activate();
      pages_status = nfc.mful.ReadPages(&nfc_data.pages);
      nfc.Deactivate();
    }
    // Run HandleErrorCallback()
    else {
      this->SetErrorMessage("Error: NFC Was Busy Reading/Writing!");
      return;
    }
  }

  void HandleOKCallback() {
    // Prevent V8 objects from being garbage collected
    Nan::HandleScope scope;

    // Return scanned NFC data
    v8::Local<v8::Object> tag_data = Nan::New<v8::Object>();

    // TODO: add conditionals on what to read
    // Create NFC data & add read status code to each object //
    // * Info
    v8::Local<v8::Object> info_data = data_info_js();
    Nan::Set(info_data, Nan::New("status").ToLocalChecked(), Nan::New(info_status));
    Nan::Set(tag_data, Nan::New("info").ToLocalChecked(), info_data);
    // * Pages
    v8::Local<v8::Object> pages_data = data_pages_js();
    Nan::Set(pages_data, Nan::New("status").ToLocalChecked(), Nan::New(pages_status));
    Nan::Set(tag_data, Nan::New("pages").ToLocalChecked(), pages_data);
    // * Page
    // * NDEF

    // Callback Parameters
    int argCount = 2;
    v8::Local<v8::Value> argv[] = {
      Nan::New(nfc_status),
      tag_data
    };

    // Start callback
    nfc_active = false;
    Nan::Call(callback->GetFunction(), Nan::GetCurrentContext()->Global(), argCount, argv);
  }

  // Called if NFC was busy
  void HandleErrorCallback() {
    Nan::HandleScope scope;
    v8::Local<v8::Value> argv[] = {
      Nan::New(-999)// status code we made up for busy NFC
    };
    Nan::Call(callback->GetFunction(), Nan::GetCurrentContext()->Global(), 1, argv);
  }
};

NAN_METHOD(read){
  //TODO: parse user args

  Nan::Callback *callback = new Nan::Callback(
    Nan::To<v8::Function>(info[0]).ToLocalChecked()
  );

  Nan::AsyncQueueWorker(new MyAsyncWorker(callback, readOptions{true,true,0,true}));
}