
char *get_stopic_ix( int ix ) {
  strcpy_P(gv_sbuffer, (char*)pgm_read_dword(&(gt_stopic_gw60[ix])));
  //strcpy_P(gv_buffer, );
  return gv_sbuffer;
}

char *get_cmd_ix( int ix ) {
  strcpy_P(gv_pbuffer, (char*)pgm_read_dword(&(gt_cmd[ix])));
  //strcpy_P(gv_buffer, );
  return gv_pbuffer;
}

void pub_sens(int ldr_val) {
  char lv_ibuffer[10];
  //itoa(ldr_val, lv_ibuffer, 4);
  sprintf_P(lv_ibuffer, (PGM_P)F("%5d"), ldr_val);
  if (!client.publish(mqtt_GetTopic_P(gv_ptopic, mqtt_pre_tele, gv_clientname, (PGM_P)F("LDR")), lv_ibuffer, true)) {
    DebugPrintln(F("pub failed!"));
  } else {
    DebugPrintln(F("pub ok!"));
  }
}

void pub_stat(int ix, int cmd) {
  // bei ix == 0 --> alle auf cmd setzen!

  if (!client.publish(mqtt_GetTopic_P(gv_ptopic, mqtt_pre_stat, gv_clientname, get_stopic_ix(ix)), get_cmd_ix(cmd), true)) {
    DebugPrintln(F("pub failed!"));
  } else {
    DebugPrintln(F("pub ok!"));
  }

}

void callback_mqtt_led_ix(char* topic, byte* payload, unsigned int length, byte iv_ix) {
  DebugPrint(F("Callback LED"));
  DebugPrintln(iv_ix);

  bool cmd_valid = true;
  String message_string = "";

  for (int i = 0; i < length; i++) {
    DebugPrint((char)payload[i]);
    //fill up the message string
    message_string.concat((char)payload[i]);
  }
  DebugPrintln();

  byte lv_status;
  if (message_string.equalsIgnoreCase(F("0"))) {
    lv_status = 0;
  }
  if (message_string.equalsIgnoreCase(F("1"))) {
    lv_status = 1;
  }

  if (iv_ix == 0) {
    for (byte i = 0; i < anz_leds; i++) {
      led_status[i] = lv_status;
      pub_stat(i + 1, !lv_status);
    }
  } else {
    led_status[iv_ix - 1] = lv_status;
    pub_stat(iv_ix, !lv_status);
  }
}

void init_mqtt_local( ) {

  init_mqtt(gv_clientname);

  add_subtopic(mqtt_GetTopic_P(gv_stopic_leds, mqtt_pre_cmnd, gv_clientname, get_stopic_ix(0)), callback_mqtt_leds);
  add_subtopic(mqtt_GetTopic_P(gv_stopic_led01, mqtt_pre_cmnd, gv_clientname, get_stopic_ix(1)), callback_mqtt_led01);
  add_subtopic(mqtt_GetTopic_P(gv_stopic_led02, mqtt_pre_cmnd, gv_clientname, get_stopic_ix(2)), callback_mqtt_led02);
  add_subtopic(mqtt_GetTopic_P(gv_stopic_led03, mqtt_pre_cmnd, gv_clientname, get_stopic_ix(3)), callback_mqtt_led03);
  add_subtopic(mqtt_GetTopic_P(gv_stopic_led04, mqtt_pre_cmnd, gv_clientname, get_stopic_ix(4)), callback_mqtt_led04);
  add_subtopic(mqtt_GetTopic_P(gv_stopic_led05, mqtt_pre_cmnd, gv_clientname, get_stopic_ix(5)), callback_mqtt_led05);
  add_subtopic(mqtt_GetTopic_P(gv_stopic_led06, mqtt_pre_cmnd, gv_clientname, get_stopic_ix(6)), callback_mqtt_led06);
  add_subtopic(mqtt_GetTopic_P(gv_stopic_led07, mqtt_pre_cmnd, gv_clientname, get_stopic_ix(7)), callback_mqtt_led07);
  add_subtopic(mqtt_GetTopic_P(gv_stopic_led08, mqtt_pre_cmnd, gv_clientname, get_stopic_ix(8)), callback_mqtt_led08);
  add_subtopic(mqtt_GetTopic_P(gv_stopic_led09, mqtt_pre_cmnd, gv_clientname, get_stopic_ix(9)), callback_mqtt_led09);
  add_subtopic(mqtt_GetTopic_P(gv_stopic_led10, mqtt_pre_cmnd, gv_clientname, get_stopic_ix(10)), callback_mqtt_led10);
  add_subtopic(mqtt_GetTopic_P(gv_stopic_led11, mqtt_pre_cmnd, gv_clientname, get_stopic_ix(11)), callback_mqtt_led11);
  add_subtopic(mqtt_GetTopic_P(gv_stopic_led12, mqtt_pre_cmnd, gv_clientname, get_stopic_ix(12)), callback_mqtt_led12);
  add_subtopic(mqtt_GetTopic_P(gv_stopic_led13, mqtt_pre_cmnd, gv_clientname, get_stopic_ix(13)), callback_mqtt_led13);
  add_subtopic(mqtt_GetTopic_P(gv_stopic_led14, mqtt_pre_cmnd, gv_clientname, get_stopic_ix(14)), callback_mqtt_led14);

  gv_mqtt_pup_stat = true;

}

void pub_stat() {

  //  char buffer[256];
  //  //dtostrf(fire.NUMFirePIXELS, 0, 0, buffer);
  //
  //  // Allocate the JSON document
  //  //
  //  // Inside the brackets, 200 is the RAM allocated to this document.
  //  // Don't forget to change this value to match your requirement.
  //  // Use arduinojson.org/v6/assistant to compute the capacity.
  //  StaticJsonDocument<200> jsondoc;
  //
  //  // StaticJsonObject allocates memory on the stack, it can be
  //  // replaced by DynamicJsonDocument which allocates in the heap.
  //  //
  //  // DynamicJsonDocument  doc(200);
  //
  //  // Add values in the document
  //  //
  //  jsondoc["anzled"] = fire.NUMFirePIXELS;
  //  int n  = serializeJson(jsondoc, buffer);
  //
  //  client.publish(mqtt_pubtopic_status, buffer, true);

}

void check_mqtt_local() {

  if (gv_mqtt_pup_stat == true && gv_mqtt_conn_ok == true) {
    pub_stat();
    gv_mqtt_pup_stat = false;
  }

  check_mqtt();

}

void callback_mqtt_leds(char* topic, byte * payload, unsigned int length) {
  callback_mqtt_led_ix(topic, payload, length, 0);
}
void callback_mqtt_led01(char* topic, byte * payload, unsigned int length) {
  callback_mqtt_led_ix(topic, payload, length, 1);
}
void callback_mqtt_led02(char* topic, byte * payload, unsigned int length) {
  callback_mqtt_led_ix(topic, payload, length, 2);
}
void callback_mqtt_led03(char* topic, byte * payload, unsigned int length) {
  callback_mqtt_led_ix(topic, payload, length, 3);
}
void callback_mqtt_led04(char* topic, byte * payload, unsigned int length) {
  callback_mqtt_led_ix(topic, payload, length, 4);
}
void callback_mqtt_led05(char* topic, byte * payload, unsigned int length) {
  callback_mqtt_led_ix(topic, payload, length, 5);
}
void callback_mqtt_led06(char* topic, byte * payload, unsigned int length) {
  callback_mqtt_led_ix(topic, payload, length, 6);
}
void callback_mqtt_led07(char* topic, byte * payload, unsigned int length) {
  callback_mqtt_led_ix(topic, payload, length, 7);
}
void callback_mqtt_led08(char* topic, byte * payload, unsigned int length) {
  callback_mqtt_led_ix(topic, payload, length, 8);
}
void callback_mqtt_led09(char* topic, byte * payload, unsigned int length) {
  callback_mqtt_led_ix(topic, payload, length, 9);
}
void callback_mqtt_led10(char* topic, byte * payload, unsigned int length) {
  callback_mqtt_led_ix(topic, payload, length, 10);
}
void callback_mqtt_led11(char* topic, byte * payload, unsigned int length) {
  callback_mqtt_led_ix(topic, payload, length, 11);
}
void callback_mqtt_led12(char* topic, byte * payload, unsigned int length) {
  callback_mqtt_led_ix(topic, payload, length, 12);
}
void callback_mqtt_led13(char* topic, byte * payload, unsigned int length) {
  callback_mqtt_led_ix(topic, payload, length, 13);
}
void callback_mqtt_led14(char* topic, byte * payload, unsigned int length) {
  callback_mqtt_led_ix(topic, payload, length, 14);
}
