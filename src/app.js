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
    LAT: cleanCoordinate(pos.coords.latitude),
    LONG: cleanCoordinate(pos.coords.longitude)
  });
  appMessageQueue.send();
}

function locationError(err) {
console.log('location error (' + err.code + '): ' + err.message);
}

function sendCourseDetails(data) {
  console.log('Received course details from Parse...');
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
  console.log(JSON.stringify(holes));
  
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
  console.log('Sending course details to Pebble...');
  appMessageQueue.send();
}

function sendCourseList(data) {
  console.log('Response received...');
  console.log(JSON.stringify(data));
  var response = JSON.parse(data);
  var courses = response.results;
  console.log(JSON.stringify(response));
  console.log(courses[0].Name);
  console.log("Number of courses: " + courses.length);
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

function getCourseDetails(courseID) {
  console.log('Getting course details...');
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

function getCourseList() {
  console.log('Getting course list...');
  var xhr = new XMLHttpRequest();
  var url = 'https://api.parse.com/1/classes/Course';
  //var url = 'https://cfjEGfMBX9PMvwb1ien9G5J6ttN6C3zDozBoL0Kp:javascript-key=E4gtLnecX313jK3D8iSbreyDKUyt09aKTaw8A6Ki@api.parse.com/1/classes/Course';
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
Pebble.addEventListener("appmessage", 
function(e) { 
  console.log("Received " + e.payload.COMMAND );
  if (e.payload.COMMAND !== null) {
        switch (e.payload.COMMAND) {
        case commands.COMMAND_LIST_COURSES:
            //console.log("List Courses");
            getCourseList();
            break;
            
        case commands.COMMAND_SELECT_COURSE:         
            console.log("Select Course " + e.payload.COURSE_ID);
            getCourseDetails(e.payload.COURSE_ID);
            break;
            
        case commands.COMMAND_GET_LOCATION:         
            //console.log("Get Location");
            navigator.geolocation.getCurrentPosition(locationSuccess, locationError, locationOptions);
            break;
        }
 
    } else {
        appMessageQueue.clear();
    }
  
} 
);