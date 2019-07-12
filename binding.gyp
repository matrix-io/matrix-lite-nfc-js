{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],

      "link_settings": {
        "libraries": [
          "-lmatrix_hal_nfc"
        ]
      },
      "target_name": "addon",
      # Each index exposes all files inside path
      "sources": ["<!@(ls -1 hal_nfc_wrapper/*.cpp)"]
    }
  ]
}
