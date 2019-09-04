#include <nan.h>
#include "../nfc.h"
#include "ndef_record.h"
#include <iostream>

std::string bytesToString(const uint8_t *vec, const uint8_t size) {
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

uint8_t getTypeLength(matrix_hal::NDEFRecord *record) {
  return record->GetTypeLength();
}

int getPayloadLength(matrix_hal::NDEFRecord *record) {
  return record->GetPayloadLength();
}

unsigned int getIdLength(matrix_hal::NDEFRecord *record) {
  return record->GetIdLength();
}

std::string getType(matrix_hal::NDEFRecord *record) {
  return record->GetType();
}

std::string getPayload(matrix_hal::NDEFRecord *record) {
  // matrix_hal::NDEFRecord new_record = *record;
  // uint8_t payload_size = record->GetPayloadLength();
  // uint8_t* payload = new uint8_t[payload_size];

  // return bytesToString(payload, payload_size);

  uint8_t payload;
  record->GetPayload(&payload);

  return "----placeholder----";
}