
var Particle = require('particle-api-js');
var particle = new Particle();
var token;

particle.login({username: 'lucaskesselman@gmail', password: 'lucas1289'}).then(
  function(data) {
    token = data.body.access_token;
  },
  function (err) {
    console.log('Could not log in.', err);
  }
);

// particle.getEventStream({ auth: token}).then(function(stream) {
//   stream.on('Wifi Strength', function(data) {
    

//     console.log("Wifi Strength: ", data);

//     document.getElementByID('wifiID').innerHTML = data;


//   });
// });

particle.getEventStream({ deviceId: '42005f001051353338363333', name: 'InternetOfSeamus', auth: token }).then(function(stream) {
  stream.on('Wifi Strength', function(data) {


    console.log("Event: ", data);
	document.getElementByID('wifiID').innerHTML = data;


  });
});