#include <pebble.h>
  
#define KEY_ONE_DATA 1
#define KEY_TWO_DATA 2

static Window *window;
static TextLayer *notification_layer;
BitmapLayer *bitmap_layer;
static GBitmap *gbitmap;
static Layer *window_layer;

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  Tuple *t = dict_read_first(iterator);
  
  static const uint32_t segments[] = {800, 500, 800, 500, 800};
  VibePattern pat = {
      .durations = segments,
      .num_segments = ARRAY_LENGTH(segments),
  };
  
  while (t != NULL) {
    static char buffer[64];
    switch (t->key) {
      case KEY_ONE_DATA:
        snprintf(buffer, sizeof(buffer), "%s", t->value->cstring);
        gbitmap = gbitmap_create_with_resource(RESOURCE_ID_BORDER_TWO);
        bitmap_layer_set_bitmap(bitmap_layer, gbitmap);
        text_layer_set_text(notification_layer, buffer);
        layer_add_child(window_layer, bitmap_layer_get_layer(bitmap_layer));
        layer_add_child(window_layer, text_layer_get_layer(notification_layer));
        vibes_enqueue_custom_pattern(pat);
    }
    t = dict_read_next(iterator);
  }
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "You missed your stop. Boo.");
}

static void send_next_data() {  
  DictionaryIterator *iterator;
  app_message_outbox_begin(&iterator);

  Tuplet t = TupletCString(2, "complete");
  dict_write_tuplet(iterator, &t);
  
  app_message_outbox_send();
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "You have woken up! Hooray!");
}

static void window_load(Window *window) {
  
  
  window_layer = window_get_root_layer(window);
  gbitmap = gbitmap_create_with_resource(RESOURCE_ID_BORDER);
  bitmap_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(bitmap_layer, gbitmap);
  
  notification_layer = text_layer_create(GRect(0, 30, 144, 168));
  text_layer_set_background_color(notification_layer, GColorClear);
  text_layer_set_text_color(notification_layer, GColorBlack);
  text_layer_set_font(notification_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_text(notification_layer, "Welcome to Wake Me Up!");
  text_layer_set_text_alignment(notification_layer, GTextAlignmentCenter);
  text_layer_set_overflow_mode(notification_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, bitmap_layer_get_layer(bitmap_layer));
  layer_add_child(window_layer, text_layer_get_layer(notification_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(notification_layer);
  gbitmap_destroy(gbitmap);
  bitmap_layer_destroy(bitmap_layer);
}

static void select_single_click_handler(ClickRecognizerRef recognizer, void *context) {
  vibes_cancel();
  send_next_data();
  char* buffer = "You have woken up! Hooray!";
  text_layer_set_text(notification_layer, buffer);
  
  gbitmap = gbitmap_create_with_resource(RESOURCE_ID_BORDER_THREE);
  bitmap_layer_set_bitmap(bitmap_layer, gbitmap);
  text_layer_set_text(notification_layer, buffer);
  layer_add_child(window_layer, bitmap_layer_get_layer(bitmap_layer));
  layer_add_child(window_layer, text_layer_get_layer(notification_layer));
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_single_click_handler);
}

static void init() {
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
  window = window_create();
  
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload
  });
  
  window_set_fullscreen(window, true);
  
  window_set_click_config_provider(window, click_config_provider);
  window_stack_push(window, true);
}

static void deinit() {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
