#include <pebble.h>
#include "globals.h"
#include "current_hole_details.h"
#include "scorecard.h"

  
static uint8_t current_hole_index;
static uint8_t current_waypoint_index;
static int32_t last_lat;
static int32_t last_lon;
static MenuLayer *callback_menu;
//static AppTimer *timer_handle;
  
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_icon_actionbar_target;
static GBitmap *s_res_icon_actionbar_flag;
static GBitmap *s_res_icon_actionbar_club;
static GFont s_res_roboto_condensed_21;
static GFont s_res_gothic_18;
static GFont s_res_bitham_30_black;
static ActionBarLayer *s_actionbarlayer;
static TextLayer *s_hole_title;
static TextLayer *s_distance_to_target_title;
static TextLayer *s_strokes_title;
static TextLayer *s_net_title;
static TextLayer *s_points_title;
static TextLayer *s_shots;
static TextLayer *s_net;
static TextLayer *s_points;
static TextLayer *s_distance_to_target;
static TextLayer *s_hole_subtitle;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, false);
  
  s_res_icon_actionbar_target = gbitmap_create_with_resource(RESOURCE_ID_ICON_ACTIONBAR_TARGET);
  s_res_icon_actionbar_flag = gbitmap_create_with_resource(RESOURCE_ID_ICON_ACTIONBAR_FLAG);
  s_res_icon_actionbar_club = gbitmap_create_with_resource(RESOURCE_ID_ICON_ACTIONBAR_CLUB);
  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  s_res_bitham_30_black = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
  // s_actionbarlayer
  s_actionbarlayer = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbarlayer, s_window);
  action_bar_layer_set_background_color(s_actionbarlayer, GColorWhite);
  action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_UP, s_res_icon_actionbar_target);
  action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_SELECT, s_res_icon_actionbar_flag);
  action_bar_layer_set_icon(s_actionbarlayer, BUTTON_ID_DOWN, s_res_icon_actionbar_club);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_actionbarlayer);
  
  // s_hole_title
  s_hole_title = text_layer_create(GRect(0, 0, 123, 25));
  text_layer_set_background_color(s_hole_title, GColorClear);
  text_layer_set_text_color(s_hole_title, GColorWhite);
  text_layer_set_text(s_hole_title, "18 - Par 3");
  text_layer_set_text_alignment(s_hole_title, GTextAlignmentCenter);
  text_layer_set_font(s_hole_title, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_hole_title);
  
  // s_distance_to_target_title
  s_distance_to_target_title = text_layer_create(GRect(2, 41, 118, 24));
  text_layer_set_background_color(s_distance_to_target_title, GColorClear);
  text_layer_set_text_color(s_distance_to_target_title, GColorWhite);
  text_layer_set_text(s_distance_to_target_title, "Select target..");
  text_layer_set_text_alignment(s_distance_to_target_title, GTextAlignmentCenter);
  text_layer_set_font(s_distance_to_target_title, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_distance_to_target_title);
  
  // s_strokes_title
  s_strokes_title = text_layer_create(GRect(2, 94, 38, 17));
  text_layer_set_text(s_strokes_title, "Shots");
  text_layer_set_text_alignment(s_strokes_title, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_strokes_title);
  
  // s_net_title
  s_net_title = text_layer_create(GRect(42, 94, 38, 17));
  text_layer_set_text(s_net_title, "Net");
  text_layer_set_text_alignment(s_net_title, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_net_title);
  
  // s_points_title
  s_points_title = text_layer_create(GRect(82, 94, 38, 17));
  text_layer_set_text(s_points_title, "Pts");
  text_layer_set_text_alignment(s_points_title, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_points_title);
  
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
  s_distance_to_target = text_layer_create(GRect(4, 60, 113, 35));
  text_layer_set_background_color(s_distance_to_target, GColorClear);
  text_layer_set_text_color(s_distance_to_target, GColorWhite);
  text_layer_set_text(s_distance_to_target, "---");
  text_layer_set_text_alignment(s_distance_to_target, GTextAlignmentCenter);
  text_layer_set_font(s_distance_to_target, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_distance_to_target);
  
  // s_hole_subtitle
  s_hole_subtitle = text_layer_create(GRect(0, 20, 124, 24));
  text_layer_set_background_color(s_hole_subtitle, GColorClear);
  text_layer_set_text_color(s_hole_subtitle, GColorWhite);
  text_layer_set_text(s_hole_subtitle, "SI 18 - 2 shots");
  text_layer_set_text_alignment(s_hole_subtitle, GTextAlignmentCenter);
  text_layer_set_font(s_hole_subtitle, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_hole_subtitle);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  action_bar_layer_destroy(s_actionbarlayer);
  text_layer_destroy(s_hole_title);
  text_layer_destroy(s_distance_to_target_title);
  text_layer_destroy(s_strokes_title);
  text_layer_destroy(s_net_title);
  text_layer_destroy(s_points_title);
  text_layer_destroy(s_shots);
  text_layer_destroy(s_net);
  text_layer_destroy(s_points);
  text_layer_destroy(s_distance_to_target);
  text_layer_destroy(s_hole_subtitle);
  gbitmap_destroy(s_res_icon_actionbar_target);
  gbitmap_destroy(s_res_icon_actionbar_flag);
  gbitmap_destroy(s_res_icon_actionbar_club);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  refresh_gps = false;
  send_message_to_phone(COMMAND_CLEAR_LOCATION_UPDATES, -1);
  destroy_ui();
}

//Function to update the display with the latest score
void display_shots(void) {
  static char shots[3];
  static char net[3];
  static char points[3];
  snprintf(shots, sizeof(shots), "%d", get_my_strokes(current_hole_index));
  text_layer_set_text(s_shots, shots);
  snprintf(net, sizeof(net), "%d", get_my_net(current_hole_index));
  text_layer_set_text(s_net, net);
  snprintf(points, sizeof(points), "%d", get_my_points(current_hole_index));
  text_layer_set_text(s_points, points);
}



static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  // Send a request to the phone to update the current location
  // and we'll then receive updates from the phone
  
  // Avoid requesting multiple updates - things go wrong!
  current_waypoint_index++;
  
  // We can only have 6 waypoints so cycle back round
  if (current_waypoint_index > 5) {
    current_waypoint_index = 0;
  }
  
  // If there's no description on the next waypoint then cycle back round
  if (strlen(get_waypoint_description(current_hole_index, current_waypoint_index)) < 1) {
    current_waypoint_index = 0;
  }
  
  if (!refresh_gps) {
    current_waypoint_index = 0;
    refresh_gps = true;
    send_message_to_phone(COMMAND_GET_LOCATION, -1);
  }
  static char title[30];
  snprintf(title, sizeof(title), "%s", get_waypoint_description(current_hole_index, current_waypoint_index));
  text_layer_set_text(s_distance_to_target_title, title);
  text_layer_set_text(s_distance_to_target, "???");
  layer_mark_dirty(window_get_root_layer(s_window));
  // Update the distance display - but only if we've got a position saved
  if (last_lat !=0 && last_lon !=0) {
    update_distance(last_lat, last_lon);
  }
}

// Once we've received current coords then calculate the distance in yards to the next target
void update_distance(int32_t latitude, int32_t longitude) {
  // Save the lat and lon - we'll use them to immediate calculate
  // distances if the target changes
  last_lat = latitude;
  last_lon = longitude;
  //We receive lat and lon as integers - values must be divided by 1000000
  uint16_t distance = calculate_distance(latitude, longitude, 
                                    get_latitude(current_hole_index, current_waypoint_index), 
                                    get_longitude(current_hole_index, current_waypoint_index)
                                   );

  // Display the yardage on-screen
  static char yardage[] = ">2000";
  if (distance < 2000) {
    snprintf(yardage, sizeof(yardage),"%d", distance);
  }
  text_layer_set_text(s_distance_to_target, yardage);
}

//If the select button is pressed then move onto the next hole....
static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  //...but first check we're not already on the last hole
  if (current_hole_index == 17) {
    window_stack_pop(true);
    hide_current_hole_details();
    show_scorecard();
    return;
  }
  //We need to make sure the selected index in the previous menulayer is
  //advanced - we've been storing the parent menu in callback_menu
  static MenuIndex idx;
  idx.row = current_hole_index + 1;
  idx.section = 0;
  menu_layer_set_selected_index(callback_menu, idx, MenuRowAlignCenter, false);
  window_stack_pop(true);
  hide_current_hole_details();
  //After closing the current hole - show the next hole details
  show_current_hole_details(current_hole_index + 1, callback_menu);
}

static void select_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  show_scorecard();
}

//Click Handler for single click on down button - adds a shot
static void add_shot(ClickRecognizerRef recognizer, void *context) {
  set_my_strokes(current_hole_index, get_my_strokes(current_hole_index)+1);
  display_shots();
}

//Click Handler for long click on down button - subtracts a shot
static void subtract_shot(ClickRecognizerRef recognizer, void *context) {
  set_my_strokes(current_hole_index, get_my_strokes(current_hole_index)-1);
  display_shots();
}

//Set up ClickHandlers
static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, add_shot);
  window_long_click_subscribe(BUTTON_ID_DOWN, 0, NULL, subtract_shot);
  window_long_click_subscribe(BUTTON_ID_SELECT, 0, NULL, select_long_click_handler);
}

//Entry function for this window - called from choose_hole menu list
void show_current_hole_details(uint8_t hole_index, void *callback_context) {
  initialise_ui();
  //Save a reference to the menu which called us here
  callback_menu = callback_context;
  current_hole_index = hole_index;
  current_waypoint_index = 0;
  last_lat = 0;
  last_lon = 0;
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_set_click_config_provider(s_window, click_config_provider);
  
  //Setup the initial values for the hole
  static char hole_number[11];
  snprintf(hole_number, sizeof(hole_number), "%d - Par %d", hole_index+1, get_par(hole_index));
  text_layer_set_text(s_hole_title, hole_number);
  
  static char hole_subtitle[16];
  snprintf(hole_subtitle, sizeof(hole_subtitle), "SI %d - %d shots", get_si(hole_index), get_my_shots_received(hole_index));
  text_layer_set_text(s_hole_subtitle, hole_subtitle);
  
  display_shots();
  window_stack_push(s_window, true);
}

void hide_current_hole_details(void) {
  window_stack_remove(s_window, true);
}
