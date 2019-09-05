#ifndef WRITE_H
#define WRITE_H

#include <nan.h>
#include "matrix_nfc/nfc.h"

enum class writeType  { page, ndef, erase };

struct pageWriteOptions {
  int index;
  std::vector<uint8_t> data;
};

struct ndefWriteOptions {
  matrix_hal::NDEFParser parser;
};

// Determines which tag write & parameters for that write.
// Options given are determined by writeType tag.
struct writeOptions {
  writeType tag;
  pageWriteOptions page;
  ndefWriteOptions ndef;
};

NAN_METHOD(write);

#endif