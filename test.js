var nfc = require('./build/Release/addon');
var matrix = require('@matrix-io/matrix-lite');

var info = nfc.info();

console.log(info)

setInterval(()=>{
    info.readAsync((err, data)=>{
        console.log(123)

        if (data.updated)
            console.log(data);
        else
            console.log("Waiting for tag");
    });
}, 40);

// everloop TODO REMOVE
everloop = new Array(matrix.led.length).fill({});
everloop[0] = {b:1};

setInterval(function(){
  var lastColor = everloop.shift();
  everloop.push(lastColor);
  matrix.led.set(everloop);
},0);