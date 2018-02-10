
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

particle.getEventStream({ auth: token}).then(function(stream) {
  stream.on('Wifi Strength', function(data) {
    

    console.log("Wifi Strength: ", data);

    document.getElementByID('wifiID') = data;


  });
});

