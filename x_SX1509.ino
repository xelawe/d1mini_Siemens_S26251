/*************************************************************
  digitalWrite.ino
  SparkFun SX1509 I/O Expander Example: digital out (digitalWrite)
  Jim Lindblom @ SparkFun Electronics
  Original Creation Date: September 21, 2015
  https://github.com/sparkfun/SparkFun_SX1509_Arduino_Library

  This simple example demonstrates the SX1509's digital output
  functionality. Attach an LED to SX1509 IO 15, or just look at
  it with a multimeter. We're gonna blink it!

  Hardware Hookup:
  SX1509 Breakout ------ Arduino -------- Breadboard
        GND -------------- GND
        3V3 -------------- 3.3V
      SDA ------------ SDA (A4)
      SCL ------------ SCL (A5)
      15 -------------------------------- LED+
                                     LED- -/\/\/\- GND
                                                330

  Development environment specifics:
  IDE: Arduino 1.6.5
  Hardware Platform: Arduino Uno
  SX1509 Breakout Version: v2.0

  This code is beerware; if you see me (or any other SparkFun
  employee) at the local, and you've found our code helpful,
  please buy us a round!

  Distributed as-is; no warranty is given.
*************************************************************/

#include <Wire.h> // Include the I2C library (required)
#include <SparkFunSX1509.h> // Include SX1509 library

// Arduino Pins (not SX1509!)
const byte ARDUINO_INT_PIN = D7; // SX1509 int output to D2

// Global variables:
volatile bool buttonPressed = false; // Track button press in ISR

// SX1509 I2C address (set by ADDR1 and ADDR0 (00 by default):
const byte SX1509_ADDRESS = 0x3E;  // SX1509 I2C address
SX1509 io; // Create an SX1509 object to be used throughout


// SX1509 pin definitions:

const byte anz_disp_pins = 8;
byte disp_pins[anz_disp_pins] = { 10, 11, 12, 13, 14, 15, 9, 8};
byte gv_disp_val;
byte gv_disp_val_byte;

const byte anz_btn = 6;
byte btnpins[anz_btn] = { 0, 1, 2, 3, 4, 5};
byte btn_state[anz_btn] = {};
boolean gv_reset;
enum btn_name { btn_system_on, btn_system_off, btn_diagnose, btn_reset, btn_full, btn_local };


