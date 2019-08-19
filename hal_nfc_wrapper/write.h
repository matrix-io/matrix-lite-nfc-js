#ifndef WRITE_H
#define WRITE_H

#include <nan.h>

enum writeType { page, ndef };

// Determines which tag write & parameters for that write.
// Options given are determined by writeType tag.
struct writeOptions {
  writeType tag;

  // page
  v8::Local<v8::Value> page_index;
  v8::Local<v8::Array> page_data;
  
  // ndef
};

NAN_METHOD(write);

#endif