#ifndef NFC_H
#define NFC_H

#include "matrix_nfc/nfc.h"
#include "matrix_nfc/nfc_data.h"

extern matrix_hal::NFC nfc;
extern matrix_hal::NFCData nfc_data;

// This is to prevent multiple async functions from using nfc.Activate()
extern bool nfc_active;

#endif