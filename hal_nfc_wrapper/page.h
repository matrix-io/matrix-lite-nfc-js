#ifndef PAGE_H
#define PAGE_H

#include <nan.h>

NAN_METHOD(page);

class Foo : public Nan::ObjectWrap {
  static void Bar(const Nan::FunctionCallbackInfo<v8::Value>& info);
//   static void Baz(const Nan::FunctionCallbackInfo<v8::Value>& info);
};

#endif