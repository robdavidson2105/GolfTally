#include <pebble.h>
#include "scorecard.h"
#include "globals.h"

//There is SURELY an easier way to this using arrays!  
  
void display_scores(void);

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
    score_labels[i] = text_layer_create(GRect(0, (int)(14+i*13), 11, 17));
    text_layer_set_background_color(score_labels[i], GColorClear);
    text_layer_set_text_color(score_labels[i], GColorWhite);
    snprintf(label[i], 3, "%d", i+1);
    text_layer_set_text(score_labels[i], label[i]);
    text_layer_set_text_alignment(score_labels[i], GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(s_window), (Layer *)score_labels[i]); 
  }
  
  //Labels for back 9
  for (int i = 0; i < 9; i++) {
    score_labels[i+9] = text_layer_create(GRect(54, (int)(14+i*13), 17, 17));
    text_layer_set_background_color(score_labels[i+9], GColorClear);
    text_layer_set_text_color(score_labels[i+9], GColorWhite);
    snprintf(label[i+9], 3, "%d", i+10);
    text_layer_set_text(score_labels[i+9], label[i+9]);
    text_layer_set_text_alignment(score_labels[i+9], GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(s_window), (Layer *)score_labels[i+9]);
    
  }
  
  // s_gross_out
  s_gross_out = text_layer_create(GRect(6, 1, 19, 15));
  text_layer_set_background_color(s_gross_out, GColorClear);
  text_layer_set_text_color(s_gross_out, GColorWhite);
  text_layer_set_text(s_gross_out, "Gr");
  text_layer_set_text_alignment(s_gross_out, GTextAlignmentCenter);
  text_layer_set_font(s_gross_out, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_gross_out);
  
  // s_out_gr
  s_out_gr = text_layer_create(GRect(7, 132, 17, 17));
  text_layer_set_background_color(s_out_gr, GColorClear);
  text_layer_set_text_color(s_out_gr, GColorWhite);
  text_layer_set_text(s_out_gr, "50");
  text_layer_set_text_alignment(s_out_gr, GTextAlignmentCenter);
  text_layer_set_font(s_out_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_out_gr);
  
  // s_net_out
  s_net_out = text_layer_create(GRect(22, 1, 19, 15));
  text_layer_set_background_color(s_net_out, GColorClear);
  text_layer_set_text_color(s_net_out, GColorWhite);
  text_layer_set_text(s_net_out, "Nt");
  text_layer_set_text_alignment(s_net_out, GTextAlignmentCenter);
  text_layer_set_font(s_net_out, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_net_out);
  
  // s_points_out
  s_points_out = text_layer_create(GRect(38, 1, 19, 15));
  text_layer_set_background_color(s_points_out, GColorClear);
  text_layer_set_text_color(s_points_out, GColorWhite);
  text_layer_set_text(s_points_out, "Pt");
  text_layer_set_text_alignment(s_points_out, GTextAlignmentCenter);
  text_layer_set_font(s_points_out, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_points_out);
  
  //Gross scores for front 9
  for (int i = 0; i < 9; i++) {
    gross_scores[i] = text_layer_create(GRect(8, (int)(14+i*13), 17, 17));
    text_layer_set_background_color(gross_scores[i], GColorClear);
    text_layer_set_text_color(gross_scores[i], GColorWhite);
    text_layer_set_text(gross_scores[i], "0");
    text_layer_set_font(gross_scores[i], s_res_gothic_14);
    text_layer_set_text_alignment(gross_scores[i], GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(s_window), (Layer *)gross_scores[i]); 
  }
  
  //Gross scores for back 9
  for (int i = 0; i < 9; i++) {
    gross_scores[i+9] = text_layer_create(GRect(67, (int)(14+i*13), 17, 17));
    text_layer_set_background_color(gross_scores[i+9], GColorClear);
    text_layer_set_text_color(gross_scores[i+9], GColorWhite);
    text_layer_set_text(gross_scores[i+9], "0");
    text_layer_set_font(gross_scores[i+9], s_res_gothic_14);
    text_layer_set_text_alignment(gross_scores[i+9], GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(s_window), (Layer *)gross_scores[i+9]);
    
  }
  
  
  
  //Net scores for front 9
  for (int i = 0; i < 9; i++) {
    net_scores[i] = text_layer_create(GRect(23, (int)(14+i*13), 17, 17));
    text_layer_set_background_color(net_scores[i], GColorClear);
    text_layer_set_text_color(net_scores[i], GColorWhite);
    text_layer_set_text(net_scores[i], "0");
    text_layer_set_font(net_scores[i], s_res_gothic_14);
    text_layer_set_text_alignment(net_scores[i], GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(s_window), (Layer *)net_scores[i]); 
  }
  
  //Net scores for back 9
  for (int i = 0; i < 9; i++) {
    net_scores[i+9] = text_layer_create(GRect(84, (int)(14+i*13), 17, 17));
    text_layer_set_background_color(net_scores[i+9], GColorClear);
    text_layer_set_text_color(net_scores[i+9], GColorWhite);
    text_layer_set_text(net_scores[i+9], "0");
    text_layer_set_font(net_scores[i+9], s_res_gothic_14);
    text_layer_set_text_alignment(net_scores[i+9], GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(s_window), (Layer *)net_scores[i+9]);
    
  }
  
  //Points scores for front 9
  for (int i = 0; i < 9; i++) {
    points_scores[i] = text_layer_create(GRect(39, (int)(14+i*13), 17, 17));
    text_layer_set_background_color(points_scores[i], GColorClear);
    text_layer_set_text_color(points_scores[i], GColorWhite);
    text_layer_set_text(points_scores[i], "0");
    text_layer_set_font(points_scores[i], s_res_gothic_14);
    text_layer_set_text_alignment(points_scores[i], GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(s_window), (Layer *)points_scores[i]); 
  }
  
  //Points scores for back 9
  for (int i = 0; i < 9; i++) {
    points_scores[i+9] = text_layer_create(GRect(98, (int)(14+i*13), 17, 17));
    text_layer_set_background_color(points_scores[i+9], GColorClear);
    text_layer_set_text_color(points_scores[i+9], GColorWhite);
    text_layer_set_text(points_scores[i+9], "0");
    text_layer_set_font(points_scores[i+9], s_res_gothic_14);
    text_layer_set_text_alignment(points_scores[i+9], GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(s_window), (Layer *)points_scores[i+9]);
    
  }
  
  // s_out_nt
  s_out_nt = text_layer_create(GRect(24, 132, 17, 17));
  text_layer_set_background_color(s_out_nt, GColorClear);
  text_layer_set_text_color(s_out_nt, GColorWhite);
  text_layer_set_text(s_out_nt, "50");
  text_layer_set_text_alignment(s_out_nt, GTextAlignmentCenter);
  text_layer_set_font(s_out_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_out_nt);

  
  // s_gross_in
  s_gross_in = text_layer_create(GRect(66, 1, 19, 15));
  text_layer_set_background_color(s_gross_in, GColorClear);
  text_layer_set_text_color(s_gross_in, GColorWhite);
  text_layer_set_text(s_gross_in, "Gr");
  text_layer_set_text_alignment(s_gross_in, GTextAlignmentCenter);
  text_layer_set_font(s_gross_in, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_gross_in);
  
  // s_net_in
  s_net_in = text_layer_create(GRect(82, 1, 19, 15));
  text_layer_set_background_color(s_net_in, GColorClear);
  text_layer_set_text_color(s_net_in, GColorWhite);
  text_layer_set_text(s_net_in, "Nt");
  text_layer_set_text_alignment(s_net_in, GTextAlignmentCenter);
  text_layer_set_font(s_net_in, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_net_in);
  
  // s_in_points
  s_in_points = text_layer_create(GRect(98, 1, 19, 15));
  text_layer_set_background_color(s_in_points, GColorClear);
  text_layer_set_text_color(s_in_points, GColorWhite);
  text_layer_set_text(s_in_points, "Pt");
  text_layer_set_text_alignment(s_in_points, GTextAlignmentCenter);
  text_layer_set_font(s_in_points, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_in_points);

  
  // s_out_pt
  s_out_pt = text_layer_create(GRect(39, 132, 17, 17));
  text_layer_set_background_color(s_out_pt, GColorClear);
  text_layer_set_text_color(s_out_pt, GColorWhite);
  text_layer_set_text(s_out_pt, "24");
  text_layer_set_text_alignment(s_out_pt, GTextAlignmentCenter);
  text_layer_set_font(s_out_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_out_pt);
  
  
  
  // s_in_gr
  s_in_gr = text_layer_create(GRect(68, 132, 17, 17));
  text_layer_set_background_color(s_in_gr, GColorClear);
  text_layer_set_text_color(s_in_gr, GColorWhite);
  text_layer_set_text(s_in_gr, "50");
  text_layer_set_text_alignment(s_in_gr, GTextAlignmentCenter);
  text_layer_set_font(s_in_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_in_gr);

  
  // s_in_pt
  s_in_pt = text_layer_create(GRect(99, 132, 17, 17));
  text_layer_set_background_color(s_in_pt, GColorClear);
  text_layer_set_text_color(s_in_pt, GColorWhite);
  text_layer_set_text(s_in_pt, "24");
  text_layer_set_text_alignment(s_in_pt, GTextAlignmentCenter);
  text_layer_set_font(s_in_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_in_pt);
  
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(112, 21, 29, 15));
  text_layer_set_text(s_textlayer_1, "Gross");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_1, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_tot_gr
  s_tot_gr = text_layer_create(GRect(111, 37, 30, 17));
  text_layer_set_background_color(s_tot_gr, GColorClear);
  text_layer_set_text_color(s_tot_gr, GColorWhite);
  text_layer_set_text(s_tot_gr, "100");
  text_layer_set_text_alignment(s_tot_gr, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_tot_gr);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(112, 58, 29, 15));
  text_layer_set_text(s_textlayer_2, "Net");
  text_layer_set_text_alignment(s_textlayer_2, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_2, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
  
  // s_tot_nt
  s_tot_nt = text_layer_create(GRect(112, 74, 28, 20));
  text_layer_set_background_color(s_tot_nt, GColorClear);
  text_layer_set_text_color(s_tot_nt, GColorWhite);
  text_layer_set_text(s_tot_nt, "100");
  text_layer_set_text_alignment(s_tot_nt, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_tot_nt);
  
  // s_textlayer_3
  s_textlayer_3 = text_layer_create(GRect(112, 95, 29, 15));
  text_layer_set_text(s_textlayer_3, "Pts");
  text_layer_set_text_alignment(s_textlayer_3, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_3, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_3);
  
  // s_tot_pt
  s_tot_pt = text_layer_create(GRect(112, 111, 28, 20));
  text_layer_set_background_color(s_tot_pt, GColorClear);
  text_layer_set_text_color(s_tot_pt, GColorWhite);
  text_layer_set_text(s_tot_pt, "50");
  text_layer_set_text_alignment(s_tot_pt, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_tot_pt);
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

void show_scorecard(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  //display_scores();
  window_stack_push(s_window, true);
}

void hide_scorecard(void) {
  window_stack_remove(s_window, true);
}

void display_scores(void) {
/*
//Front 9 Gross
  static char buf_s_1_gr[] = "18";
  snprintf(buf_s_1_gr, sizeof(buf_s_1_gr), "%d", get_my_strokes(0));
  text_layer_set_text(s_1_gr, buf_s_1_gr);
  
  static char buf_s_2_gr[] = "18";
  snprintf(buf_s_2_gr, sizeof(buf_s_2_gr), "%d", get_my_strokes(1));
  text_layer_set_text(s_2_gr, buf_s_2_gr);
  
  static char buf_s_3_gr[] = "18";
  snprintf(buf_s_3_gr, sizeof(buf_s_3_gr), "%d", get_my_strokes(2));
  text_layer_set_text(s_3_gr, buf_s_3_gr);
  
  static char buf_s_4_gr[] = "18";
  snprintf(buf_s_4_gr, sizeof(buf_s_4_gr), "%d", get_my_strokes(3));
  text_layer_set_text(s_4_gr, buf_s_4_gr);
  
  static char buf_s_5_gr[] = "18";
  snprintf(buf_s_5_gr, sizeof(buf_s_5_gr), "%d", get_my_strokes(4));
  text_layer_set_text(s_5_gr, buf_s_5_gr);
  
  static char buf_s_6_gr[] = "18";
  snprintf(buf_s_6_gr, sizeof(buf_s_6_gr), "%d", get_my_strokes(5));
  text_layer_set_text(s_6_gr, buf_s_6_gr);
  
  static char buf_s_7_gr[] = "18";
  snprintf(buf_s_7_gr, sizeof(buf_s_7_gr), "%d", get_my_strokes(6));
  text_layer_set_text(s_7_gr, buf_s_7_gr);
  
  static char buf_s_8_gr[] = "18";
  snprintf(buf_s_8_gr, sizeof(buf_s_8_gr), "%d", get_my_strokes(7));
  text_layer_set_text(s_8_gr, buf_s_8_gr);
  
  static char buf_s_9_gr[] = "18";
  snprintf(buf_s_9_gr, sizeof(buf_s_9_gr), "%d", get_my_strokes(8));
  text_layer_set_text(s_9_gr, buf_s_9_gr);
  
//Back 9 Gross
  static char buf_s_10_gr[] = "18";
  snprintf(buf_s_10_gr, sizeof(buf_s_10_gr), "%d", get_my_strokes(9));
  text_layer_set_text(s_10_gr, buf_s_10_gr);
  
  static char buf_s_11_gr[] = "18";
  snprintf(buf_s_11_gr, sizeof(buf_s_11_gr), "%d", get_my_strokes(10));
  text_layer_set_text(s_11_gr, buf_s_11_gr);
  
  static char buf_s_12_gr[] = "18";
  snprintf(buf_s_12_gr, sizeof(buf_s_12_gr), "%d", get_my_strokes(11));
  text_layer_set_text(s_12_gr, buf_s_12_gr);
  
  static char buf_s_13_gr[] = "18";
  snprintf(buf_s_13_gr, sizeof(buf_s_13_gr), "%d", get_my_strokes(12));
  text_layer_set_text(s_13_gr, buf_s_13_gr);
  
  static char buf_s_14_gr[] = "18";
  snprintf(buf_s_14_gr, sizeof(buf_s_14_gr), "%d", get_my_strokes(13));
  text_layer_set_text(s_14_gr, buf_s_14_gr);
  
  static char buf_s_15_gr[] = "18";
  snprintf(buf_s_15_gr, sizeof(buf_s_15_gr), "%d", get_my_strokes(14));
  text_layer_set_text(s_15_gr, buf_s_15_gr);
  
  static char buf_s_16_gr[] = "18";
  snprintf(buf_s_16_gr, sizeof(buf_s_16_gr), "%d", get_my_strokes(15));
  text_layer_set_text(s_16_gr, buf_s_16_gr);
  
  static char buf_s_17_gr[] = "18";
  snprintf(buf_s_17_gr, sizeof(buf_s_17_gr), "%d", get_my_strokes(16));
  text_layer_set_text(s_17_gr, buf_s_17_gr);
  
  static char buf_s_18_gr[] = "18";
  snprintf(buf_s_18_gr, sizeof(buf_s_18_gr), "%d", get_my_strokes(17));
  text_layer_set_text(s_18_gr, buf_s_18_gr);
  
  //Front 9 Net
  static char buf_s_1_nt[] = "18";
  snprintf(buf_s_1_nt, sizeof(buf_s_1_nt), "%d", get_my_net(0));
  text_layer_set_text(s_1_nt, buf_s_1_nt);
  
  static char buf_s_2_nt[] = "18";
  snprintf(buf_s_2_nt, sizeof(buf_s_2_nt), "%d", get_my_net(1));
  text_layer_set_text(s_2_nt, buf_s_2_nt);
  
  static char buf_s_3_nt[] = "18";
  snprintf(buf_s_3_nt, sizeof(buf_s_3_nt), "%d", get_my_net(2));
  text_layer_set_text(s_3_nt, buf_s_3_nt);
  
  static char buf_s_4_nt[] = "18";
  snprintf(buf_s_4_nt, sizeof(buf_s_4_nt), "%d", get_my_net(3));
  text_layer_set_text(s_4_nt, buf_s_4_nt);
  
  static char buf_s_5_nt[] = "18";
  snprintf(buf_s_5_nt, sizeof(buf_s_5_nt), "%d", get_my_net(4));
  text_layer_set_text(s_5_nt, buf_s_5_nt);
  
  static char buf_s_6_nt[] = "18";
  snprintf(buf_s_6_nt, sizeof(buf_s_6_nt), "%d", get_my_net(5));
  text_layer_set_text(s_6_nt, buf_s_6_nt);
  
  static char buf_s_7_nt[] = "18";
  snprintf(buf_s_7_nt, sizeof(buf_s_7_nt), "%d", get_my_net(6));
  text_layer_set_text(s_7_nt, buf_s_7_nt);
  
  static char buf_s_8_nt[] = "18";
  snprintf(buf_s_8_nt, sizeof(buf_s_8_nt), "%d", get_my_net(7));
  text_layer_set_text(s_8_nt, buf_s_8_nt);
  
  static char buf_s_9_nt[] = "18";
  snprintf(buf_s_9_nt, sizeof(buf_s_9_nt), "%d", get_my_net(8));
  text_layer_set_text(s_9_nt, buf_s_9_nt);
  
//Back 9 Net
  static char buf_s_10_nt[] = "18";
  snprintf(buf_s_10_nt, sizeof(buf_s_10_nt), "%d", get_my_net(9));
  text_layer_set_text(s_10_nt, buf_s_10_nt);
  
  static char buf_s_11_nt[] = "18";
  snprintf(buf_s_11_nt, sizeof(buf_s_11_nt), "%d", get_my_net(10));
  text_layer_set_text(s_11_nt, buf_s_11_nt);
  
  static char buf_s_12_nt[] = "18";
  snprintf(buf_s_12_nt, sizeof(buf_s_12_nt), "%d", get_my_net(11));
  text_layer_set_text(s_12_nt, buf_s_12_nt);
  
  static char buf_s_13_nt[] = "18";
  snprintf(buf_s_13_nt, sizeof(buf_s_13_nt), "%d", get_my_net(12));
  text_layer_set_text(s_13_nt, buf_s_13_nt);
  
  static char buf_s_14_nt[] = "18";
  snprintf(buf_s_14_nt, sizeof(buf_s_14_nt), "%d", get_my_net(13));
  text_layer_set_text(s_14_nt, buf_s_14_nt);
  
  static char buf_s_15_nt[] = "18";
  snprintf(buf_s_15_nt, sizeof(buf_s_15_nt), "%d", get_my_net(14));
  text_layer_set_text(s_15_nt, buf_s_15_nt);
  
  static char buf_s_16_nt[] = "18";
  snprintf(buf_s_16_nt, sizeof(buf_s_16_nt), "%d", get_my_net(15));
  text_layer_set_text(s_16_nt, buf_s_16_nt);
  
  static char buf_s_17_nt[] = "18";
  snprintf(buf_s_17_nt, sizeof(buf_s_17_nt), "%d", get_my_net(16));
  text_layer_set_text(s_17_nt, buf_s_17_nt);
  
  static char buf_s_18_nt[] = "18";
  snprintf(buf_s_18_nt, sizeof(buf_s_18_nt), "%d", get_my_net(17));
  text_layer_set_text(s_18_nt, buf_s_18_nt);
  
//Front 9 Pts
  static char buf_s_1_pt[] = "18";
  snprintf(buf_s_1_pt, sizeof(buf_s_1_pt), "%d", get_my_points(0));
  text_layer_set_text(s_1_pt, buf_s_1_pt);
  
  static char buf_s_2_pt[] = "18";
  snprintf(buf_s_2_pt, sizeof(buf_s_2_pt), "%d", get_my_points(1));
  text_layer_set_text(s_2_nt, buf_s_2_nt);
  
  static char buf_s_3_pt[] = "18";
  snprintf(buf_s_3_pt, sizeof(buf_s_3_pt), "%d", get_my_points(2));
  text_layer_set_text(s_3_pt, buf_s_3_pt);
  
  static char buf_s_4_pt[] = "18";
  snprintf(buf_s_4_pt, sizeof(buf_s_4_pt), "%d", get_my_points(3));
  text_layer_set_text(s_4_pt, buf_s_4_pt);
  
  static char buf_s_5_pt[] = "18";
  snprintf(buf_s_5_pt, sizeof(buf_s_5_pt), "%d", get_my_points(4));
  text_layer_set_text(s_5_pt, buf_s_5_pt);
  
  static char buf_s_6_pt[] = "18";
  snprintf(buf_s_6_pt, sizeof(buf_s_6_pt), "%d", get_my_points(5));
  text_layer_set_text(s_6_pt, buf_s_6_pt);
  
  static char buf_s_7_pt[] = "18";
  snprintf(buf_s_7_pt, sizeof(buf_s_7_pt), "%d", get_my_points(6));
  text_layer_set_text(s_7_pt, buf_s_7_pt);
  
  static char buf_s_8_pt[] = "18";
  snprintf(buf_s_8_pt, sizeof(buf_s_8_pt), "%d", get_my_points(7));
  text_layer_set_text(s_8_pt, buf_s_8_pt);
  
  static char buf_s_9_pt[] = "18";
  snprintf(buf_s_9_pt, sizeof(buf_s_9_pt), "%d", get_my_points(8));
  text_layer_set_text(s_9_pt, buf_s_9_pt);
  
//Back 9 Pts
  static char buf_s_10_pt[] = "18";
  snprintf(buf_s_10_pt, sizeof(buf_s_10_pt), "%d", get_my_points(9));
  text_layer_set_text(s_10_pt, buf_s_10_pt);
  
  static char buf_s_11_pt[] = "18";
  snprintf(buf_s_11_pt, sizeof(buf_s_11_pt), "%d", get_my_points(10));
  text_layer_set_text(s_11_pt, buf_s_11_pt);
  
  static char buf_s_12_pt[] = "18";
  snprintf(buf_s_12_pt, sizeof(buf_s_12_pt), "%d", get_my_points(11));
  text_layer_set_text(s_12_pt, buf_s_12_pt);
  
  static char buf_s_13_pt[] = "18";
  snprintf(buf_s_13_pt, sizeof(buf_s_13_pt), "%d", get_my_points(12));
  text_layer_set_text(s_13_pt, buf_s_13_pt);
  
  static char buf_s_14_pt[] = "18";
  snprintf(buf_s_14_pt, sizeof(buf_s_14_pt), "%d", get_my_points(13));
  text_layer_set_text(s_14_pt, buf_s_14_pt);
  
  static char buf_s_15_pt[] = "18";
  snprintf(buf_s_15_pt, sizeof(buf_s_15_pt), "%d", get_my_points(14));
  text_layer_set_text(s_15_pt, buf_s_15_pt);
  
  static char buf_s_16_pt[] = "18";
  snprintf(buf_s_16_pt, sizeof(buf_s_16_pt), "%d", get_my_points(15));
  text_layer_set_text(s_16_pt, buf_s_16_pt);
  
  static char buf_s_17_pt[] = "18";
  snprintf(buf_s_17_pt, sizeof(buf_s_17_pt), "%d", get_my_points(16));
  text_layer_set_text(s_17_pt, buf_s_17_pt);
  
  static char buf_s_18_pt[] = "18";
  snprintf(buf_s_18_pt, sizeof(buf_s_18_pt), "%d", get_my_points(17));
  text_layer_set_text(s_18_pt, buf_s_18_pt);
  
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
  */
}
