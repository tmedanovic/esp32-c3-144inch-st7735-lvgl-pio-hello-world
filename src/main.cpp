#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "lvgl.h"

// Pin definitions for ST7735
#define TFT_CS 2
#define TFT_DC 0
#define TFT_RST 5
#define TFT_MOSI 4
#define TFT_SCLK 3

// Screen dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

// Buffer size for LVGL
#define DISP_BUF_SIZE (SCREEN_WIDTH * 10)

// Initialize Adafruit ST7735 display
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// LVGL Display buffer
static lv_color_t buf1[DISP_BUF_SIZE];
static lv_disp_draw_buf_t draw_buf;

// Flush function for LVGL
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint16_t width = area->x2 - area->x1 + 1;
    uint16_t height = area->y2 - area->y1 + 1;

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, width, height);

    // Send each pixel color
    for (uint16_t y = 0; y < height; y++) {
        for (uint16_t x = 0; x < width; x++) {
            tft.pushColor((uint16_t)color_p->full);
            color_p++;
        }
    }
    tft.endWrite();

    // Notify LVGL that flushing is done
    lv_disp_flush_ready(disp);
}

void setup() {
    // Initialize serial for debugging
    Serial.begin(115200);
    Serial.println("Initializing...");

    // Initialize the display
    tft.initR(INITR_GREENTAB);
    tft.fillScreen(ST77XX_BLACK);

    // Initialize LVGL
    lv_init();

    // Initialize the display buffer
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, DISP_BUF_SIZE);

    // Set up the display driver
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SCREEN_WIDTH;
    disp_drv.ver_res = SCREEN_HEIGHT;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    // Create a label with word wrapping
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);  // Enable word wrapping
    lv_label_set_text(label, "Hello world");
    lv_obj_set_width(label, SCREEN_WIDTH - 10);         // Set the label width (leave padding)
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0); // Center text alignment
    lv_obj_set_style_text_color(label, lv_color_white(), 0);     // Set text color
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);         // Center the label

    Serial.println("Setup complete.");
}

void loop() {
    // Periodically update LVGL
    lv_timer_handler();
    delay(5);
}
