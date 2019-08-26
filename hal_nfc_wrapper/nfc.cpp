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

// Node addon entry point
NAN_MODULE_INIT(Initialize){
  // Exported JS functions
  NAN_EXPORT(target, status);
  NAN_EXPORT(target, read);
  NAN_EXPORT(target, write);

  ndef_parser::Init(target); //TODO change name to ndefParser
}

// Create a Node module called "addon"
NODE_MODULE(addon, Initialize);