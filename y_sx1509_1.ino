//
void init_sx1509_1() {


  Serial.print("SX1509 #2 ");
  if (!io1.begin(SX1509_ADDRESS1))
  {
    Serial.println(" failed");
    //while (1) ; // If we fail to communicate, loop forever.
    return;
  }
  Serial.println(" done");

  for (byte i = 0; i < anz_leds; i++) {
    io1.pinMode(led_pins[i], OUTPUT);
  }

}

void disp_led_all(boolean iv_status) {

  int lv_status = 1;
  if (iv_status) {
    lv_status = 0;
  }

  for (int i = 0; i < anz_leds; i++) {
    io1.digitalWrite(led_pins[i], lv_status);
  }
}

void disp_led( ) {

  if (btn_state[btn_diagnose] == LOW ) {
    disp_led_all(true);
    return;
  }

  for (int i = 0; i < anz_leds; i++) {
    int lv_status = 1;
    if (led_status[i]) {
      lv_status = 0;
    }

    io1.digitalWrite(led_pins [i], lv_status);
  }

}

