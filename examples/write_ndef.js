const nfc = require('../');

// Create an empty NDEF message
let msg = new nfc.message();

// Add NDEF Records to message
msg.addUriRecord("https://community.matrix.one");
msg.addUriRecord("tel:+14085551212");
msg.addTextRecord("Hello World");
msg.addTextRecord("Hola Mundo", "es");
msg.addMimeMediaRecord("text/json", '{"answer": 42}');

nfc.read.start({rate: 10, info:true}, (code, tag)=>{
        if (code === 256){
            console.log(tag);
            console.log("Tag Was Scanned");

            // write.message requires an nfc.message
            nfc.write.message(msg).then((code)=>{
                console.log("Activation Status:" + code.activation + " == " + nfc.status(code.activation));
                console.log("Write Status:" + code.write + " == " + nfc.status(code.write));

                // Exit after successful writing
                if(code.write === 0)
                    process.exit(0);
            });
        }

        else if (code === 1024)
            console.log("Nothing Was Scanned");
});
