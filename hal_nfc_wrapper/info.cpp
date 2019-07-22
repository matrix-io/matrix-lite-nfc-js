#include <nan.h>
#include "nfc.h"
#include "info.h"

// - Populate nfc.data.info
NAN_METHOD(read){
  nfc.ReadInfo(&nfc_data.info);
}

// - TODO change to variable
NAN_METHOD(recentlyUpdated){
  info.GetReturnValue().Set(nfc_data.info.recently_updated);
}

// - TODO
NAN_METHOD(toString){
  auto message = Nan::New(nfc_data.info.ToString()).ToLocalChecked();
  info.GetReturnValue().Set(message);
}

///////////////////////////////////////
// ** EXPORTED DEVICE INFO OBJECT ** //
NAN_METHOD(info) {
  // Create object
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  // Set Object Properties //
  Nan::Set(obj, Nan::New("read").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(read)).ToLocalChecked());

  Nan::Set(obj, Nan::New("recentlyUpdated").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(recentlyUpdated)).ToLocalChecked());

  Nan::Set(obj, Nan::New("toString").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(toString)).ToLocalChecked());

  // Return object
  info.GetReturnValue().Set(obj);
}