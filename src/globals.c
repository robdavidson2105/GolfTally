#include <pebble.h>
#include "globals.h"

#define PI 3.14159265  

#define HANDICAP_KEY 1 
#define COURSE_NAME_KEY 10
#define COURSE_ID_KEY 11
#define HOLE_KEY 100
#define PAR_KEY 20
#define SI_KEY 40
#define LAT_KEY 50
#define LON_KEY 60
#define WAYPOINT_DESCRIPTION_KEY 70
  
// Gathered together a number of global functions here - there's probably an easier way to avoid
// doing this - but hey, it works!
  
static uint8_t handicap;
uint8_t count_of_courses = 0;
int8_t selected_course_index = -1;
static bool round_in_progress = false;
bool refresh_gps = false;

typedef struct {
  double latitude;
  double longitude;
  char description[20];
} waypoint;

struct holes {
  uint8_t par;
  uint8_t si;
  waypoint waypoints[NUMBER_OF_WAYPOINTS];
  uint8_t my_strokes;
  uint8_t my_shots_received;
  int8_t my_net;
  int8_t my_points;
} hole[18];

struct courses {
  char course_id[11];
  char course_name[20];
} course[20];

void add_course(char* course_id, char* course_name) {
  snprintf(course[count_of_courses].course_id, 11, "%s", course_id);
  snprintf(course[count_of_courses].course_name, 20, "%s", course_name);
  count_of_courses++;
}

char* get_course(uint8_t course_index) {
  return course[course_index].course_name;
}

char* get_course_id(uint8_t course_index) {
  return course[course_index].course_id;
}

//TODO - reset and clear array
void reset_course_count(void) {
  count_of_courses = 0;
}

uint8_t get_count_of_courses(void) {
  return count_of_courses;
}
int8_t get_selected_course_index() {
  return selected_course_index;
}

void set_selected_course_index(int8_t course_index) {
  selected_course_index = course_index;
}

bool is_round_in_progress(void) {
  return round_in_progress;
}
void set_round_in_progress(void) {
  round_in_progress = true;
}
void clear_round_in_progress(void) {
  round_in_progress = false;
}

void set_handicap(uint8_t new_handicap) {
  handicap = new_handicap;
  if (selected_course_index != -1) {
    for (uint8_t i=0; i <18; i++) {
      //if the handicap changed and we've started a round
      //then need to update the score - so we call set strokes just in case...
      hole[i].my_shots_received = calculate_shots(hole[i].si, handicap);
      set_my_strokes(i, get_my_strokes(i));
    }
  }
}

uint8_t get_handicap(void) {
  return handicap;
}

uint8_t get_par(uint8_t hole_index) {
  return hole[hole_index].par;
};
uint8_t get_si(uint8_t hole_index) {
  return hole[hole_index].si;
};

int8_t get_my_net(uint8_t hole_index) {
  return hole[hole_index].my_net;
};

int8_t get_my_points(uint8_t hole_index) {
  return hole[hole_index].my_points;
};

uint8_t get_my_shots_received(uint8_t hole_index) {
  return hole[hole_index].my_shots_received;
};

uint8_t get_my_strokes(uint8_t hole_index) {
  return hole[hole_index].my_strokes;
};

double get_latitude(uint8_t hole_index, uint8_t waypoint_index) {
  return hole[hole_index].waypoints[waypoint_index].latitude;
}

double get_longitude(uint8_t hole_index, uint8_t waypoint_index) {
  return hole[hole_index].waypoints[waypoint_index].longitude;
}

char* get_waypoint_description(uint8_t hole_index, uint8_t waypoint_index) {
  return hole[hole_index].waypoints[waypoint_index].description;
}

void set_my_strokes(uint8_t hole_index, int8_t new_strokes) {
  if (new_strokes <= 0) {
    hole[hole_index].my_strokes = 0;
    hole[hole_index].my_net = 0;
    hole[hole_index].my_points = 0;
    return;
  }
  hole[hole_index].my_strokes = new_strokes;
  hole[hole_index].my_net = new_strokes - hole[hole_index].my_shots_received;
  hole[hole_index].my_points = 2 - (hole[hole_index].my_net - hole[hole_index].par);
  if (hole[hole_index].my_points < 0) {
    hole[hole_index].my_points = 0;
  }
};

void setup_holes(uint8_t hole_index, uint8_t par, uint8_t si) {
  hole[hole_index].par = par;
  hole[hole_index].si = si;
  hole[hole_index].my_strokes = 0;
  hole[hole_index].my_net = 0;
  hole[hole_index].my_points = 0;
  hole[hole_index].my_shots_received = calculate_shots(si, get_handicap());
};

void setup_waypoints(uint8_t hole_index, uint8_t waypoint_index, double latitude, double longitude, char* description) {
  hole[hole_index].waypoints[waypoint_index].latitude = latitude;
  hole[hole_index].waypoints[waypoint_index].longitude = longitude;
  snprintf(hole[hole_index].waypoints[waypoint_index].description, 30, "%s", description);
}

uint8_t calculate_shots(uint8_t si, uint8_t handicap) {
  uint8_t shots = 0;
  if (handicap >= si) {
    shots++;
    handicap = handicap - 18;
    if (handicap >= si) {
      shots++;
    }
  }
  return shots;
}

// This is a cosine approximation function - since we don't have math.h
double cosine(double x) {
  double cos = 0.0;
  x += 1.57079632;
  if (x >  3.14159265)
      x -= 6.28318531;
    if (x < 0) { 
    cos = 1.27323954 * x + 0.405284735 * x * x;
    
    if (cos < 0)
        cos = .225 * (cos *-cos - cos) + cos;
    else
        cos = .225 * (cos * cos - cos) + cos;
    }
    else
    {
    cos = 1.27323954 * x - 0.405284735 * x * x;

    if (cos < 0)
        cos = .225 * (cos *-cos - cos) + cos;
    else
        cos = .225 * (cos * cos - cos) + cos;
    }
  return cos;
}

// This is a square root approximation function - since no math support
#define SQRT_MAGIC_F 0x5f3759df 
float my_sqrt(const float x)
{
  const float xhalf = 0.5f*x;
 
  union // get bits for floating value
  {
    float x;
    int i;
  } u;
  u.x = x;
  u.i = SQRT_MAGIC_F - (u.i >> 1);  // gives initial guess y0
  return x*u.x*(1.5f - xhalf*u.x*u.x);// Newton step, repeating increases accuracy 
}

// calculate distances between two points on surface of sphere - the calculation is an approximation,
// the cosine function is an approximation, and the square root function isn't exact either .....
// put it all together and its as accurate as my golf shots 
int calculate_distance(double lat1, double long1, double lat2, double long2) {
  lat1 = PI * lat1 / 180.0;
  lat2 = PI * lat2 / 180.0;
  long1 = PI * long1 / 180.0;
  long2 = PI * long2 / 180.0;
  double x = long2 - long1;
  x = x * cosine((lat1 + lat2)/2.0);
  double y = lat2 - lat1;
  double distance = x * x + y * y ;
  distance = 6967325 * my_sqrt(distance);
  return (int)(distance);
}

void save_state(void) {
  // SWITCH OFF SAVING/RESTORING STATE UNTIL FIXED IT
  return;
  int8_t course_index = get_selected_course_index();
  if (course_index == -1) {
    // There's no courses selected so nothing to save so bail out
    return;
  }
  persist_write_string(COURSE_NAME_KEY, course[course_index].course_name);
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Written course_name: %s", course[course_index].course_name);
  persist_write_string(COURSE_ID_KEY, course[course_index].course_id);
  
  // We'll use a byte array to store some of the data - using write_int was crashing watch
  uint8_t pars_and_SI[36];
  
  for (int i = 0; i < 18; i++) {
    pars_and_SI[i * 2] = hole[i].par;
    pars_and_SI[i * 2 + 1] = hole[i].si;
    persist_write_data(HOLE_KEY, pars_and_SI, sizeof(pars_and_SI));
    for (int n = 0; n < NUMBER_OF_WAYPOINTS; n++) {
      int lat = (int)(hole[i].waypoints[n].latitude * CONVERSION_FACTOR);
      int lon = (int)(hole[i].waypoints[n].longitude * CONVERSION_FACTOR);
      
      if (lat !=0  && lon !=0) {
        persist_write_int(HOLE_KEY * i + (LAT_KEY + n), lat);
        persist_write_int(HOLE_KEY * i + (LON_KEY + n), lon);
        persist_write_string(HOLE_KEY * i + WAYPOINT_DESCRIPTION_KEY + n, hole[i].waypoints[n].description);
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Writing waypoint: %s", hole[i].waypoints[n].description);
      } else {
        // Tidyup unwanted keys
        if (persist_exists(HOLE_KEY * i + LAT_KEY + n)) {persist_delete(HOLE_KEY * i + LAT_KEY + n);}
        if (persist_exists(HOLE_KEY * i + LON_KEY + n)) {persist_delete(HOLE_KEY * i + LON_KEY + n);}
        if (persist_exists(HOLE_KEY * i + WAYPOINT_DESCRIPTION_KEY + n)) {
          persist_delete(HOLE_KEY * i + WAYPOINT_DESCRIPTION_KEY + n);
        }
      }
      
    }
  }
  
}

void restore_state(void) {
  // Use a default handicap of 18 - but see if we've stored a value in persistent storage
  set_handicap(18);
  if (persist_exists(HANDICAP_KEY)) {
    set_handicap(persist_read_int(HANDICAP_KEY));
  }
  // SWITCH OFF SAVING/RESTORING STATE UNTIL FIXED IT
  return;
  
  // Now lets see if we've got the details of a course cached in storage
  if (!persist_exists(COURSE_NAME_KEY)) {
    // bail out of function if no courses found
    return;
  }
  if (!persist_exists(COURSE_ID_KEY)) {
    // bail out of function if not course id found
    return;
  }
  
  // So at this point we must have a course cached - so lets load all the details
  bool no_errors = true;  // .... but lets watch out for any errors in loading
  char course_id[11];
  char course_name[20];
  persist_read_string(COURSE_NAME_KEY, course_name, sizeof(course_name));
  persist_read_string(COURSE_ID_KEY, course_id, sizeof(course_id));
  add_course(course_id, course_name);
  selected_course_index = 0;
  
  // Read pars and SIs from byte array storage
  uint8_t pars_and_SI[36];
  persist_read_data(HOLE_KEY, pars_and_SI, sizeof(pars_and_SI));
  
  for (int i = 0; i < 18; i++) {
    hole[i].par = pars_and_SI[i * 2];
    hole[i].si = pars_and_SI[i * 2 + 1];
    for (int n = 0; n < 6; n++)
      {
      if (persist_exists(HOLE_KEY * i + WAYPOINT_DESCRIPTION_KEY + n)) {
        hole[i].waypoints[n].latitude = (double)persist_read_int(HOLE_KEY * i + LAT_KEY + n)/CONVERSION_FACTOR;
        hole[i].waypoints[n].longitude = (double)persist_read_int(HOLE_KEY * i + LON_KEY + n)/CONVERSION_FACTOR;
        persist_read_string(HOLE_KEY * i + WAYPOINT_DESCRIPTION_KEY + n,
                          hole[i].waypoints[n].description,
                          sizeof(hole[i].waypoints[n].description)
                         );
/*      
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Retrieved - hole %d, si %d, par %d, lat %d, long %d, desc %s", 
              (int)i,
              (int)hole[i].par,
              (int)hole[i].si,
              (int)(hole[i].waypoints[n].latitude * CONVERSION_FACTOR),
              (int)(hole[i].waypoints[n].longitude * CONVERSION_FACTOR),
              hole[i].waypoints[n].description
             );  */
      }
    }
  }
  // Now calculate the shots received for the current handicap
  // just use the set_handicap function
  set_handicap(get_handicap());
}
