var nfc = require('./build/Release/addon');
var matrix = require('@matrix-io/matrix-lite');

console.log(nfc.info());
info = nfc.info();

setInterval(function(){
    nfc.activate();
    info.read();
    nfc.deactivate(); 

    if (info.recentlyUpdated()) {
        console.log(info.toString());
        matrix.led.set("green");
    } else {
        matrix.led.set("black");
    }
},50);