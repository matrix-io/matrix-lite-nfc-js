{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "/usr/local/include/matrix_nfc/nxp_nfc/NxpNfcRdLib/intfs",
        "/usr/local/include/matrix_nfc/nxp_nfc/NxpNfcRdLib/types"
      ],

      "link_settings": {
        "libraries": [
          "-lmatrix_hal_nfc"
        ]
      },

      'defines': ['NXPBUILD__PH_RASPBERRY_PI'],

      "cflags_cc": ["-std=c++11"],

      "target_name": "addon",

      "sources": ["<!@(ls -1 hal_nfc_wrapper/*.cpp)"],  
    
    }
  ]
}
