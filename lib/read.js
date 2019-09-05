const nfc = require('.././build/Release/addon');

class Reader {
  _readLoop = undefined;

  start(options = {}, callback) {
    let config = {
      rate:  (options.rate === 0)? 0 : options.rate || 500,// *fix to allow 0
      info:  options.info  || false,
      pages: options.pages || false, 
      page:  (options.page === 0)? 0 : options.page || -1,// *fix to allow 0
      ndef:  options.ndef  || false
    }

    // Start NFC read loop
    this._readLoop = setInterval(() => {
      nfc.read(config, callback);
    }, config.rate);
  }

  stop() {
    clearInterval(this._readLoop);
  };
}

module.exports = new Reader();