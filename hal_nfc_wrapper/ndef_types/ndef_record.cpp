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
  SetPrototypeMethod(tpl, "getId", GetId);
  SetPrototypeMethod(tpl, "getIdLength", GetIdLength);
  SetPrototypeMethod(tpl, "getTnf", GetTnf);
  SetPrototypeMethod(tpl, "setTnf", SetTnf);
  SetPrototypeMethod(tpl, "toString", ToString);
  SetPrototypeMethod(tpl, "info", Info);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());

  Nan::Set(target, Nan::New("ndefRecord").ToLocalChecked(),
    Nan::GetFunction(tpl).ToLocalChecked());
}

// - Creates an NDEFRecord from an NDEFParser
void ndef_record::NewFromParser(const Nan::FunctionCallbackInfo<v8::Value>& info, v8::Local<v8::Object> parser) {
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

//////////////////////////////////////////////////////
// NDEF RECORD JS METHODS
//////////////////////////////////////////////////////

NAN_METHOD(ndef_record::GetPayloadLength) {
  ndef_record* obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
  info.GetReturnValue().Set(obj->ndef_record_.GetPayloadLength());
}

NAN_METHOD(ndef_record::GetId) {
  ndef_record* obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->ndef_record_.GetId()).ToLocalChecked());
}

NAN_METHOD(ndef_record::GetIdLength) {
  ndef_record* obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
  info.GetReturnValue().Set(obj->ndef_record_.GetIdLength());
}

NAN_METHOD(ndef_record::GetTnf) {
  ndef_record* obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
  std::string result;

  switch (obj->ndef_record_.GetTnf()) {
    case TNF_EMPTY:
        result = "Empty";
        break;
    case TNF_WELL_KNOWN:
        result = "Well Known";
        break;
    case TNF_MIME_MEDIA:
        result = "Mime Media";
        break;
    case TNF_ABSOLUTE_URI:
        result = "Absolute URI";
        break;
    case TNF_EXTERNAL_TYPE:
        result = "External";
        break;
    case TNF_UNKNOWN:
        result = "Unknown";
        break;
    case TNF_UNCHANGED:
        result = "Unchanged";
        break;
    case TNF_RESERVED:
        result = "Reserved";
        break;
    default:
        result = "Unknown TNF";
  }
  
  info.GetReturnValue().Set(Nan::New(result).ToLocalChecked());
}

NAN_METHOD(ndef_record::SetTnf) {
  if (!info[0]->IsNumber()) {Nan::ThrowTypeError("Argument must be a number"); return;}
  int number = Nan::To<int>(info[0]).FromJust();

  ndef_record* obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
  obj->ndef_record_.SetTnf(number);
}

NAN_METHOD(ndef_record::ToString) {
  ndef_record* obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->ndef_record_.ToString()).ToLocalChecked());
}

// - Returns object to access data given by NDEFRecord ToString
NAN_METHOD(ndef_record::Info) {
  // TODO ....
}




//////////////////////////////////////////////////////
// NDEF Records Paring Functions
//////////////////////////////////////////////////////

std::string BytesToString(const uint8_t *vec, const uint8_t size) {
    std::stringstream result;
    for (int i = 0; i < size; i++) {
        if ((vec[i] < 0x20) || (vec[i] > 0x7e))
            result << '.';
        else
            result << vec[i];
    }
    result << std::flush;
    return result.str();
}
