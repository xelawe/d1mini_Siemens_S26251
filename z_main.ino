//
void setup()
{
  Serial.begin(115200);
  Serial.println(" ");


  init_sx1509();

  init_sx1509_1();



  Serial.println("Setup done");
  io1.digitalWrite(13, LOW);
}

void loop()
{
  // It's blinken time!
  // Call io.digitalWrite(<pin>, <HIGH | LOW>) to set a SX1509
  // output pin as either 3.3V or 0V.


  //  for (int j = 0; j < 4; j++) {
  //    io.digitalWrite(10, !bitRead(j, 1));
  //    io.digitalWrite(11, !bitRead(j, 0));

  for (int i = 0; i < 64; i++) {


    if (buttonPressed) // If the button() ISR was executed
    {
      // read io.interruptSource() find out which pin generated
      // an interrupt and clear the SX1509's interrupt output.
      unsigned int intStatus = io.interruptSource();
      // For debugging handiness, print the intStatus variable.
      // Each bit in intStatus represents a single SX1509 IO.
      Serial.println("intStatus = " + String(intStatus, BIN));

      // If the bit corresponding to our button IO generated
      // the input:
      if (intStatus & (1 << SX1509_BUTTON_PIN))
      {
        Serial.println("Button pressed!"); // Print a message.
      }


      if (intStatus & (1 << 3))
      {
        Serial.println("RESET Button pressed!"); // Print a message.
        i = 0;
      }

      buttonPressed = false; // Clear the buttonPressed flag
    }

    disp_byte(i);
    //disp_hex(i);


    //    io1.digitalWrite(2, !bitRead(i, 1));
    //    io1.digitalWrite(3, !bitRead(i, 0));
    //    io1.digitalWrite(4, !bitRead(i, 5));
    //    io1.digitalWrite(5, !bitRead(i, 4));
    //    io1.digitalWrite(6, !bitRead(i, 3));
    //    io1.digitalWrite(7, !bitRead(i, 2));
    //    io1.digitalWrite(8, !bitRead(i, 1));
    //    io1.digitalWrite(9, !bitRead(i, 0));
    //    io1.digitalWrite(10, !bitRead(i, 5));
    //    io1.digitalWrite(11, !bitRead(i, 4));
    //    io1.digitalWrite(12, !bitRead(i, 3));
    //    io1.digitalWrite(14, !bitRead(i, 2));
   
    //    io1.digitalWrite(15, !bitRead(i, 0));

    delay(500); // Delay half-a-second
  }
  // }



}
