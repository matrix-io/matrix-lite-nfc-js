#include <nan.h>
#include "../nfc.h"
#include "js_data.h"

// Parse NDEF content array
NAN_METHOD(ndef_to_string) {info.GetReturnValue().Set(Nan::New(nfc_data.ndef.ToString()).ToLocalChecked());}
NAN_METHOD(ndef_to_hex) {info.GetReturnValue().Set(Nan::New(nfc_data.ndef.ToHex()).ToLocalChecked());}

// - Convert nfc.data.ndef to a JS object
v8::Local<v8::Object> ndef_data_js() {
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  
  Nan::Set(obj, Nan::New("valid").ToLocalChecked(), Nan::New(nfc_data.ndef.valid));
  Nan::Set(obj, Nan::New("updated").ToLocalChecked(), Nan::New(nfc_data.ndef.recently_updated));

  // Create NDEF content property
  v8::Local<v8::Array> content = Nan::New<v8::Array>();
  for (int i = 0; i < nfc_data.ndef.content.size(); i++){
    content->Set(i, Nan::New(nfc_data.ndef.content[i]));
  }
  Nan::Set(obj, Nan::New("content").ToLocalChecked(), content);

  // Content Methods //
  // NDEF content -> ASCII string
  Nan::Set(content, Nan::New("toString").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(ndef_to_string)).ToLocalChecked());
  // NDEF content -> Hex string
  Nan::Set(content, Nan::New("toHex").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(ndef_to_hex)).ToLocalChecked());

  return obj;
}