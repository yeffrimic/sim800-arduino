
// Connect VIO to +5V
// Connect GND to Ground
// Connect RX (data into SIM808) to Digital 11
// Connect TX (data out from SIM808) to Digital 10

//libraries
#include <SoftwareSerial.h>

// variables
SoftwareSerial mySerial(2, 3); // RX, TX

String gprsStr1 = "";//this is the string that will receive the data from serial
String dos = "null";//this string is the localitation and timestamp from network
int a = 0;// control variable
String lat, lon, timestamp;
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  mySerial.begin(9600);
  // delay(5000);
  Serial.println("beginning");
}

void loop() // run over and over
{
  while (a < 8) {
    //Serial.println  ("sending");
    // Serial.println(a);
    atCommands(); // function that sends the AT commands
    serial(); // function that receives the serial data from sim800
    delay(200);
  }
  Serial.println(dos);
  Serial.println(lat);
  Serial.println(lon);
  Serial.println(timestamp);
  delay(30000);
  a = 0;

}
void atCommands() {
  switch (a) {
    case 0:
      mySerial.write("AT");
      mySerial.println();
      break;
    case 1:
      mySerial.write("AT+CGATT=1");
      mySerial.println();
      break;
    case 2:
      mySerial.write("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
      mySerial.println();
      break;
    case 3:
      mySerial.write("AT+SAPBR=3,1,\"APN\",\"broadband.tigo.gt\"");
      mySerial.println();
      break;
    case 4:
      mySerial.write("AT+SAPBR=1,1");
      mySerial.println();
      break;
    case 5:
      mySerial.write("AT+CIPGSMLOC=1,1");
      mySerial.println();
      break;
    case 6:
      mySerial.write("AT+CIPGSMLOC=1,1");
      mySerial.println();
      break;
    case 7:
      mySerial.write("AT+SAPBR=0,1");
      mySerial.println();
      break;
  }
}


byte data2;


void serial() {
  while ( gprsStr1[gprsStr1.length() - 1] != 10 && gprsStr1[gprsStr1.length() - 2] != 13 && gprsStr1[gprsStr1.length() - 3] != 75 ) {
    while (mySerial.available()) {
      data2 = (char)mySerial.read();
      Serial.write(data2);
      gprsStr1 += char(data2);

    }

    if ( gprsStr1[gprsStr1.length() - 1] == 10 && gprsStr1[gprsStr1.length() - 2] == 13 && gprsStr1[gprsStr1.length() - 3] == 75  ) { // == "658413131079751310"){

      //  Serial.println(gprsStr1.length());
      Serial.println(gprsStr1);
      if (a == 5) {
        dos = gprsStr1.substring(33, gprsStr1.length() - 5);
        lon = dos.substring(0, 10);
        lat = dos.substring(11, 20);
        timestamp=dos.substring(21);
      }
      Serial.println(a);
      Serial.println("bieen");
      a++;
    }
  }
  gprsStr1 = "";
  Serial.println();
}
