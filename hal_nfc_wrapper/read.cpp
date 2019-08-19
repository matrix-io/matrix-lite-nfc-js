#include "read.h"
#include <nan.h>
#include "nfc.h"
#include "data/info.h"
#include "data/page.h"
#include "data/ndef.h"

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
    // Avoid reading, if NFC is being used by another thread
    if (!nfc_usage.try_lock()){
      this->SetErrorMessage("NFC was Busy"); // calls HandleErrorCallback()
      return; // we avoid queuing since .read() will be in an endless loop
    }

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
      ndef_status = nfc.ndef.Read(&nfc_data.ndef);
      nfc.Deactivate();
    }

    // Allow other threads to use NFC
    nfc_usage.unlock();
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
      // Instead of a status, page will return an empty array if it fails & a populated one if it passes.
      Nan::Set(tag_data, Nan::New("page").ToLocalChecked(), page_data_js(nfc_page));
    }
    // * NDEF
    if (options.ndef){
      v8::Local<v8::Object> ndef_data = ndef_data_js();
      Nan::Set(ndef_data, Nan::New("status").ToLocalChecked(), Nan::New(ndef_status));
      Nan::Set(tag_data, Nan::New("ndef").ToLocalChecked(), ndef_data);
    }

    // Callback Parameters
    int argCount = 2;
    v8::Local<v8::Value> argv[] = {
      Nan::New(nfc_status),
      tag_data
    };

    // Start callback
    Nan::Call(callback->GetFunction(), Nan::GetCurrentContext()->Global(), argCount, argv);
  }

  // Called if NFC was busy
  void HandleErrorCallback() {/*Left here for debugging*/}
};

// - NFC read function for info, page, pages, & NDEF.
// Calls an async worker for NFC reading after handling user arguments.
NAN_METHOD(read){
  // Set all NFC read options to fault
  readOptions options = {false,false,-1,false};

  // Ensure object is passed
  if (info[1]->IsObject()) {
    // Grab object
    v8::Local<v8::Object> read_options = Nan::To<v8::Object>(info[1]).ToLocalChecked();
    v8::Local<v8::String> info_prop  = Nan::New("info").ToLocalChecked();
    v8::Local<v8::String> pages_prop = Nan::New("pages").ToLocalChecked();
    v8::Local<v8::String> page_prop  = Nan::New("page").ToLocalChecked();
    v8::Local<v8::String> ndef_prop  = Nan::New("ndef").ToLocalChecked();

    // If given, update NFC read options
    if (Nan::HasOwnProperty(read_options, info_prop).FromJust() && Nan::True() == Nan::Get(read_options, info_prop).ToLocalChecked())
      options.info = true;

    if (Nan::HasOwnProperty(read_options, pages_prop).FromJust() && Nan::True() == Nan::Get(read_options, pages_prop).ToLocalChecked())
      options.pages = true;
    
    if (Nan::HasOwnProperty(read_options, page_prop).FromJust())
      options.page = Nan::To<int>(Nan::Get(read_options, page_prop).ToLocalChecked()).FromJust();

    if (Nan::HasOwnProperty(read_options, ndef_prop).FromJust() && Nan::True() == Nan::Get(read_options, ndef_prop).ToLocalChecked())
      options.ndef = true;
  }

  // Ensure callback is passed
  if (!info[0]->IsFunction()) {Nan::ThrowTypeError(".read argument 0 must be a function");return;}

  // Grab callback
  Nan::Callback *callback = new Nan::Callback(Nan::To<v8::Function>(info[0]).ToLocalChecked());

  // Run async function
  Nan::AsyncQueueWorker(new AsyncReader(callback, options));
}