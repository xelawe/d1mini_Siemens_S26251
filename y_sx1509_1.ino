//
void init_sx1509_1() {


  Serial.print("SX1509 #2 ");
  if (!io1.begin(SX1509_ADDRESS1))
  {
    Serial.println(" failed");
    while (1) ; // If we fail to communicate, loop forever.
  }
  Serial.println(" done");

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

}
