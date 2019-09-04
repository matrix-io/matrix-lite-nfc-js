#include <nan.h>
#include "../nfc.h"
#include "ndef_record.h"
#include "ndef_parser.h"

#include <iostream>// TODO remove

// NAN_METHOD(ndef_record::GetTnf) {
//   ndef_record* obj = ObjectWrap::Unwrap<ndef_record>(info.Holder());
//   std::string result;

//   switch (obj->ndef_record_.GetTnf()) {
//     case TNF_EMPTY:
//         result = "Empty";
//         break;
//     case TNF_WELL_KNOWN:
//         result = "Well Known";
//         break;
//     case TNF_MIME_MEDIA:
//         result = "Mime Media";
//         break;
//     case TNF_ABSOLUTE_URI:
//         result = "Absolute URI";
//         break;
//     case TNF_EXTERNAL_TYPE:
//         result = "External";
//         break;
//     case TNF_UNKNOWN:
//         result = "Unknown";
//         break;
//     case TNF_UNCHANGED:
//         result = "Unchanged";
//         break;
//     case TNF_RESERVED:
//         result = "Reserved";
//         break;
//     default:
//         result = "Unknown TNF";
//   }
  
//   info.GetReturnValue().Set(Nan::New(result).ToLocalChecked());
// }

// Needed 
std::string BytesToString(const uint8_t *vec, const uint8_t size) {
    std::stringstream result;
    for (int i = 0; i < size; i++) {
        if ((vec[i] < 0x20) || (vec[i] > 0x7e))
            result << '.';
        else
            result << vec[i];
    }
    result << std::flush;
    return result.str();
}