#ifndef NFC_H
#define NFC_H

#include "matrix_nfc/nfc.h"
#include "matrix_nfc/nfc_data.h"
#include <mutex>

extern matrix_hal::NFC nfc;
extern matrix_hal::NFCData nfc_data;

// This is to prevent multiple async functions from using nfc.Activate()
extern std::mutex nfc_usage;

#endif