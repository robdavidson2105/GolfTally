#include <pebble.h>
#include "scorecard.h"
#include "globals.h"
  

// Originally used the UI editor and created each label separately
// ..... it took too much space in RAM so had to re-write using arrays
void display_scores(void);
TextLayer* print_label(int x, int y, int w, int h, bool bold, bool invert, char* value );
TextLayer* print_title(int x, int y, int w, int h, bool bold, char* value );

static Window *s_window;
static ScrollLayer *s_scroll_layer;
static GFont s_res_gothic_24;
static GFont s_res_gothic_24_bold;
static TextLayer *score_labels[18];
static TextLayer *gross_scores[18];
static TextLayer *net_scores[18];
static TextLayer *points_scores[18];
static TextLayer *s_gross;
static TextLayer *s_net;
static TextLayer *s_points;
static TextLayer *s_out_gr;
static TextLayer *s_out_nt;
static TextLayer *s_gross_in;
static TextLayer *s_net_in;
static TextLayer *s_in_points;
static TextLayer *s_in_gr;
static TextLayer *s_in_nt;
static TextLayer *s_out_pt;
static TextLayer *s_in_pt;
static TextLayer *s_tot_gr;
static TextLayer *s_tot_nt;
static TextLayer *s_tot_pt;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, false);
  
  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  
  // Get the window size and create a scroll layer on it
  Layer *window_layer = window_get_root_layer(s_window);
  GRect bounds = layer_get_frame(window_layer);
  bounds.origin.y = bounds.origin.y + 28;
  s_scroll_layer = scroll_layer_create(bounds);
  
  // Set the default click handlers for scrolling
  scroll_layer_set_click_config_onto_window(s_scroll_layer, s_window);
  scroll_layer_set_content_size(s_scroll_layer, GSize(bounds.size.w, bounds.size.h * 3 + 120));
  layer_add_child(window_layer, scroll_layer_get_layer(s_scroll_layer));
  
  
  
  //Scorecard hole labels
  static char label[18][3];
  for (int i = 0; i < 18; i++) {
    snprintf(label[i], 3, "%d", i+1);
    score_labels[i] = print_label(0, (i*25) + 26 * (i / 9), 26, 26, true, false, label[i]);
  }
  
  
  s_gross = print_title(27, 0, 40, 40, true, "Gross"); //Label for Gross score column
  s_net = print_title(73, 1, 26, 40, true, "Net"); // Label for Net score column
  s_points = print_title(108, 1, 40, 40, true, "Pts"); //Label for Points column
  
  s_out_gr = print_label(27, 225, 40, 30, true, false, "50"); //Placeholder for front 9 gross scores
  s_in_gr = print_label(27, 476, 40, 30, true, false, "50"); //Placeholder back 9 gross score
  
  s_out_nt = print_label(67, 225, 40, 30, true, false, "50"); //Placeholder for front 9 net score 
  s_in_nt = print_label(67, 476, 40, 30, true, false, "50"); //Placeholder for back 9 net score
  
  s_out_pt = print_label(107, 225, 40, 28, true, false, "24"); //Placeholder for front 9 points
  s_in_pt = print_label(107, 476, 40, 28, true, false, "24"); //Placeholder for back 9 points
  
  s_tot_gr = print_label(27, 506, 38, 30, true, true, "100"); //Placeholder for round gross total
  s_tot_nt = print_label(67, 506, 38, 30, true, true, "100"); //Placeholder for round net total
  s_tot_pt = print_label(107, 506, 38, 30, true, true, "50"); //Placeholder for round points total
  
  //Gross scores
  for (int i = 0; i < 18; i++) {
    gross_scores[i] = print_label(27, (i*25) + 26 * (i / 9), 40, 40, false, false, "0"); 
  }
  
  //Net scores 
  for (int i = 0; i < 18; i++) {
    net_scores[i] = print_label(67, (i*25) + 26 * (i / 9), 40, 40, false, false, "0");
  }
  
  //Points scores
  for (int i = 0; i < 18; i++) {
    points_scores[i] = print_label(107, (i*25) + 26 * (i / 9), 40, 40, false, false, "0");
  }
}

static void destroy_ui(void) {
  window_destroy(s_window);
  for (int i = 0; i <18; i++) {
    text_layer_destroy(score_labels[i]);
  }
  for (int i = 0; i <18; i++) {
    text_layer_destroy(gross_scores[i]);
  }
  for (int i = 0; i <18; i++) {
    text_layer_destroy(net_scores[i]);
  }
  for (int i = 0; i <18; i++) {
    text_layer_destroy(points_scores[i]);
  }
  
  text_layer_destroy(s_gross);
  text_layer_destroy(s_net);
  text_layer_destroy(s_points);
  text_layer_destroy(s_out_gr);
  text_layer_destroy(s_out_nt);
  text_layer_destroy(s_in_nt);
  text_layer_destroy(s_in_points);
  text_layer_destroy(s_out_pt);
  text_layer_destroy(s_in_gr);
  text_layer_destroy(s_in_pt);
  text_layer_destroy(s_tot_gr);
  text_layer_destroy(s_tot_nt);
  text_layer_destroy(s_tot_pt);
  scroll_layer_destroy(s_scroll_layer);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

// Main entry function to show the overall round scorecard
// It get's called if we do a long-click from the holes menu
void show_scorecard(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  display_scores();
  window_stack_push(s_window, true);
}

void hide_scorecard(void) {
  window_stack_remove(s_window, true);
}


//Helper function to print the golf scorecase
TextLayer* print_label(int x, int y, int w, int h, bool bold, bool invert, char* value ) {
  TextLayer* this_label = text_layer_create(GRect(x, y, w, h));
  APP_LOG(APP_LOG_LEVEL_DEBUG,"Printing label for: %s", value);
  if (!invert) {
    text_layer_set_background_color(this_label, GColorClear);
    text_layer_set_text_color(this_label, GColorWhite);
  }
  text_layer_set_text(this_label, value);
  text_layer_set_text_alignment(this_label, GTextAlignmentCenter);
  if (bold) {
    text_layer_set_font(this_label, s_res_gothic_24_bold);
  } else {
    text_layer_set_font(this_label, s_res_gothic_24);
  }
  scroll_layer_add_child(s_scroll_layer, (Layer *)this_label);
  //layer_add_child(window_get_root_layer(s_window), (Layer *)this_label);
  return this_label;
}

TextLayer* print_title(int x, int y, int w, int h, bool bold, char* value ) {
  TextLayer* this_label = text_layer_create(GRect(x, y, w, h));
  text_layer_set_background_color(this_label, GColorClear);
  text_layer_set_text_color(this_label, GColorWhite);
  text_layer_set_text(this_label, value);
  text_layer_set_text_alignment(this_label, GTextAlignmentCenter);
  if (bold) {
    text_layer_set_font(this_label, s_res_gothic_24_bold);
  } else {
    text_layer_set_font(this_label, s_res_gothic_24);
  }
  layer_add_child(window_get_root_layer(s_window), (Layer *)this_label);
  return this_label;
}

void display_scores(void) {

// Gross scores
  static char buf_gr[18][3];
  for (int i=0; i < 18; i++) {
    snprintf(buf_gr[i], 3, "%d", get_my_strokes(i));
    text_layer_set_text(gross_scores[i], buf_gr[i]);
  }
// Net scores
  static char buf_nt[18][3];
  for (int i=0; i < 18; i++) {
    snprintf(buf_nt[i], 3, "%d", get_my_net(i));
    text_layer_set_text(net_scores[i], buf_nt[i]);
  }
// Points scores
  static char buf_pt[18][3];
  for (int i=0; i < 18; i++) {
    snprintf(buf_pt[i], 3, "%d", get_my_points(i));
    text_layer_set_text(points_scores[i], buf_pt[i]);
  }
  
  //Calculate totals
  int8_t gross_out = 0;
  int8_t gross_in = 0;
  int8_t net_out = 0;
  int8_t net_in = 0;
  int8_t points_out = 0;
  int8_t points_in = 0;
  
  for (uint8_t i = 0; i < 9; i++) {
    gross_out += get_my_strokes(i);
    net_out += get_my_net(i);
    points_out += get_my_points(i);
  }
  for (uint8_t i = 9; i < 18; i++) {
    gross_in += get_my_strokes(i);
    net_in += get_my_net(i);
    points_in += get_my_points(i);
  }
  
  static char buf_s_out_gr[] = "50";
  snprintf(buf_s_out_gr, sizeof(buf_s_out_gr), "%d", gross_out);
  text_layer_set_text(s_out_gr, buf_s_out_gr);
  
  static char buf_s_out_nt[] = "50";
  snprintf(buf_s_out_nt, sizeof(buf_s_out_nt), "%d", net_out);
  text_layer_set_text(s_out_nt, buf_s_out_nt);
  
  static char buf_s_out_pt[] = "50";
  snprintf(buf_s_out_pt, sizeof(buf_s_out_pt), "%d", points_out);
  text_layer_set_text(s_out_pt, buf_s_out_pt);
  
  static char buf_s_in_gr[] = "50";
  snprintf(buf_s_in_gr, sizeof(buf_s_in_gr), "%d", gross_in);
  text_layer_set_text(s_in_gr, buf_s_in_gr);
  
  static char buf_s_in_nt[] = "50";
  snprintf(buf_s_in_nt, sizeof(buf_s_in_nt), "%d", net_in);
  text_layer_set_text(s_in_nt, buf_s_in_nt);
  
  static char buf_s_in_pt[] = "50";
  snprintf(buf_s_in_pt, sizeof(buf_s_in_pt), "%d", points_in);
  text_layer_set_text(s_in_pt, buf_s_in_pt);
  
  static char buf_s_tot_gr[] = "100";
  snprintf(buf_s_tot_gr, sizeof(buf_s_tot_gr), "%d", gross_out+gross_in);
  text_layer_set_text(s_tot_gr, buf_s_tot_gr);
  
  static char buf_s_tot_nt[] = "100";
  snprintf(buf_s_tot_nt, sizeof(buf_s_tot_nt), "%d", net_out+net_in);
  text_layer_set_text(s_tot_nt, buf_s_tot_nt);
  
  static char buf_s_tot_pt[] = "50";
  snprintf(buf_s_tot_pt, sizeof(buf_s_tot_pt), "%d", points_out+points_in);
  text_layer_set_text(s_tot_pt, buf_s_tot_pt);

}

