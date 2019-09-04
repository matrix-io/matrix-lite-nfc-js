const nfc = require('.././build/Release/addon');
const events = require('events');

let reader = function(options) {
  // Use default or user passed options
  options = options || {};
  let that = new events.EventEmitter();
  let refreshRate = options.rate || 1000;
  let getInfo = options.info || false;
  let getPages = options.pages || false;
  let getPage = options.page || -1;
  let getNdef = options.ndef || false;

  // TODO
  // that.reading = false;

  // that.readLoop = async function() {
  //   return await new Promise(resolve => {
  //     const interval = setInterval(() => {
  //       if(that.reading = false)
  //         resolve("Stopped Reading");

  //       // NFC read
  //       console.log(reading)
  //       nfc.read((code, tag)=>{
  //         clearInterval(interval);
  //       }, {info: getInfo, pages: getPages, page: getPage,  ndef: getNdef});
  //     }, refreshRate);
  //   });
  // }

  /////////////////////
  // Event Emitters //
  that.start = function(){
    // TODO start read loop
    that.emit("start");
  }

  /////////////////////
  // Event Listeners //
  that.on("start", ()=>{
    console.log("events started");
  });

  return that;
}

module.exports = reader;

////////////////////////
// HELPFUL FUNCTIONS //
