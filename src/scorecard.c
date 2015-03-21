#include <pebble.h>
#include "scorecard.h"
#include "globals.h"

// Originally used the UI editor and created each label separately
// ..... it took too much space in RAM so had to re-write using arrays
void display_scores(void);
TextLayer* print_label(int x, int y, int w, int h, bool bold, char* value );

static Window *s_window;
static GFont s_res_gothic_14;
static TextLayer *score_labels[18];
static TextLayer *gross_scores[18];
static TextLayer *net_scores[18];
static TextLayer *points_scores[18];
static TextLayer *s_gross_out;
static TextLayer *s_net_out;
static TextLayer *s_points_out;
static TextLayer *s_out_gr;
static TextLayer *s_out_nt;
static TextLayer *s_gross_in;
static TextLayer *s_net_in;
static TextLayer *s_in_points;
static TextLayer *s_in_gr;
static TextLayer *s_in_nt;
static TextLayer *s_out_pt;
static TextLayer *s_in_pt;
static TextLayer *s_textlayer_1;
static TextLayer *s_tot_gr;
static TextLayer *s_textlayer_2;
static TextLayer *s_tot_nt;
static TextLayer *s_textlayer_3;
static TextLayer *s_tot_pt;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, false);
  
  s_res_gothic_14 = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  
  //Labels for front 9
  static char label[18][3];
  for (int i = 0; i < 9; i++) {
    snprintf(label[i], 3, "%d", i+1);
    score_labels[i] = print_label(0, (14+i*13), 11, 17, true, label[i]);
  }
  
  //Labels for back 9
  for (int i = 0; i < 9; i++) {
    snprintf(label[i+9], 3, "%d", i+10);
    score_labels[i+9] = print_label(54, (14+i*13), 17, 17, true, label[i+9]); 
  }
  
  s_gross_out = print_label(6, 1, 19, 15, true, "Gr"); //Label for front 9 Gross score column
  s_out_gr = print_label(7, 132, 17, 17, false, "50"); //Placeholder for front 9 Gross scores
  s_gross_in = print_label(66, 1, 19, 15, true, "Gr"); //Placeholder for back 9 gross score
  s_in_gr = print_label(68, 132, 17, 17, false, "50"); //Placeholder back 9 gross score
  
  s_net_out = print_label(22, 1, 19, 15, true, "Nt"); // Label for front 9 Net score column
  s_out_nt = print_label(24, 132, 17, 17, false, "50"); //Placeholder for front 9 net score 
  s_net_in = print_label(82, 1, 19, 15, true, "Nt"); //Placeholder for back 9 net score
  s_in_nt = print_label(84, 132, 17, 17, false, "50"); //Placeholder for back 9 net score
  
  s_points_out = print_label(38, 1, 19, 15, true, "Pt"); //Label for front 9 Points column
  s_out_pt = print_label(39, 132, 17, 17, false, "24"); //Placeholder for front 9 points
  s_in_points = print_label(98, 1, 19, 15, true, "Pt"); //Label for back 9 points column
  s_in_pt = print_label(99, 132, 17, 17, false, "24"); //Placeholder for back 9 points
  
  s_tot_gr = print_label(111, 37, 30, 17, false, "100"); //Placeholder for round gross total
  s_tot_nt = print_label(112, 74, 28, 20, false, "100"); //Placeholder for round net total
  s_tot_pt = print_label(112, 111, 28, 20, false, "50"); //Placeholder for round points total
  
  //Gross scores for front 9
  for (int i = 0; i < 9; i++) {
    gross_scores[i] = print_label(8, (14+i*13), 17, 17, false, "0"); 
  }
  
  //Gross scores for back 9
  for (int i = 0; i < 9; i++) {
    gross_scores[i+9] = print_label(68, (14+i*13), 17, 17, false, "0"); 
  }
  
  //Net scores for front 9
  for (int i = 0; i < 9; i++) {
    net_scores[i] = print_label(23, (14+i*13), 17, 17, false, "0");
  }
  
  //Net scores for back 9
  for (int i = 0; i < 9; i++) {
    net_scores[i+9] = print_label(84, (14+i*13), 17, 17, false, "0");
  }
  
  //Points scores for front 9
  for (int i = 0; i < 9; i++) {
    points_scores[i] = print_label(39, (14+i*13), 17, 17, false, "0");
  }
  
  //Points scores for back 9
  for (int i = 0; i < 9; i++) {
    points_scores[i+9] = print_label(98, (14+i*13), 17, 17, false, "0"); 
  }
  
  
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(112, 21, 29, 15));
  text_layer_set_text(s_textlayer_1, "Gross");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(112, 58, 29, 15));
  text_layer_set_text(s_textlayer_2, "Net");
  text_layer_set_text_alignment(s_textlayer_2, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_2, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
  
  // s_textlayer_3
  s_textlayer_3 = text_layer_create(GRect(112, 95, 29, 15));
  text_layer_set_text(s_textlayer_3, "Pts");
  text_layer_set_text_alignment(s_textlayer_3, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_3, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_3);
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
  
  text_layer_destroy(s_gross_out);
  text_layer_destroy(s_net_out);
  text_layer_destroy(s_points_out);
  text_layer_destroy(s_out_gr);
  text_layer_destroy(s_out_nt);
  text_layer_destroy(s_gross_in);
  text_layer_destroy(s_net_in);
  text_layer_destroy(s_in_nt);
  text_layer_destroy(s_in_points);
  text_layer_destroy(s_out_pt);
  text_layer_destroy(s_in_gr);
  text_layer_destroy(s_in_pt);
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(s_tot_gr);
  text_layer_destroy(s_textlayer_2);
  text_layer_destroy(s_tot_nt);
  text_layer_destroy(s_textlayer_3);
  text_layer_destroy(s_tot_pt);
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
TextLayer* print_label(int x, int y, int w, int h, bool bold, char* value ) {
  TextLayer* this_label = text_layer_create(GRect(x, y, w, h));
  text_layer_set_background_color(this_label, GColorClear);
  text_layer_set_text_color(this_label, GColorWhite);
  text_layer_set_text(this_label, value);
  text_layer_set_text_alignment(this_label, GTextAlignmentCenter);
  if (!bold) {text_layer_set_font(this_label, s_res_gothic_14);}
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

