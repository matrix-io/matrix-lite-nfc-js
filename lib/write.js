const nfc = require('.././build/Release/addon');

// TODO use promises
write = nfc.write();

module.exports = write;