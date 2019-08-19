#ifndef PAGE_H
#define PAGE_H

#include <nan.h>

v8::Local<v8::Object> pages_data_js();
v8::Local<v8::Array>  page_data_js(std::vector<uint8_t> page);

int page_write_async(v8::Local<v8::Value> page_index, v8::Local<v8::Array> page_data);

#endif