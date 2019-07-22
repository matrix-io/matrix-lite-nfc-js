#include <nan.h>
#include "nfc.h"
#include "info.h"

matrix_hal::NFC nfc;
matrix_hal::NFCData nfc_data;

// Basis for NFC usage: Activate() -> Some_NFC_Function -> Deactivate()
NAN_METHOD(activate)   {nfc.Activate();}
NAN_METHOD(deactivate) {nfc.Deactivate();}

// Node addon entry point
NAN_MODULE_INIT(Initialize){
  // Exported JS functions
  NAN_EXPORT(target, activate);
  NAN_EXPORT(target, deactivate);

  NAN_EXPORT(target, info);
}

// Create a Node module called "addon"
NODE_MODULE(addon, Initialize);