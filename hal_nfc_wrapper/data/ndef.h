#ifndef NDEF_H
#define NDEF_H

#include <nan.h>

NAN_METHOD(ndef);

v8::Local<v8::Object> ndef_data_js();

#endif