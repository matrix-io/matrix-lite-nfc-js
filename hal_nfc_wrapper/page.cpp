#include <nan.h>
#include "nfc.h"
#include "page.h"
#include <iostream>

NAN_METHOD(writePage){
  // Grab desired page number
  if (!info[0]->IsNumber()) {Nan::ThrowTypeError("First argument must be a number"); return;}
  int page_number = Nan::To<int>(info[0]).FromJust(); 

  // Grab data to write
  if (!info[1]->IsArray()) {Nan::ThrowTypeError("Second argument must be an array of ints"); return;}
  v8::Local<v8::Array> content = v8::Local<v8::Array>::Cast(info[1]);

  // Create vector from JS array
  std::vector<uint8_t> new_page;
  for (int i = 0; i < content->Length(); i++){
    new_page.push_back(Nan::To<int>(Nan::Get(content, i).ToLocalChecked()).FromJust());
  }

  // Overwrite NFC page
  int statusCode = nfc.mful.WritePage(page_number, new_page);

  //return code for JS nfc.status()
  info.GetReturnValue().Set(statusCode);
}

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

  Nan::Set(obj, Nan::New("write").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(writePage)).ToLocalChecked());

  // Return object
  info.GetReturnValue().Set(obj);
}