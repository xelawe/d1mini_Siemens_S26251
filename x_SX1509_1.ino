// SX1509 I2C address (set by ADDR1 and ADDR0 (00 by default):
const byte SX1509_ADDRESS1 = 0x3F;  // SX1509 I2C address
SX1509 io1; // Create an SX1509 object to be used throughout

const byte anz_leds = 14;

enum led_name             {led_load, led_system_on, led_svp, led_sinix, led_interlock, led_pu1, led_pu2, led_pu3, led_contacor, led_ac, led_fm1, led_fm2, led_fm3, led_fm4};
byte led_pins[anz_leds] = { 15,      14,            13,      12,        2,             10,      9,       8,             3,      11,       4,       5,       6,       7    };

boolean led_status[anz_leds];
