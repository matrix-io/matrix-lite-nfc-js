#include <nan.h>
#include "nfc.h"
#include "page.h"

// NAN_METHOD(read){
//   if (!info[0]->IsNumber()) {Nan::ThrowTypeError("Argument must be a number"); return;}

//   int pageNum = Nan::To<int>(info[0]).FromJust();

//   v8::Local<v8::Array> page = Nan::New<v8::Array>();

  // for (int i = 0; i < nfc_data.info.UID.size(); i++){
  //   UID->Set(i, Nan::New(nfc_data.info.UID.at(i)));
  // }

  // Return NFC info
  // info.GetReturnValue().Set(page);
// }

void Foo::Bar(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  info.GetReturnValue().Set(Nan::New(12121212));
}

// ** EXPORTED NFC INFO OBJECT ** //
NAN_METHOD(page) {
  // Create object
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  // Set Object Properties //
  // Nan::Set(obj, Nan::New("read").ToLocalChecked(),
  // Nan::GetFunction(Nan::New<v8::FunctionTemplate>(read)).ToLocalChecked());

  // Return object
  info.GetReturnValue().Set(obj);
}