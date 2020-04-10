/*
   Test FlySky IBus interface on an Arduino Mega.
    Connect FS-iA6B receiver to Serial1.
*/

#include "FlySkyIBus.h"
HardwareSerial FSkySerial(1);

void setup()
{
  Serial.begin(115200);
  IBus.begin(FSkySerial);
}

void loop()
{
  
  static uint16_t C0 = 0, C1 = 0, C2 = 0, C3 = 0, C4 = 0, C5 = 0, C6 = 0, C7 = 0, C8 = 0, C9 = 0; 
  IBus.loop();
  
  uint16_t C0n, C1n, C2n, C3n, C4n, C5n, C6n, C7n, C8n, C9n;
  C0n = IBus.readChannel(0);
  C1n = IBus.readChannel(1);
  C2n = IBus.readChannel(2);
  C3n = IBus.readChannel(3);
  C4n = IBus.readChannel(4);
  C5n = IBus.readChannel(5);
  C6n = IBus.readChannel(6);
  C7n = IBus.readChannel(7);
  C8n = IBus.readChannel(8);
  C9n = IBus.readChannel(9);
 

  if (((C0 <= (C0n - 5)) || ((C0 >= (C0n + 5)))) ||
      ((C1 <= (C1n - 5)) || ((C1 >= (C1n + 5)))) ||
      ((C2 <= (C2n - 5)) || ((C2 >= (C2n + 5)))) ||
      ((C3 <= (C3n - 5)) || ((C3 >= (C3n + 5)))) ||
      ((C4 <= (C4n - 5)) || ((C4 >= (C4n + 5)))) ||
      ((C5 <= (C5n - 5)) || ((C5 >= (C5n + 5)))) ||
      ((C6 <= (C6n - 5)) || ((C6 >= (C6n + 5)))) ||
      ((C7 <= (C7n - 5)) || ((C7 >= (C7n + 5)))) ||
      ((C8 <= (C8n - 5)) || ((C8 >= (C8n + 5)))) ||
      ((C9 <= (C9n - 5)) || ((C9 >= (C9n + 5)))))
  {
    C0 = C0n; C1 = C1n; C2 = C2n; C3 = C3n; C4 = C4n; C5 = C5n; C6 = C6n;
    C7 = C7n; C8 = C8n; C9 = C9n; 
    Serial.print("Ch0  "); Serial.println(C0, DEC);
    Serial.print("Ch1  "); Serial.println(C1, DEC);
    Serial.print("Ch2  "); Serial.println(C2, DEC);
    Serial.print("Ch3  "); Serial.println(C3, DEC);
    Serial.print("Ch4  "); Serial.println(C4, DEC);
    Serial.print("Ch5  "); Serial.println(C5, DEC);
    Serial.print("Ch6  "); Serial.println(C6, DEC);
    Serial.print("Ch7  "); Serial.println(C7, DEC);
    Serial.print("Ch8  "); Serial.println(C8, DEC);
    Serial.print("Ch9  "); Serial.println(C9, DEC);
    Serial.println("==================================================");

 //   sendFlySkyVoltage(15);
    delay(10);
  }
  
//  delay(45);
 // sendFlySkyVoltage(4);
}

//void sendFlySkyVoltage(uint16_t voltage) {
//  uint8_t first = voltage;
//  uint8_t second = voltage >> 8;
//  FSkySerial.write( 0x06);
//  FSkySerial.write( 0xA1);
//  FSkySerial.write( first);
//  FSkySerial.write( second);
//
//  uint16_t checksum = ~(0x06 + 0xA1 + first + second);
//  FSkySerial.write(checksum & 0xFF);
//  FSkySerial.write( checksum >> 8);
//}
