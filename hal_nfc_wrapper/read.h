#ifndef READ_H
#define READ_H

#include <nan.h>

NAN_METHOD(read);

// Determines which read functions to use in read()
struct readOptions {
  bool info;
  bool pages;
  int page;
  bool ndef;
};

#endif