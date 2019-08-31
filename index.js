// UNDER DEVELOPMENT * NOTHING FINAL
// The code below is a working async read/write example while
// the library is being finished.

var nfc = require('./build/Release/addon');
var matrix = require('@matrix-io/matrix-lite');

console.log(nfc);

// var record = new nfc.ndefRecord(12);
// console.log(record);
// console.log(record.setTnf(2));
// console.log(record.getTnf());
// console.log(record.getPayloadLength());

// // Testing C++ object wrapping
var message = new nfc.ndefParser();
message.addUriRecord("tel:+14085551212"); // https://developer.apple.com/documentation/corenfc/adding_support_for_background_tag_reading
message.addTextRecord("Hello");
message.addTextRecord("Hello");
message.addTextRecord("Hello");


var record1 = message.getRecord(2);
console.log(record1);

console.log("THE NEW RECORD!");
console.log(record1.getPayloadLength());


// message.getRecord();

// var write = nfc.write();
// setInterval(()=>{
//     nfc.read((code, tag)=>{
//         // Read tag
//         if(code === 256){
//             // write.ndef(message);
//             console.log(tag);
//             // var text = new nfc.ndefParser(tag.ndef.content);
//             // console.log(text.toString());
//             matrix.led.set({g:1});
//         }

//         // Didn't read tag
//         else if (code === 1024){
//             console.log("no tag found")
//             matrix.led.set();
//         }

//     }, {info: true});// you can remove what you don't want to read
// }, 1000);