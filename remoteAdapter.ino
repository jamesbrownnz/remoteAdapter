#include <IRremote.h>
#include <SoftwareSerial.h>

#define bit9600Delay 100  
#define halfBit9600Delay 50
#define bit4800Delay 188
#define halfBit4800Delay 94

// https://forum.arduino.cc/t/serial-input-basics/278284/2

int IRPIN = 3;
int rxPin = 2;
int txPin = 4;

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;
byte messageName[] = {0x37, 0x51, 0x02, 0xEB, 0x01, 0x8E}

SoftwareSerial mySerial(rxPin, txPin);

void setup() {
 Serial.begin(9600);
 Serial.println("<Arduino is ready>");

 mySerial.begin(9600);

 mySerial.write(messageName, sizeof(messageName));
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
