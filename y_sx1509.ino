//
void disp_byte(byte iv_val) {

  byte lv_ten = iv_val / 10;
  byte lv_one = iv_val - (lv_ten * 10);

  io.digitalWrite(10, !bitRead(lv_one, 0)); //Einer D0
  io.digitalWrite(11, !bitRead(lv_one, 1)); //Einer D1
  io.digitalWrite(12, !bitRead(lv_one, 2)); //Einer D2
  io.digitalWrite(13, !bitRead(lv_one, 3)); //Einer D3

  io.digitalWrite(14, !bitRead(lv_ten, 0)); //Zehner D0
  io.digitalWrite(15, !bitRead(lv_ten, 1)); //Zehner D1
  io.digitalWrite( 9, !bitRead(lv_ten, 2)); //Zehner D3
  io.digitalWrite( 8, !bitRead(lv_ten, 3)); //Zehner D2
}

void disp_hex(byte iv_val) {

  for (int i = 0; i < 8; i++) {
    io.digitalWrite(disp_pins[i], !bitRead(iv_val, i));
  }

}



void init_sx1509() {

  // Call io.begin(<address>) to initialize the SX1509. If it
  // successfully communicates, it'll return 1.
  Serial.print("SX1509 #1 ");
  if (!io.begin(SX1509_ADDRESS))
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

}

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
