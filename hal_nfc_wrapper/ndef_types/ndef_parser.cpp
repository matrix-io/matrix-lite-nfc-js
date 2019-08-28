#include <nan.h>
#include <iostream>
#include "matrix_nfc/nfc.h"
#include "matrix_nfc/nfc_data.h"
#include "../nfc.h"
#include "ndef_parser.h"

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

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());

  Nan::Set(target, Nan::New("ndefParser").ToLocalChecked(),
    Nan::GetFunction(tpl).ToLocalChecked());
}

/* Used if ndefParser is needed as a function return 
// NAN_METHOD(ndef_parser::NewInstance) {
//   v8::Local<v8::Function> cons = Nan::New(constructor);
  
//   ndef_parser *obj = new ndef_parser(matrix_hal::NDEFParser(&nfc_data.ndef));
//   const int argc = 1;
//   v8::Local<v8::Value> argv[1] = {Nan::New(obj)};
  
//   info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
// }

C++ example
  #include "../ndef_types/ndef_parser.h"
  Nan::Set(obj, Nan::New<v8::String>("parser").ToLocalChecked(),Nan::GetFunction(Nan::New<v8::FunctionTemplate>(ndef_parser::NewInstance)).ToLocalChecked());
*/

// - NDEF initialization logic
NAN_METHOD(ndef_parser::New) {
  if (info.IsConstructCall()) {
    
    // Initialize NDEF parser from NDEF content
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
    // Initialize empty NDEF parser
    else {
      ndef_parser *obj = new ndef_parser(matrix_hal::NDEFParser());
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    }
  }

  else {
    // Enforce users to use new ndefParser()
    Nan::ThrowTypeError("ndefParser must be initialized! -> var thing = new ndefParser()");
    // const int argc = 1;
    // v8::Local<v8::Value> argv[argc] = {info[0]};
    // v8::Local<v8::Function> cons = Nan::New(constructor);
    // info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
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
matrix_hal::NDEFParser ndef_parser::self() {
  return ndef_parser_;
}

//////////////////////////
// NDEF PARSER METHODS //

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
    obj->ndef_parser_.AddTextRecord( *Nan::Utf8String(info[0]), *Nan::Utf8String(info[1]) );
  }
  // No langauge specified
  else{
    obj->ndef_parser_.AddTextRecord( *Nan::Utf8String(info[0]) );
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