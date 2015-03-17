#include <pebble.h>
#include "globals.h"
#include "main_menu.h"
#include "choose_handicap.h" 
#include "current_hole_details.h"

#define HANDICAP_KEY 1   
  
static void init(void);
static void deinit(void);
  

static void in_received_handler(DictionaryIterator *iter, void *context) 
{
  Tuple* command = dict_find(iter, KEY_COMMAND);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Msg received from phone: %d", (int)command->value->int32);
  switch(command->value->int32) {
    case COMMAND_RECEIVE_LOCATION:;
      Tuple* longitude = dict_find(iter, KEY_LONG);
      Tuple* latitude = dict_find(iter, KEY_LAT);
      update_distance((int)latitude->value->int32, (int)longitude->value->int32);      
      break;
  }
}


int main(void) {
  init();

  /*APP_LOG(APP_LOG_LEVEL_DEBUG, 
          "distance: %d", 
          calculate_distance(53.518376, -2.379803, 53.518832, -2.381675)
         );
  */       
  app_message_register_inbox_received(in_received_handler);
  app_message_open(64, 64);
  app_event_loop();
  deinit();
}

static void testholes(void) {
  for (uint8_t i = 0; i < 18; i++) {
    setup_holes(i, 3, i+1); 
  }
}

static void init(void) {
  //Use a default handicap of 18 - but see if we've stored a value in persistent storage
  set_handicap(18);
  if (persist_exists(HANDICAP_KEY)) {
    set_handicap(persist_read_int(HANDICAP_KEY));
  }
  testholes();
  show_main_menu();
}

static void deinit(void) {
  hide_main_menu();
}