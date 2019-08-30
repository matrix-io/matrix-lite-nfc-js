#ifndef NDEF_RECORD_H
#define NDEF_RECORD_H

#include <nan.h>
#include "matrix_nfc/nfc.h"
#include "matrix_nfc/nfc_data.h"

class ndef_record : public Nan::ObjectWrap {
public:
  ndef_record(matrix_hal::NDEFRecord ndef_record = matrix_hal::NDEFRecord());
  ~ndef_record();

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(NewInstance);
  matrix_hal::NDEFRecord self();

  static Nan::Persistent<v8::Function> constructor;

private:
  static NAN_METHOD(New);
  static NAN_METHOD(GetHandle);
  static NAN_METHOD(GetHandleConst);
  static NAN_METHOD(GetPayloadLength);
  static NAN_METHOD(GetPayload);
  static NAN_METHOD(SetTnf);
  static NAN_METHOD(GetTnf);
  
  matrix_hal::NDEFRecord ndef_record_;
};

#endif