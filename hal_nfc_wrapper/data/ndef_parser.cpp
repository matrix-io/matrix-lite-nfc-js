#include <nan.h>
#include "../nfc.h"
#include "ndef_parser.h"

NAN_METHOD(ndef_parser_to_string) {
  //TODO
}

// ** EXPORTED NDEF PARSE OBJECT ** //
NAN_METHOD(ndef_parser) {


  // Create object
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  // Set Object Properties //
  Nan::Set(obj, Nan::New("toString").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(ndef_parser_to_string)).ToLocalChecked());

  info.GetReturnValue().Set(obj);
}