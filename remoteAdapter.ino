#include <IRremote.h>
#include <SoftwareSerial.h>

#define bit9600Delay 100  
#define halfBit9600Delay 50
#define bit4800Delay 188
#define halfBit4800Delay 94


int IRPIN = 3;
int rxPin = 2;
int txPin = 4;
SoftwareSerial mySerial(rxPin, txPin);

void setup() {
 Serial.begin(9600);
 Serial.println("<Arduino is ready>");

 mySerial.begin(9600);
}

void loop() {
 recvOneChar();
 showNewData();
}

void recvOneChar() {
 if (mySerial.available() > 0) {
 receivedChar = mySerial.read();
 newData = true;
 }
}

void showNewData() {
 if (newData == true) {
 Serial.print("This just in ... ");
 Serial.println(receivedChar);
 newData = false;
 }
}
