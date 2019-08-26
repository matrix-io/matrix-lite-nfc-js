// UNDER DEVELOPMENT * NOTHING FINAL
// The code below is a working async read/write example while
// the library is being finished.

var nfc = require('./build/Release/addon');
var matrix = require('@matrix-io/matrix-lite');

// console.log(nfc);

// // Testing C++ object wrapping
// var message = new nfc.ndefParser();
// message.addTextRecord("hola mundo", "es");
// message.addTextRecord("hello world");
// message.addUriRecord("http://docs.matrix.one");
// message.addEmptyRecord();

// console.log(message.toString());

var message2 = new nfc.ndefParser(12);
message2.addTextRecord("world");
console.log("message: " + message2.toString());







var write = nfc.write();

setInterval(()=>{
    nfc.read((code, tag)=>{
        // Read tag
        if(code === 256){
            // console.log(tag.ndef)
            var text = new nfc.ndefParser();
            console.log(text.toString());
            matrix.led.set({g:1});
        }

        // Didn't read tag
        else if (code === 1024){
            console.log("no tag found")
            matrix.led.set();
        }

    }, {ndef: true});// you can remove what you don't want to read
}, 1000);