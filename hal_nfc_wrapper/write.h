#ifndef WRITE_H
#define WRITE_H

#include <nan.h>

enum writeType { page, ndef, erase };

struct pageWriteOptions {
  int index;
  std::vector<uint8_t> data;
};

// Determines which tag write & parameters for that write.
// Options given are determined by writeType tag.
struct writeOptions {
  writeType tag;
  pageWriteOptions page;
  // ndefWriteOptions ndef; // not implemented yet
};

NAN_METHOD(write);

#endif