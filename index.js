const nfc = require('./build/Release/addon');

const read = require('./lib/read.js');
const write = require('./lib/write.js');

module.exports = {
    // Returns a string based on number given (used for NFC status codes)
    'status': nfc.status,
    'read': read,
    'write': write,
    'message': nfc.ndefParser
};