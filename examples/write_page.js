/*
BE SUPER CAREFUL!
You might accidentally lock your nfc tag if you don't know what you're doing.
*/
const nfc = require('../');

let page_index = 25;
let page_byte = [48,45,59,21];

nfc.read.start({rate: 100, info:true}, (code, tag)=>{
        if (code === 256){
            console.log("Tag Was Scanned");

            nfc.write.page(page_index, page_byte).then((code)=>{
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
