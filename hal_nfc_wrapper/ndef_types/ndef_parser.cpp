#include <nan.h>
#include "../nfc.h"
#include "ndef_parser.h"

#include <iostream>// TODO remove

// NDEF PARSER OBJECT //
Nan::Persistent<v8::Function> ndef_parser::constructor;

ndef_parser::ndef_parser(double value) : value_(value) {}
ndef_parser::~ndef_parser() {}

NAN_MODULE_INIT(ndef_parser::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("ndefParser").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    SetPrototypeMethod(tpl, "getHandle", GetHandle);
    SetPrototypeMethod(tpl, "getHandleConst", GetHandleConst);
    SetPrototypeMethod(tpl, "getValue", GetValue);
    SetPrototypeMethod(tpl, "add", Add);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());

    Nan::Set(target, Nan::New("ndefParser").ToLocalChecked(),
      Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(ndef_parser::New) {
    if (info.IsConstructCall()) {
      double value = info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();

      ndef_parser *obj = new ndef_parser(value);
      obj->Wrap(info.This());

      info.GetReturnValue().Set(info.This());

    } else {
      const int argc = 1;
      v8::Local<v8::Value> argv[argc] = {info[0]};
      v8::Local<v8::Function> cons = Nan::New(constructor);
      info.GetReturnValue().Set(
          Nan::NewInstance(cons, argc, argv).ToLocalChecked());
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

NAN_METHOD(ndef_parser::GetValue) {
    ndef_parser* obj = ObjectWrap::Unwrap<ndef_parser>(info.Holder());
    info.GetReturnValue().Set(obj->value_);
}

NAN_METHOD(ndef_parser::Add) {
    ndef_parser* obj = ObjectWrap::Unwrap<ndef_parser>(info.Holder());
    obj->value_ += 1;

    // std::cout << value_ << std::endl;

    info.GetReturnValue().Set(Nan::New(obj->value_));


    // ndef_parser* obj = ObjectWrap::Unwrap<ndef_parser>(info.Holder());
    // info.GetReturnValue().Set(obj->value_);
}