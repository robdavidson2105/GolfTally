#include <pebble.h>
#include "globals.h"

static uint8_t handicap;
struct holes {
  uint8_t par;
  uint8_t si;
  uint8_t my_strokes;
  uint8_t my_net;
  uint8_t my_points;
} hole[18];
  
void set_handicap(uint8_t new_handicap) {
  handicap = new_handicap;
}

uint8_t get_handicap(void) {
  return handicap;
}


uint8_t get_par(uint8_t hole_index) {
  return hole[hole_index].par;
};
uint8_t get_si(uint8_t hole_index) {
  return hole[hole_index].si;
};

uint8_t get_my_net(uint8_t hole_index) {
  return hole[hole_index].my_net;
};

uint8_t get_my_points(uint8_t hole_index) {
  return hole[hole_index].my_points;
};

uint8_t get_my_strokes(uint8_t hole_index) {
  return hole[hole_index].my_strokes;
};

void set_my_strokes(uint8_t hole_index, uint8_t new_strokes) {
  hole[hole_index].my_strokes = new_strokes;
};

void setup_holes(uint8_t hole_index, uint8_t par, uint8_t si) {
  hole[hole_index].par = par;
  hole[hole_index].si = si;
  hole[hole_index].my_strokes = si+1;
  hole[hole_index].my_net = 0;
  hole[hole_index].my_points = 0;
};
