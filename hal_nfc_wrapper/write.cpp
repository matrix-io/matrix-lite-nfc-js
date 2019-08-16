#include "write.h"
#include <nan.h>
#include "nfc.h"
#include "data/page.h"
#include "data/ndef.h"

class AsyncWriter : public Nan::AsyncWorker {
public:
  AsyncWriter(Nan::Callback *callback)
    : Nan::AsyncWorker(callback) {}

  // Execute non-blocking code. **DO NOT MAKE V8 CALLS HERE!**
  void Execute() {

  }

  void HandleOKCallback() {

  }
};