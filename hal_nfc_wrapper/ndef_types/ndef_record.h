#ifndef NDEF_RECORD_H
#define NDEF_RECORD_H

#include <nan.h>
#include "matrix_nfc/nfc.h"
#include "matrix_nfc/nfc_data.h"

class ndef_record : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);
  matrix_hal::NDEFRecord Value();
  static void NewFromParser(const Nan::FunctionCallbackInfo<v8::Value>& info, v8::Local<v8::Object> parser);

private:
  explicit ndef_record(matrix_hal::NDEFRecord ndef_record = matrix_hal::NDEFRecord());
  ~ndef_record();

  static NAN_METHOD(New);
  static NAN_METHOD(GetHandle);
  static NAN_METHOD(GetHandleConst);
  static NAN_METHOD(GetPayloadLength);
  static NAN_METHOD(GetId);
  static NAN_METHOD(GetIdLength);
  static NAN_METHOD(SetTnf);
  static NAN_METHOD(GetTnf);
  static NAN_METHOD(Info);
  static NAN_METHOD(ToString);
  
  static Nan::Persistent<v8::Function> constructor;
  matrix_hal::NDEFRecord ndef_record_;
};

struct record_info {

};

#endif