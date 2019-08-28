#ifndef NDEF_RECORD_H
#define NDEF_RECORD_H

#include <nan.h>
#include "matrix_nfc/nfc.h"
#include "matrix_nfc/nfc_data.h"

class ndef_record : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);

private:
  explicit ndef_record(double value = 0);
  ~ndef_record();

  static NAN_METHOD(New);
  static NAN_METHOD(GetHandle);
  static NAN_METHOD(GetHandleConst);
  static NAN_METHOD(GetValue);
  static NAN_METHOD(Add);
  

  static Nan::Persistent<v8::Function> constructor;
  double value_;
};

#endif