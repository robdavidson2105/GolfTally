#include <pebble.h>
#include "globals.h"

#define PI 3.14159265  
  
static uint8_t handicap;
struct holes {
  uint8_t par;
  uint8_t si;
  uint8_t my_strokes;
  uint8_t my_shots_received;
  int8_t my_net;
  int8_t my_points;
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

int8_t get_my_net(uint8_t hole_index) {
  return hole[hole_index].my_net;
};

int8_t get_my_points(uint8_t hole_index) {
  return hole[hole_index].my_points;
};

uint8_t get_my_shots_received(uint8_t hole_index) {
  return hole[hole_index].my_shots_received;
};

uint8_t get_my_strokes(uint8_t hole_index) {
  return hole[hole_index].my_strokes;
};


void set_my_strokes(uint8_t hole_index, int8_t new_strokes) {
  if (new_strokes <= 0) {
    hole[hole_index].my_strokes = 0;
    hole[hole_index].my_net = 0;
    hole[hole_index].my_points = 0;
    return;
  }
  hole[hole_index].my_strokes = new_strokes;
  hole[hole_index].my_net = new_strokes - hole[hole_index].my_shots_received;
  hole[hole_index].my_points = 2 - (hole[hole_index].my_net - hole[hole_index].par);
  if (hole[hole_index].my_points < 0) {
    hole[hole_index].my_points = 0;
  }
};

void setup_holes(uint8_t hole_index, uint8_t par, uint8_t si) {
  hole[hole_index].par = par;
  hole[hole_index].si = si;
  hole[hole_index].my_strokes = 0;
  hole[hole_index].my_net = 0;
  hole[hole_index].my_points = 0;
  hole[hole_index].my_shots_received = calculate_shots(si, get_handicap());
};

uint8_t calculate_shots(uint8_t si, uint8_t handicap) {
  uint8_t shots = 0;
  if (handicap >= si) {
    shots++;
    handicap = handicap - 18;
    if (handicap >= si) {
      shots++;
    }
  }
  return shots;
}

double cosine(double x) {
  double cos = 0.0;
  x += 1.57079632;
  if (x >  3.14159265)
      x -= 6.28318531;
    if (x < 0) { 
    cos = 1.27323954 * x + 0.405284735 * x * x;
    
    if (cos < 0)
        cos = .225 * (cos *-cos - cos) + cos;
    else
        cos = .225 * (cos * cos - cos) + cos;
    }
    else
    {
    cos = 1.27323954 * x - 0.405284735 * x * x;

    if (cos < 0)
        cos = .225 * (cos *-cos - cos) + cos;
    else
        cos = .225 * (cos * cos - cos) + cos;
    }
  return cos;
}

#define SQRT_MAGIC_F 0x5f3759df 
float my_sqrt(const float x)
{
  const float xhalf = 0.5f*x;
 
  union // get bits for floating value
  {
    float x;
    int i;
  } u;
  u.x = x;
  u.i = SQRT_MAGIC_F - (u.i >> 1);  // gives initial guess y0
  return x*u.x*(1.5f - xhalf*u.x*u.x);// Newton step, repeating increases accuracy 
}

int calculate_distance(double lat1, double long1, double lat2, double long2) {
  lat1 = PI * lat1 / 180.0;
  lat2 = PI * lat2 / 180.0;
  long1 = PI * long1 / 180.0;
  long2 = PI * long2 / 180.0;
  double x = long2 - long1;
  x = x * cosine((lat1 + lat2)/2.0);
  double y = lat2 - lat1;
  double distance = x * x + y * y ;
  distance = 6967325 * my_sqrt(distance);
  return (int)(distance);
}

