#include <nan.h>
#include "../nfc.h"
#include "page.h"
#include <iostream>

// - Convert nfc.pages.info to JS variables
v8::Local<v8::Object> data_pages_js() {
  // Create & return JS object
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

// // - Read a page from an NFC tag.
// // Data returned will be an array of 4 bytes
// NAN_METHOD(readPage){
//   // Grab desired page number
//   if (!info[0]->IsNumber()) {Nan::ThrowTypeError("Argument must be a number"); return;}
//   int page_number = Nan::To<int>(info[0]).FromJust(); 
  
//   // Read page
//   std::vector<uint8_t> read_page = nfc.mful.ReadPage(page_number);

//   // Create JS array from page
//   v8::Local<v8::Array> page = Nan::New<v8::Array>();
  
//   for (int i = 0; i < read_page.size(); i++){
//     page->Set(i, Nan::New(read_page.at(i)));
//   }

//   // Return JS array
//   info.GetReturnValue().Set(page);
// }

// // - Overwrite an existing NFC page.
// // Byte array given must be < 5.
// NAN_METHOD(writePage){
//   // Grab desired page number
//   if (!info[0]->IsNumber()) {Nan::ThrowTypeError("First argument must be a number"); return;}
//   int page_number = Nan::To<int>(info[0]).FromJust(); 

//   // Grab data to write
//   if (!info[1]->IsArray()) {Nan::ThrowTypeError("Second argument must be an array of ints"); return;}
//   v8::Local<v8::Array> content = v8::Local<v8::Array>::Cast(info[1]);
//   if (content->Length() > 4){Nan::ThrowTypeError("Second argument cannot have an array bigger than 4"); return;}

//   // Create vector from JS array
//   std::vector<uint8_t> new_page;
//   for (int i = 0; i < content->Length(); i++){
//     new_page.push_back(Nan::To<int>(Nan::Get(content, i).ToLocalChecked()).FromJust());
//   }

//   // Overwrite NFC page
//   int statusCode = nfc.mful.WritePage(page_number, new_page);

//   //return code for JS nfc.status()
//   info.GetReturnValue().Set(statusCode);
// }