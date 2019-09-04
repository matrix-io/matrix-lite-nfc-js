> Under Development

# MATRIX-Lite-JS

MATRIX Lite NFC JS is an npm package that allows users of varying skill levels to easily program NFC with their MATRIX Creator.

# Roadmap
`index.js` will contain example code. Note that the usage for this library will change before release.

This roadmap is for achieving a basic implementation of the checklist below.
- [x] Reading Info  (All tags)
- [x] Reading Pages (MIFARE Ultralight & NTAG)
- [x] Writing Page  (MIFARE Ultralight & NTAG)
- [x] Reading NDEF  (MIFARE Ultralight & NTAG)
- [x] Writing NDEF  (MIFARE Ultralight & NTAG)

# Installation
Install [matrix-hal-nfc](https://github.com/matrix-io/matrix-hal-nfc) to use this library.

Download the repository.
```
git clone https://github.com/matrix-io/matrix-lite-nfc-js
```

Install all dependencies.
```
npm install
```

Temporary examples are in `index.js`


# Building
Compiles any new C++ changes.
```
npm run build
```