#include <nan.h>
#include "nfc.h"
#include "info.h"
#include<iostream>

class MyAsyncWorker : public Nan::AsyncWorker {
public:
  MyAsyncWorker(Nan::Callback *callback)
    : Nan::AsyncWorker(callback) {}

  // Run non-blocking code
  void Execute() {
    nfc.Activate();
    nfc.ReadInfo(&nfc_data.info);
    nfc.Deactivate();
  }

  void HandleOKCallback() {
    // prevent created v8 objects to be garbage collected
    Nan::HandleScope scope;

    // Update NFC object
    v8::Local<v8::Object> nfc_info_data = Nan::New<v8::Object>();
    Nan::Set(nfc_info_data, Nan::New("technology").ToLocalChecked(), Nan::New(nfc_data.info.technology).ToLocalChecked());
    Nan::Set(nfc_info_data, Nan::New("type").ToLocalChecked(), Nan::New(nfc_data.info.type).ToLocalChecked());
    Nan::Set(nfc_info_data, Nan::New("UID").ToLocalChecked(), Nan::New(nfc_data.info.UIDToHex()).ToLocalChecked());
    Nan::Set(nfc_info_data, Nan::New("ATQ").ToLocalChecked(), Nan::New(nfc_data.info.ATQToHex()).ToLocalChecked());
    Nan::Set(nfc_info_data, Nan::New("SAK").ToLocalChecked(), Nan::New(nfc_data.info.SAKToHex()).ToLocalChecked());
    Nan::Set(nfc_info_data, Nan::New("card_family").ToLocalChecked(), Nan::New(nfc_data.info.card_family).ToLocalChecked());
    Nan::Set(nfc_info_data, Nan::New("IC_type").ToLocalChecked(), Nan::New(nfc_data.info.IC_type).ToLocalChecked());
    Nan::Set(nfc_info_data, Nan::New("bit_rate").ToLocalChecked(), Nan::New(nfc_data.info.bit_rate));
    Nan::Set(nfc_info_data, Nan::New("storage_size").ToLocalChecked(), Nan::New(nfc_data.info.storage_size));
    Nan::Set(nfc_info_data, Nan::New("updated").ToLocalChecked(), Nan::New(nfc_data.info.recently_updated));

    // Set parameters for callback
    v8::Local<v8::Value> argv[] = {
      Nan::Null(),// no error
      nfc_info_data
    };

    // Start callback
    Nan::Call(callback->GetFunction(), Nan::GetCurrentContext()->Global(), 2, argv);
  }
};

NAN_METHOD(readInfoAsync) {
  // Nan::AsyncQueueWorker(new MyAsyncWorker(
  //   new Nan::Callback(info[3].As<v8::Function>())
  // ));

  Nan::Callback *callback = new Nan::Callback(Nan::To<v8::Function>(info[0]).ToLocalChecked());

  Nan::AsyncQueueWorker(new MyAsyncWorker(callback));
}

// - Populate nfc.data.info
NAN_METHOD(readInfo) {
  // Read NFC tag
  nfc.ReadInfo(&nfc_data.info);

  // Create & populate NFC info object
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  Nan::Set(obj, Nan::New("technology").ToLocalChecked(), Nan::New(nfc_data.info.technology).ToLocalChecked());
  Nan::Set(obj, Nan::New("type").ToLocalChecked(), Nan::New(nfc_data.info.type).ToLocalChecked());
  Nan::Set(obj, Nan::New("UID").ToLocalChecked(), Nan::New(nfc_data.info.UIDToHex()).ToLocalChecked());
  Nan::Set(obj, Nan::New("ATQ").ToLocalChecked(), Nan::New(nfc_data.info.ATQToHex()).ToLocalChecked());
  Nan::Set(obj, Nan::New("SAK").ToLocalChecked(), Nan::New(nfc_data.info.SAKToHex()).ToLocalChecked());
  Nan::Set(obj, Nan::New("card_family").ToLocalChecked(), Nan::New(nfc_data.info.card_family).ToLocalChecked());
  Nan::Set(obj, Nan::New("IC_type").ToLocalChecked(), Nan::New(nfc_data.info.IC_type).ToLocalChecked());
  Nan::Set(obj, Nan::New("bit_rate").ToLocalChecked(), Nan::New(nfc_data.info.bit_rate));
  Nan::Set(obj, Nan::New("storage_size").ToLocalChecked(), Nan::New(nfc_data.info.storage_size));
  Nan::Set(obj, Nan::New("updated").ToLocalChecked(), Nan::New(nfc_data.info.recently_updated));

  // Return NFC info
  info.GetReturnValue().Set(obj);
}

// ** EXPORTED NFC INFO OBJECT ** //
NAN_METHOD(info) {
  // Create object
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  // Set Object Properties //
  Nan::Set(obj, Nan::New("read").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(readInfo)).ToLocalChecked());

  // TODO remove later
  Nan::Set(obj, Nan::New("readAsync").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(readInfoAsync)).ToLocalChecked());

  // Return object
  info.GetReturnValue().Set(obj);
}