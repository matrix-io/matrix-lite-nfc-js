#include <nan.h>
#include "nfc.h"
#include "page.h"

NAN_METHOD(readPage){
  // Grab desired page number
  if (!info[0]->IsNumber()) {Nan::ThrowTypeError("Argument must be a number"); return;}
  int page_number = Nan::To<int>(info[0]).FromJust(); 
  
  // Read page
  std::vector<uint8_t> read_page = nfc.mful.ReadPage(page_number);

  // Create JS array from page
  v8::Local<v8::Array> page = Nan::New<v8::Array>();
  
  for (int i = 0; i < read_page.size(); i++){
    page->Set(i, Nan::New(read_page.at(i)));
  }

  // Return JS array
  info.GetReturnValue().Set(page);
}

// ** EXPORTED NFC INFO OBJECT ** //
NAN_METHOD(page) {
  // Create object
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  // Set Object Properties //
  Nan::Set(obj, Nan::New("read").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(readPage)).ToLocalChecked());

  // Return object
  info.GetReturnValue().Set(obj);
}