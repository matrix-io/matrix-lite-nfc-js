/*
Entry point for reading NFC Tags. Only one reader can be created at a time or things start getting weird.
The nfc.read function can be spammed as much as desired. C++ will automatically discard overlapping calls.
*/
const nfc = require('.././build/Release/addon');

class Reader {
    constructor() {
        this._readLoop = undefined;
    }

    start(options = {}, callback) {
        let config = {
            rate: (options.rate === 0) ? 0 : options.rate || 500,// *fix to allow 0
            info: options.info || false,
            pages: options.pages || false,
            page: (options.page === 0) ? 0 : options.page || -1,// *fix to allow 0
            ndef: options.ndef || false
        }

        // Start NFC read loop
        // Called twice to avoid waiting for first interval
        nfc.read(config, (code, tag) => {
            callback(code, tag);
            this._readLoop = setInterval(() => {
                nfc.read(config, callback);
            }, config.rate);
        });
    }

    stop() {
        clearInterval(this._readLoop);
    };
}

module.exports = new Reader();
