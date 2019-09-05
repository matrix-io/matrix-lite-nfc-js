#include <nan.h>
#include "../nfc.h"
#include "ndef_record.h"
#include <iostream>

std::string getTnf (matrix_hal::NDEFRecord *record) {
  switch (record->GetTnf()) {
  case TNF_EMPTY:
      return "Empty";
      break;
  case TNF_WELL_KNOWN:
      return "Well Known";
      break;
  case TNF_MIME_MEDIA:
      return "Mime Media";
      break;
  case TNF_ABSOLUTE_URI:
      return "Absolute URI";
      break;
  case TNF_EXTERNAL_TYPE:
      return "External";
      break;
  case TNF_UNKNOWN:
      return "Unknown";
      break;
  case TNF_UNCHANGED:
      return "Unchanged";
      break;
  case TNF_RESERVED:
      return "Reserved";
      break;
  default:
      return "Unknown TNF";
  }
}