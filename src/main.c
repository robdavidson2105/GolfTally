#include <pebble.h>
#include "globals.h"
#include "main_menu.h"
#include "choose_handicap.h"  

#define HANDICAP_KEY 1   
  
static void init(void);
static void deinit(void);

void process_tuple(Tuple *t)
{
  //Get key
  int key = t->key;
 
  //Get integer value, if present
  int value = t->value->int32;
 
  //Get string value, if present
  char string_value[32];
  strcpy(string_value, t->value->cstring);
 
  //Log
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%d", key);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%d, %d, %d", string_value[0], string_value[1], string_value[2]);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%d", value);
  
}
  

static void in_received_handler(DictionaryIterator *iter, void *context) 
{
    (void) context;
     
    //Get data
    Tuple *t = dict_read_first(iter);
    while(t != NULL)
    {
        process_tuple(t);
         
        //Get next
        t = dict_read_next(iter);
    }
}


int main(void) {
  init();
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