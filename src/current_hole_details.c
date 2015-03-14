#include <pebble.h>
#include "globals.h"
#include "current_hole_details.h"
  
  
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_icon_actionbar_target;
static GBitmap *s_res_icon_actionbar_flag;
static GBitmap *s_res_icon_actionbar_club;
static GFont s_res_gothic_14;
static GFont s_res_bitham_30_black;
static GFont s_res_roboto_condensed_21;
static ActionBarLayer *s_actionbarlayer;
static TextLayer *s_hole_title;
static TextLayer *s_distance_to_target_title;
static TextLayer *s_strokes_title;
static TextLayer *s_net_title;
static TextLayer *s_points_title;
static TextLayer *s_hole_si;
static TextLayer *s_shots;
static TextLayer *s_net;
static TextLayer *s_points;
static TextLayer *s_distance_to_target;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, false);
  
  s_res_icon_actionbar_target = gbitmap_create_with_resource(RESOURCE_ID_ICON_ACTIONBAR_TARGET);
  s_res_icon_actionbar_flag = gbitmap_create_with_resource(RESOURCE_ID_ICON_ACTIONBAR_FLAG);
  s_res_icon_actionbar_club = gbitmap_create_with_resource(RESOURCE_ID_ICON_ACTIONBAR_CLUB);
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  s_res_bitham_30_black = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  // s_actionbarlayer
  s_actionbarlayer = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer, GColorWhite);
  action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_UP, s_res_icon_actionbar_target);
  action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_SELECT, s_res_icon_actionbar_flag);
  action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_DOWN, s_res_icon_actionbar_club);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer);
  
  // s_hole_title
  s_hole_title = text_layer_create(GRect(0, 0, 121, 19));
  text_layer_set_background_color(s_hole_title, GColorClear);
  text_layer_set_text_color(s_hole_title, GColorWhite);
  text_layer_set_text(s_hole_title, "Hole 1 - Par 3");
  text_layer_set_text_alignment(s_hole_title, GTextAlignmentCenter);
  text_layer_set_font(s_hole_title, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_hole_title);
  
  // s_distance_to_target_title
  s_distance_to_target_title = text_layer_create(GRect(2, 43, 118, 16));
  text_layer_set_background_color(s_distance_to_target_title, GColorClear);
  text_layer_set_text_color(s_distance_to_target_title, GColorWhite);
  text_layer_set_text(s_distance_to_target_title, "Distance to pin");
  text_layer_set_text_alignment(s_distance_to_target_title, GTextAlignmentCenter);
  text_layer_set_font(s_distance_to_target_title, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_distance_to_target_title);
  
  // s_strokes_title
  s_strokes_title = text_layer_create(GRect(2, 94, 38, 17));
  text_layer_set_text(s_strokes_title, "Shots");
  text_layer_set_text_alignment(s_strokes_title, GTextAlignmentCenter);
  text_layer_set_font(s_strokes_title, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_strokes_title);
  
  // s_net_title
  s_net_title = text_layer_create(GRect(42, 94, 38, 17));
  text_layer_set_text(s_net_title, "Net");
  text_layer_set_text_alignment(s_net_title, GTextAlignmentCenter);
  text_layer_set_font(s_net_title, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_net_title);
  
  // s_points_title
  s_points_title = text_layer_create(GRect(82, 94, 38, 17));
  text_layer_set_text(s_points_title, "Pts");
  text_layer_set_text_alignment(s_points_title, GTextAlignmentCenter);
  text_layer_set_font(s_points_title, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_points_title);
  
  // s_hole_si
  s_hole_si = text_layer_create(GRect(1, 16, 120, 16));
  text_layer_set_background_color(s_hole_si, GColorClear);
  text_layer_set_text_color(s_hole_si, GColorWhite);
  text_layer_set_text(s_hole_si, "SI 18 - Strokes rec'd 2");
  text_layer_set_text_alignment(s_hole_si, GTextAlignmentCenter);
  text_layer_set_font(s_hole_si, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_hole_si);
  
  // s_shots
  s_shots = text_layer_create(GRect(2, 113, 38, 36));
  text_layer_set_text(s_shots, "10");
  text_layer_set_text_alignment(s_shots, GTextAlignmentCenter);
  text_layer_set_font(s_shots, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_shots);
  
  // s_net
  s_net = text_layer_create(GRect(42, 113, 38, 36));
  text_layer_set_text(s_net, "2");
  text_layer_set_text_alignment(s_net, GTextAlignmentCenter);
  text_layer_set_font(s_net, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_net);
  
  // s_points
  s_points = text_layer_create(GRect(82, 113, 38, 36));
  text_layer_set_text(s_points, "3");
  text_layer_set_text_alignment(s_points, GTextAlignmentCenter);
  text_layer_set_font(s_points, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_points);
  
  // s_distance_to_target
  s_distance_to_target = text_layer_create(GRect(4, 60, 113, 23));
  text_layer_set_background_color(s_distance_to_target, GColorClear);
  text_layer_set_text_color(s_distance_to_target, GColorWhite);
  text_layer_set_text(s_distance_to_target, "350 Yds");
  text_layer_set_text_alignment(s_distance_to_target, GTextAlignmentCenter);
  text_layer_set_font(s_distance_to_target, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_distance_to_target);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  action_bar_layer_destroy(s_actionbarlayer);
  text_layer_destroy(s_hole_title);
  text_layer_destroy(s_distance_to_target_title);
  text_layer_destroy(s_strokes_title);
  text_layer_destroy(s_net_title);
  text_layer_destroy(s_points_title);
  text_layer_destroy(s_hole_si);
  text_layer_destroy(s_shots);
  text_layer_destroy(s_net);
  text_layer_destroy(s_points);
  text_layer_destroy(s_distance_to_target);
  gbitmap_destroy(s_res_icon_actionbar_target);
  gbitmap_destroy(s_res_icon_actionbar_flag);
  gbitmap_destroy(s_res_icon_actionbar_club);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void display_shots(uint8_t hole_index) {
  static char shots[] = "10";
  snprintf(shots, sizeof(shots), "%d", get_my_strokes(hole_index));
  text_layer_set_text(s_shots, shots);
}

void show_current_hole_details(uint8_t hole_index) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  static char hole_number[] = "Hole 18 - Par 3";
  snprintf(hole_number, sizeof(hole_number), "Hole %d - Par %d", hole_index+1, get_par(hole_index));
  display_shots(hole_index);
  
  APP_LOG(APP_LOG_LEVEL_DEBUG,"Show hole number");
  APP_LOG(APP_LOG_LEVEL_DEBUG,hole_number);
  text_layer_set_text(s_hole_title, hole_number);
  
  window_stack_push(s_window, true);
}

void hide_current_hole_details(void) {
  window_stack_remove(s_window, true);
}
