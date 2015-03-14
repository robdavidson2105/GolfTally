#include <pebble.h>
void set_handicap(uint8_t new_handicap);
uint8_t get_handicap(void);

uint8_t get_par(uint8_t hole_index);
uint8_t get_si(uint8_t hole_index);
int8_t get_my_net(uint8_t hole_index);
int8_t get_my_points(uint8_t hole_index);
uint8_t get_my_strokes(uint8_t hole_index);
uint8_t get_my_shots_received(uint8_t hole_index);
void set_my_strokes(uint8_t hole_index, int8_t new_strokes);
void setup_holes(uint8_t hole_index, uint8_t par, uint8_t si);

uint8_t calculate_shots(uint8_t si, uint8_t handicap);

