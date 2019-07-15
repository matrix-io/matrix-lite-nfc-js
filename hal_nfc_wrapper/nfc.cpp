#include <nan.h>
#include "nfc.h"

// Shared NFC objects
matrix_hal::NFCSensor nfc_sensor;
matrix_hal::NFCInfo nfc_info;

NAN_METHOD(recently_updated) {
  // nfc_info.recently_updated
}

// Node addon entry point
NAN_MODULE_INIT(Initialize){
  NAN_EXPORT(target, recently_updated);
  
  // Export functions that return JS objects
  // NAN_EXPORT(target, read);
}

// Create a Node module called "addon"
NODE_MODULE(addon, Initialize);