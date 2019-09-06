const nfc = require('../');

nfc.read.start({rate: 100, info:true}, (code, tag)=>{
        if (code === 256){
            console.log("Tag Was Scanned");

            // write.message requires an nfc.message
            nfc.write.erase().then((code)=>{
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