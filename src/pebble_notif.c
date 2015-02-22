#include <pebble.h>
  
#define KEY_DATA 1

static Window *window;
static TextLayer *notification_layer;

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  Tuple *t = dict_read_first(iterator);
  while (t != NULL) {
    static char buffer[64];
    switch (t->key) {
      case KEY_DATA:
        snprintf(buffer, sizeof(buffer), "%s", t->value->cstring);
        text_layer_set_text(notification_layer, buffer);
        while (true) {
          vibes_double_pulse(); 
        }
        break;
    }
    t = dict_read_next(iterator);
  }
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  
  notification_layer = text_layer_create(GRect(0, 55, 144, 50));
  text_layer_set_background_color(notification_layer, GColorClear);
  text_layer_set_text_color(notification_layer, GColorBlack);
  text_layer_set_font(notification_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(notification_layer, "Not quite yet...");
  text_layer_set_overflow_mode(notification_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(notification_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(notification_layer);
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
