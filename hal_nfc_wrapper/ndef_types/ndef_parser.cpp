#include <nan.h>
#include <iostream>
#include "matrix_nfc/nfc.h"
#include "matrix_nfc/nfc_data.h"
#include "../nfc.h"
#include "ndef_parser.h"
#include "ndef_record.h"

Nan::Persistent<v8::Function> ndef_parser::constructor;
ndef_parser::ndef_parser(matrix_hal::NDEFParser ndef_parser) : ndef_parser_(ndef_parser) {}
ndef_parser::~ndef_parser() {}

// ** EXPORTED NDEF OBJECT ** //
NAN_MODULE_INIT(ndef_parser::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("ndefParser").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  SetPrototypeMethod(tpl, "getHandle", GetHandle);
  SetPrototypeMethod(tpl, "getHandleConst", GetHandleConst);

  // NDEF parser methods
  SetPrototypeMethod(tpl, "toString", ToString);
  SetPrototypeMethod(tpl, "addTextRecord", AddTextRecord);
  SetPrototypeMethod(tpl, "addUriRecord", AddUriRecord);
  SetPrototypeMethod(tpl, "addEmptyRecord", AddEmptyRecord);
  SetPrototypeMethod(tpl, "addMimeMediaRecord", AddMimeMediaRecord);
  SetPrototypeMethod(tpl, "getEncodedSize", GetEncodedSize);
  SetPrototypeMethod(tpl, "getRecordCount", GetRecordCount);
  SetPrototypeMethod(tpl, "records", Records);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());

  Nan::Set(target, Nan::New("ndefParser").ToLocalChecked(),
    Nan::GetFunction(tpl).ToLocalChecked());
}

// - NDEF JS initialization
NAN_METHOD(ndef_parser::New) {
  if (info.IsConstructCall()) {
    
    // Initialize NDEFParser from NDEF content
    if (info[0]->IsArray()) {

      // Create NDEF content
      matrix_hal::NDEFContent ndef_content;
      ndef_content.valid = true; // assume it's valid

      // Set NDEF content.content from JS array
      v8::Local<v8::Array> new_content = v8::Local<v8::Array>::Cast(info[0]);
      for (int i = 0; i < new_content->Length(); i++) {
        int new_num = Nan::To<int>(Nan::Get(new_content, i).ToLocalChecked()).FromJust();
        ndef_content.content.push_back(new_num);
      }

      // Initialize populated NDEF parser
      ndef_parser *obj = new ndef_parser(matrix_hal::NDEFParser(&ndef_content));
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());

      return;
    }
    // Or initialize empty NDEFParser
    else {
      ndef_parser *obj = new ndef_parser(matrix_hal::NDEFParser());
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    }
    
  }

  // Enforce users to use `new ndefParser()`
  else {
    Nan::ThrowTypeError("ndefParser must be initialized! -> var thing = new ndefParser();");
  }
}

NAN_METHOD(ndef_parser::GetHandle) {
  ndef_parser* obj = ObjectWrap::Unwrap<ndef_parser>(info.Holder());
  info.GetReturnValue().Set(obj->handle());
}

NAN_METHOD(ndef_parser::GetHandleConst) {
  ndef_parser const *obj = ObjectWrap::Unwrap<ndef_parser>(info.Holder());
  info.GetReturnValue().Set(obj->handle());
}

// - Retrieve NDEFParser from a JS ndefParser. 
matrix_hal::NDEFParser ndef_parser::Value() {
  return ndef_parser_;
}

/////////////////////////////
// NDEF PARSER JS METHODS //

NAN_METHOD(ndef_parser::ToString) {
  ndef_parser* obj = ObjectWrap::Unwrap<ndef_parser>(info.Holder());
  
  v8::Local<v8::String> data = Nan::New(obj->ndef_parser_.ToString()).ToLocalChecked();
  
  info.GetReturnValue().Set(data);
}

NAN_METHOD(ndef_parser::AddTextRecord) {
  if (!info[0]->IsString()) {Nan::ThrowTypeError("Argument must be a string"); return;}
  
  ndef_parser* obj = ObjectWrap::Unwrap<ndef_parser>(info.Holder());

  // Try to set language
  if (info.Length() == 2 && info[1]->IsString()) {
    obj->ndef_parser_.AddTextRecord(*Nan::Utf8String(info[0]), *Nan::Utf8String(info[1]));
  }
  // No langauge specified
  else{
    obj->ndef_parser_.AddTextRecord(*Nan::Utf8String(info[0]));
  }
}

NAN_METHOD(ndef_parser::AddUriRecord) {
  if (!info[0]->IsString()) {Nan::ThrowTypeError("Argument must be a string"); return;}
  
  ndef_parser* obj = ObjectWrap::Unwrap<ndef_parser>(info.Holder());
  obj->ndef_parser_.AddUriRecord( *Nan::Utf8String(info[0]) );
}

NAN_METHOD(ndef_parser::AddEmptyRecord) {
  ndef_parser* obj = ObjectWrap::Unwrap<ndef_parser>(info.Holder());
  obj->ndef_parser_.AddEmptyRecord();
}

NAN_METHOD(ndef_parser::AddMimeMediaRecord) {
  // Grab User args
  if (!info[0]->IsString()) {Nan::ThrowTypeError("Argument 1 must be a string"); return;}
  std::string mimeType = *Nan::Utf8String(info[0]);

  if (!info[1]->IsString()) {Nan::ThrowTypeError("Argument 2 must be a string"); return;}
  std::string payload = *Nan::Utf8String(info[1]);

  ndef_parser* obj = ObjectWrap::Unwrap<ndef_parser>(info.Holder());
  obj->ndef_parser_.AddMimeMediaRecord(mimeType, payload);
}

NAN_METHOD(ndef_parser::GetEncodedSize) {
  ndef_parser* obj = ObjectWrap::Unwrap<ndef_parser>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->ndef_parser_.GetEncodedSize()));
}

NAN_METHOD(ndef_parser::GetRecordCount) {
  ndef_parser* obj = ObjectWrap::Unwrap<ndef_parser>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->ndef_parser_.GetRecordCount()));
}










// TODO finish
// - Returns an array containing data from each NDEF Record
NAN_METHOD(ndef_parser::Records) {
  ndef_parser* obj = ObjectWrap::Unwrap<ndef_parser>(info.Holder());
  matrix_hal::NDEFParser parser = obj->ndef_parser_;

  v8::Local<v8::Array> result = Nan::New<v8::Array>();

  // Create JS object for each record
  for (int i = 0; i < parser.GetRecordCount(); i++){
    matrix_hal::NDEFRecord record= parser.GetRecord(i);
    v8::Local<v8::Object> record_js = Nan::New<v8::Object>();

    // Set each record property
    record_js->Set(Nan::New("all").ToLocalChecked(), Nan::New(record.ToString()).ToLocalChecked());

    // Append record to JS array
    result->Set(i, record_js);
  }

  // Return JS array of NDEF record data
  info.GetReturnValue().Set(result);
}