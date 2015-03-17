#include <pebble.h>
#define KEY_COMMAND 0
#define KEY_HOLE_INDEX 1
#define KEY_SI 2
#define KEY_PAR 3
#define KEY_LAT 4
#define KEY_LONG 5

#define COMMAND_LIST_COURSES 0
#define COMMAND_SELECT_COURSE 1
#define COMMAND_GET_LOCATION 2
#define COMMAND_RECEIVE_COURSES 3
#define COMMAND_RECEIVE_LOCATION  4 
  

/*  
enum {
  KEY_COMMAND       = 0,
  KEY_HOLE_INDEX    = 1,
  KEY_SI            = 2,
  KEY_PAR           = 3,
  KEY_LAT           = 4,
  KEY_LONG          = 5
};
  
enum {
  COMMAND_LIST_COURSES   = 0,
  COMMAND_SELECT_COURSE  = 1,
  COMMAND_GET_LOCATION   = 2,
  COMMAND_RECEIVE_COURSES = 3,
  COMMAND_RECEIVE_LOCATION = 4
};  
*/ 
void set_handicap(uint8_t new_handicap);
uint8_t get_handicap(void);

uint8_t get_par(uint8_t hole_index);
uint8_t get_si(uint8_t hole_index);
int8_t get_my_net(uint8_t hole_index);
int8_t get_my_points(uint8_t hole_index);
uint8_t get_my_strokes(uint8_t hole_index);
uint8_t get_my_shots_received(uint8_t hole_index);
void set_my_strokes(uint8_t hole_index, int8_t new_strokes);
void setup_holes(uint8_t hole_index, uint8_t par, uint8_t si);

uint8_t calculate_shots(uint8_t si, uint8_t handicap);

double cosine(double x);
int calculate_distance(double lat1, double long1, double lat2, double long2);

