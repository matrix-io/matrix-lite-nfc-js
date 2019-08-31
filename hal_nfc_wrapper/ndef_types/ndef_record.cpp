#include <nan.h>
#include "../nfc.h"
#include "ndef_record.h"
#include "ndef_parser.h"

#include <iostream>// TODO remove

// NDEF RECORD OBJECT //
Nan::Persistent<v8::Function> ndef_record::constructor;
ndef_record::ndef_record(matrix_hal::NDEFRecord ndef_record) : ndef_record_(ndef_record) {}
ndef_record::~ndef_record() {}

// ** EXPORTED NDEF OBJECT ** //
NAN_MODULE_INIT(ndef_record::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("ndefRecord").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  SetPrototypeMethod(tpl, "getHandle", GetHandle);
  SetPrototypeMethod(tpl, "getHandleConst", GetHandleConst);
  SetPrototypeMethod(tpl, "getPayloadLength", GetPayloadLength);
  SetPrototypeMethod(tpl, "getPayload", GetPayload);
  SetPrototypeMethod(tpl, "getTnf", GetTnf);
  SetPrototypeMethod(tpl, "setTnf", SetTnf);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());

  Nan::Set(target, Nan::New("ndefRecord").ToLocalChecked(),
    Nan::GetFunction(tpl).ToLocalChecked());
}

// - TODO RENAME this function to somethgin easier to understand
void ndef_record::NewInstance(const Nan::FunctionCallbackInfo<v8::Value>& info, v8::Local<v8::Object> parser) {
  // Grab NDEFParser
  ndef_parser* parser_unwrapped = ObjectWrap::Unwrap<ndef_parser>(parser);
  
  // Pass parameters to the ndef_record constructor
  const int argc = 2;
  v8::Local<v8::Value> argv[argc] = {parser, info[0]};// Note that the parameters passed are JS values.
  info.GetReturnValue().Set(Nan::NewInstance(Nan::New(constructor), argc, argv).ToLocalChecked());
}

// - NDEF Record JS initialization
NAN_METHOD(ndef_record::New) {
  if (info.IsConstructCall()) {

    // Check if record is taken from existing NDEFParser
    if (info[0]->IsObject()) {
      // Unwrap NDEF Parser.
      // We're going to assume any object passed is an NDEFParser
      Nan::MaybeLocal<v8::Object> maybe = Nan::To<v8::Object>(info[0]);
      ndef_parser* parser = ObjectWrap::Unwrap<ndef_parser>(maybe.ToLocalChecked());

      // Create record from NDEFParser index
      ndef_record *obj = new ndef_record(parser->Value().GetRecord(Nan::To<int>(info[1]).FromJust()));
      obj->Wrap(info.This());
      
      info.GetReturnValue().Set(info.This());
    }

    // Else make a new NDEFRecord
    else{
      ndef_record *obj = new ndef_record(matrix_hal::NDEFRecord());
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    }

  }

  // Enforce users to use `new ndefRecord()`
  else {
    Nan::ThrowTypeError("ndefRecord must be initialized! -> var thing = new ndefRecord();");
  }
}

NAN_METHOD(ndef_record::GetHandle) {
  ndef_record* obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
  info.GetReturnValue().Set(obj->handle());
}

NAN_METHOD(ndef_record::GetHandleConst) {
  ndef_record const *obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
  info.GetReturnValue().Set(obj->handle());
}

// - Retrieve NDEFRecord from a JS ndefRecord. 
matrix_hal::NDEFRecord ndef_record::Value() {
  return ndef_record_;
}

/////////////////////////////
// NDEF RECORD JS METHODS //

NAN_METHOD(ndef_record::GetPayloadLength) {
  ndef_record* obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
  info.GetReturnValue().Set(obj->ndef_record_.GetPayloadLength());
}

// TODO finish
NAN_METHOD(ndef_record::GetPayload) {
  // uint8_t* payload = new uint8_t[payload_size];

  // ndef_record* obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
  // info.GetReturnValue().Set(obj->ndef_record_.GetPayloadLength());
}

NAN_METHOD(ndef_record::GetTnf) {
  ndef_record* obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
  info.GetReturnValue().Set(obj->ndef_record_.GetTnf());
}

NAN_METHOD(ndef_record::SetTnf) {
  if (!info[0]->IsNumber()) {Nan::ThrowTypeError("Argument must be a number"); return;}
  int number = Nan::To<int>(info[0]).FromJust();

  ndef_record* obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
  obj->ndef_record_.SetTnf(number);
}