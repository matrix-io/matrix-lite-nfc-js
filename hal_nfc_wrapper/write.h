#ifndef WRITE_H
#define WRITE_H

#include <nan.h>

// TODO: fix compiling issue with the code below

class AsyncWriter : public Nan::AsyncWorker {
public:
  std::vector<uint8_t> nfc_page;

  AsyncWriter(Nan::Callback *callback):Nan::AsyncWorker(callback);// TODO: maybe remove

  // Execute non-blocking code. **DO NOT MAKE V8 CALLS HERE!**
  void Execute();

  void HandleOKCallback();
};

#endif
