var nfc = require('./build/Release/addon');
var matrix = require('@matrix-io/matrix-lite');

console.log(nfc.info());
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