#include <nan.h>
#include "nfc.h"
#include "info.h"
#include "page.h"
#include "ndef.h"

namespace hal = matrix_hal;

matrix_hal::NFC nfc;
matrix_hal::NFCData nfc_data;

// Basis for NFC usage: Activate() -> Some_NFC_Function -> Deactivate()
NAN_METHOD(activate)   {info.GetReturnValue().Set(nfc.Activate());}
NAN_METHOD(deactivate) {nfc.Deactivate();}

// Returns a string for the given status code.
// given by: .Activate & .WritePage
NAN_METHOD(status) {
  if (!info[0]->IsNumber()) {Nan::ThrowTypeError("Argument must be a number"); return;}

  int statusCode = Nan::To<int>(info[0]).FromJust();

  info.GetReturnValue().Set(Nan::New(hal::NFCStatus(statusCode)).ToLocalChecked());
}

// Node addon entry point
NAN_MODULE_INIT(Initialize){
  // Exported JS functions
  NAN_EXPORT(target, activate);
  NAN_EXPORT(target, deactivate);
  NAN_EXPORT(target, status);

  NAN_EXPORT(target, info);
  NAN_EXPORT(target, page);
  NAN_EXPORT(target, ndef);
}

// Create a Node module called "addon"
NODE_MODULE(addon, Initialize);