#include <pebble.h>
#include "scorecard.h"
#include "globals.h"

//There is SURELY an easier way to this using arrays!  
  
void display_scores(void);

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_14;
static TextLayer *s_1;
static TextLayer *s_2;
static TextLayer *s_3;
static TextLayer *s_4;
static TextLayer *s_5;
static TextLayer *s_6;
static TextLayer *s_8;
static TextLayer *s_9;
static TextLayer *s_gross_out;
static TextLayer *s_net_out;
static TextLayer *s_points_out;
static TextLayer *s_1_gr;
static TextLayer *s_2_gr;
static TextLayer *s_3_gr;
static TextLayer *s_4_gr;
static TextLayer *s_5_gr;
static TextLayer *s_7;
static TextLayer *s_6_gr;
static TextLayer *s_7_gr;
static TextLayer *s_8_gr;
static TextLayer *s_9_gr;
static TextLayer *s_out_gr;
static TextLayer *s_1_nt;
static TextLayer *s_2_nt;
static TextLayer *s_3_nt;
static TextLayer *s_4_nt;
static TextLayer *s_5_nt;
static TextLayer *s_6_nt;
static TextLayer *s_7_nt;
static TextLayer *s_8_nt;
static TextLayer *s_9_nt;
static TextLayer *s_out_nt;
static TextLayer *s_1_pt;
static TextLayer *s_10;
static TextLayer *s_10_gr;
static TextLayer *s_gross_in;
static TextLayer *s_net_in;
static TextLayer *s_in_points;
static TextLayer *s_10_nt;
static TextLayer *s_10_pt;
static TextLayer *s_3_pt;
static TextLayer *s_4_pt;
static TextLayer *s_5_pt;
static TextLayer *s_6_pt;
static TextLayer *s_7_pt;
static TextLayer *s_8_pt;
static TextLayer *s_9_pt;
static TextLayer *s_out_pt;
static TextLayer *s_11;
static TextLayer *s_12;
static TextLayer *s_13;
static TextLayer *s_14;
static TextLayer *s_15;
static TextLayer *s_2_pt;
static TextLayer *s_16;
static TextLayer *s_17;
static TextLayer *s_18;
static TextLayer *s_11_gr;
static TextLayer *s_12_gr;
static TextLayer *s_13_gr;
static TextLayer *s_14_gr;
static TextLayer *s_15_gr;
static TextLayer *s_16_gr;
static TextLayer *s_17_gr;
static TextLayer *s_18_gr;
static TextLayer *s_in_gr;
static TextLayer *s_11_nt;
static TextLayer *s_12_nt;
static TextLayer *s_13_nt;
static TextLayer *s_14_nt;
static TextLayer *s_15_nt;
static TextLayer *s_16_nt;
static TextLayer *s_17_nt;
static TextLayer *s_18_nt;
static TextLayer *s_in_nt;
static TextLayer *s_11_pt;
static TextLayer *s_12_pt;
static TextLayer *s_13_pt;
static TextLayer *s_14_pt;
static TextLayer *s_15_pt;
static TextLayer *s_16_pt;
static TextLayer *s_17_pt;
static TextLayer *s_18_pt;
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
  // s_1
  s_1 = text_layer_create(GRect(0, 14, 11, 17));
  text_layer_set_background_color(s_1, GColorClear);
  text_layer_set_text_color(s_1, GColorWhite);
  text_layer_set_text(s_1, "1");
  text_layer_set_text_alignment(s_1, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_1);
  
  // s_2
  s_2 = text_layer_create(GRect(0, 27, 11, 17));
  text_layer_set_background_color(s_2, GColorClear);
  text_layer_set_text_color(s_2, GColorWhite);
  text_layer_set_text(s_2, "2");
  text_layer_set_text_alignment(s_2, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_2);
  
  // s_3
  s_3 = text_layer_create(GRect(0, 40, 11, 17));
  text_layer_set_background_color(s_3, GColorBlack);
  text_layer_set_text_color(s_3, GColorWhite);
  text_layer_set_text(s_3, "3");
  text_layer_set_text_alignment(s_3, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_3);
  
  // s_4
  s_4 = text_layer_create(GRect(0, 53, 11, 17));
  text_layer_set_background_color(s_4, GColorClear);
  text_layer_set_text_color(s_4, GColorWhite);
  text_layer_set_text(s_4, "4");
  text_layer_set_text_alignment(s_4, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_4);
  
  // s_5
  s_5 = text_layer_create(GRect(0, 66, 11, 17));
  text_layer_set_background_color(s_5, GColorClear);
  text_layer_set_text_color(s_5, GColorWhite);
  text_layer_set_text(s_5, "5");
  text_layer_set_text_alignment(s_5, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_5);
  
  // s_6
  s_6 = text_layer_create(GRect(0, 79, 11, 17));
  text_layer_set_background_color(s_6, GColorClear);
  text_layer_set_text_color(s_6, GColorWhite);
  text_layer_set_text(s_6, "6");
  text_layer_set_text_alignment(s_6, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_6);
  
  // s_8
  s_8 = text_layer_create(GRect(0, 105, 11, 17));
  text_layer_set_background_color(s_8, GColorClear);
  text_layer_set_text_color(s_8, GColorWhite);
  text_layer_set_text(s_8, "8");
  text_layer_set_text_alignment(s_8, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_8);
  
  // s_9
  s_9 = text_layer_create(GRect(0, 118, 11, 17));
  text_layer_set_background_color(s_9, GColorClear);
  text_layer_set_text_color(s_9, GColorWhite);
  text_layer_set_text(s_9, "9");
  text_layer_set_text_alignment(s_9, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_9);
  
  // s_gross_out
  s_gross_out = text_layer_create(GRect(6, 1, 19, 15));
  text_layer_set_background_color(s_gross_out, GColorClear);
  text_layer_set_text_color(s_gross_out, GColorWhite);
  text_layer_set_text(s_gross_out, "Gr");
  text_layer_set_text_alignment(s_gross_out, GTextAlignmentCenter);
  text_layer_set_font(s_gross_out, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_gross_out);
  
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
  
  // s_1_gr
  s_1_gr = text_layer_create(GRect(8, 14, 17, 17));
  text_layer_set_background_color(s_1_gr, GColorClear);
  text_layer_set_text_color(s_1_gr, GColorWhite);
  text_layer_set_text(s_1_gr, "10");
  text_layer_set_text_alignment(s_1_gr, GTextAlignmentCenter);
  text_layer_set_font(s_1_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_1_gr);
  
  // s_2_gr
  s_2_gr = text_layer_create(GRect(8, 27, 17, 17));
  text_layer_set_background_color(s_2_gr, GColorClear);
  text_layer_set_text_color(s_2_gr, GColorWhite);
  text_layer_set_text(s_2_gr, "4");
  text_layer_set_text_alignment(s_2_gr, GTextAlignmentCenter);
  text_layer_set_font(s_2_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_2_gr);
  
  // s_3_gr
  s_3_gr = text_layer_create(GRect(8, 40, 17, 17));
  text_layer_set_background_color(s_3_gr, GColorClear);
  text_layer_set_text_color(s_3_gr, GColorWhite);
  text_layer_set_text(s_3_gr, "4");
  text_layer_set_text_alignment(s_3_gr, GTextAlignmentCenter);
  text_layer_set_font(s_3_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_3_gr);
  
  // s_4_gr
  s_4_gr = text_layer_create(GRect(8, 53, 17, 17));
  text_layer_set_background_color(s_4_gr, GColorClear);
  text_layer_set_text_color(s_4_gr, GColorWhite);
  text_layer_set_text(s_4_gr, "4");
  text_layer_set_text_alignment(s_4_gr, GTextAlignmentCenter);
  text_layer_set_font(s_4_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_4_gr);
  
  // s_5_gr
  s_5_gr = text_layer_create(GRect(8, 66, 17, 17));
  text_layer_set_background_color(s_5_gr, GColorClear);
  text_layer_set_text_color(s_5_gr, GColorWhite);
  text_layer_set_text(s_5_gr, "4");
  text_layer_set_text_alignment(s_5_gr, GTextAlignmentCenter);
  text_layer_set_font(s_5_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_5_gr);
  
  // s_7
  s_7 = text_layer_create(GRect(1, 92, 11, 17));
  text_layer_set_background_color(s_7, GColorClear);
  text_layer_set_text_color(s_7, GColorWhite);
  text_layer_set_text(s_7, "7");
  text_layer_set_text_alignment(s_7, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_7);
  
  // s_6_gr
  s_6_gr = text_layer_create(GRect(8, 79, 17, 17));
  text_layer_set_background_color(s_6_gr, GColorClear);
  text_layer_set_text_color(s_6_gr, GColorWhite);
  text_layer_set_text(s_6_gr, "4");
  text_layer_set_text_alignment(s_6_gr, GTextAlignmentCenter);
  text_layer_set_font(s_6_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_6_gr);
  
  // s_7_gr
  s_7_gr = text_layer_create(GRect(8, 92, 17, 17));
  text_layer_set_background_color(s_7_gr, GColorClear);
  text_layer_set_text_color(s_7_gr, GColorWhite);
  text_layer_set_text(s_7_gr, "4");
  text_layer_set_text_alignment(s_7_gr, GTextAlignmentCenter);
  text_layer_set_font(s_7_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_7_gr);
  
  // s_8_gr
  s_8_gr = text_layer_create(GRect(8, 105, 17, 17));
  text_layer_set_background_color(s_8_gr, GColorClear);
  text_layer_set_text_color(s_8_gr, GColorWhite);
  text_layer_set_text(s_8_gr, "4");
  text_layer_set_text_alignment(s_8_gr, GTextAlignmentCenter);
  text_layer_set_font(s_8_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_8_gr);
  
  // s_9_gr
  s_9_gr = text_layer_create(GRect(8, 118, 17, 17));
  text_layer_set_background_color(s_9_gr, GColorClear);
  text_layer_set_text_color(s_9_gr, GColorWhite);
  text_layer_set_text(s_9_gr, "4");
  text_layer_set_text_alignment(s_9_gr, GTextAlignmentCenter);
  text_layer_set_font(s_9_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_9_gr);
  
  // s_out_gr
  s_out_gr = text_layer_create(GRect(7, 132, 17, 17));
  text_layer_set_background_color(s_out_gr, GColorClear);
  text_layer_set_text_color(s_out_gr, GColorWhite);
  text_layer_set_text(s_out_gr, "50");
  text_layer_set_text_alignment(s_out_gr, GTextAlignmentCenter);
  text_layer_set_font(s_out_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_out_gr);
  
  // s_1_nt
  s_1_nt = text_layer_create(GRect(23, 14, 17, 17));
  text_layer_set_background_color(s_1_nt, GColorClear);
  text_layer_set_text_color(s_1_nt, GColorWhite);
  text_layer_set_text(s_1_nt, "10");
  text_layer_set_text_alignment(s_1_nt, GTextAlignmentCenter);
  text_layer_set_font(s_1_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_1_nt);
  
  // s_2_nt
  s_2_nt = text_layer_create(GRect(23, 27, 17, 17));
  text_layer_set_background_color(s_2_nt, GColorClear);
  text_layer_set_text_color(s_2_nt, GColorWhite);
  text_layer_set_text(s_2_nt, "3");
  text_layer_set_text_alignment(s_2_nt, GTextAlignmentCenter);
  text_layer_set_font(s_2_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_2_nt);
  
  // s_3_nt
  s_3_nt = text_layer_create(GRect(23, 40, 17, 17));
  text_layer_set_background_color(s_3_nt, GColorClear);
  text_layer_set_text_color(s_3_nt, GColorWhite);
  text_layer_set_text(s_3_nt, "3");
  text_layer_set_text_alignment(s_3_nt, GTextAlignmentCenter);
  text_layer_set_font(s_3_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_3_nt);
  
  // s_4_nt
  s_4_nt = text_layer_create(GRect(23, 53, 17, 17));
  text_layer_set_background_color(s_4_nt, GColorClear);
  text_layer_set_text_color(s_4_nt, GColorWhite);
  text_layer_set_text(s_4_nt, "3");
  text_layer_set_text_alignment(s_4_nt, GTextAlignmentCenter);
  text_layer_set_font(s_4_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_4_nt);
  
  // s_5_nt
  s_5_nt = text_layer_create(GRect(23, 66, 17, 17));
  text_layer_set_background_color(s_5_nt, GColorClear);
  text_layer_set_text_color(s_5_nt, GColorWhite);
  text_layer_set_text(s_5_nt, "3");
  text_layer_set_text_alignment(s_5_nt, GTextAlignmentCenter);
  text_layer_set_font(s_5_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_5_nt);
  
  // s_6_nt
  s_6_nt = text_layer_create(GRect(23, 79, 17, 17));
  text_layer_set_background_color(s_6_nt, GColorClear);
  text_layer_set_text_color(s_6_nt, GColorWhite);
  text_layer_set_text(s_6_nt, "3");
  text_layer_set_text_alignment(s_6_nt, GTextAlignmentCenter);
  text_layer_set_font(s_6_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_6_nt);
  
  // s_7_nt
  s_7_nt = text_layer_create(GRect(23, 92, 17, 17));
  text_layer_set_background_color(s_7_nt, GColorClear);
  text_layer_set_text_color(s_7_nt, GColorWhite);
  text_layer_set_text(s_7_nt, "3");
  text_layer_set_text_alignment(s_7_nt, GTextAlignmentCenter);
  text_layer_set_font(s_7_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_7_nt);
  
  // s_8_nt
  s_8_nt = text_layer_create(GRect(23, 105, 17, 17));
  text_layer_set_background_color(s_8_nt, GColorClear);
  text_layer_set_text_color(s_8_nt, GColorWhite);
  text_layer_set_text(s_8_nt, "3");
  text_layer_set_text_alignment(s_8_nt, GTextAlignmentCenter);
  text_layer_set_font(s_8_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_8_nt);
  
  // s_9_nt
  s_9_nt = text_layer_create(GRect(23, 118, 17, 17));
  text_layer_set_background_color(s_9_nt, GColorClear);
  text_layer_set_text_color(s_9_nt, GColorWhite);
  text_layer_set_text(s_9_nt, "3");
  text_layer_set_text_alignment(s_9_nt, GTextAlignmentCenter);
  text_layer_set_font(s_9_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_9_nt);
  
  // s_out_nt
  s_out_nt = text_layer_create(GRect(24, 132, 17, 17));
  text_layer_set_background_color(s_out_nt, GColorClear);
  text_layer_set_text_color(s_out_nt, GColorWhite);
  text_layer_set_text(s_out_nt, "50");
  text_layer_set_text_alignment(s_out_nt, GTextAlignmentCenter);
  text_layer_set_font(s_out_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_out_nt);
  
  // s_1_pt
  s_1_pt = text_layer_create(GRect(39, 14, 17, 17));
  text_layer_set_background_color(s_1_pt, GColorClear);
  text_layer_set_text_color(s_1_pt, GColorWhite);
  text_layer_set_text(s_1_pt, "2");
  text_layer_set_text_alignment(s_1_pt, GTextAlignmentCenter);
  text_layer_set_font(s_1_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_1_pt);
  
  // s_10
  s_10 = text_layer_create(GRect(54, 14, 17, 17));
  text_layer_set_background_color(s_10, GColorClear);
  text_layer_set_text_color(s_10, GColorWhite);
  text_layer_set_text(s_10, "10");
  text_layer_set_text_alignment(s_10, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_10);
  
  // s_10_gr
  s_10_gr = text_layer_create(GRect(67, 14, 17, 17));
  text_layer_set_background_color(s_10_gr, GColorClear);
  text_layer_set_text_color(s_10_gr, GColorWhite);
  text_layer_set_text(s_10_gr, "10");
  text_layer_set_text_alignment(s_10_gr, GTextAlignmentCenter);
  text_layer_set_font(s_10_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_10_gr);
  
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
  
  // s_10_nt
  s_10_nt = text_layer_create(GRect(84, 14, 17, 17));
  text_layer_set_background_color(s_10_nt, GColorClear);
  text_layer_set_text_color(s_10_nt, GColorWhite);
  text_layer_set_text(s_10_nt, "4");
  text_layer_set_text_alignment(s_10_nt, GTextAlignmentCenter);
  text_layer_set_font(s_10_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_10_nt);
  
  // s_10_pt
  s_10_pt = text_layer_create(GRect(98, 14, 17, 17));
  text_layer_set_background_color(s_10_pt, GColorClear);
  text_layer_set_text_color(s_10_pt, GColorWhite);
  text_layer_set_text(s_10_pt, "2");
  text_layer_set_text_alignment(s_10_pt, GTextAlignmentCenter);
  text_layer_set_font(s_10_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_10_pt);
  
  // s_3_pt
  s_3_pt = text_layer_create(GRect(39, 40, 17, 17));
  text_layer_set_background_color(s_3_pt, GColorClear);
  text_layer_set_text_color(s_3_pt, GColorWhite);
  text_layer_set_text(s_3_pt, "2");
  text_layer_set_text_alignment(s_3_pt, GTextAlignmentCenter);
  text_layer_set_font(s_3_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_3_pt);
  
  // s_4_pt
  s_4_pt = text_layer_create(GRect(39, 53, 17, 17));
  text_layer_set_background_color(s_4_pt, GColorClear);
  text_layer_set_text_color(s_4_pt, GColorWhite);
  text_layer_set_text(s_4_pt, "2");
  text_layer_set_text_alignment(s_4_pt, GTextAlignmentCenter);
  text_layer_set_font(s_4_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_4_pt);
  
  // s_5_pt
  s_5_pt = text_layer_create(GRect(39, 66, 17, 17));
  text_layer_set_background_color(s_5_pt, GColorClear);
  text_layer_set_text_color(s_5_pt, GColorWhite);
  text_layer_set_text(s_5_pt, "2");
  text_layer_set_text_alignment(s_5_pt, GTextAlignmentCenter);
  text_layer_set_font(s_5_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_5_pt);
  
  // s_6_pt
  s_6_pt = text_layer_create(GRect(39, 79, 17, 17));
  text_layer_set_background_color(s_6_pt, GColorClear);
  text_layer_set_text_color(s_6_pt, GColorWhite);
  text_layer_set_text(s_6_pt, "2");
  text_layer_set_text_alignment(s_6_pt, GTextAlignmentCenter);
  text_layer_set_font(s_6_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_6_pt);
  
  // s_7_pt
  s_7_pt = text_layer_create(GRect(39, 92, 17, 17));
  text_layer_set_background_color(s_7_pt, GColorClear);
  text_layer_set_text_color(s_7_pt, GColorWhite);
  text_layer_set_text(s_7_pt, "2");
  text_layer_set_text_alignment(s_7_pt, GTextAlignmentCenter);
  text_layer_set_font(s_7_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_7_pt);
  
  // s_8_pt
  s_8_pt = text_layer_create(GRect(39, 105, 17, 17));
  text_layer_set_background_color(s_8_pt, GColorClear);
  text_layer_set_text_color(s_8_pt, GColorWhite);
  text_layer_set_text(s_8_pt, "2");
  text_layer_set_text_alignment(s_8_pt, GTextAlignmentCenter);
  text_layer_set_font(s_8_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_8_pt);
  
  // s_9_pt
  s_9_pt = text_layer_create(GRect(39, 118, 17, 17));
  text_layer_set_background_color(s_9_pt, GColorClear);
  text_layer_set_text_color(s_9_pt, GColorWhite);
  text_layer_set_text(s_9_pt, "2");
  text_layer_set_text_alignment(s_9_pt, GTextAlignmentCenter);
  text_layer_set_font(s_9_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_9_pt);
  
  // s_out_pt
  s_out_pt = text_layer_create(GRect(39, 132, 17, 17));
  text_layer_set_background_color(s_out_pt, GColorClear);
  text_layer_set_text_color(s_out_pt, GColorWhite);
  text_layer_set_text(s_out_pt, "24");
  text_layer_set_text_alignment(s_out_pt, GTextAlignmentCenter);
  text_layer_set_font(s_out_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_out_pt);
  
  // s_11
  s_11 = text_layer_create(GRect(54, 27, 17, 17));
  text_layer_set_background_color(s_11, GColorClear);
  text_layer_set_text_color(s_11, GColorWhite);
  text_layer_set_text(s_11, "11");
  text_layer_set_text_alignment(s_11, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_11);
  
  // s_12
  s_12 = text_layer_create(GRect(54, 40, 17, 17));
  text_layer_set_background_color(s_12, GColorClear);
  text_layer_set_text_color(s_12, GColorWhite);
  text_layer_set_text(s_12, "12");
  text_layer_set_text_alignment(s_12, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_12);
  
  // s_13
  s_13 = text_layer_create(GRect(54, 53, 17, 17));
  text_layer_set_background_color(s_13, GColorClear);
  text_layer_set_text_color(s_13, GColorWhite);
  text_layer_set_text(s_13, "13");
  text_layer_set_text_alignment(s_13, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_13);
  
  // s_14
  s_14 = text_layer_create(GRect(54, 66, 17, 17));
  text_layer_set_background_color(s_14, GColorClear);
  text_layer_set_text_color(s_14, GColorWhite);
  text_layer_set_text(s_14, "14");
  text_layer_set_text_alignment(s_14, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_14);
  
  // s_15
  s_15 = text_layer_create(GRect(54, 79, 17, 17));
  text_layer_set_background_color(s_15, GColorClear);
  text_layer_set_text_color(s_15, GColorWhite);
  text_layer_set_text(s_15, "15");
  text_layer_set_text_alignment(s_15, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_15);
  
  // s_2_pt
  s_2_pt = text_layer_create(GRect(39, 27, 17, 17));
  text_layer_set_background_color(s_2_pt, GColorClear);
  text_layer_set_text_color(s_2_pt, GColorWhite);
  text_layer_set_text(s_2_pt, "2");
  text_layer_set_text_alignment(s_2_pt, GTextAlignmentCenter);
  text_layer_set_font(s_2_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_2_pt);
  
  // s_16
  s_16 = text_layer_create(GRect(54, 92, 17, 17));
  text_layer_set_background_color(s_16, GColorClear);
  text_layer_set_text_color(s_16, GColorWhite);
  text_layer_set_text(s_16, "16");
  text_layer_set_text_alignment(s_16, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_16);
  
  // s_17
  s_17 = text_layer_create(GRect(54, 105, 17, 17));
  text_layer_set_background_color(s_17, GColorClear);
  text_layer_set_text_color(s_17, GColorWhite);
  text_layer_set_text(s_17, "17");
  text_layer_set_text_alignment(s_17, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_17);
  
  // s_18
  s_18 = text_layer_create(GRect(54, 118, 17, 17));
  text_layer_set_background_color(s_18, GColorClear);
  text_layer_set_text_color(s_18, GColorWhite);
  text_layer_set_text(s_18, "18");
  text_layer_set_text_alignment(s_18, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_18);
  
  // s_11_gr
  s_11_gr = text_layer_create(GRect(68, 27, 17, 17));
  text_layer_set_background_color(s_11_gr, GColorClear);
  text_layer_set_text_color(s_11_gr, GColorWhite);
  text_layer_set_text(s_11_gr, "4");
  text_layer_set_text_alignment(s_11_gr, GTextAlignmentCenter);
  text_layer_set_font(s_11_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_11_gr);
  
  // s_12_gr
  s_12_gr = text_layer_create(GRect(68, 40, 17, 17));
  text_layer_set_background_color(s_12_gr, GColorClear);
  text_layer_set_text_color(s_12_gr, GColorWhite);
  text_layer_set_text(s_12_gr, "4");
  text_layer_set_text_alignment(s_12_gr, GTextAlignmentCenter);
  text_layer_set_font(s_12_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_12_gr);
  
  // s_13_gr
  s_13_gr = text_layer_create(GRect(68, 53, 17, 17));
  text_layer_set_background_color(s_13_gr, GColorClear);
  text_layer_set_text_color(s_13_gr, GColorWhite);
  text_layer_set_text(s_13_gr, "4");
  text_layer_set_text_alignment(s_13_gr, GTextAlignmentCenter);
  text_layer_set_font(s_13_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_13_gr);
  
  // s_14_gr
  s_14_gr = text_layer_create(GRect(68, 66, 17, 17));
  text_layer_set_background_color(s_14_gr, GColorClear);
  text_layer_set_text_color(s_14_gr, GColorWhite);
  text_layer_set_text(s_14_gr, "4");
  text_layer_set_text_alignment(s_14_gr, GTextAlignmentCenter);
  text_layer_set_font(s_14_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_14_gr);
  
  // s_15_gr
  s_15_gr = text_layer_create(GRect(68, 79, 17, 17));
  text_layer_set_background_color(s_15_gr, GColorClear);
  text_layer_set_text_color(s_15_gr, GColorWhite);
  text_layer_set_text(s_15_gr, "4");
  text_layer_set_text_alignment(s_15_gr, GTextAlignmentCenter);
  text_layer_set_font(s_15_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_15_gr);
  
  // s_16_gr
  s_16_gr = text_layer_create(GRect(68, 92, 17, 17));
  text_layer_set_background_color(s_16_gr, GColorClear);
  text_layer_set_text_color(s_16_gr, GColorWhite);
  text_layer_set_text(s_16_gr, "4");
  text_layer_set_text_alignment(s_16_gr, GTextAlignmentCenter);
  text_layer_set_font(s_16_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_16_gr);
  
  // s_17_gr
  s_17_gr = text_layer_create(GRect(68, 105, 17, 17));
  text_layer_set_background_color(s_17_gr, GColorClear);
  text_layer_set_text_color(s_17_gr, GColorWhite);
  text_layer_set_text(s_17_gr, "4");
  text_layer_set_text_alignment(s_17_gr, GTextAlignmentCenter);
  text_layer_set_font(s_17_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_17_gr);
  
  // s_18_gr
  s_18_gr = text_layer_create(GRect(68, 118, 17, 17));
  text_layer_set_background_color(s_18_gr, GColorClear);
  text_layer_set_text_color(s_18_gr, GColorWhite);
  text_layer_set_text(s_18_gr, "4");
  text_layer_set_text_alignment(s_18_gr, GTextAlignmentCenter);
  text_layer_set_font(s_18_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_18_gr);
  
  // s_in_gr
  s_in_gr = text_layer_create(GRect(68, 132, 17, 17));
  text_layer_set_background_color(s_in_gr, GColorClear);
  text_layer_set_text_color(s_in_gr, GColorWhite);
  text_layer_set_text(s_in_gr, "50");
  text_layer_set_text_alignment(s_in_gr, GTextAlignmentCenter);
  text_layer_set_font(s_in_gr, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_in_gr);
  
  // s_11_nt
  s_11_nt = text_layer_create(GRect(84, 27, 17, 17));
  text_layer_set_background_color(s_11_nt, GColorClear);
  text_layer_set_text_color(s_11_nt, GColorWhite);
  text_layer_set_text(s_11_nt, "4");
  text_layer_set_text_alignment(s_11_nt, GTextAlignmentCenter);
  text_layer_set_font(s_11_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_11_nt);
  
  // s_12_nt
  s_12_nt = text_layer_create(GRect(84, 40, 17, 17));
  text_layer_set_background_color(s_12_nt, GColorClear);
  text_layer_set_text_color(s_12_nt, GColorWhite);
  text_layer_set_text(s_12_nt, "4");
  text_layer_set_text_alignment(s_12_nt, GTextAlignmentCenter);
  text_layer_set_font(s_12_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_12_nt);
  
  // s_13_nt
  s_13_nt = text_layer_create(GRect(84, 53, 17, 17));
  text_layer_set_background_color(s_13_nt, GColorClear);
  text_layer_set_text_color(s_13_nt, GColorWhite);
  text_layer_set_text(s_13_nt, "4");
  text_layer_set_text_alignment(s_13_nt, GTextAlignmentCenter);
  text_layer_set_font(s_13_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_13_nt);
  
  // s_14_nt
  s_14_nt = text_layer_create(GRect(84, 66, 17, 17));
  text_layer_set_background_color(s_14_nt, GColorClear);
  text_layer_set_text_color(s_14_nt, GColorWhite);
  text_layer_set_text(s_14_nt, "4");
  text_layer_set_text_alignment(s_14_nt, GTextAlignmentCenter);
  text_layer_set_font(s_14_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_14_nt);
  
  // s_15_nt
  s_15_nt = text_layer_create(GRect(84, 79, 17, 17));
  text_layer_set_background_color(s_15_nt, GColorClear);
  text_layer_set_text_color(s_15_nt, GColorWhite);
  text_layer_set_text(s_15_nt, "4");
  text_layer_set_text_alignment(s_15_nt, GTextAlignmentCenter);
  text_layer_set_font(s_15_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_15_nt);
  
  // s_16_nt
  s_16_nt = text_layer_create(GRect(84, 92, 17, 17));
  text_layer_set_background_color(s_16_nt, GColorClear);
  text_layer_set_text_color(s_16_nt, GColorWhite);
  text_layer_set_text(s_16_nt, "4");
  text_layer_set_text_alignment(s_16_nt, GTextAlignmentCenter);
  text_layer_set_font(s_16_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_16_nt);
  
  // s_17_nt
  s_17_nt = text_layer_create(GRect(84, 105, 17, 17));
  text_layer_set_background_color(s_17_nt, GColorClear);
  text_layer_set_text_color(s_17_nt, GColorWhite);
  text_layer_set_text(s_17_nt, "4");
  text_layer_set_text_alignment(s_17_nt, GTextAlignmentCenter);
  text_layer_set_font(s_17_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_17_nt);
  
  // s_18_nt
  s_18_nt = text_layer_create(GRect(84, 118, 17, 17));
  text_layer_set_background_color(s_18_nt, GColorClear);
  text_layer_set_text_color(s_18_nt, GColorWhite);
  text_layer_set_text(s_18_nt, "4");
  text_layer_set_text_alignment(s_18_nt, GTextAlignmentCenter);
  text_layer_set_font(s_18_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_18_nt);
  
  // s_in_nt
  s_in_nt = text_layer_create(GRect(84, 132, 17, 17));
  text_layer_set_background_color(s_in_nt, GColorClear);
  text_layer_set_text_color(s_in_nt, GColorWhite);
  text_layer_set_text(s_in_nt, "50");
  text_layer_set_text_alignment(s_in_nt, GTextAlignmentCenter);
  text_layer_set_font(s_in_nt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_in_nt);
  
  // s_11_pt
  s_11_pt = text_layer_create(GRect(98, 27, 17, 17));
  text_layer_set_background_color(s_11_pt, GColorClear);
  text_layer_set_text_color(s_11_pt, GColorWhite);
  text_layer_set_text(s_11_pt, "2");
  text_layer_set_text_alignment(s_11_pt, GTextAlignmentCenter);
  text_layer_set_font(s_11_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_11_pt);
  
  // s_12_pt
  s_12_pt = text_layer_create(GRect(98, 40, 17, 17));
  text_layer_set_background_color(s_12_pt, GColorClear);
  text_layer_set_text_color(s_12_pt, GColorWhite);
  text_layer_set_text(s_12_pt, "2");
  text_layer_set_text_alignment(s_12_pt, GTextAlignmentCenter);
  text_layer_set_font(s_12_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_12_pt);
  
  // s_13_pt
  s_13_pt = text_layer_create(GRect(98, 53, 17, 17));
  text_layer_set_background_color(s_13_pt, GColorClear);
  text_layer_set_text_color(s_13_pt, GColorWhite);
  text_layer_set_text(s_13_pt, "2");
  text_layer_set_text_alignment(s_13_pt, GTextAlignmentCenter);
  text_layer_set_font(s_13_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_13_pt);
  
  // s_14_pt
  s_14_pt = text_layer_create(GRect(98, 66, 17, 17));
  text_layer_set_background_color(s_14_pt, GColorClear);
  text_layer_set_text_color(s_14_pt, GColorWhite);
  text_layer_set_text(s_14_pt, "2");
  text_layer_set_text_alignment(s_14_pt, GTextAlignmentCenter);
  text_layer_set_font(s_14_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_14_pt);
  
  // s_15_pt
  s_15_pt = text_layer_create(GRect(98, 80, 17, 17));
  text_layer_set_background_color(s_15_pt, GColorClear);
  text_layer_set_text_color(s_15_pt, GColorWhite);
  text_layer_set_text(s_15_pt, "2");
  text_layer_set_text_alignment(s_15_pt, GTextAlignmentCenter);
  text_layer_set_font(s_15_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_15_pt);
  
  // s_16_pt
  s_16_pt = text_layer_create(GRect(98, 92, 17, 17));
  text_layer_set_background_color(s_16_pt, GColorClear);
  text_layer_set_text_color(s_16_pt, GColorWhite);
  text_layer_set_text(s_16_pt, "2");
  text_layer_set_text_alignment(s_16_pt, GTextAlignmentCenter);
  text_layer_set_font(s_16_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_16_pt);
  
  // s_17_pt
  s_17_pt = text_layer_create(GRect(98, 105, 17, 17));
  text_layer_set_background_color(s_17_pt, GColorClear);
  text_layer_set_text_color(s_17_pt, GColorWhite);
  text_layer_set_text(s_17_pt, "2");
  text_layer_set_text_alignment(s_17_pt, GTextAlignmentCenter);
  text_layer_set_font(s_17_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_17_pt);
  
  // s_18_pt
  s_18_pt = text_layer_create(GRect(98, 118, 17, 17));
  text_layer_set_background_color(s_18_pt, GColorClear);
  text_layer_set_text_color(s_18_pt, GColorWhite);
  text_layer_set_text(s_18_pt, "2");
  text_layer_set_text_alignment(s_18_pt, GTextAlignmentCenter);
  text_layer_set_font(s_18_pt, s_res_gothic_14);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_18_pt);
  
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
  text_layer_destroy(s_1);
  text_layer_destroy(s_2);
  text_layer_destroy(s_3);
  text_layer_destroy(s_4);
  text_layer_destroy(s_5);
  text_layer_destroy(s_6);
  text_layer_destroy(s_8);
  text_layer_destroy(s_9);
  text_layer_destroy(s_gross_out);
  text_layer_destroy(s_net_out);
  text_layer_destroy(s_points_out);
  text_layer_destroy(s_1_gr);
  text_layer_destroy(s_2_gr);
  text_layer_destroy(s_3_gr);
  text_layer_destroy(s_4_gr);
  text_layer_destroy(s_5_gr);
  text_layer_destroy(s_7);
  text_layer_destroy(s_6_gr);
  text_layer_destroy(s_7_gr);
  text_layer_destroy(s_8_gr);
  text_layer_destroy(s_9_gr);
  text_layer_destroy(s_out_gr);
  text_layer_destroy(s_1_nt);
  text_layer_destroy(s_2_nt);
  text_layer_destroy(s_3_nt);
  text_layer_destroy(s_4_nt);
  text_layer_destroy(s_5_nt);
  text_layer_destroy(s_6_nt);
  text_layer_destroy(s_7_nt);
  text_layer_destroy(s_8_nt);
  text_layer_destroy(s_9_nt);
  text_layer_destroy(s_out_nt);
  text_layer_destroy(s_1_pt);
  text_layer_destroy(s_10);
  text_layer_destroy(s_10_gr);
  text_layer_destroy(s_gross_in);
  text_layer_destroy(s_net_in);
  text_layer_destroy(s_in_points);
  text_layer_destroy(s_10_nt);
  text_layer_destroy(s_10_pt);
  text_layer_destroy(s_3_pt);
  text_layer_destroy(s_4_pt);
  text_layer_destroy(s_5_pt);
  text_layer_destroy(s_6_pt);
  text_layer_destroy(s_7_pt);
  text_layer_destroy(s_8_pt);
  text_layer_destroy(s_9_pt);
  text_layer_destroy(s_out_pt);
  text_layer_destroy(s_11);
  text_layer_destroy(s_12);
  text_layer_destroy(s_13);
  text_layer_destroy(s_14);
  text_layer_destroy(s_15);
  text_layer_destroy(s_2_pt);
  text_layer_destroy(s_16);
  text_layer_destroy(s_17);
  text_layer_destroy(s_18);
  text_layer_destroy(s_11_gr);
  text_layer_destroy(s_12_gr);
  text_layer_destroy(s_13_gr);
  text_layer_destroy(s_14_gr);
  text_layer_destroy(s_15_gr);
  text_layer_destroy(s_16_gr);
  text_layer_destroy(s_17_gr);
  text_layer_destroy(s_18_gr);
  text_layer_destroy(s_in_gr);
  text_layer_destroy(s_11_nt);
  text_layer_destroy(s_12_nt);
  text_layer_destroy(s_13_nt);
  text_layer_destroy(s_14_nt);
  text_layer_destroy(s_15_nt);
  text_layer_destroy(s_16_nt);
  text_layer_destroy(s_17_nt);
  text_layer_destroy(s_18_nt);
  text_layer_destroy(s_in_nt);
  text_layer_destroy(s_11_pt);
  text_layer_destroy(s_12_pt);
  text_layer_destroy(s_13_pt);
  text_layer_destroy(s_14_pt);
  text_layer_destroy(s_15_pt);
  text_layer_destroy(s_16_pt);
  text_layer_destroy(s_17_pt);
  text_layer_destroy(s_18_pt);
  text_layer_destroy(s_in_pt);
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(s_tot_gr);
  text_layer_destroy(s_textlayer_2);
  text_layer_destroy(s_tot_nt);
  text_layer_destroy(s_textlayer_3);
  text_layer_destroy(s_tot_pt);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

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

void display_scores(void) {
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
  
}




