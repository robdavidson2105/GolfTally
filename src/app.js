// Message Queue helper to stack up messages to the Pebble then
// send them sequentially
/* from https://raw.github.com/Skipstone/Skipstone/master/js/appmessage.js */
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

// The command references which are sent to and from the Pebble
var commands = {
  COMMAND_LIST_COURSES : 0,
  COMMAND_SELECT_COURSE : 1,
  COMMAND_GET_LOCATION : 2,
  COMMAND_RECEIVE_COURSES : 3,
  COMMAND_RECEIVE_LOCATION : 4,
  COMMAND_RECEIVE_COURSE_DETAILS : 5,
};

// It's easier to send integers to the Pebble
function cleanCoordinate(coord) {
  return (coord * 1000000)|0;
}

//Object to hold the keys and values sent to the GPS function
var locationOptions = {
enableHighAccuracy: true,
maximumAge: 0,
timeout: 10000
};

// Callback function - successful acquisition of GPS coords => send them to the Pebble
function locationSuccess(pos) {
  console.log('lat= ' + pos.coords.latitude + ' lon= ' + pos.coords.longitude);
  appMessageQueue.clear();
  appMessageQueue.add({
    COMMAND: commands.COMMAND_RECEIVE_LOCATION,
    LAT: cleanCoordinate(pos.coords.latitude),
    LONG: cleanCoordinate(pos.coords.longitude)
  });
  appMessageQueue.send();
}

function locationError(err) {
console.log('location error (' + err.code + '): ' + err.message);
}

// Once we've got the course details from Parse, we parse the json response
// then push them into an array and send to the Pebble
function sendCourseDetails(data) {
  var holes =[];
  var response = JSON.parse(data);
  var hole_details = response.Holes;
  for (var i = 0; i < 18; i++) {
    holes.push({
      COMMAND: commands.COMMAND_RECEIVE_COURSE_DETAILS,
      HOLE_INDEX: parseInt(hole_details[i].HoleIndex),
      SI: parseInt(hole_details[i].StrokeIndex),
      PAR: parseInt(hole_details[i].Par),
      LAT: cleanCoordinate(parseFloat(hole_details[i].Lat)),
      LONG: cleanCoordinate(parseFloat(hole_details[i].Long))
    });
  }
  //TODO: implement the appMessageQueue add instead of holes.push
  //The two loops are left over from testing
  appMessageQueue.clear();
  for (var n = 0; n < 18; n++) {
    appMessageQueue.add({
      COMMAND: commands.COMMAND_RECEIVE_COURSE_DETAILS,
      HOLE_INDEX: holes[n].HOLE_INDEX,
      SI: holes[n].SI,
      PAR: holes[n].PAR,
      LAT: holes[n].LAT,
      LONG: holes[n].LONG
    });
  }
  appMessageQueue.send();
}

// Once we've received the list of courses from Parse then
// parse them as json and then transfer them to the Pebble
function sendCourseList(data) {
  var response = JSON.parse(data);
  var courses = response.results;
  appMessageQueue.clear();
  for (var i = 0; i < courses.length; i++) {
    appMessageQueue.add({
              COMMAND: commands.COMMAND_RECEIVE_COURSES,
              COURSE_ID: courses[i].objectId,
              COURSE_NAME: courses[i].Name
            });
  }
  appMessageQueue.send();
}

// The Pebble has requested the details for a specific course - so send
// an async request for the Parse object
function getCourseDetails(courseID) {
  var xhr = new XMLHttpRequest();
  var url = 'https://api.parse.com/1/classes/Course/' + courseID;
  xhr.open('GET', url, true);
  xhr.responseType = 'json';
  xhr.setRequestHeader('X-Parse-Application-Id','cfjEGfMBX9PMvwb1ien9G5J6ttN6C3zDozBoL0Kp');
  xhr.setRequestHeader('X-Parse-REST-API-Key','a7EWINL4OUZ4lEuA4t7X9iCwQ1wPl0fRliCGnQmU');
  xhr.onload = function () {
    console.log(xhr.responseText);
    sendCourseDetails(xhr.responseText);
  };
  xhr.send();
}

// The Pebble has requested the list of courses from Parse - so send an async request for them
function getCourseList() {
  console.log('Getting course list...');
  var xhr = new XMLHttpRequest();
  var url = 'https://api.parse.com/1/classes/Course';
  xhr.open('GET', url, true);
  xhr.responseType = 'json';
  xhr.setRequestHeader('X-Parse-Application-Id','cfjEGfMBX9PMvwb1ien9G5J6ttN6C3zDozBoL0Kp');
  xhr.setRequestHeader('X-Parse-REST-API-Key','a7EWINL4OUZ4lEuA4t7X9iCwQ1wPl0fRliCGnQmU');
  xhr.onload = function () {
    console.log(xhr.responseText);
    sendCourseList(xhr.responseText);
  };
  xhr.send();
}

// Listen out for messages from the Pebble
Pebble.addEventListener("appmessage", 
function(e) { 
  if (e.payload.COMMAND !== null) {
        switch (e.payload.COMMAND) {
        // The Pebble wants to know the list of courses    
        case commands.COMMAND_LIST_COURSES:
            getCourseList();
            break;
            
        // A particular course has been selected so the Pebble needs the details
        case commands.COMMAND_SELECT_COURSE:         
            getCourseDetails(e.payload.COURSE_ID);
            break;
        
        // The current GPS position has been requested by the Pebble
        case commands.COMMAND_GET_LOCATION:         
            navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);
            break;
        }
    } else {
        appMessageQueue.clear();
    }
} 
);