var nfc = require('./build/Release/addon');
var matrix = require('@matrix-io/matrix-lite');

// - Read A Page (MIFARE Ultralight & NTAG)
// let page = nfc.page();
// data = [];

// setInterval(function(){
//     nfc.activate();
//     data = page.read(1);
//     nfc.deactivate(); 

//     if (data.length > 0)
//         console.log(data);
// },0);

// - Reading Info (All tags)
// let info = nfc.info();
// let data = {};

// setInterval(function(){
//     nfc.activate();
//     data = info.read();
//     nfc.deactivate(); 

//     if (data.updated) {
//         console.log("********");
//         console.log(data);
//         matrix.led.set("green");
//     } else {
//         matrix.led.set("black");
//     }
// },50);