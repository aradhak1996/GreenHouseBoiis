
// Hide Temp and Light for now...
document.getElementById("labelTemp").hidden = true;
document.getElementById("labelPhoto").hidden = true;

var particle = new Particle();
var token = "55e9973b571f594ebc4cc2c2aabff1f1dda8a17f";

console.log("Page Running");

particle.getEventStream({ deviceId: '42005f001051353338363333', auth: token }).then(function(stream) {
  stream.on('Temperature', function(data) {
    document.getElementById("TempID").innerHTML = data.data;
  });
});

particle.getEventStream({ deviceId: '42005f001051353338363333', auth: token }).then(function(stream) {
  stream.on('Photoresistor Reading', function(data) {
    document.getElementById("photoID").innerHTML = data.data;
  });
});

particle.getEventStream({ deviceId: '42005f001051353338363333', auth: token }).then(function(stream) {
  stream.on('status', function(data) {
    document.getElementById('status').innerHTML = data.data;
  });
});


document.getElementById('openButton').addEventListener("click", Open);
document.getElementById('closeButton').addEventListener("click", Close);

function Open(){
  var functionDataOpen = {
    deviceId: '42005f001051353338363333',
    name: "actuate",
    argument: "open",
    auth: token
  }
  particle.callFunction(functionDataOpen).then(onSuccess, onFailure);
  document.getElementById('status').innerHTML = "Open"; 
}

function Close(){
  var functionDataClose = {
    deviceId: '42005f001051353338363333',
    name: "actuate",
    argument: "close",
    auth: token
  }
  particle.callFunction(functionDataClose).then(onSuccess, onFailure);
  document.getElementById('status').innerHTML = "Closed";
}


function onSuccess(){
  console.log("__Actuation Success");
}

function onFailure(){
  console.log("__Actuation Failure");
}

