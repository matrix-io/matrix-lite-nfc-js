const nfc = require('..');

let options = {
    rate: 10,
    pages: true
    // You can request a specific page instead for faster reading
    // page: 10,
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
setTimeout(()=>{
    console.log("Exiting...");
    nfc.read.stop();
}, 10000);