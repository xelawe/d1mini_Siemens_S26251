
time_t get_mqtt_time( ) {

  DebugPrintln("Sync...");

  if ( ! gv_timestamp_mqtt_ok ) {
    return 0;
  }

  // it's ok now to sync every Minute
  setSyncInterval(60);
  DebugPrintln("Synced");

  return gv_timestamp_mqtt_local;
}

void init_time() {

  setSyncProvider(get_mqtt_time);
  // sync every Second to start asap
  setSyncInterval(1);

}
