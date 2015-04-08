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
  if (command->value->int32 == COMMAND_RECEIVE_LOCATION) {
      //The dictionary should contain lat, long of our gps position
      Tuple* longitude = dict_find(iter, KEY_LONG);
      Tuple* latitude = dict_find(iter, KEY_LAT);
      
      //This function is in current_hole_details and should update the distance to current target
      
      // Just check that refresh_gps is still true - this is a callback, so the value
      // could've changed in the meantime
      if (refresh_gps) {
        update_distance((int32_t)latitude->value->int32, (int32_t)longitude->value->int32);
      }
  }
  
  if (command->value->int32 == COMMAND_RECEIVE_COURSES) { 
      //The dictionary should contain a single course id and course name
      Tuple* course_id = dict_find(iter, KEY_COURSE_ID);
      Tuple* course_name = dict_find(iter, KEY_COURSE_NAME);
      add_course(course_id->value->cstring, course_name->value->cstring);
      menu_layer_reload_data(s_course_list);
      layer_mark_dirty(menu_layer_get_layer(s_course_list));
  }
  
  if (command->value->int32 == COMMAND_RECEIVE_COURSE_DETAILS) {     
      Tuple* hole_index = dict_find(iter, KEY_HOLE_INDEX);
      Tuple* hole_si = dict_find(iter, KEY_SI);
      Tuple* hole_par = dict_find(iter, KEY_PAR);
              
      setup_holes((uint8_t)hole_index->value->int32,
                  (uint8_t)hole_par->value->int32,
                  (uint8_t)hole_si->value->int32
                  );
   }
    
   if (command->value->int32 == COMMAND_RECEIVE_WAYPOINTS) {
      Tuple* this_hole_index = dict_find(iter, KEY_HOLE_INDEX);
      Tuple* waypoint_index = dict_find(iter, KEY_WAYPOINT_INDEX);
      Tuple* waypoint_description = dict_find(iter, KEY_WAYPOINT_DESCRIPTION);
      Tuple* lon = dict_find(iter, KEY_LONG);
      Tuple* lat = dict_find(iter, KEY_LAT);
    
      setup_waypoints((uint8_t)this_hole_index->value->int32,
                      (uint8_t)waypoint_index->value->int32,
                      lat->value->int32,
                      lon->value->int32,
                      waypoint_description->value->cstring);
   }

}

// Here's the main entry point for the app
int main(void) {
  init();
  app_message_register_inbox_received(in_received_handler);
  app_message_open(128, 32);
  app_event_loop();
  deinit();
}

static void init(void) {
  // Attempt to load data from persistent storage
  restore_state();
  show_main_menu();
}

static void deinit(void) {
  hide_main_menu();
}