/**
 * @file lv_conf.h
 * Configuration file for LVGL
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

/*====================
   COLOR SETTINGS
 *====================*/

/* Color depth: 16-bit (RGB565) */
#define LV_COLOR_DEPTH 16

/* Swap the 2 bytes of RGB565 color. */
#define LV_COLOR_16_SWAP 0

/* Transparent screen support (disabled for this use case). */
#define LV_COLOR_SCREEN_TRANSP 0

/* Chroma keying color for transparent images. */
#define LV_COLOR_CHROMA_KEY lv_color_hex(0x00ff00)

/*=========================
   DISPLAY SETTINGS
 *=========================*/

/* Horizontal and vertical resolution of the display */
#define LV_HOR_RES_MAX 128
#define LV_VER_RES_MAX 128

/* Default display refresh period (in ms) */
#define LV_DISP_DEF_REFR_PERIOD 30

/* Enable anti-aliasing */
#define LV_ANTIALIAS 1

/*=========================
   MEMORY SETTINGS
 *=========================*/

/* Use custom malloc/free */
#define LV_MEM_CUSTOM 1
#if LV_MEM_CUSTOM
    #define LV_MEM_CUSTOM_INCLUDE <stdlib.h> /* Header for memory functions */
    #define LV_MEM_CUSTOM_ALLOC malloc
    #define LV_MEM_CUSTOM_FREE free
    #define LV_MEM_CUSTOM_REALLOC realloc
#endif

/* Max number of intermediate memory buffers for rendering */
#define LV_MEM_BUF_MAX_NUM 4

/* Use the standard memcpy/memset */
#define LV_MEMCPY_MEMSET_STD 1

/*====================
   HAL SETTINGS
 *====================*/

/* Input device read period (in ms) */
#define LV_INDEV_DEF_READ_PERIOD 30

/* Use a custom tick source for timekeeping */
#define LV_TICK_CUSTOM 1
#if LV_TICK_CUSTOM
    #define LV_TICK_CUSTOM_INCLUDE "Arduino.h"
    #define LV_TICK_CUSTOM_SYS_TIME_EXPR (millis())
#endif

/*=======================
 * FEATURE CONFIGURATION
 *=======================*/

/* Enable complex drawing (shadows, gradients, etc.) */
#define LV_DRAW_COMPLEX 1

/* Default font settings */
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_DEFAULT &lv_font_montserrat_14

/* Enable text selection */
#define LV_LABEL_TEXT_SELECTION 1

/*===================
 * DEBUG SETTINGS
 *===================*/

/* Disable debugging features for performance */
#define LV_USE_PERF_MONITOR 0
#define LV_USE_MEM_MONITOR 0

/*===================
 * THEME SETTINGS
 *===================*/

/* Enable the default theme */
#define LV_USE_THEME_DEFAULT 1
#if LV_USE_THEME_DEFAULT
    #define LV_THEME_DEFAULT_DARK 1 /* Use dark theme */
    #define LV_THEME_DEFAULT_TRANSITION_TIME 80
#endif

#endif /* LV_CONF_H */
