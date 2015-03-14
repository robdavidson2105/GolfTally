#include <pebble.h>
#include "globals.h"
#include "main_menu.h"
#include "choose_handicap.h"
#include "choose_hole.h"
  
  
#define MENU_ROW_SET_HANDICAP 0
#define MENU_ROW_CHOOSE_COURSE 1
#define MENU_ROW_START_GAME 2

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static MenuLayer *s_main_menu;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  // s_main_menu
  s_main_menu = menu_layer_create(GRect(0, 0, 144, 152));
  menu_layer_set_click_config_onto_window(s_main_menu, s_window);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_main_menu);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  menu_layer_destroy(s_main_menu);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

static uint16_t main_menu_get_num_rows(struct MenuLayer* menu, uint16_t section_index, void* callback_context) {
  return 3;
}

static void main_menu_draw_row(GContext* ctx, const Layer* cell_layer, MenuIndex* cell_index, void* callback_context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG,"Draw rows");
  
  switch (cell_index->row) {
    case MENU_ROW_SET_HANDICAP:
      APP_LOG(APP_LOG_LEVEL_DEBUG,"Draw hcap row");
      char subtitle[] = "My handicap: 18";
      snprintf(subtitle, sizeof(subtitle), "My handicap: %d", get_handicap());
      menu_cell_basic_draw(ctx, cell_layer, "Set Handicap", subtitle, NULL);
      break;
    case MENU_ROW_CHOOSE_COURSE:
      APP_LOG(APP_LOG_LEVEL_DEBUG,"Draw course row");
      menu_cell_basic_draw(ctx, cell_layer, "Choose Course", "None selected", NULL);
      break;
    case MENU_ROW_START_GAME:
      menu_cell_basic_draw(ctx, cell_layer, "Lets go", NULL, NULL);
      break;
  }
}

static void main_menu_select_click(struct MenuLayer* menu, MenuIndex* cell_index, void* callback_context) {
  switch (cell_index->row) {
    case MENU_ROW_SET_HANDICAP:
      APP_LOG(APP_LOG_LEVEL_DEBUG,"Set hcap");
      show_choose_handicap();
      break;
    case MENU_ROW_CHOOSE_COURSE:
      APP_LOG(APP_LOG_LEVEL_DEBUG,"Choose Course");
      break;
    case MENU_ROW_START_GAME:
      APP_LOG(APP_LOG_LEVEL_DEBUG,"Start Game");
      show_choose_hole();
      break;
  }
}


void show_main_menu(void) {
  initialise_ui();
  menu_layer_set_callbacks(s_main_menu, s_main_menu, (MenuLayerCallbacks){
    .draw_row = main_menu_draw_row,
    .get_num_rows = main_menu_get_num_rows,
    .select_click = main_menu_select_click,
  } );
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_main_menu(void) {
  window_stack_remove(s_window, true);
}
