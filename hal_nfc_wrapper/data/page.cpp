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
// Used for AsyncWriter.
int page_write_async(v8::Local<v8::Value> page_index, v8::Local<v8::Array> page_data){
  // Grab page index from JS var
  int index = Nan::To<int>(page_index).FromJust();
  
  // Create vector from JS array
  std::vector<uint8_t> new_page;
  for (int i = 0; i < page_data->Length(); i++){
    new_page.push_back(Nan::To<int>(Nan::Get(page_data, i).ToLocalChecked()).FromJust());
  }

  // Write to NFC page & return status code
  return nfc.mful.WritePage(index, new_page);
}