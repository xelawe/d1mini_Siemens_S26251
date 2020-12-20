// D1mini controls C70 Panel Siemens S26251

#define USE_SERIAL Serial
#include <cy_serdebug.h>
#include <cy_serial.h>

const char *gc_hostname = "d1mS2651";
#include "cy_wifi.h"
#include "cy_ota.h"

byte gv_counter;

void init_ser(){
    cy_serial::start(__FILE__);
}

