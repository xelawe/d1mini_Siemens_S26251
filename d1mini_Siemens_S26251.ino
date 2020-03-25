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

// SX1509 I2C address (set by ADDR1 and ADDR0 (00 by default):
const byte SX1509_ADDRESS = 0x3E;  // SX1509 I2C address
SX1509 io; // Create an SX1509 object to be used throughout
// SX1509 I2C address (set by ADDR1 and ADDR0 (00 by default):
const byte SX1509_ADDRESS1 = 0x3F;  // SX1509 I2C address
SX1509 io1; // Create an SX1509 object to be used throughout

// SX1509 pin definitions:
const byte SX1509_LED_PIN = 15; // LED connected to pin 15
// SX1509 Pins:
const byte SX1509_BUTTON_PIN = 0; // IO 0 connected to button

// Arduino Pins (not SX1509!)
const byte ARDUINO_INT_PIN = D7; // SX1509 int output to D2

// Global variables:
volatile bool buttonPressed = false; // Track button press in ISR

// button() is an Arduino interrupt routine, called whenever
// the interrupt pin goes from HIGH to LOW.
ICACHE_RAM_ATTR void button()
{
  buttonPressed = true; // Set the buttonPressed flag to true
  // We can't do I2C communication in an Arduino ISR. The best
  // we can do is set a flag, to tell the loop() to check next
  // time through.
}

void init_button(int pin_but) {
  // Use io.pinMode(<pin>, <mode>) to set our button to an
  // input with internal pullup resistor activated:
  io.pinMode(pin_but, INPUT_PULLUP);

  // Use io.enableInterrupt(<pin>, <signal>) to enable an
  // interrupt on a pin. The <signal> variable can be either
  // FALLING, RISING, or CHANGE. Set it to falling, which will
  // mean the button was pressed:
  io.enableInterrupt(pin_but, FALLING);

  // After configuring the debounce time, use
  // debouncePin(<pin>) to enable debounce on an input pin.
  io.debouncePin(pin_but); // Enable debounce

}
void init_button_B(int pin_but) {
  // Use io.pinMode(<pin>, <mode>) to set our button to an
  // input with internal pullup resistor activated:
  io.pinMode(pin_but, INPUT_PULLUP);

  // Use io.enableInterrupt(<pin>, <signal>) to enable an
  // interrupt on a pin. The <signal> variable can be either
  // FALLING, RISING, or CHANGE. Set it to falling, which will
  // mean the button was pressed:
  io.enableInterrupt(pin_but, CHANGE);

  // After configuring the debounce time, use
  // debouncePin(<pin>) to enable debounce on an input pin.
  io.debouncePin(pin_but); // Enable debounce

}

void setup()
{
  Serial.begin(115200);
  Serial.println(" ");

  // Call io.begin(<address>) to initialize the SX1509. If it
  // successfully communicates, it'll return 1.
  Serial.print("SX1509 #1 ");
  if (!io.begin(SX1509_ADDRESS))
  {
    Serial.println(" failed");
    while (1) ; // If we fail to communicate, loop forever.
  }
  Serial.println(" done");

  Serial.print("SX1509 #2 ");
  if (!io1.begin(SX1509_ADDRESS1))
  {
    Serial.println(" failed");
    while (1) ; // If we fail to communicate, loop forever.
  }
  Serial.println(" done");

  // Call io.pinMode(<pin>, <mode>) to set an SX1509 pin as
  // an output:
  io.pinMode(SX1509_LED_PIN, OUTPUT);
  io.pinMode(14, OUTPUT);
  io.pinMode(13, OUTPUT);
  io.pinMode(12, OUTPUT);
  io.pinMode(11, OUTPUT);
  io.pinMode(10, OUTPUT);
  io.pinMode(9, OUTPUT);
  io.pinMode(8, OUTPUT);

  io1.pinMode(15, OUTPUT);
  io1.pinMode(14, OUTPUT);
  io1.pinMode(13, OUTPUT);
  io1.pinMode(12, OUTPUT);
  io1.pinMode(11, OUTPUT);
  io1.pinMode(10, OUTPUT);
  io1.pinMode(9, OUTPUT);
  io1.pinMode(8, OUTPUT);
  io1.pinMode(7, OUTPUT);
  io1.pinMode(6, OUTPUT);
  io1.pinMode(5, OUTPUT);
  io1.pinMode(4, OUTPUT);
  io1.pinMode(3, OUTPUT);
  io1.pinMode(2, OUTPUT);

  // The SX1509 has built-in debounce features, so a single
  // button-press doesn't accidentally create multiple ints.
  // Use io.debounceTime(<time_ms>) to set the GLOBAL SX1509
  // debounce time.
  // <time_ms> can be either 0, 1, 2, 4, 8, 16, 32, or 64 ms.
  io.debounceTime(32); // Set debounce time to 32 ms.

  init_button(0);
  init_button(1);
  init_button(2);
  init_button(3);
  init_button(4);
  init_button_B(5);

  // Don't forget to configure your Arduino pins! Set the
  // Arduino's interrupt input to INPUT_PULLUP. The SX1509's
  // interrupt output is active-low.
  pinMode(ARDUINO_INT_PIN, INPUT_PULLUP);

  // Attach an Arduino interrupt to the interrupt pin. Call
  // the button function, whenever the pin goes from HIGH to
  // LOW.
  attachInterrupt(digitalPinToInterrupt(ARDUINO_INT_PIN), button, FALLING);


  Serial.println("Setup done");
  io1.digitalWrite(13, LOW);
}

void loop()
{
  // It's blinken time!
  // Call io.digitalWrite(<pin>, <HIGH | LOW>) to set a SX1509
  // output pin as either 3.3V or 0V.


  //  for (int j = 0; j < 4; j++) {
  //    io.digitalWrite(10, !bitRead(j, 1));
  //    io.digitalWrite(11, !bitRead(j, 0));

  for (int i = 0; i < 64; i++) {


    if (buttonPressed) // If the button() ISR was executed
    {
      // read io.interruptSource() find out which pin generated
      // an interrupt and clear the SX1509's interrupt output.
      unsigned int intStatus = io.interruptSource();
      // For debugging handiness, print the intStatus variable.
      // Each bit in intStatus represents a single SX1509 IO.
      Serial.println("intStatus = " + String(intStatus, BIN));

      // If the bit corresponding to our button IO generated
      // the input:
      if (intStatus & (1 << SX1509_BUTTON_PIN))
      {
        Serial.println("Button pressed!"); // Print a message.
      }


      if (intStatus & (1 << 3))
      {
        Serial.println("RESET Button pressed!"); // Print a message.
        i = 0;
      }

      buttonPressed = false; // Clear the buttonPressed flag
    }
    io.digitalWrite(8, !bitRead(i, 1));
    io.digitalWrite(9, !bitRead(i, 0));
    io.digitalWrite(10, !bitRead(i, 5));
    io.digitalWrite(11, !bitRead(i, 4));
    io.digitalWrite(12, !bitRead(i, 3));
    io.digitalWrite(13, !bitRead(i, 2));
    io.digitalWrite(14, !bitRead(i, 1));
    io.digitalWrite(15, !bitRead(i, 0));

    //    io1.digitalWrite(10, !bitRead(i, 5));
    //    io1.digitalWrite(11, !bitRead(i, 4));
    io1.digitalWrite(2, !bitRead(i, 1));
    io1.digitalWrite(3, !bitRead(i, 0));
    io1.digitalWrite(4, !bitRead(i, 5));
    io1.digitalWrite(5, !bitRead(i, 4));
    io1.digitalWrite(6, !bitRead(i, 3));
    io1.digitalWrite(7, !bitRead(i, 2));
    io1.digitalWrite(8, !bitRead(i, 1));
    io1.digitalWrite(9, !bitRead(i, 0));
    io1.digitalWrite(10, !bitRead(i, 5));
    io1.digitalWrite(11, !bitRead(i, 4));
    io1.digitalWrite(12, !bitRead(i, 3));
    io1.digitalWrite(14, !bitRead(i, 2));

    io1.digitalWrite(15, !bitRead(i, 0));

    delay(500); // Delay half-a-second
  }
  // }



}
