var locationOptions = {
enableHighAccuracy: true,
maximumAge: 10000,
timeout: 40000
};

var current_index = 0;

function locationSuccess(pos) {
console.log('lat= ' + pos.coords.latitude + ' lon= ' + pos.coords.longitude);
}

function locationError(err) {
console.log('location error (' + err.code + '): ' + err.message);
}

var sendNextTuple = function(e) {
  if (current_index === 0) {
    var dict = {"COURSE_NAME" : "Ellesemere", "HOLES" : [3,5,3,4,4,5]};
    current_index++;
    Pebble.sendAppMessage(dict , 
                         function(e){
                           current_index++;
                           sendNextTuple();
                         });
    return;
  }
  var next = {"COURSE_NAME" : "Marriott", "HOLES" : [2,9,4,3,2,4]};
  Pebble.sendAppMessage(next);
};


Pebble.addEventListener("ready", 
function(e) { 
//App is ready to receive JS messages
console.log("Ready");
} 
); 
Pebble.addEventListener("appmessage", 
function(e) { 
//Watch wants new data!
  console.log("Request data");
  navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);
  sendNextTuple();
  
} 
); 