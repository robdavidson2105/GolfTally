#include <pebble.h>
#include "globals.h"
#include "main_menu.h"
#include "choose_handicap.h"
#include "choose_hole.h"
#include "choose_course.h"
#include "confirm_or_cancel.h"
  
  
#define MENU_ROW_SET_HANDICAP 0
#define MENU_ROW_CHOOSE_COURSE 1
#define MENU_ROW_START_GAME 2
#define MENU_ROW_CLEAR_ROUND 3

void confirm_clear_scores_callback(bool result);  

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

// Number of rows in the main menu - it changes once we've selected a course - or we've
// started a round
static uint16_t main_menu_get_num_rows(struct MenuLayer* menu, uint16_t section_index, void* callback_context) {
  if (is_round_in_progress) {
    // If there's a round in progress then we must need all the rows
    return 4;
  } else {
    if (selected_course_index == -1) {
    // If there's no course selected then don't draw the Start Round row
      return 2;
    } else {
      // If there's no round in progress then don't draw the clear scores row
      return 3;
    }
  }
}

/// Draw the menu rows
static void main_menu_draw_row(GContext* ctx, const Layer* cell_layer, MenuIndex* cell_index, void* callback_context) {
  if (cell_index->row == MENU_ROW_SET_HANDICAP) {
    // Choose the handicap
      static char subtitle[] = "My handicap: 18";
      snprintf(subtitle, sizeof(subtitle), "My handicap: %d", get_handicap());
      menu_cell_basic_draw(ctx, cell_layer, "Set Handicap", subtitle, NULL);
  } else if (cell_index->row == MENU_ROW_CHOOSE_COURSE) {
    // Choose the course
      if (selected_course_index == -1) {
        menu_cell_basic_draw(ctx, cell_layer, "Choose Course", "None selected", NULL);  
      } else {
        menu_cell_basic_draw(ctx, cell_layer, "Choose Course", get_course(selected_course_index), NULL);
      } 
  } else if (cell_index->row == MENU_ROW_START_GAME) {
    // Start the game
      //If there's a round in progress then text should say continue
      if (is_round_in_progress) {
        menu_cell_basic_draw(ctx, cell_layer, "Continue round", NULL, NULL);
      } else {
        if (selected_course_index != -1) {
          menu_cell_basic_draw(ctx, cell_layer, "Start round", NULL, NULL);
        } 
      }
  } else if (cell_index->row == MENU_ROW_CLEAR_ROUND) {
    // Clear all the scores
      //If there's no round in progress then don't draw the clear scores row
      if (is_round_in_progress) {
        menu_cell_basic_draw(ctx, cell_layer, "Clear scores", NULL, NULL);
      }
  }
}
  
  
  
  /*
  switch (cell_index->row) {
    // Choose the handicap
    // had to put a ; at the end of the next line - otherwise the compiler didn't like it
    case MENU_ROW_SET_HANDICAP: ;
      static char subtitle[] = "My handicap: 18";
      snprintf(subtitle, sizeof(subtitle), "My handicap: %d", get_handicap());
      menu_cell_basic_draw(ctx, cell_layer, "Set Handicap", subtitle, NULL);
      break;
    // Choose the course
    case MENU_ROW_CHOOSE_COURSE:
      if (selected_course_index == -1) {
        menu_cell_basic_draw(ctx, cell_layer, "Choose Course", "None selected", NULL);  
      } else {
        menu_cell_basic_draw(ctx, cell_layer, "Choose Course", get_course(selected_course_index), NULL);
      } 
      break;
    // Start the game
    case MENU_ROW_START_GAME:
      //If there's a round in progress then text should say continue
      if (is_round_in_progress) {
        menu_cell_basic_draw(ctx, cell_layer, "Continue round", NULL, NULL);
      } else {
        if (selected_course_index != -1) {
          menu_cell_basic_draw(ctx, cell_layer, "Start round", NULL, NULL);
        } 
      }
      break;
    // Clear all the scores
    case MENU_ROW_CLEAR_ROUND:
      //If there's no round in progress then don't draw the clear scores row
      if (is_round_in_progress) {
        menu_cell_basic_draw(ctx, cell_layer, "Clear scores", NULL, NULL);
      }
      break;
  }  */

// Click handler for the menu
static void main_menu_select_click(struct MenuLayer* menu, MenuIndex* cell_index, void* callback_context) {
  if (cell_index->row == MENU_ROW_SET_HANDICAP) {
      show_choose_handicap();
  } else if (cell_index->row == MENU_ROW_CHOOSE_COURSE) {
      show_choose_course(callback_context);
  } else if (cell_index->row == MENU_ROW_START_GAME) {
      // Only start a game if we have already selected a course to play
      if (selected_course_index != -1) {
        is_round_in_progress = true;
        show_choose_hole();
        menu_layer_reload_data(s_main_menu);
        layer_mark_dirty(menu_layer_get_layer(s_main_menu));
      }
  } else if (cell_index->row == MENU_ROW_CLEAR_ROUND) {
      void (*ptr_confirm_or_cancel_callback)(bool);
      //show the confirm or cancel dialog box and send a pointer to
      //the callback function
      ptr_confirm_or_cancel_callback = confirm_clear_scores_callback;
      show_confirm_or_cancel(ptr_confirm_or_cancel_callback);
  }
}

void confirm_clear_scores_callback(bool result) {
  if (result) {
    for (uint8_t i = 0; i < 18; i++) {
        set_my_strokes(i, 0);
      }
    is_round_in_progress = false;
    // We need to reload the data in the MenuLayer
    menu_layer_reload_data(s_main_menu);
    // The MenuLayer needs to redraw otherwise it doesn't scroll correctly
    layer_mark_dirty(menu_layer_get_layer(s_main_menu));
  }
}

// Main entry function to create the menu
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
