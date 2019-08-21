// UNDER DEVELOPMENT * NOTHING FINAL
// The code below is a working async read/write example while
// the library is being finished.

var nfc = require('./build/Release/addon');
var matrix = require('@matrix-io/matrix-lite');

console.log(nfc);


// Testing C++ object wrapping
var thing1 = new nfc.MyObject(10);
var thing2 = new nfc.MyObject(36);

console.log(thing1);
console.log(typeof (thing1.getHandle()));
console.log(typeof (thing1.getHandleConst()));
console.log(typeof (thing1.getValue()));



// console.log(thing2.getValue());


// setInterval(()=>{
//     nfc.read((code, tag)=>{
//     //     // Read tag
//         if(code === 256){
//             // console.log(tag);
//             matrix.led.set({g:1});
//             console.log(tag);
//         }

//         // Didn't read tag
//         else if (code === 1024){
//             console.log("no tag found")
//             matrix.led.set();
//         }

//     }, {ndef: true});// you can remove what you don't want to read
// }, 1000);