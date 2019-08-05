#include <nan.h>
#include "nfc.h"
#include "info.h"
#include <string>//TODO remvoe

// - Populate nfc.data.info
NAN_METHOD(read){
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

  // Unused Example for returning UID array
  // v8::Local<v8::Array> UID = Nan::New<v8::Array>(nfc_data.info.UID.size());
  // for (int i = 0; i < nfc_data.info.UID.size(); i++){
  //   UID->Set(i, Nan::New(nfc_data.info.UID.at(i)));
  // }
  // Nan::Set(obj, Nan::New("UID").ToLocalChecked(), UID);
}

// ** EXPORTED NFC INFO OBJECT ** //
NAN_METHOD(info) {
  // Create object
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  // Set Object Properties //
  Nan::Set(obj, Nan::New("read").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(read)).ToLocalChecked());

  // Return object
  info.GetReturnValue().Set(obj);
}