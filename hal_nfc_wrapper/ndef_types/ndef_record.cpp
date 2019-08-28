#include <nan.h>
#include "../nfc.h"
#include "ndef_record.h"

#include <iostream>// TODO remove

// NDEF RECORD OBJECT //
Nan::Persistent<v8::Function> ndef_record::constructor;

ndef_record::ndef_record(double value) : value_(value) {}
ndef_record::~ndef_record() {}

NAN_MODULE_INIT(ndef_record::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("ndefRecord").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    SetPrototypeMethod(tpl, "getHandle", GetHandle);
    SetPrototypeMethod(tpl, "getHandleConst", GetHandleConst);
    SetPrototypeMethod(tpl, "getValue", GetValue);
    SetPrototypeMethod(tpl, "add", Add);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());

    Nan::Set(target, Nan::New("ndefRecord").ToLocalChecked(),
      Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(ndef_record::New) {
    if (info.IsConstructCall()) {
      double value = info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();

      ndef_record *obj = new ndef_record(value);
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

NAN_METHOD(ndef_record::GetHandle) {
    ndef_record* obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
    info.GetReturnValue().Set(obj->handle());
}

NAN_METHOD(ndef_record::GetHandleConst) {
    ndef_record const *obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
    info.GetReturnValue().Set(obj->handle());
}

NAN_METHOD(ndef_record::GetValue) {
    ndef_record* obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
    info.GetReturnValue().Set(obj->value_);
}

NAN_METHOD(ndef_record::Add) {
    ndef_record* obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
    obj->value_ += 1;

    // std::cout << value_ << std::endl;

    info.GetReturnValue().Set(Nan::New(obj->value_));


    // ndef_record* obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
    // info.GetReturnValue().Set(obj->value_);
}