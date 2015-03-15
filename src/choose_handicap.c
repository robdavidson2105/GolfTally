#include <pebble.h>
#include "globals.h"
#include "choose_handicap.h"
#include "current_hole_details.h"
  
#define HANDICAP_KEY 1   

static NumberWindow *s_num_window;

//Handler for the select button being pressed
static void select_handicap(NumberWindow *window, void *context) {
  //read the value of the number window
  set_handicap(number_window_get_value(s_num_window));
  //write it to persistent storage
  persist_write_int(HANDICAP_KEY, get_handicap());
  //close this window and return to previous menu
  window_stack_pop(true);
  number_window_destroy(s_num_window);
}

//Entry function for this window
void show_choose_handicap(void) {
  //Use the built-in NumberWindow function to get the player's handicap
  s_num_window = number_window_create("My handicap", (NumberWindowCallbacks) {
    .selected = select_handicap
    }, NULL);
  //Set the max handicap to 36 and the minimum to 0
  number_window_set_max(s_num_window, 36);
  number_window_set_min(s_num_window, 0);
  
  //Write the handicap value to the NumberWindow
  number_window_set_value(s_num_window, get_handicap());
  //Show the NumberWindow
  window_stack_push((Window *)s_num_window, true);
}

//Exit function for this window
void hide_choose_handicap(void) {
  number_window_destroy(s_num_window);
}
