#ifndef NDEF_RECORD_H
#define NDEF_RECORD_H

#include <nan.h>
#include <iostream>
#include "matrix_nfc/nfc.h"
#include "matrix_nfc/nfc_data.h"

struct record_info {
  std::string payload;
  std::string encodedSize;
};

std::string getTnf(matrix_hal::NDEFRecord *record);
uint8_t getTypeLength(matrix_hal::NDEFRecord *record);
int getPayloadLength(matrix_hal::NDEFRecord *record);
unsigned int getIdLength (matrix_hal::NDEFRecord *record);
std::string getType(matrix_hal::NDEFRecord *record);
std::string getPayload(matrix_hal::NDEFRecord *record);

#endif