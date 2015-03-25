#include <pebble.h>
#include "globals.h"

#define PI 3.14159265  

#define HANDICAP_KEY 1 
#define COURSE_NAME_KEY 10
#define COURSE_ID_KEY 11
#define PAR_KEY 20
#define SI_KEY 40
#define LAT_KEY 60
#define LON_KEY 80
  
// Gathered together a number of global functions here - there's probably an easier way to avoid
// doing this - but hey, it works!
  
static uint8_t handicap;
uint8_t count_of_courses = 0;
int8_t selected_course_index = -1;
static bool round_in_progress = false;

struct holes {
  uint8_t par;
  uint8_t si;
  double latitude;
  double longitude;
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

double get_latitude(uint8_t hole_index) {
  return hole[hole_index].latitude;
}

double get_longitude(uint8_t hole_index) {
  return hole[hole_index].longitude;
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

void setup_holes(uint8_t hole_index, uint8_t par, uint8_t si, double latitude, double longitude) {
  hole[hole_index].par = par;
  hole[hole_index].si = si;
  hole[hole_index].latitude = latitude;
  hole[hole_index].longitude = longitude;
  hole[hole_index].my_strokes = 0;
  hole[hole_index].my_net = 0;
  hole[hole_index].my_points = 0;
  hole[hole_index].my_shots_received = calculate_shots(si, get_handicap());
};

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
  int8_t course_index = get_selected_course_index();
  if (course_index == -1) {
    // There's no courses selected so nothing to save so bail out
    return;
  }
  persist_write_string(COURSE_NAME_KEY, course[course_index].course_name);
  persist_write_string(COURSE_ID_KEY, course[course_index].course_id);
  
  for (int i = 0; i < 18; i++) {
    persist_write_int(PAR_KEY + i, hole[i].par);
    persist_write_int(SI_KEY + i, hole[i].si);
    persist_write_int(LAT_KEY + i, (int)(hole[i].latitude * CONVERSION_FACTOR));
    persist_write_int(LON_KEY + i, (int)(hole[i].longitude * CONVERSION_FACTOR));
    /*
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Writing - hole %d, si %d, par %d, lat %d, long %d", 
              (int)i,
              (int)hole[i].par,
              (int)hole[i].si,
              (int)(hole[i].latitude * CONVERSION_FACTOR),
              (int)(hole[i].longitude * CONVERSION_FACTOR)
             );
             */
  }
  
}

void restore_state(void) {
  // Use a default handicap of 18 - but see if we've stored a value in persistent storage
  set_handicap(18);
  if (persist_exists(HANDICAP_KEY)) {
    set_handicap(persist_read_int(HANDICAP_KEY));
  }
  
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
  for (int i = 0; i < 18; i++) {
    hole[i].par = persist_read_int(PAR_KEY + i);
    hole[i].si = persist_read_int(SI_KEY + i);
    hole[i].latitude = (double)persist_read_int(LAT_KEY + i)/CONVERSION_FACTOR;
    hole[i].longitude = (double)persist_read_int(LON_KEY + i)/CONVERSION_FACTOR;
    /*
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Retrieved - hole %d, si %d, par %d, lat %d, long %d", 
              (int)i,
              (int)hole[i].par,
              (int)hole[i].si,
              (int)(hole[i].latitude * CONVERSION_FACTOR),
              (int)(hole[i].longitude * CONVERSION_FACTOR)
             );
             */
  }
  
}
