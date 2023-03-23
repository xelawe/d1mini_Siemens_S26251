#include "cy_mqtt_v1.h"
#include <ArduinoJson.h>

char gv_stopic_leds[MQTT_TOPSZ];
char gv_stopic_led01[MQTT_TOPSZ];
char gv_stopic_led02[MQTT_TOPSZ];
char gv_stopic_led03[MQTT_TOPSZ];
char gv_stopic_led04[MQTT_TOPSZ];
char gv_stopic_led05[MQTT_TOPSZ];
char gv_stopic_led06[MQTT_TOPSZ];
char gv_stopic_led07[MQTT_TOPSZ];
char gv_stopic_led08[MQTT_TOPSZ];
char gv_stopic_led09[MQTT_TOPSZ];
char gv_stopic_led10[MQTT_TOPSZ];
char gv_stopic_led11[MQTT_TOPSZ];
char gv_stopic_led12[MQTT_TOPSZ];
char gv_stopic_led13[MQTT_TOPSZ];
char gv_stopic_led14[MQTT_TOPSZ];

const char gc_stopic_leds[] PROGMEM = "LEDS";
const char gc_stopic_led01[] PROGMEM = "LED01";
const char gc_stopic_led02[] PROGMEM = "LED02";
const char gc_stopic_led03[] PROGMEM = "LED03";
const char gc_stopic_led04[] PROGMEM = "LED04";
const char gc_stopic_led05[] PROGMEM = "LED05";
const char gc_stopic_led06[] PROGMEM = "LED06";
const char gc_stopic_led07[] PROGMEM = "LED07";
const char gc_stopic_led08[] PROGMEM = "LED08";
const char gc_stopic_led09[] PROGMEM = "LED09";
const char gc_stopic_led10[] PROGMEM = "LED10";
const char gc_stopic_led11[] PROGMEM = "LED11";
const char gc_stopic_led12[] PROGMEM = "LED12";
const char gc_stopic_led13[] PROGMEM = "LED13";
const char gc_stopic_led14[] PROGMEM = "LED14";

const char* const gt_stopic[] PROGMEM = { gc_stopic_leds, gc_stopic_led01, gc_stopic_led02, gc_stopic_led03, gc_stopic_led04, gc_stopic_led05
                                               , gc_stopic_led06, gc_stopic_led07, gc_stopic_led08, gc_stopic_led09, gc_stopic_led10, gc_stopic_led11
                                               , gc_stopic_led12, gc_stopic_led13, gc_stopic_led14};
char gv_sbuffer[16];// buffer for reading the string to (needs to be large enough to take the longest string

char gv_ptopic[MQTT_TOPSZ];
char gv_pbuffer[5];// buffer for reading the string to (needs to be large enough to take the longest string

const char gc_cmd_on[] PROGMEM = "1";
const char gc_cmd_off[] PROGMEM = "0";

const char* const gt_cmd[] PROGMEM = { gc_cmd_on, gc_cmd_off };

boolean gv_mqtt_pub_stat;
