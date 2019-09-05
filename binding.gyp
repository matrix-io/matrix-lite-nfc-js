{
  "targets": [
    {
      "link_settings": {
        "libraries": [
          "-lmatrix_hal_nfc"
        ]
      },

      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "/usr/local/include/matrix_nfc/nxp_nfc/NxpNfcRdLib/intfs",
        "/usr/local/include/matrix_nfc/nxp_nfc/NxpNfcRdLib/types"
      ],

      "defines": ["NXPBUILD__PH_RASPBERRY_PI"],
      "cflags_cc": ["-std=c++11"],
      "target_name": "addon",
      "sources": ["<!@(ls -1 hal_nfc_wrapper/*.cpp)", "<!@(ls -1 hal_nfc_wrapper/reader/*.cpp)", "<!@(ls -1 hal_nfc_wrapper/writer/*.cpp)", "<!@(ls -1 hal_nfc_wrapper/ndef_types/*.cpp)"],  
    
    }
  ]
}
