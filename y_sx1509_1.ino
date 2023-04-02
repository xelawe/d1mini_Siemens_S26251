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

  time_to_led();

  for (int i = 0; i < anz_leds; i++) {
    int lv_status = 1;
    if (led_status[i]) {
      lv_status = 0;
    }

    io1.digitalWrite(led_pins [i], lv_status);
  }

}

void time_to_led() {

  int lv_hour = hour(gv_timestamp_mqtt_local);
  if (lv_hour > 12 ) {
    lv_hour = lv_hour - 12;
  }
  if (lv_hour == 0 ) {
    lv_hour = 12;
  }

  lv_hour++;

  for (int i = 2; i < anz_leds; i++) {
    if (i == lv_hour) {
      led_status[i] = true;
    } else {
      led_status[i] = false;
    }

  }
}
