#include <nan.h>
#include "../nfc.h"
#include "info.h"

// - Convert nfc.data.info to a JS object
v8::Local<v8::Object> info_data_js() {
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

  return obj;
}

int infoTest() {
  return 4949;
}