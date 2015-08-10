#include "workout_data.h"

typedef void(* InputHandler)(void);

void show_workout_set(
  workout_data *data, 
  InputHandler split_handler, 
  InputHandler clear_splits_handler, 
  InputHandler toggle_runstop_stopwatch_handler, 
  InputHandler clear_stopwatch_handler);

void hide_workout_set(void);
void display_data(workout_data *data);