/*
Although it's easy to read ndef data, this example shows you how to read each
NDEF record from an NDEF message that was read.

// example msg.getRecords output
  [{
    tnf: 'Well Known',
    type: 'U',
    payload: '.https://community.matrix.one',
    ByteSize: 33,
    typeLength: 1,
    payloadLength: 29,
    IdLength: 0
  }]
*/

const nfc = require('..');

var options = {
    rate: 10,
    ndef: true
}

nfc.read.start(options, (code, tag)=>{
    switch(code){
        case 256:
            console.log("Tag Was Scanned");
            console.log(tag);
            
            let msg = new nfc.message(tag.ndef.content);

            // View an array of all records on tag
            console.log(msg.getRecords());

            // You can also request a specific record instead
            // let i = msg.getRecordCount() - 1;
            // console.log(msg.getRecord(i));
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