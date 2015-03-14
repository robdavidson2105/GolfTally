#include <pebble.h>
#include "choose_course.h"
#include "globals.h"
  
  
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, false);
}

static void destroy_ui(void) {
  window_destroy(s_window);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_choose_course(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_choose_course(void) {
  window_stack_remove(s_window, true);
}
