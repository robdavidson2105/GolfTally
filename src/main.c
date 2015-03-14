#include <pebble.h>
#include "globals.h"
#include "main_menu.h"
#include "choose_handicap.h"  

#define HANDICAP_KEY 1   
  
static void init(void);
static void deinit(void);

int main(void) {
  init();
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
  //APP_LOG(APP_LOG_LEVEL_DEBUG,"Handicap: %d", handicap);
}