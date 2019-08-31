#ifndef NDEF_RECORD_H
#define NDEF_RECORD_H

#include <nan.h>
#include "matrix_nfc/nfc.h"
#include "matrix_nfc/nfc_data.h"

class ndef_record : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);
  matrix_hal::NDEFRecord Self();
  static void NewInstance(const Nan::FunctionCallbackInfo<v8::Value>& info, matrix_hal::NDEFRecord *new_record);

private:
  explicit ndef_record(matrix_hal::NDEFRecord ndef_record = matrix_hal::NDEFRecord());
  ~ndef_record();

  static NAN_METHOD(New);
  static NAN_METHOD(GetHandle);
  static NAN_METHOD(GetHandleConst);
  static NAN_METHOD(GetPayloadLength);
  static NAN_METHOD(GetPayload);
  static NAN_METHOD(SetTnf);
  static NAN_METHOD(GetTnf);
  
  static Nan::Persistent<v8::Function> constructor;
  matrix_hal::NDEFRecord ndef_record_;
};

#endif