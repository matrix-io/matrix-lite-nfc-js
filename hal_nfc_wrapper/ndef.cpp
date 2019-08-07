#include <nan.h>
#include "nfc.h"
#include "ndef.h"

NAN_METHOD(NDEF_To_String) {
  info.GetReturnValue().Set(Nan::New(nfc_data.ndef.ToString()).ToLocalChecked());
}

NAN_METHOD(NDEF_To_Hex) {
  info.GetReturnValue().Set(Nan::New(nfc_data.ndef.ToHex()).ToLocalChecked());
}

NAN_METHOD(readNDEF) {
  // Create object
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  // Read NFC tag
  nfc.ndef.Read(&nfc_data.ndef);

  // Set Object Properties //
  Nan::Set(obj, Nan::New("valid").ToLocalChecked(), Nan::New(nfc_data.ndef.valid));
  Nan::Set(obj, Nan::New("updated").ToLocalChecked(), Nan::New(nfc_data.ndef.recently_updated));

  // Create content property
  v8::Local<v8::Array> content = Nan::New<v8::Array>();
  for (int i = 0; i < nfc_data.ndef.content.size(); i++){
    content->Set(i, Nan::New(nfc_data.ndef.content[i]));
  }
  Nan::Set(obj, Nan::New("content").ToLocalChecked(), content);

  // NDEF content -> ASCII string
  Nan::Set(content, Nan::New("toString").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(NDEF_To_String)).ToLocalChecked());

  // NDEF content -> Hex string
  Nan::Set(content, Nan::New("toHex").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(NDEF_To_Hex)).ToLocalChecked());

  // Return object
  info.GetReturnValue().Set(obj);
}

// ** EXPORTED NFC NDEF OBJECT ** //
NAN_METHOD(ndef) {
  // Create object
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  // Set Object Properties //
  Nan::Set(obj, Nan::New("read").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(readNDEF)).ToLocalChecked());

  // Return object
  info.GetReturnValue().Set(obj);
}