// Display on TIL311

void disp() {
  if (btn_state[btn_diagnose] == LOW ) {
    disp_byte(88);
    return;
  }

  disp_byte(gv_disp_val);

}

void disp_byte(byte iv_val) {

  if (iv_val == gv_disp_val_byte) {
    return;
  }
  gv_disp_val_byte = iv_val;

  byte lv_ten = iv_val / 10;
  byte lv_one = iv_val - (lv_ten * 10);

  check_button();
  io.digitalWrite(10, !bitRead(lv_one, 0)); //Einer D0
  check_button();
  io.digitalWrite(11, !bitRead(lv_one, 1)); //Einer D1
  check_button();
  io.digitalWrite(12, !bitRead(lv_one, 2)); //Einer D2
  check_button();
  io.digitalWrite(13, !bitRead(lv_one, 3)); //Einer D3

  check_button();
  io.digitalWrite(14, !bitRead(lv_ten, 0)); //Zehner D0
  check_button();
  io.digitalWrite(15, !bitRead(lv_ten, 1)); //Zehner D1
  check_button();
  io.digitalWrite( 9, !bitRead(lv_ten, 2)); //Zehner D3
  check_button();
  io.digitalWrite( 8, !bitRead(lv_ten, 3)); //Zehner D2
}

void disp_hex(byte iv_val) {

  for (int i = 0; i < 8; i++) {
    check_button();
    io.digitalWrite(disp_pins[i], !bitRead(iv_val, i));
  }

}


void check_button() {
  //  button() ISR was executed?
  if (!buttonPressed)
  {
    return;
  }

  // read io.interruptSource() find out which pin generated
  // an interrupt and clear the SX1509's interrupt output.
  unsigned int intStatus = io.interruptSource();

  buttonPressed = false; // Clear the buttonPressed flag

  // For debugging handiness, print the intStatus variable.
  // Each bit in intStatus represents a single SX1509 IO.
  Serial.println("intStatus = " + String(intStatus, BIN));


  for (byte i = 0; i < anz_btn; i++) {
    // If the bit corresponding to our button IO generated
    // the input:
    if (intStatus & (1 << i)) {

      btn_state[i] = io.digitalRead(btnpins[i]);

      //Serial.println(btnpins[i]);
      Serial.println(i);

      switch (i) {
        case 0:
          Serial.print("SYSTEM ON");
          break;
        case 1:
          Serial.print("SYSTEM OFF");
          break;
        case 2:
          Serial.print("DIAGNOSE");
          break;
        case 3:
          Serial.print("RESET");
          if (btn_state[i] == LOW) {
            gv_reset = true;
          }
          break;
        case 4:
          Serial.print("FULL");
          break;
        case 5:
          Serial.print("LOCAL");
          break;
      }

      if (btn_state[i] == LOW) {
        Serial.println(" pressed!");
      } else {
        Serial.println(" released!");
      }
    }
  }
}

void init_sx1509() {

  // Call io.begin(<address>) to initialize the SX1509. If it
  // successfully communicates, it'll return 1.
  Serial.print("SX1509 #1 ");
  if (!io.begin(SX1509_ADDRESS))
  {
    Serial.println(" failed");
    //while (1) ; // If we fail to communicate, loop forever.
    return;
  }
  Serial.println(" done");

  // Call io.pinMode(<pin>, <mode>) to set an SX1509 pin as
  // an output:
  for (byte i = 0; i < anz_disp_pins; i++) {
    io.pinMode(disp_pins[i], OUTPUT);
  }

  // The SX1509 has built-in debounce features, so a single
  // button-press doesn't accidentally create multiple ints.
  // Use io.debounceTime(<time_ms>) to set the GLOBAL SX1509
  // debounce time.
  // <time_ms> can be either 0, 1, 2, 4, 8, 16, 32, or 64 ms.
  io.debounceTime(32); // Set debounce time to 32 ms.

  for (byte i = 0; i < anz_btn; i++) {
    init_button(btnpins[i]);
  }

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

void init_button(byte pin_but) {

  init_button(pin_but, CHANGE);

}

void init_button(byte pin_but, byte riseFall) {

  btn_state[pin_but] = HIGH;

  // Use io.pinMode(<pin>, <mode>) to set our button to an
  // input with internal pullup resistor activated:
  io.pinMode(pin_but, INPUT_PULLUP);

  // Use io.enableInterrupt(<pin>, <signal>) to enable an
  // interrupt on a pin. The <signal> variable can be either
  // FALLING, RISING, or CHANGE. Set it to falling, which will
  // mean the button was pressed:
  io.enableInterrupt(pin_but, riseFall);

  // After configuring the debounce time, use
  // debouncePin(<pin>) to enable debounce on an input pin.
  io.debouncePin(pin_but); // Enable debounce

}
