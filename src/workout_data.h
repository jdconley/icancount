#include <pebble.h>
  
#define MAX_SPLITS 11 //store the last 10 splits, and the start time
#define MAX_COUNTER 999 //the max number on the "split" counter

typedef struct stopwatch_time stopwatch_time;
struct stopwatch_time {
  time_t seconds;
  uint16_t milliseconds;
};

typedef struct workout_data workout_data;
struct workout_data {
  bool stopwatch_running;
  stopwatch_time accumulated_time;
  stopwatch_time now;
  stopwatch_time splits[MAX_SPLITS];
  int current_split;
};

