var nfc = require('./build/Release/addon');
var matrix = require('@matrix-io/matrix-lite');

// var info = nfc.info();

// console.log(info)

// setInterval(()=>{
//     info.readAsync((err, data)=>{
//         if (data.updated)
//             console.log(data);
//         else
//             console.log("Waiting for tag");
//     });
// }, 50);

// // everloop TODO REMOVE
// everloop = new Array(matrix.led.length).fill({});
// everloop[0] = {b:1};

// setInterval(function(){
//   var lastColor = everloop.shift();
//   everloop.push(lastColor);
//   matrix.led.set(everloop);
// },0);


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
let info = nfc.info();
let data = {};

setInterval(function(){
    nfc.activate();
    data = info.read();
    nfc.deactivate(); 

    if (data.updated) {
        console.log("********");
        console.log(data);
        matrix.led.set("green");
    } else {
        matrix.led.set("black");
    }
},50);

everloop = new Array(matrix.led.length).fill({});
everloop[0] = {b:1};

setInterval(function(){
  var lastColor = everloop.shift();
  everloop.push(lastColor);
  matrix.led.set(everloop);
},0);
//////////////////////////////////////////////////////////////////