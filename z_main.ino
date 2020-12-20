//
void setup()
{
  init_ser();

  init_sx1509();

  init_sx1509_1();

  // Blink the LED pin -- ~x ms LOW, ~x ms HIGH:
  io1.blink(led_pins[led_system_on], 500, 500);

  delay(500);
  wifi_init(gc_hostname);
  Serial.println("connected to " + WiFi.SSID() + " ...yeey");
  Serial.println( WiFi.localIP() );

  init_ota_local();

  Serial.println("Setup done");

  io1.setupBlink(led_pins[led_system_on], 0, 0, 255);
  led_status[led_system_on] = true;

  init_ticker_count();
}

void loop()
{

  check_ota();

  check_ticker_count();

  check_button();
  if (gv_reset) {
    gv_counter = 0;
    gv_reset = false;
  }

  gv_disp_val = gv_counter;
  disp();
  //disp_hex(i);

  disp_led( );
}
