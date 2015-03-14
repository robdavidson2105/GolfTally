#include <pebble.h>
#include "globals.h"
#include "choose_hole.h"
#include "current_hole_details.h"
  
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static MenuLayer *s_holes_menu;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  // s_holes_menu
  s_holes_menu = menu_layer_create(GRect(0, 0, 144, 152));
  menu_layer_set_click_config_onto_window(s_holes_menu, s_window);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_holes_menu);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  menu_layer_destroy(s_holes_menu);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

static uint16_t holes_menu_get_num_rows(struct MenuLayer* menu, uint16_t section_index, void* callback_context) {
  return 18;
}

static void holes_menu_draw_row(GContext* ctx, const Layer* cell_layer, MenuIndex* cell_index, void* callback_context) {

  char title[] = "18 / Par 3 / SI 18";
  snprintf(title, sizeof(title), 
           "%d / Par %d / SI %d", 
           (cell_index->row)+1, 
           get_par(cell_index->row), 
           get_si(cell_index->row));
  char subtitle[] = "10/Net 10/Pts 5";
  snprintf(subtitle, sizeof(subtitle), 
           "%d/Net %d/Pts %d", 
           get_my_strokes(cell_index->row), 
           get_my_net(cell_index->row), 
           get_my_points(cell_index->row));
  menu_cell_basic_draw(ctx, cell_layer, title, subtitle, NULL);
}

static void holes_menu_select_click(struct MenuLayer* menu, MenuIndex* cell_index, void* callback_context) {
  show_current_hole_details(cell_index->row, callback_context);
  
}




void show_choose_hole(void) {
  initialise_ui();
  menu_layer_set_callbacks(s_holes_menu, s_holes_menu, (MenuLayerCallbacks){
    .draw_row = holes_menu_draw_row,
    .get_num_rows = holes_menu_get_num_rows,
    .select_click = holes_menu_select_click,
  } );
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_choose_hole(void) {
  window_stack_remove(s_window, true);
}
