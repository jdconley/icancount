#include <pebble.h>
#include "workout_set.h"

#define MS_PER_TICK 200 //~5fps

static workout_data *s_data;
static AppTimer *timer;

void timer_tick(void *data) {
  timer = app_timer_register(MS_PER_TICK, (AppTimerCallback)timer_tick, NULL);
  s_data->now.milliseconds = time_ms(&s_data->now.seconds, NULL);
  
  if (s_data->stopwatch_running) {
    s_data->accumulated_time.seconds = s_data->accumulated_time.seconds + (s_data->now.seconds > s_data->splits[0].seconds ? s_data->now.seconds - s_data->splits[0].seconds : 0);
    s_data->accumulated_time.milliseconds = s_data->accumulated_time.milliseconds + s_data->now.milliseconds + s_data->splits[0].milliseconds;
  }

  display_data(s_data);
  
  s_data->splits[0].milliseconds = time_ms(&s_data->splits[0].seconds, NULL);
}

void split_handler(void) {
  if (++s_data->current_split > MAX_COUNTER) {
    s_data->current_split = 0;
  }
  
  int split_index = (s_data->current_split % (MAX_SPLITS - 1)) + 1;
  s_data->splits[split_index].milliseconds = time_ms(&s_data->splits[split_index].seconds, NULL);
}

void clear_splits_handler(void) {
  s_data->current_split = 0;
}

void toggle_runstop_stopwatch_handler(void) {
  s_data->stopwatch_running = !s_data->stopwatch_running;

  //immediately upon toggle to running, reset our start time to "now"
  if (s_data->stopwatch_running) {
    s_data->splits[0].milliseconds = time_ms(&s_data->splits[0].seconds, NULL);
  }
}

void clear_stopwatch_handler(void) {
  s_data->accumulated_time.seconds = 0;
  s_data->accumulated_time.milliseconds = 0;
}

void handle_init(void) {
  s_data = malloc(sizeof(workout_data));
  s_data->stopwatch_running = true;
  s_data->current_split = 0;
  s_data->splits[0].milliseconds = time_ms(&s_data->splits[0].seconds, NULL);
  s_data->now.milliseconds = s_data->splits[0].milliseconds;
  s_data->now.seconds = s_data->splits[0].seconds;
  s_data->accumulated_time.seconds = 0;
  s_data->accumulated_time.milliseconds = 0;
  
  show_workout_set(s_data, split_handler, clear_splits_handler, toggle_runstop_stopwatch_handler, clear_stopwatch_handler);
    
  //start the timer
  timer = app_timer_register(MS_PER_TICK, (AppTimerCallback)timer_tick, NULL);
}

void handle_deinit(void) {
  //do we need to clean up the window or is this handled for us?
  app_timer_cancel(timer);
  hide_workout_set();
  free(s_data);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
