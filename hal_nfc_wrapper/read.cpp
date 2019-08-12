#include "read.h"
#include <nan.h>
#include "nfc.h"
#include "data/info.h"
#include "data/page.h"
#include "data/ndef.h"

#include <iostream>

class AsyncReader : public Nan::AsyncWorker {
public:
  int nfc_status, info_status, pages_status, page_status, ndef_status;
  readOptions options;
  std::vector<uint8_t> nfc_page;

  AsyncReader(Nan::Callback *callback, readOptions options )
    : Nan::AsyncWorker(callback) {
      this->options = options;
    }

  // Execute non-blocking code. **DO NOT MAKE V8 CALLS HERE!**
  void Execute() {
    // Prevent async calls overlapping NFC
    if (!nfc_active){
      nfc_active = true;

      // Get requested NFC data //
      if (options.info) {
        nfc_status = nfc.Activate();
        info_status = nfc.ReadInfo(&nfc_data.info);
        nfc.Deactivate();
      }
      if (options.pages) {
        nfc_status = nfc.Activate();
        pages_status = nfc.mful.ReadPages(&nfc_data.pages);
        nfc.Deactivate();
      }
      if (options.page != -1){
        nfc_status = nfc.Activate();
        nfc_page = nfc.mful.ReadPage(options.page);
        nfc.Deactivate();
      }
      if (options.ndef){
        nfc_status = nfc.Activate();
        // TODO
        nfc.Deactivate();
      }
    }

    // Run HandleErrorCallback()
    else {
      this->SetErrorMessage("Error: NFC Was Busy Reading/Writing!");
      return;
    }
  }

  void HandleOKCallback() {
    // Prevent V8 objects from being garbage collected
    Nan::HandleScope scope;

    // Return scanned NFC data
    v8::Local<v8::Object> tag_data = Nan::New<v8::Object>();

    // Create NFC data & add read status to each data object //
    // * Info
    if (options.info) {
      v8::Local<v8::Object> info_data = info_data_js();
      Nan::Set(info_data, Nan::New("status").ToLocalChecked(), Nan::New(info_status));
      Nan::Set(tag_data, Nan::New("info").ToLocalChecked(), info_data);
    }
    // * Pages
    if (options.pages) {
      v8::Local<v8::Object> pages_data = pages_data_js();
      Nan::Set(pages_data, Nan::New("status").ToLocalChecked(), Nan::New(pages_status));
      Nan::Set(tag_data, Nan::New("pages").ToLocalChecked(), pages_data);
    }
    // * Page
    if (options.page != -1){
      // Instead of a status, page will return an empty array if it fails & a populated one if is passes.
      Nan::Set(tag_data, Nan::New("page").ToLocalChecked(), page_data_js(nfc_page));
    }
    // * NDEF
    if (options.ndef){
        // TODO
    }

    // Callback Parameters
    int argCount = 2;
    v8::Local<v8::Value> argv[] = {
      Nan::New(nfc_status),
      tag_data
    };

    // Start callback
    nfc_active = false;
    Nan::Call(callback->GetFunction(), Nan::GetCurrentContext()->Global(), argCount, argv);
  }

  // Called if NFC was busy
  void HandleErrorCallback() {
    Nan::HandleScope scope;
    v8::Local<v8::Value> argv[] = {
      Nan::New(-999)// status code we made up for busy NFC
    };
    Nan::Call(callback->GetFunction(), Nan::GetCurrentContext()->Global(), 1, argv);
  }
};

NAN_METHOD(read){
  //TODO: parse user args

  Nan::Callback *callback = new Nan::Callback(
    Nan::To<v8::Function>(info[0]).ToLocalChecked()
  );

  Nan::AsyncQueueWorker(new AsyncReader(callback, readOptions{true,true,0,true}));
}