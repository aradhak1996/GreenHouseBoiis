

var particle = new Particle();


particle.getEventStream({ auth: token}).then(function(stream) {
  stream.on('event', function(data) {
    console.log("Event: ", data);
  });
});