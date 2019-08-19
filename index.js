// UNDER DEVELOPMENT * NOTHING FINAL
// The code below is a working async read/write example while
// the library is being finished.

var nfc = require('./build/Release/addon');
var matrix = require('@matrix-io/matrix-lite');

var write = nfc.write();

setInterval(()=>{
    nfc.read((code, tag)=>{
        // Read tag
        if(code === 256){
            console.log(tag);
            matrix.led.set({g:1});

            // Write to tag page
            write.page(15, [12,12,12,12], (activate_code, write_code)=>{
                console.log("Activate:" + activate_code +" "+ nfc.status(activate_code)+"\n");
                console.log("Write:" + write_code +" "+nfc.status(write_code));
            });
        }
        // Didn't read tag
        else if (code === 1024){
            console.log("no tag found")
            matrix.led.set();
        }
    }, {info: true, pages: true, page: 15, ndef: true});// you can remove what you don't want to read

}, 1000);