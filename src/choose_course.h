#include <pebble.h>
  
void show_choose_course(void* callback_context);
void hide_choose_course(void);
// s_course_list is extern so we can use it to refresh the layer when it changes
extern MenuLayer *s_course_list;