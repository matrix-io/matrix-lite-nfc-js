#include <nan.h>
#include "nfc.h"
#include "reader/read.h"
#include "writer/write.h"
#include "ndef_types/ndef_parser.h"

namespace hal = matrix_hal;

matrix_hal::NFC nfc;
matrix_hal::NFCData nfc_data;
std::mutex nfc_usage;

// Returns a string for the given status code.
// given by: activate, read, & write functions
NAN_METHOD(status) {
  if (!info[0]->IsNumber()) {Nan::ThrowTypeError("Argument must be a number"); return;}

  int statusCode = Nan::To<int>(info[0]).FromJust();
  info.GetReturnValue().Set(Nan::New(hal::NFCStatus(statusCode)).ToLocalChecked());
}

// TODO REMOVE
static NAN_METHOD(Sum) {
  // Nan::MaybeLocal<v8::Object> maybe1 = Nan::To<v8::Object>(info[0]);
  // Nan::MaybeLocal<v8::Object> maybe2 = Nan::To<v8::Object>(info[1]);

  // // Quick check:
  // if (maybe1.IsEmpty() || maybe2.IsEmpty()) {
  //   // return value is undefined by default
  //   return;
  // }

  // ndef_parser* obj1 =
  //   Nan::ObjectWrap::Unwrap<ndef_parser>(maybe1.ToLocalChecked());
  // ndef_parser* obj2 =
  //   Nan::ObjectWrap::Unwrap<ndef_parser>(maybe2.ToLocalChecked());

  // info.GetReturnValue().Set(Nan::New(obj1->value() + obj2->value()));
}

// Node addon entry point
NAN_MODULE_INIT(Initialize){
  // Exported JS functions
  NAN_EXPORT(target, status);
  NAN_EXPORT(target, read);
  NAN_EXPORT(target, write);

  NAN_EXPORT(target, Sum);//TODO remove
  ndef_parser::Init(target);
}

// Create a Node module called "addon"
NODE_MODULE(addon, Initialize);