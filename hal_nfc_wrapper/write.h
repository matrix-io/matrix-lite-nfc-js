#ifndef WRITE_H
#define WRITE_H

#include <nan.h>
#include "data/page.h"
// #include "data/ndef.h"

enum writeType { page, ndef };

// Determines which tag write & parameters for that write.
// Options given are determined by writeType tag.
struct writeOptions {
  writeType tag;
  pageWriteOptions page;
  // ndefWriteOptions ndef; // not implemented yet
};

NAN_METHOD(write);

#endif