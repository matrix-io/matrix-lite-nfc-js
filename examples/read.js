const nfc = require('../');

// Aside from rate, fewer read options improves read speed.
var options = {
    rate: 10,
    info: true,
    // pages: true,
    // page: 0,
    // ndef: true
}

nfc.read.start(options, (code, tag)=>{
    switch(code){
        case 256:
            console.log("Tag Was Scanned");
            console.log(tag);
            break;

        case 1024:
            console.log("Nothing Was Scanned");
            break;
        
        default:
            console.log(code + " == " + nfc.status(code));
    }   
});

// Stop after 10 seconds
setTimeout(()=>{nfc.read.stop}, 1000);