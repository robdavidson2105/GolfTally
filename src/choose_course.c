#include <pebble.h>
#include "choose_course.h"
#include "globals.h"
  

MenuLayer *s_course_list;
static MenuLayer *callback_menu;
  
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, 0);
  
  // s_course_list
  s_course_list = menu_layer_create(GRect(0, 0, 144, 168));
  menu_layer_set_click_config_onto_window(s_course_list, s_window);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_course_list);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  menu_layer_destroy(s_course_list);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

// Function called when a course is selected from the menu
static void course_list_select_click(struct MenuLayer* menu, MenuIndex* cell_index, void* callback_context) {
  //set_selected_course_index(cell_index->row);
  selected_course_index = cell_index->row;
  is_round_in_progress = false;
  // Send a request to the phone to get the details of the selected course
  send_message_to_phone(COMMAND_SELECT_COURSE, selected_course_index);
  // Need to send the course ID !!
  //Dismiss this winow and return to the main menu and move the menu to Start Round
  MenuIndex idx = menu_layer_get_selected_index(callback_menu);
  idx.row = idx.row + 1;
  menu_layer_set_selected_index(callback_menu, idx, MenuRowAlignCenter, false);
  window_stack_pop(true);
  hide_choose_course();
}

static uint16_t course_list_get_num_rows(struct MenuLayer* menu, uint16_t section_index, void* callback_context) {
  return get_count_of_courses();
}

static void course_list_draw_row(GContext* ctx, const Layer* cell_layer, MenuIndex* cell_index, void* callback_context) {
  menu_cell_basic_draw(ctx, cell_layer, get_course(cell_index->row), NULL, NULL);
}

void show_choose_course(void* callback_context) {
  callback_menu = callback_context;
  initialise_ui();
  // If we haven't got any courses loaded then call the request_courses() function
  // if (get_count_of_courses() == 0) {
  reset_course_count();
  send_message_to_phone(COMMAND_LIST_COURSES, -1);
  
  menu_layer_set_callbacks(s_course_list, s_course_list, (MenuLayerCallbacks){
    .draw_row = course_list_draw_row,
    .get_num_rows = course_list_get_num_rows,
    .select_click = course_list_select_click,
  } );
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
  
}

void hide_choose_course(void) {
  window_stack_remove(s_window, true);
}
