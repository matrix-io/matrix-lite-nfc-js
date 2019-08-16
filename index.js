var nfc = require('./build/Release/addon');
var matrix = require('@matrix-io/matrix-lite');

var ndef = nfc.ndef();

setInterval(()=>{

    console.log(ndef.parser());

    // nfc.read((code, tag)=>{
    //     // Read tag
    //     if(code === 256){
    //         // console.log(code)
    //         console.log(tag);
    //         matrix.led.set({g:1});
    //     }
    //     // Didn't read tag
    //     else if (code === 1024){
    //         // console.log(code);
    //         matrix.led.set();
    //     }
    // }, {info: true, pages: true, page: 12, ndef: true});

}, 1000);

//////////////////////////////////////////////////////////////////
// - Read NDEF Pages (MIFARE Ultralight & NTAG)
// ndef = nfc.ndef();
// console.log(ndef);

// setInterval(function(){
//     nfc.activate();
//     let data = ndef.read();
//     nfc.deactivate(); 

//     console.log(data);

//     if (data.updated)
//         console.log(data.content.toString());
// },0);

//////////////////////////////////////////////////////////////////
// - Read Pages (MIFARE Ultralight & NTAG)
// let page = nfc.page();

// setInterval(function(){
//     nfc.activate();
//     let data = page.readAll();
//     nfc.deactivate(); 

//     console.log(data);
//     if (data.length > 0){
//         console.log("This tag had " + data.length + " pages");
//         process.exit(0);
//     }
// },1000);
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
// - Write To A Page (MIFARE Ultralight & NTAG)
// let page = nfc.page();

// setInterval(function(){
//     nfc.activate();

//     let message = "heyo".split("").map((x)=>{return x.charCodeAt(0);});
//     let code = page.write(21, message);//BE CAREFUL ON WHAT PAGE YOU WRITE TO!!!

//     nfc.deactivate();

//     if (code === 0){
//         console.log(nfc.status(code));
//     }
// }, 50);
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////