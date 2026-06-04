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

/* 0 = no timeout, keeps the layer indicator visible */
#define OLED_TIMEOUT 0

/* One-Shot mods: single tap = one-shot, double tap = locked (toggle) */
#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 2000
