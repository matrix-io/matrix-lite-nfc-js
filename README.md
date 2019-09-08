> Under Development

# MATRIX-Lite-JS

MATRIX Lite NFC JS is an npm package that allows users of varying skill levels to easily program NFC with their MATRIX Creator.

# Smartphone Apps For Debugging
- [IOS App](https://apps.apple.com/us/app/nfc-taginfo-by-nxp/id1246143596)
- [Android App](https://play.google.com/store/apps/details?id=com.nxp.nfc.tagwriter&hl=en_US)

# Roadmap
This roadmap is for achieving a basic implementation of the checklist below.
- [x] Reading Info  (All tags)
- [x] Reading Pages (MIFARE Ultralight & NTAG)
- [x] Writing Page  (MIFARE Ultralight & NTAG)
- [x] Reading NDEF  (MIFARE Ultralight & NTAG)
- [x] Writing NDEF  (MIFARE Ultralight & NTAG)
- [ ] Upload package to npm

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

You can now import the module into any `.js` file. We will eventually create an npm package.
```
const nfc = require("./matrix-lite-nfc-js");
```


# Building
Compiles any new C++ changes.
```
npm run build
```

# Examples
View the [examples](https://github.com/matrix-io/matrix-lite-nfc-js/tree/master/examples) folder!

# Reference

## nfc.status
When a read or write function completes, it will return a status code to indicate the result. `nfc.Status` returns a string of what that number means.
```
nfc.status(/*number*/);
```

## nfc.read
There can only be one instance of NFC reading. This is a hardware limitation that will not change.
### Starting Read Loop
```js
// Configure what you want to read
let options = {
    rate: 100    // Read loop speed (Milliseconds)
    // At least 1 read options is required. Less options -> faster reading!
    info: true,  // Generic information for any NFC tag
    pages: true, // All page data
    page: 0,     // A single page(faster than pages)
    ndef: true   // All NDEF data
}

// Start the loop
nfc.read.start(options, (code, tag) => {
    // code: NFC activation status
    // tag : Object with requested NFC data
});
```
### Stopping Read Loop
```js
nfc.read.stop();
```

## nfc.message
An NFC constructor that represents an NDEF message. There are 2 uses for this class.

### 1. Creating a new NDEF Message
```js
// Create an empty NDEF message
let msg = new nfc.message();

// Add 4 NDEF Records to message
msg.addUriRecord("tel:+14085551212");
msg.addTextRecord("Hello World");
msg.addTextRecord("Hola Mundo", "es");
msg.addMimeMediaRecord("text/json", '{"answer": 42}');

// You then pass msg into nfc.write.message(msg);
```
### 2. Reading an existing NDEF Message
```js
nfc.read.start({ndef:true}, (code, tag) => {
    // You can create a new NDEF message from a scanned tag.
    msg = new nfc.message(tag.ndef.content);

    // Once created, you can read any known NDEF record.
    console.log(msg.getRecords());
    // or
    console.log(msg.getRecord(0));
});
```

## nfc.write
Writing to an NFC tag **should normally be done inside the read loop**.

### Writing an NDEF message
```js
var msg = new nfc.message();
msg.addUriRecord("https://community.matrix.one");

nfc.write.message(msg).then((codes)=>{
    // codes.activation : NFC activation status
    // codes.write      : NFC write status
});

```

### Erasing an NDEF message
```js
nfc.write.erase().then((codes)=>{
    // codes.activation : NFC activation status
    // codes.write      : NFC write status
});
```

### Writing to a tag's page (**WARNING**)
Be careful when writing to a page. You can accidentally lock your NFC tag!
```js
var page_index = 25;            // page you want to overwrite
var page_byte = [48,45,59,21];  // Array of numbers that represents a byte

nfc.write.page(page_index, page_byte).then((code)=>{
    // codes.activation : NFC activation status
    // codes.write      : NFC write status
});
```
