#include <nan.h>
#include "nfc.h"
#include "ndef_parser.h"

#include <iostream>// TODO remove

// NDEF PARSER OBJECT //
Nan::Persistent<v8::Function> MyObject::constructor;

MyObject::MyObject(double value) : value_(value) {}
MyObject::~MyObject() {}

NAN_MODULE_INIT(MyObject::Init) {
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("MyObject").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    SetPrototypeMethod(tpl, "getHandle", GetHandle);
    SetPrototypeMethod(tpl, "getHandleConst", GetHandleConst);
    SetPrototypeMethod(tpl, "getValue", GetValue);

    constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());

    Nan::Set(target, Nan::New("MyObject").ToLocalChecked(),
      Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(MyObject::New) {
    if (info.IsConstructCall()) {
      double value =
          info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();
      MyObject *obj = new MyObject(value);
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

NAN_METHOD(MyObject::GetHandle) {
    MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
    info.GetReturnValue().Set(obj->handle());
}

NAN_METHOD(MyObject::GetHandleConst) {
    MyObject const *obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
    info.GetReturnValue().Set(obj->handle());
}

NAN_METHOD(MyObject::GetValue) {
    MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
    info.GetReturnValue().Set(obj->value_);
}
