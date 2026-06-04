#pragma once

#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP28
#define I2C1_SCL_PIN GP29

#define OLED_IC OLED_IC_SSD1312
#define OLED_DISPLAY_128X64
#define OLED_DISPLAY_ADDRESS 0x3C
#define OLED_FLIP_SEGMENT
#define OLED_CHARGE_PUMP_VALUE 0x72
#define OLED_BRIGHTNESS 64
#define OLED_UPDATE_INTERVAL 50

/* OLED on/off is managed in oled_task_user so both halves stay in sync;
   built-in timeout disabled, OLED_TIMEOUT_USER drives the idle blank */
#define OLED_TIMEOUT 0
#define OLED_TIMEOUT_USER 30000
#define OLED_FADE_OUT

/* split sync: WPM, last key and per-half press counts for the OLED HUD */
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_WPM_ENABLE
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_OLED_STATE, USER_SYNC_LASTKEY, USER_SYNC_PRESSES

/* One-Shot mods: single tap = one-shot, double tap = locked (toggle) */
#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 2000
