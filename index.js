// UNDER DEVELOPMENT * NOTHING FINAL
// The code below is a working async read/write example while
// the library is being finished.

var nfc = require('./build/Release/addon');
var matrix = require('@matrix-io/matrix-lite');

console.log(nfc);

var record = new nfc.ndefRecord(12);
var parser = new nfc.ndefParser();

console.log(record.getValue());
console.log(parser.toString());


// // Testing C++ object wrapping
var message = new nfc.ndefParser();
// message.addTextRecord("hola mundo", "es");
// message.addMimeMediaRecord("text/json", '{"answer": 42}');
// message.addTextRecord("hello world");
message.addUriRecord("https://docs.matrix.one"); // https://developer.apple.com/documentation/corenfc/adding_support_for_background_tag_reading
// message.addEmptyRecord();


message.getRecord(21);
message.addTextRecord("Hello");
message.getRecord();








// var write = nfc.write();

// setInterval(()=>{
//     nfc.read((code, tag)=>{
//         // Read tag
//         if(code === 256){
//             write.ndef(message);
//             console.log(tag.ndef.content);
//             // var text = new nfc.ndefParser(tag.ndef.content);
//             // console.log(text.toString());
//             matrix.led.set({g:1});
//         }

//         // Didn't read tag
//         else if (code === 1024){
//             console.log("no tag found")
//             matrix.led.set();
//         }

//     }, {ndef: true});// you can remove what you don't want to read
// }, 1000);