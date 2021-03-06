#include <pebble.h>
#include "scorecard.h"
#include "globals.h"
  

// Originally used the UI editor and created each label separately
// ..... it took too much space in RAM so had to re-write using arrays
void print_label(TextLayer* this_label, bool bold, bool invert, bool is_title, char* value, GTextAlignment alignment );


static char buf_score_area[512];
static char buf_s_out_gr[3];
static char buf_s_out_nt[3];
static char buf_s_out_pt[3];
static char buf_s_in_gr[3];
static char buf_s_in_nt[3];
static char buf_s_in_pt[3];
static char buf_s_tot_gr[4];
static char buf_s_tot_nt[4];
static char buf_s_tot_pt[4];

static Window *s_window;
static ScrollLayer *s_scroll_layer;
static GFont s_res_gothic_24;
static GFont s_res_gothic_24_bold;
static TextLayer *score_labels;
static TextLayer *score_area;
static TextLayer *s_labels;

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
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, true);
  
  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  
  // Get the window size and create a scroll layer on it
  s_scroll_layer = scroll_layer_create(GRect(0, 28, 144, 140));
  
  // Set the default click handlers for scrolling
  scroll_layer_set_click_config_onto_window(s_scroll_layer, s_window);
  scroll_layer_set_content_size(s_scroll_layer, GSize(144, 600));
  
  score_labels = text_layer_create(GRect(0, 0, 30, 600));
  print_label(score_labels,true,false,false, 
              "1\n2\n3\n4\n5\n6\n7\n8\n9\n\n\n10\n11\n12\n13\n14\n15\n16\n17\n18",
             GTextAlignmentCenter);
  
  s_labels = text_layer_create(GRect(22, 0, 119, 40)); 
  print_label(s_labels, true, false, true,"Gross  Net   Pts", GTextAlignmentLeft); //Column labels

  char buf[25];
  // Empty buf_score_area
  memset(buf_score_area, 0, sizeof(buf_score_area));
  for (uint8_t i=0; i < 18; i++) {
    if (get_my_strokes(i) < 10) {strcat(buf_score_area,"  ");}
    snprintf(buf, sizeof(buf), "%d", get_my_strokes(i));
    strcat(buf_score_area,buf);
    strcat(buf_score_area,"     ");
    
    if (get_my_net(i) < 10) {strcat(buf_score_area,"  ");}
    snprintf(buf, sizeof(buf), "%d", get_my_net(i));
    strcat(buf_score_area,buf);
    strcat(buf_score_area,"       ");
    snprintf(buf, sizeof(buf), "%d\n", get_my_points(i));
    strcat(buf_score_area,buf);
    
    // After 9 holes leave a gap for the "Out" score
    if (i == 8) {
      strcat(buf_score_area, "\n\n");
    }
  } 
 
  score_area = text_layer_create(GRect(34, 0, 110, 600));
  print_label(score_area,false,false,false, buf_score_area, GTextAlignmentLeft);
  
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
  
  snprintf(buf_s_out_gr, sizeof(buf_s_out_gr), "%d", gross_out);
  snprintf(buf_s_out_nt, sizeof(buf_s_out_nt), "%d", net_out);
  snprintf(buf_s_out_pt, sizeof(buf_s_out_pt), "%d", points_out);
  snprintf(buf_s_in_gr, sizeof(buf_s_in_gr), "%d", gross_in);
  snprintf(buf_s_in_nt, sizeof(buf_s_in_nt), "%d", net_in);
  snprintf(buf_s_in_pt, sizeof(buf_s_in_pt), "%d", points_in); 
  snprintf(buf_s_tot_gr, sizeof(buf_s_tot_gr), "%d", gross_out+gross_in);
  snprintf(buf_s_tot_nt, sizeof(buf_s_tot_nt), "%d", net_out+net_in);
  snprintf(buf_s_tot_pt, sizeof(buf_s_tot_pt), "%d", points_out+points_in);
  
  s_out_gr = text_layer_create(GRect(25, 225, 40, 30)); 
  print_label(s_out_gr, true, false, false, buf_s_out_gr, GTextAlignmentCenter); //Placeholder for front 9 gross scores
  s_in_gr = text_layer_create(GRect(25, 484, 40, 30)); 
  print_label(s_in_gr, true, false, false, buf_s_in_gr, GTextAlignmentCenter); //Placeholder for front 9 gross scores

  
  s_out_nt = text_layer_create(GRect(64, 225, 40, 30)); 
  print_label(s_out_nt, true, false, false, buf_s_out_nt, GTextAlignmentCenter); //Placeholder for front 9 gross scores
  s_in_nt = text_layer_create(GRect(64, 484, 40, 30)); 
  print_label(s_in_nt, true, false, false, buf_s_in_nt, GTextAlignmentCenter); //Placeholder for front 9 gross scores

  
  s_out_pt = text_layer_create(GRect(101, 225, 40, 28)); 
  print_label(s_out_pt, true, false, false, buf_s_out_pt, GTextAlignmentCenter); //Placeholder for front 9 gross scores
  s_in_pt = text_layer_create(GRect(101, 484, 40, 28)); 
  print_label(s_in_pt, true, false, false, buf_s_in_pt, GTextAlignmentCenter); //Placeholder for front 9 gross scores
  
  s_tot_gr = text_layer_create(GRect(23, 519, 38, 30)); 
  print_label(s_tot_gr, true, true, false, buf_s_tot_gr, GTextAlignmentCenter); //Placeholder for round gross total
  s_tot_nt = text_layer_create(GRect(63, 519, 38, 30)); 
  print_label(s_tot_nt, true, true, false, buf_s_tot_nt, GTextAlignmentCenter); //Placeholder for round net total
  s_tot_pt = text_layer_create(GRect(103, 519, 35, 30)); 
  print_label(s_tot_pt, true, true, false, buf_s_tot_pt, GTextAlignmentCenter); //Placeholder for round points total
  
  layer_add_child(window_get_root_layer(s_window), scroll_layer_get_layer(s_scroll_layer));
  
}

static void destroy_ui(void) {
 
  text_layer_destroy(score_labels);
  text_layer_destroy(score_area);
  text_layer_destroy(s_labels);
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
  destroy_ui();
}

// Main entry function to show the overall round scorecard
// It get's called if we do a long-click from the holes menu
void show_scorecard(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_scorecard(void) {
  window_stack_remove(s_window, true);
}


//Helper function to print the golf scorecase
void print_label(TextLayer* this_label, bool bold, bool invert, bool is_title, char* value, GTextAlignment alignment ) {

  if (!invert) {
    text_layer_set_background_color(this_label, GColorClear);
    text_layer_set_text_color(this_label, GColorWhite);
  }

  text_layer_set_text(this_label, value);
  text_layer_set_text_alignment(this_label, alignment);
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

