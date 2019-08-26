// NOT IMPLEMENTED //

// #include <nan.h>
// #include "../nfc.h"
// #include "ndef_record.h"

// #include <iostream>// TODO remove

// // NDEF RECORD OBJECT //
// Nan::Persistent<v8::Function> MyObject::constructor;

// MyObject::MyObject(double value) : value_(value) {}
// MyObject::~MyObject() {}

// NAN_MODULE_INIT(MyObject::Init) {
//     v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
//     tpl->SetClassName(Nan::New("MyObject").ToLocalChecked());
//     tpl->InstanceTemplate()->SetInternalFieldCount(1);

//     SetPrototypeMethod(tpl, "getHandle", GetHandle);
//     SetPrototypeMethod(tpl, "getHandleConst", GetHandleConst);
//     SetPrototypeMethod(tpl, "getValue", GetValue);
//     SetPrototypeMethod(tpl, "add", Add);

//     constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());

//     Nan::Set(target, Nan::New("MyObject").ToLocalChecked(),
//       Nan::GetFunction(tpl).ToLocalChecked());
// }

// NAN_METHOD(MyObject::New) {
//     if (info.IsConstructCall()) {
//       double value = info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();

//       MyObject *obj = new MyObject(value);
//       obj->Wrap(info.This());

//       info.GetReturnValue().Set(info.This());

//     } else {
//       const int argc = 1;
//       v8::Local<v8::Value> argv[argc] = {info[0]};
//       v8::Local<v8::Function> cons = Nan::New(constructor);
//       info.GetReturnValue().Set(
//           Nan::NewInstance(cons, argc, argv).ToLocalChecked());
//     }
// }

// NAN_METHOD(MyObject::GetHandle) {
//     MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
//     info.GetReturnValue().Set(obj->handle());
// }

// NAN_METHOD(MyObject::GetHandleConst) {
//     MyObject const *obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
//     info.GetReturnValue().Set(obj->handle());
// }

// NAN_METHOD(MyObject::GetValue) {
//     MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
//     info.GetReturnValue().Set(obj->value_);
// }

// NAN_METHOD(MyObject::Add) {
//     MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
//     obj->value_ += 1;

//     // std::cout << value_ << std::endl;

//     info.GetReturnValue().Set(Nan::New(obj->value_));


//     // MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
//     // info.GetReturnValue().Set(obj->value_);
// }