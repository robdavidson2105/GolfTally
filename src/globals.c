#include <pebble.h>
#include "globals.h"

#define PI 3.14159265  

#define HANDICAP_KEY 1 
/*  
#define COURSE_NAME_KEY 10
#define COURSE_ID_KEY 11
#define HOLE_KEY 100
#define PAR_KEY 20
#define SI_KEY 40
#define LAT_KEY 50
#define LON_KEY 60
#define WAYPOINT_DESCRIPTION_KEY 70  */
  
// Gathered together a number of global functions here - there's probably an easier way to avoid
// doing this - but hey, it works!
  
static uint8_t handicap;
static uint8_t count_of_courses = 0;
int8_t selected_course_index = -1;
bool is_round_in_progress = false;
bool refresh_gps = false;

typedef struct {
  int32_t latitude;
  int32_t longitude;
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

void send_message_to_phone(uint8_t command, int8_t course_index) {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  Tuplet value = TupletInteger(KEY_COMMAND, command);
  dict_write_tuplet(iter, &value);
  if (course_index != -1) {
    Tuplet value = TupletCString(KEY_COURSE_ID, get_course_id(course_index));
    dict_write_tuplet(iter, &value);
  }
  app_message_outbox_send();
}

uint8_t set_handicap(uint8_t new_handicap) {
  handicap = new_handicap;
  if (selected_course_index != -1) {
    for (uint8_t i=0; i <18; i++) {
      //if the handicap changed and we've started a round
      //then need to update the score - so we call set strokes just in case...
      hole[i].my_shots_received = calculate_shots(hole[i].si, handicap);
      set_my_strokes(i, get_my_strokes(i));
    }
  }
  return 0;
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

int32_t get_latitude(uint8_t hole_index, uint8_t waypoint_index) {
  return hole[hole_index].waypoints[waypoint_index].latitude;
}

int32_t get_longitude(uint8_t hole_index, uint8_t waypoint_index) {
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

void setup_waypoints(uint8_t hole_index, uint8_t waypoint_index, int32_t latitude, int32_t longitude, char* description) {
  hole[hole_index].waypoints[waypoint_index].latitude = latitude;
  hole[hole_index].waypoints[waypoint_index].longitude = longitude;
  snprintf(hole[hole_index].waypoints[waypoint_index].description, 20, "%s", description);
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
uint16_t calculate_distance(int32_t lat1, int32_t long1, int32_t lat2, int32_t long2) {
  double d_lat1 = PI * (double)lat1 / 180.0 / CONVERSION_FACTOR;
  double d_lat2 = PI * (double)lat2 / 180.0 / CONVERSION_FACTOR;
  double x = ((double)long2 - (double)long1) * PI / 180.0 / CONVERSION_FACTOR ;
  x = x * cosine((d_lat1 + d_lat2)/2.0);
  double y = d_lat2 - d_lat1;
  uint16_t distance = 6967325 * my_sqrt(x * x + y * y);
  //distance = 6967325 * my_sqrt(distance);
  return (distance);
}

void restore_state(void) {
  // Use a default handicap of 18 - but see if we've stored a value in persistent storage
  set_handicap(18);
  if (persist_exists(HANDICAP_KEY)) {
    set_handicap(persist_read_int(HANDICAP_KEY));
  }
  set_handicap(get_handicap());
}
