var appMessageQueue = {
    queue: [],
    numTries: 0,
    maxTries: 5,
    maxBuffer: 480,
    lastId: "",
    add: function(obj) {
        this.queue.push(obj);
    },
    clear: function() {
        this.queue = [];
    },
    isEmpty: function() {
        return this.queue.length === 0;
    },
    nextMessage: function() {
        return this.isEmpty() ? {} : this.queue[0];
    },
    send: function() {
        if (this.queue.length > 0) {
            var ack = function() {
                appMessageQueue.numTries = 0;
                appMessageQueue.queue.shift();
                appMessageQueue.send();
            };
            var nack = function() {
                appMessageQueue.numTries++;
                appMessageQueue.send();
            };
            if (this.numTries >= this.maxTries) {
                console.log('Failed sending AppMessage: ' + JSON.stringify(this.nextMessage()));
                ack();
            }
            console.log('Sending AppMessage: ' + JSON.stringify(this.nextMessage()));
            Pebble.sendAppMessage(this.nextMessage(), ack, nack);
        }
    }
};

var commands = {
  COMMAND_LIST_COURSES : 0,
  COMMAND_SELECT_COURSE : 1,
  COMMAND_GET_LOCATION : 2,
  COMMAND_RECEIVE_COURSES : 3,
  COMMAND_RECEIVE_LOCATION : 4
};

function cleanCoordinate(coord) {
  return (coord * 1000000)|0;
}


var locationOptions = {
enableHighAccuracy: true,
maximumAge: 10000,
timeout: 40000
};

var current_index = 0;

function locationSuccess(pos) {
  //test coords: 53.518376, -2.379803
  console.log('lat= ' + pos.coords.latitude + ' lon= ' + pos.coords.longitude);
  appMessageQueue.clear();
  appMessageQueue.add({
    COMMAND: commands.COMMAND_RECEIVE_LOCATION,
    LAT: cleanCoordinate(53.518376),
    LONG: cleanCoordinate(-2.379803)
  });
  appMessageQueue.send();
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
  console.log("Received " + e.payload.COMMAND );
  if (e.payload.COMMAND !== null) {
 
        switch (e.payload.COMMAND) {
        case commands.COMMAND_LIST_COURSES:
            console.log("List Courses");
            break;
        case commands.COMMAND_SELECT_COURSE:         
            console.log("Select Course");
            break;
        case commands.COMMAND_GET_LOCATION:         
            console.log("Get Location");
            navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);
            break;
        }
 
    } else {
        appMessageQueue.clear();
    }
  
  //sendNextTuple();
  
} 
); 