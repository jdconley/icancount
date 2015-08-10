#include <pebble.h>
#include "workout_set.h"

#define TIMER_STR_BUFFER_SIZE 10 //"9999:99.9"
#define COUNTER_STR_BUFFER_SIZE 4 //"999"

static char *s_timer_buffer;
static char *s_counter_buffer;
static InputHandler s_split_handler;
static InputHandler s_clear_splits_handler;
static InputHandler s_toggle_runstop_stopwatch_handler;
static InputHandler s_clear_stopwatch_handler;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_digital_dream_fat_subset_28;
static GFont s_res_roboto_bold_subset_49;
static TextLayer *s_textlayer_timer;
static TextLayer *s_textlayer_counter;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_digital_dream_fat_subset_28 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_DIGITAL_DREAM_FAT_SUBSET_28));
  s_res_roboto_bold_subset_49 = fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49);
  // s_textlayer_timer
  s_textlayer_timer = text_layer_create(GRect(2, 2, 140, 49));
  text_layer_set_background_color(s_textlayer_timer, GColorClear);
  text_layer_set_text_color(s_textlayer_timer, GColorWhite);
  text_layer_set_text(s_textlayer_timer, "0000:00");
  text_layer_set_text_alignment(s_textlayer_timer, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_timer, s_res_digital_dream_fat_subset_28);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_timer);
  
  // s_textlayer_counter
  s_textlayer_counter = text_layer_create(GRect(2, 55, 140, 54));
  text_layer_set_background_color(s_textlayer_counter, GColorClear);
  text_layer_set_text_color(s_textlayer_counter, GColorWhite);
  text_layer_set_text(s_textlayer_counter, "99");
  text_layer_set_text_alignment(s_textlayer_counter, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_counter, s_res_roboto_bold_subset_49);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_counter);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_timer);
  text_layer_destroy(s_textlayer_counter);
  fonts_unload_custom_font(s_res_digital_dream_fat_subset_28);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void select_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_split_handler();
}

void select_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_clear_splits_handler();
}

void up_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_toggle_runstop_stopwatch_handler();
}

void up_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_clear_stopwatch_handler();
}

void down_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  s_clear_stopwatch_handler();
  s_clear_splits_handler();
}

void config_provider(Window *window) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_single_click_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT, 700, select_long_click_handler, NULL);
  window_single_click_subscribe(BUTTON_ID_UP, up_single_click_handler);
  window_long_click_subscribe(BUTTON_ID_UP,  700, up_long_click_handler, NULL);
  window_long_click_subscribe(BUTTON_ID_DOWN,  700, down_long_click_handler, NULL);
}

void show_workout_set(
  workout_data *data, 
  InputHandler split_handler, 
  InputHandler clear_splits_handler, 
  InputHandler toggle_runstop_stopwatch_handler, 
  InputHandler clear_stopwatch_handler) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  
  #ifdef PBL_COLOR
      text_layer_set_text_color(s_textlayer_timer, GColorBrightGreen);
      text_layer_set_text_color(s_textlayer_counter, GColorChromeYellow);
  #endif
  
  s_timer_buffer = malloc(TIMER_STR_BUFFER_SIZE);
  s_counter_buffer = malloc(COUNTER_STR_BUFFER_SIZE);
  
  display_data(data);
  
  window_stack_push(s_window, true);

  s_split_handler = split_handler;
  s_clear_splits_handler = clear_splits_handler;
  s_toggle_runstop_stopwatch_handler = toggle_runstop_stopwatch_handler;
  s_clear_stopwatch_handler = clear_stopwatch_handler;
  window_set_click_config_provider(s_window, (ClickConfigProvider) config_provider);
}

void hide_workout_set(void) {
  free(s_timer_buffer);
  s_timer_buffer = NULL;
  free(s_counter_buffer);
  s_counter_buffer = NULL;
  
  window_stack_remove(s_window, true);
}

void display_data(workout_data *data) {
  unsigned int totalSeconds = data->accumulated_time.seconds;
  unsigned int secondsPart = totalSeconds % 60;
  unsigned int minutesPart = totalSeconds / 60;
  //unsigned int tenthsPart = (data->accumulated_time.milliseconds % 1000) / 100;
  
  if (minutesPart > 9999 || secondsPart > 59) {
    text_layer_set_text(s_textlayer_timer, "9999:99");
  } else {
    snprintf(s_timer_buffer, TIMER_STR_BUFFER_SIZE, "%02u:%02u", minutesPart, secondsPart);
    text_layer_set_text(s_textlayer_timer, s_timer_buffer);
  }

  if (data->current_split > MAX_COUNTER || data->current_split < 0) {
    text_layer_set_text(s_textlayer_counter, "0");
  } else {
    snprintf(s_counter_buffer, COUNTER_STR_BUFFER_SIZE, "%u", data->current_split);
    text_layer_set_text(s_textlayer_counter, s_counter_buffer);
  }
  
}
