#ifndef NDEF_PARSER_H
#define NDEF_PARSER_H

#include <nan.h>
#include "matrix_nfc/nfc.h"
#include "../nfc.h"

class ndef_parser : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);
  matrix_hal::NDEFParser Value();

private:
  explicit ndef_parser(matrix_hal::NDEFParser ndef_parser = matrix_hal::NDEFParser());
  ~ndef_parser();

  static NAN_METHOD(New);
  static NAN_METHOD(GetHandle);
  static NAN_METHOD(GetHandleConst);
  static NAN_METHOD(ToString);
  static NAN_METHOD(AddTextRecord);
  static NAN_METHOD(AddUriRecord);
  static NAN_METHOD(AddEmptyRecord);
  static NAN_METHOD(AddMimeMediaRecord);
  static NAN_METHOD(GetEncodedSize);
  static NAN_METHOD(GetRecordCount);
  static NAN_METHOD(GetRecord);
  
  static Nan::Persistent<v8::Function> constructor;
  matrix_hal::NDEFParser ndef_parser_;
};

#endif