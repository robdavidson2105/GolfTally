#include <pebble.h>
#define KEY_COMMAND 0
#define KEY_HOLE_INDEX 1
#define KEY_SI 2
#define KEY_PAR 3
#define KEY_LAT 4
#define KEY_LONG 5
#define KEY_COURSE_ID 6
#define KEY_COURSE_NAME 7

#define COMMAND_LIST_COURSES 0
#define COMMAND_SELECT_COURSE 1
#define COMMAND_GET_LOCATION 2
#define COMMAND_RECEIVE_COURSES 3
#define COMMAND_RECEIVE_LOCATION 4 
#define COMMAND_RECEIVE_COURSE_DETAILS 5
  
#define CONVERSION_FACTOR 1000000
   
void set_handicap(uint8_t new_handicap);
uint8_t get_handicap(void);
uint8_t get_count_of_courses(void);
void add_course(uint8_t course_id, char* course_name);
char* get_course(uint8_t course_index);
int8_t get_selected_course_index();
void set_selected_course_index(int8_t course_index);
void reset_course_count(void);
bool is_round_in_progress(void);
void set_round_in_progress(void);
void clear_round_in_progress(void);

uint8_t get_par(uint8_t hole_index);
uint8_t get_si(uint8_t hole_index);
int8_t get_my_net(uint8_t hole_index);
int8_t get_my_points(uint8_t hole_index);
uint8_t get_my_strokes(uint8_t hole_index);
uint8_t get_my_shots_received(uint8_t hole_index);
void set_my_strokes(uint8_t hole_index, int8_t new_strokes);
void setup_holes(uint8_t hole_index, uint8_t par, uint8_t si, double latitude, double longitude);

uint8_t calculate_shots(uint8_t si, uint8_t handicap);

double cosine(double x);
int calculate_distance(double lat1, double long1, double lat2, double long2);


