// UNDER DEVELOPMENT * NOTHING FINAL
// The code below is a working async read/write example while
// the library is being finished.

var nfc = require('./build/Release/addon');
var matrix = require('@matrix-io/matrix-lite');

console.log(nfc);

var message = new nfc.ndefParser(20);
var message2 = new nfc.ndefParser(3);

console.log("message1: " + message.getValue());
console.log("message2: " + message2.getValue());

console.log(nfc.Sum(message, message2));

// Testing C++ object wrapping
// var thing1 = new nfc.MyObject();
// var thing2 = new nfc.MyObject(36);

// console.log(thing1);
// console.log(typeof (thing1.getHandle()));
// console.log(typeof (thing1.getHandleConst()));
// console.log(typeof (thing1.getValue()));

// console.log("\n\n");
// console.log(thing1.getValue());
// thing1.add();
// console.log("Thing 1: " + thing1.getValue());
// console.log("Thing 2: " + thing2.getValue());




// console.log(thing2.getValue());


setInterval(()=>{
    nfc.read((code, tag)=>{
    //     // Read tag
        if(code === 256){
            // console.log(tag);
            matrix.led.set({g:1});
            console.log(tag);
        }

        // Didn't read tag
        else if (code === 1024){
            console.log("no tag found")
            matrix.led.set();
        }

    }, {ndef: true});// you can remove what you don't want to read
}, 1000);