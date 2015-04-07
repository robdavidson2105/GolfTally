#include <pebble.h>
#include "scorecard.h"
#include "globals.h"
  

// Originally used the UI editor and created each label separately
// ..... it took too much space in RAM so had to re-write using arrays
void display_scores(void);
void print_label(TextLayer* this_label, bool bold, bool invert, bool is_title, char* value );
//TextLayer* print_title(int x, int y, int w, int h, bool bold, char* value );
static char label[48];
static char gross_label[256];
static char net_label[60];
static char points_label[40];
static char buf_gross_scores[256];
static char buf_net_scores[60];
static char buf_points_scores[40];
static char buf_s_out_gr[] = "50";
static char buf_s_out_nt[] = "50";
static char buf_s_out_pt[] = "50";
static char buf_s_in_gr[] = "50";
static char buf_s_in_nt[] = "50";
static char buf_s_in_pt[] = "50";
static char buf_s_tot_gr[] = "100";
static char buf_s_tot_nt[] = "100";
static char buf_s_tot_pt[] = "50";

static Window *s_window;
static ScrollLayer *s_scroll_layer;
static GFont s_res_gothic_24;
static GFont s_res_gothic_24_bold;
static TextLayer *score_labels;
static TextLayer *gross_scores;
//static TextLayer *net_scores;
//static TextLayer *points_scores;
static TextLayer *s_gross;

static TextLayer *s_out_gr;
static TextLayer *s_out_nt;
static TextLayer *s_in_points;
static TextLayer *s_in_gr;
static TextLayer *s_in_nt;
static TextLayer *s_out_pt;
static TextLayer *s_in_pt;
static TextLayer *s_tot_gr;
static TextLayer *s_tot_nt;
static TextLayer *s_tot_pt;

static void initialise_ui(void) {
  APP_LOG(APP_LOG_LEVEL_DEBUG,"Creating window - memory free: %d", heap_bytes_free());
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, false);
  
  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  
  APP_LOG(APP_LOG_LEVEL_DEBUG,"Creating scroll layer - memory free: %d", heap_bytes_free());
  // Get the window size and create a scroll layer on it
  //Layer *window_layer = window_get_root_layer(s_window);
  //GRect bounds = layer_get_frame(window_layer);
  //bounds.origin.y = bounds.origin.y + 28;
  s_scroll_layer = scroll_layer_create(GRect(0, 28, 144, 140));
  
  // Set the default click handlers for scrolling
  scroll_layer_set_click_config_onto_window(s_scroll_layer, s_window);
  scroll_layer_set_content_size(s_scroll_layer, GSize(144, 600));
  
  snprintf(label, 
           sizeof(label), 
           "1"
          );
  score_labels = text_layer_create(GRect(0, 0, 30, 600));
  print_label(score_labels,true,false,false, label);
  APP_LOG(APP_LOG_LEVEL_DEBUG,"Label %s", label);
  
  s_gross = text_layer_create(GRect(25, 0, 119, 40)); 
  print_label(s_gross, true, false, true,"Gross  Net  Pts"); //Column labels

  
  s_out_gr = text_layer_create(GRect(27, 225, 40, 30)); 
  print_label(s_out_gr, true, false, false, "50"); //Placeholder for front 9 gross scores
  s_in_gr = text_layer_create(GRect(27, 476, 40, 30)); 
  print_label(s_in_gr, true, false, false, "50"); //Placeholder back 9 gross score
  
  s_out_nt = text_layer_create(GRect(67, 225, 40, 30)); 
  print_label(s_out_nt, true, false, false, "50"); //Placeholder for front 9 net score 
  s_in_nt = text_layer_create(GRect(67, 476, 40, 30)); 
  print_label(s_in_nt, true, false, false, "50"); //Placeholder for back 9 net score
  
  s_out_pt = text_layer_create(GRect(107, 225, 40, 28)); 
  print_label(s_out_pt, true, false, false, "24"); //Placeholder for front 9 points
  s_in_pt = text_layer_create(GRect(107, 476, 40, 28)); 
  print_label(s_in_pt, true, false, false, "24"); //Placeholder for back 9 points
  
  s_tot_gr = text_layer_create(GRect(27, 506, 38, 30)); 
  print_label(s_tot_gr, true, true, false, "100"); //Placeholder for round gross total
  s_tot_nt = text_layer_create(GRect(67, 506, 38, 30)); 
  print_label(s_tot_nt, true, true, false, "100"); //Placeholder for round net total
  s_tot_pt = text_layer_create(GRect(107, 506, 38, 30)); 
  print_label(s_tot_pt, true, true, false, "50"); //Placeholder for round points total
  

  
  snprintf(gross_label, 
           sizeof(gross_label), 
           "99"
          );
  gross_scores = text_layer_create(GRect(27, 0, 144, 600));
  print_label(gross_scores,false,false,false, gross_label);
  
  /*
  snprintf(net_label, 
           sizeof(net_label), 
           "0\n0\n0\n0\n0\n0\n0\n0\n0\n\n\n\n0\n0\n0\n0\n0\n0\n0\n0\n0"
          );
  net_scores = text_layer_create(GRect(67, 0, 40, 500));
  print_label(net_scores,false,false,false,net_label);
    
  
  snprintf(points_label, 
           sizeof(points_label), 
           "2\n2\n2\n2\n2\n2\n0\n0\n0\n\n\n\n0\n0\n0\n0\n0\n0\n0\n0\n0"
          );
  points_scores = text_layer_create(GRect(107, 0, 40, 500));
  print_label(points_scores,false,false,false,points_label);
  */
  layer_add_child(window_get_root_layer(s_window), scroll_layer_get_layer(s_scroll_layer));
  
}

static void destroy_ui(void) {
 
  text_layer_destroy(score_labels);
  text_layer_destroy(gross_scores);
  //text_layer_destroy(net_scores);
  //text_layer_destroy(points_scores);
  text_layer_destroy(s_gross);
  //text_layer_destroy(s_net);
  //text_layer_destroy(s_points);
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
  window_destroy(s_window);
}

static void handle_window_unload(Window* window) {
  APP_LOG(APP_LOG_LEVEL_DEBUG,"Destroying scorecard - memory free: %d", heap_bytes_free());
  destroy_ui();
  APP_LOG(APP_LOG_LEVEL_DEBUG,"Scorecard destroyed - memory free: %d", heap_bytes_free());
}

// Main entry function to show the overall round scorecard
// It get's called if we do a long-click from the holes menu
void show_scorecard(void) {
  APP_LOG(APP_LOG_LEVEL_DEBUG,"Starting scorecard - memory free: %d", heap_bytes_free());
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
void print_label(TextLayer* this_label, bool bold, bool invert, bool is_title, char* value ) {

  //APP_LOG(APP_LOG_LEVEL_DEBUG,"Printing scorecard - memory free: %d", heap_bytes_free());
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
  if (is_title) {
    layer_add_child(window_get_root_layer(s_window), text_layer_get_layer(this_label));
  } else {
    scroll_layer_add_child(s_scroll_layer, text_layer_get_layer(this_label));
  }
}

void display_scores(void) {
APP_LOG(APP_LOG_LEVEL_DEBUG,"Showing scores - memory free: %d", heap_bytes_free());
// Gross scores
  char buf[12];
  
  for (uint8_t i=0; i < 18; i++) {
    snprintf(buf, sizeof(buf), "%d  %d  %d\n", get_my_strokes(i), get_my_net(i), get_my_points(i));
    strcat(buf_gross_scores,buf);
    /*
    snprintf(buf, sizeof(buf), "%d\n", get_my_net(i));
    strcat(buf_net_scores,buf);
    snprintf(buf, sizeof(buf), "%d\n", get_my_points(i));
    strcat(buf_points_scores,buf); */
    // After 9 holes leave a gap for the "Out" score
    if (i == 8) {
      strcat(buf_gross_scores, "\n\n");
      //strcat(buf_net_scores, "\n\n");
      //strcat(buf_points_scores, "\n\n");
    }
  } 
  //APP_LOG(APP_LOG_LEVEL_DEBUG,"Setting gross score text layers - memory free: %d", heap_bytes_free());
  text_layer_set_text(gross_scores, buf_gross_scores);
  //APP_LOG(APP_LOG_LEVEL_DEBUG,"net scores - memory free: %d", heap_bytes_free());
  //text_layer_set_text(net_scores, buf_net_scores);
  //APP_LOG(APP_LOG_LEVEL_DEBUG,"points scores - memory free: %d", heap_bytes_free());
  //text_layer_set_text(points_scores, buf_points_scores);
  
  //static char buf_nt[18][3];
  
/*
  for (uint8_t i=0; i < 18; i++) {
    snprintf(buf, sizeof(buf), "%d\n", get_my_net(i));
    strcat(buf_net_scores,buf);
    // After 9 holes leave a gap for the "Out" score
    if (i == 8) {
      strcat(buf_net_scores, "\n\n");
    }
  } 
  text_layer_set_text(net_scores, buf_net_scores);
 
  //static char buf_pt[18][3];
  

  for (uint8_t i=0; i < 18; i++) {
    snprintf(buf, sizeof(buf), "%d\n", get_my_points(i));
    strcat(buf_points_scores,buf);
    // After 9 holes leave a gap for the "Out" score
    if (i == 8) {
      strcat(buf_points_scores, "\n\n");
    }
  } 
  text_layer_set_text(points_scores, buf_points_scores);
  */
  APP_LOG(APP_LOG_LEVEL_DEBUG,"Calculating totals - memory free: %d", heap_bytes_free());
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
  APP_LOG(APP_LOG_LEVEL_DEBUG,"Showing totals - memory free: %d", heap_bytes_free());
  
  snprintf(buf_s_out_gr, sizeof(buf_s_out_gr), "%d", gross_out);
  text_layer_set_text(s_out_gr, buf_s_out_gr);
  
  snprintf(buf_s_out_nt, sizeof(buf_s_out_nt), "%d", net_out);
  text_layer_set_text(s_out_nt, buf_s_out_nt);
  
  
  snprintf(buf_s_out_pt, sizeof(buf_s_out_pt), "%d", points_out);
  text_layer_set_text(s_out_pt, buf_s_out_pt);
  
  
  snprintf(buf_s_in_gr, sizeof(buf_s_in_gr), "%d", gross_in);
  text_layer_set_text(s_in_gr, buf_s_in_gr);
  
  
  snprintf(buf_s_in_nt, sizeof(buf_s_in_nt), "%d", net_in);
  text_layer_set_text(s_in_nt, buf_s_in_nt);
  
  snprintf(buf_s_in_pt, sizeof(buf_s_in_pt), "%d", points_in);
  text_layer_set_text(s_in_pt, buf_s_in_pt);
  
 
  snprintf(buf_s_tot_gr, sizeof(buf_s_tot_gr), "%d", gross_out+gross_in);
  text_layer_set_text(s_tot_gr, buf_s_tot_gr);
  
  
  snprintf(buf_s_tot_nt, sizeof(buf_s_tot_nt), "%d", net_out+net_in);
  text_layer_set_text(s_tot_nt, buf_s_tot_nt);
  
  
  snprintf(buf_s_tot_pt, sizeof(buf_s_tot_pt), "%d", points_out+points_in);
  text_layer_set_text(s_tot_pt, buf_s_tot_pt);
APP_LOG(APP_LOG_LEVEL_DEBUG,"Scores displayed - memory free: %d", heap_bytes_free());
}

