#include <nan.h>
#include "../nfc.h"
#include "ndef_parser.h"

#include <iostream>// TODO remove

NAN_METHOD(ndef_parser_to_string) {
  //TODO
}

// ** EXPORTED NDEF PARSE OBJECT ** //
NAN_METHOD(ndef_parser) {
  matrix_hal::NDEFParser ndef_parser = matrix_hal::NDEFParser(&nfc_data.ndef);

  // Create object
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  
  std::cout << ndef_parser.ToString() << std::endl;

  // Set Object Properties //
  Nan::Set(obj, Nan::New("toString").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(ndef_parser_to_string)).ToLocalChecked());

  info.GetReturnValue().Set(obj);
}