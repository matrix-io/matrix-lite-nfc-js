const nfc = require('.././build/Release/addon');

class Reader {
  _active = false;
  _readLoop = undefined;

  start(options = {}, callback) {
    if(this._active){throw new Error("Already reading NFC!");}
    this._active = true;
    
    let config = {
      rate: (options.rate === 0)? 0 : options.rate || 1000,// *fix to allow 0
      info: options.info || false,
      pages: options.pages || false, 
      page: options.page || -1,
      ndef: options.ndef || false
    }

    // Recursive NFC read loop
    function read(proceed, rate) {
      if (proceed)
        setTimeout(()=>{
          nfc.read(config, callback); 
          read(proceed, rate)}, 
        rate);
    }

    // Start NFC read loop
    this._readLoop = (()=>{
      read(this._active, config.rate);
    })();
  }

  stop() {
    this._readLoop = undefined;
  };
}

module.exports = new Reader();