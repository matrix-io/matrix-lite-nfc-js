#ifndef NDEF_RECORD_H
#define NDEF_RECORD_H

#include <nan.h>
#include <iostream>
#include "matrix_nfc/nfc.h"
#include "matrix_nfc/nfc_data.h"

std::string getTnf(matrix_hal::NDEFRecord *record);

#endif