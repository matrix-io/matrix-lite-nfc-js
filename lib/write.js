const nfc = require('.././build/Release/addon');
const nfcWrite = nfc.write();
write = {};

// - NDEF write
write.message = (message)=> {
    if (typeof message !== "object")
        throw new Error("Argument expected 1 nfc.message");

    return new Promise((resolve) => {
        nfcWrite.ndef(message, (code, write_code)=>{
            resolve({activation: code, write: write_code});
        });
    });
}

// - NDEF erase
write.erase = ()=> {
    return new Promise((resolve) => {
        nfcWrite.erase((code, write_code)=>{
            resolve({activation: code, write: write_code});
        });
    });
}


write.page = () => {}
write.pages = () => {}

module.exports = write;