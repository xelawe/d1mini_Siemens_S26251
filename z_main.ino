//
void setup()
{
  init_ser();

  Wire.begin(/*SDA*/D2,/*SCL*/D1); //(D1mini)
  init_sx1509();

  init_sx1509_1();

  // Blink the LED pin -- ~x ms LOW, ~x ms HIGH:
  io1.blink(led_pins[led_system_on], 500, 500);

  delay(500);
  wifi_init(gc_hostname);
  Serial.println("connected to " + WiFi.SSID() + " ...yeey");
  Serial.println( WiFi.localIP() );

  init_ota_local();
  
  init_time();

  init_mqtt_local();

  Serial.println("Setup done");

  io1.setupBlink(led_pins[led_system_on], 0, 0, 255);
  led_status[led_system_on] = true;

  init_ticker_count();
}

void loop()
{

  check_ota();

  check_mqtt_reset( );

  check_ticker_count();

  check_button();
  if (gv_reset) {
    gv_counter = 0;
    gv_reset = false;
  }

  //gv_disp_val = gv_counter;

  gv_disp_val = minute(gv_timestamp_mqtt_local);

  disp();
  //disp_hex(i);

  disp_led( );
}
