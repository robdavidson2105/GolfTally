#include <pebble.h>
#include "globals.h"
#include "main_menu.h"
#include "choose_handicap.h" 
#include "current_hole_details.h"
#include "choose_course.h"

  
  
static void init(void);
static void deinit(void);
  
// handler for a message received from the phone - it's telling us that its either:
// sending a GPS location, sending a list of courses, or sending the details for a course
static void in_received_handler(DictionaryIterator *iter, void *context) 
{
  Tuple* command = dict_find(iter, KEY_COMMAND);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Msg received from phone: %d", (int)command->value->int32);
  switch(command->value->int32) {
    case COMMAND_RECEIVE_LOCATION:;
      //The dictionary should contain lat, long of our gps position
      Tuple* longitude = dict_find(iter, KEY_LONG);
      Tuple* latitude = dict_find(iter, KEY_LAT);
      //This function is in current_hole_details and should update the distance to current target
      APP_LOG(APP_LOG_LEVEL_DEBUG, "Coords received from phone - updating distance...");
      update_distance((int)latitude->value->int32, (int)longitude->value->int32);      
      break;
    
    case COMMAND_RECEIVE_COURSES:;
      //The dictionary should contain a single course id and course name
      Tuple* course_id = dict_find(iter, KEY_COURSE_ID);
      Tuple* course_name = dict_find(iter, KEY_COURSE_NAME);
      add_course(course_id->value->cstring, course_name->value->cstring);
      menu_layer_reload_data(s_course_list);
      break;
    
    case COMMAND_RECEIVE_COURSE_DETAILS:;
      Tuple* hole_index = dict_find(iter, KEY_HOLE_INDEX);
      Tuple* hole_si = dict_find(iter, KEY_SI);
      Tuple* hole_par = dict_find(iter, KEY_PAR);
      Tuple* lon = dict_find(iter, KEY_LONG);
      Tuple* lat = dict_find(iter, KEY_LAT);
/*    
      APP_LOG(APP_LOG_LEVEL_DEBUG, "Msg received - hole %d, si %d, par %d, lat %d, long %d", 
              (int)hole_index->value->int32,
              (int)hole_si->value->int32,
              (int)hole_par->value->int32,
              (int)lat->value->int32,
              (int)lon->value->int32
             );
             */
      setup_holes((uint8_t)hole_index->value->int32,
                  (uint8_t)hole_par->value->int32,
                  (uint8_t)hole_si->value->int32,
                  (double)lat->value->int32/CONVERSION_FACTOR,
                  (double)lon->value->int32/CONVERSION_FACTOR);
  }
}

// Here's the main entry point for the app
int main(void) {
  init();
  app_message_register_inbox_received(in_received_handler);
  app_message_open(64, 64);
  app_event_loop();
  deinit();
}

static void init(void) {
  // Attempt to load data from persistent storage
  restore_state();
  show_main_menu();
}

static void deinit(void) {
  save_state();
  hide_main_menu();
}