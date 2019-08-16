#include <nan.h>
#include "../nfc.h"
#include "page.h"

// - Convert an NFC page into a JS array of ints. 
// The array represents a byte.
v8::Local<v8::Array> page_data_js(std::vector<uint8_t> page) {  
  v8::Local<v8::Array> page_js = Nan::New<v8::Array>();
  
  for (int i = 0; i < page.size(); i++){
    page_js->Set(i, Nan::New(page.at(i)));
  }

  return page_js;
}

// - Convert nfc.pages.info to a JS object
v8::Local<v8::Object> pages_data_js() {
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  Nan::Set(obj, Nan::New("read_complete").ToLocalChecked(), Nan::New(nfc_data.pages.read_complete));
  Nan::Set(obj, Nan::New("updated").ToLocalChecked(), Nan::New(nfc_data.pages.recently_updated));

  // Create JS array for pages
  v8::Local<v8::Array> pages_js = Nan::New<v8::Array>();

  // Populate pages with page[ints]
  for (int i = 0; i < nfc_data.pages.content.size(); i++){
    v8::Local<v8::Array> page_js = Nan::New<v8::Array>();

    for (int j = 0; j < nfc_data.pages.content[i].size(); j++){
      page_js->Set(j, Nan::New(nfc_data.pages.content[i][j]));
    }

    pages_js->Set(i, page_js);
  }

  Nan::Set(obj, Nan::New("content").ToLocalChecked(), pages_js);

  return obj;
}

// - Overwrite an existing NFC page.
// Byte array given must be < 5.
NAN_METHOD(page_write){
  // Grab desired page number
  if (!info[0]->IsNumber()) {Nan::ThrowTypeError("First argument must be a number"); return;}
  int page_number = Nan::To<int>(info[0]).FromJust(); 

  // Grab data to write
  if (!info[1]->IsArray()) {Nan::ThrowTypeError("Second argument must be an array of ints"); return;}
  v8::Local<v8::Array> content = v8::Local<v8::Array>::Cast(info[1]);
  if (content->Length() > 4){Nan::ThrowTypeError("Second argument cannot have an array bigger than 4"); return;}

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

// ** EXPORTED NFC Page OBJECT ** //
NAN_METHOD(page) {
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  // Set Object Properties //
  Nan::Set(obj, Nan::New("write").ToLocalChecked(),
  Nan::GetFunction(Nan::New<v8::FunctionTemplate>(page_write)).ToLocalChecked());

  info.GetReturnValue().Set(obj);
}