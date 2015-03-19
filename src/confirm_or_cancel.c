#include <pebble.h>
#include "confirm_or_cancel.h"

  
#define MENU_ROW_CANCEL 0
#define MENU_ROW_CONFIRM 1
  
static confirm_or_cancel_callback callback_function;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static MenuLayer *s_confirm_or_cancel;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  // s_confirm_or_cancel
  s_confirm_or_cancel = menu_layer_create(GRect(0, 0, 144, 152));
  menu_layer_set_click_config_onto_window(s_confirm_or_cancel, s_window);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_confirm_or_cancel);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  menu_layer_destroy(s_confirm_or_cancel);
}
// END AUTO-GENERATED UI CODE

static uint16_t confirm_or_cancel_get_num_rows(struct MenuLayer* menu, uint16_t section_index, void* callback_context) {
  return 2;
}

static uint16_t confirm_or_cancel_get_header_height(struct MenuLayer* menu, uint16_t section_index, void* callback_context) {
  return 18;
}
static void handle_window_unload(Window* window) {
  destroy_ui();
}
static void confirm_or_cancel_draw_row(GContext* ctx, const Layer* cell_layer, MenuIndex* cell_index, void* callback_context) {
  switch (cell_index->row) {
    case MENU_ROW_CANCEL:
      menu_cell_basic_draw(ctx, cell_layer, "Cancel", NULL, NULL);
      break;
    case MENU_ROW_CONFIRM:
      menu_cell_basic_draw(ctx, cell_layer, "Confirm", NULL, NULL);
      break;
  }
}
static void confirm_or_cancel_select_click(struct MenuLayer* menu, MenuIndex* cell_index, void* callback_context) {
  switch (cell_index->row) {
    case MENU_ROW_CANCEL:
      window_stack_pop(true);
      hide_confirm_or_cancel();
      callback_function(false);
      break;
    case MENU_ROW_CONFIRM:
      window_stack_pop(true);
      hide_confirm_or_cancel();
      callback_function(true);
      break;
  }
}
static void confirm_or_cancel_draw_header(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *callback_context) {
  menu_cell_basic_header_draw(ctx, cell_layer, "Are you sure?");
}


void show_confirm_or_cancel(confirm_or_cancel_callback ptr_confirm_cancel_callback) {
  callback_function = ptr_confirm_cancel_callback;
  initialise_ui();
   menu_layer_set_callbacks(s_confirm_or_cancel, s_confirm_or_cancel, (MenuLayerCallbacks){
    .draw_header = confirm_or_cancel_draw_header,
    .draw_row = confirm_or_cancel_draw_row,
    .get_num_rows = confirm_or_cancel_get_num_rows,
    .select_click = confirm_or_cancel_select_click,
    .get_header_height = (MenuLayerGetHeaderHeightCallback)confirm_or_cancel_get_header_height,
  } );
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_confirm_or_cancel(void) {
  window_stack_remove(s_window, true);
}
