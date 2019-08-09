#include "read.h"
#include <nan.h>
#include "nfc.h"
#include "data/info.h"
#include "data/page.h"
#include "data/ndef.h"

#include <iostream>

class MyAsyncWorker : public Nan::AsyncWorker {
public:

  int statusCode;

  MyAsyncWorker(Nan::Callback *callback, readOptions options )
    : Nan::AsyncWorker(callback) {}

  // Execute non-blocking code
  void Execute() {
    // Read NFC tag
    statusCode = nfc.Activate();

    nfc.ReadInfo(&nfc_data.info);
    nfc.mful.ReadPages(&nfc_data.pages);

    nfc.Deactivate();
  }

  void HandleOKCallback() {
    // prevent V8 objects from being garbage collected
    Nan::HandleScope scope;

    // Return scanned NFC data
    v8::Local<v8::Object> nfcData = Nan::New<v8::Object>();
    Nan::Set(nfcData, Nan::New("info").ToLocalChecked(), data_info_js());
    Nan::Set(nfcData, Nan::New("pages").ToLocalChecked(), data_pages_js());
    // TODO: page
    // TODO: ndef

    // Callback Parameters
    int argCount = 2;

    v8::Local<v8::Value> argv[] = {
      Nan::New(statusCode),
      nfcData
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


///////////////////////////
// BLUEPRINT
//////////////////////////
/*
read({info: bool, pages: bool, page: int, ndef: bool}, callback());
*/