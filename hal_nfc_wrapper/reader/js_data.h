#ifndef js_data_H
#define js_data_H

#include <nan.h>

// Functions to convert C++ data to JS 

v8::Local<v8::Object> info_data_js();

v8::Local<v8::Object> pages_data_js();
v8::Local<v8::Array>  page_data_js(std::vector<uint8_t> page);

v8::Local<v8::Object> ndef_data_js();

#endif