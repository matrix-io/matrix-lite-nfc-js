> Under Development

# MATRIX-Lite-JS

MATRIX Lite NFC JS is an npm package that allows users of varying skill levels to easily program NFC with their MATRIX Creator.

# Roadmap
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
View the [examples](https://github.com/matrix-io/matrix-lite-nfc-js/tree/master/examples) folder for a better understanding.

## Reading
```js
// Aside from rate, fewer read options improves read speed.
let options = {
    rate: 500,
    info: true,     
    // pages: true,
    // page: 0,
    // ndef: true,
}

// Start reading
nfc.read.start(options, (code, tag) => {
    // Read status code
    console.log(nfc.status(code));
    
    // Tag Found
    if(code === 256){
        console.log("Tag Was Scanned");
        console.log(tag);
    }

    // Nothing Found
    else if (code === 1024)
        console.log("nothing found");
});

// Stop reading after 10 seconds
setTimeout(() => {nfc.read.stop()}, 10000);
```

## Writing
```js
// Manually write to tag's page (make sure you know what you're doing!!!)
nfc.write.page([0,1,2,3]);// Array represents a byte

// Accepts an ndef
let message = new nfc.message();
message.addUriRecord("https://github.com");
message.addUriRecord("https://community.matrix.one");
nfc.write.ndef(message);

// Remove all NDEF messages
nfc.write.erase()
```