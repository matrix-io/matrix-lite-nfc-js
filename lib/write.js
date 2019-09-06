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

// - Page write requires a valid page number and an int array with 4 numbers (represents a byte)
write.page = (i, byte) => {
    return new Promise((resolve) => {
        nfcWrite.page(i, byte, (code, write_code)=>{
            resolve({activation: code, write: write_code});
        });
    });
}

// TODO
// write.pages = () => {}

module.exports = write;