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
            //console.log('Sending AppMessage: ' + JSON.stringify(this.nextMessage()));
            Pebble.sendAppMessage(this.nextMessage(), ack, nack);
        }
    }
};

var commands = {
  COMMAND_LIST_COURSES : 0,
  COMMAND_SELECT_COURSE : 1,
  COMMAND_GET_LOCATION : 2,
  COMMAND_RECEIVE_COURSES : 3,
  COMMAND_RECEIVE_LOCATION : 4,
  COMMAND_RECEIVE_COURSE_DETAILS : 5,
};

function cleanCoordinate(coord) {
  return (coord * 1000000)|0;
}

function sendCourses() {
  appMessageQueue.clear();
            appMessageQueue.add({
              COMMAND: commands.COMMAND_RECEIVE_COURSES,
              COURSE_ID: 1,
              COURSE_NAME: "Ellesmere"
            });
            appMessageQueue.add({
              COMMAND: commands.COMMAND_RECEIVE_COURSES,
              COURSE_ID: 2,
              COURSE_NAME: "Worsley"
            });
            appMessageQueue.send();
}

var locationOptions = {
enableHighAccuracy: true,
maximumAge: 10000,
timeout: 40000
};

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

function sendCourseDetails() {
  var holes =[];
  holes.push({
    COMMAND: commands.COMMAND_RECEIVE_COURSE_DETAILS,
    HOLE_INDEX: 0,
    SI: 18,
    PAR: 3,
    LAT: 5351837600,
    LONG: -237980300
  });
  holes.push({
    COMMAND: commands.COMMAND_RECEIVE_COURSE_DETAILS,
    HOLE_INDEX: 1,
    SI: 17,
    PAR: 4,
    LAT: 5351837600,
    LONG: -237980300
  });

  console.log(JSON.stringify(holes));
  appMessageQueue.clear();
  var len = holes.length;
  for (var i = 0; i < len; i++) {
    appMessageQueue.add({
    COMMAND: commands.COMMAND_RECEIVE_COURSE_DETAILS,
    HOLE_INDEX: holes[i].HOLE_INDEX,
    SI: holes[i].SI,
    PAR: holes[i].PAR,
    LAT: cleanCoordinate(53.518376),
    LONG: cleanCoordinate(-2.379803)
  });
    console.log();
  }
  console.log("Sending course details... ");
  appMessageQueue.send();
}

Pebble.addEventListener("appmessage", 
function(e) { 
  console.log("Received " + e.payload.COMMAND );
  if (e.payload.COMMAND !== null) {
        switch (e.payload.COMMAND) {
        case commands.COMMAND_LIST_COURSES:
            console.log("List Courses");
            sendCourses();
            break;
            
        case commands.COMMAND_SELECT_COURSE:         
            console.log("Select Course " + e.payload.COURSE_ID);
            sendCourseDetails();
            break;
            
        case commands.COMMAND_GET_LOCATION:         
            console.log("Get Location");
            navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);
            break;
        }
 
    } else {
        appMessageQueue.clear();
    }
  
} 
); 