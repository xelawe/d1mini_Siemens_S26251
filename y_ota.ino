

void init_ota_local() {

  init_ota(gv_clientname);

  ArduinoOTA.onStart([]() { // switch off all the PWMs during upgrade
    io1.blink(led_pins[led_load], 500, 500);
    gv_ota_perc = 0;
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    //Serial.printf("Progress: %u%%\r", (progress / (total / 100)));

    int lv_ota_perc = ( progress / (total / 100));

    if ( ((lv_ota_perc % 10) == 0) && ( lv_ota_perc != gv_ota_perc ) ) {
      gv_ota_perc = lv_ota_perc;
      //      oled.print("#");
      //      oled.display();
    }
    gv_disp_val = gv_ota_perc;
    disp();
  });

  ArduinoOTA.onEnd([]() {
    io1.setupBlink(led_pins[led_load], 0, 0, 255);
  });
  
}
