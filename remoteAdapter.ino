#include <IRremote.h>
#include <SoftwareSerial.h>

#define bit9600Delay 100  
#define halfBit9600Delay 50
#define bit4800Delay 188
#define halfBit4800Delay 94

// https://www.arduino.cc/en/Reference/softwareSerial
/*
 * byte message[] = {0xAA, 0xBB, 0x06, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03 };
 * Serial.write(message, sizeof(message));
 */

int IRPIN = 3;
int rxPin = 2;
int txPin = 4;
SoftwareSerial mySerial(rxPin, txPin);

//struct CommandTuple {
//  public:
//  uint8_t *rs232Command;
//
//  CommandTuple(uint8_t *newRS232Command ) : rs232Command{newRS232Command} {}
//};
//
//struct Command {
//  char *rs232Command;
//
//  Command(char *newRS232Command ) : rs232Command{newRS232Command} {}
//};
//
//CommandTuple byteCommandList[] = 
//{
//  CommandTuple(new uint8_t[10]{0x37, 0x51, 0x06, 0xEA, 0x62, 0x01, 0x00, 0x00, 0x00, 0xE9}), // HDMI1 // 0
//  CommandTuple(new uint8_t[10]{0x37, 0x51, 0x06, 0xEA, 0x62, 0x02, 0x00, 0x00, 0x00, 0xEA}), // HDMI2 // 1
//  CommandTuple(new uint8_t[10]{0x37, 0x51, 0x06, 0xEA, 0x62, 0x08, 0x00, 0x00, 0x00, 0xE0}), // DP1   // 2
//  CommandTuple(new uint8_t[10]{0x37, 0x51, 0x06, 0xEA, 0x62, 0x10, 0x00, 0x00, 0x00, 0xF8}), // DP2   // 3
//  CommandTuple(new uint8_t[6]{0x37, 0x51, 0x02, 0xEB, 0x20, 0xAF}), // GetPowerState                  // 4
//  CommandTuple(new uint8_t[7]{0x37, 0x51, 0x03, 0xEA, 0x20, 0x01, 0xAE }), // SetPowerStateOn         // 5
//  CommandTuple(new uint8_t[7]{0x37, 0x51, 0x03, 0xEA, 0x20, 0x00, 0xAF}), // SetPowerStateOff         // 6
//  CommandTuple(new uint8_t[6]{0x37, 0x51, 0x02, 0xEB, 0x01, 0x8E}) // GetMonitorName                  // 7
//};
//
//Command commandList[] = 
//{
//  Command("37 51 06 EA 62 01 00 00 00 E9"),
//  Command("37 51 06 EA 62 02 00 00 00 EA"),
//  Command("37 51 06 EA 62 08 00 00 00 E0"),
//  Command("37 51 06 EA 62 10 00 00 00 F8"),
//  Command("37 51 02 EB 20 AF"),
//  Command("37 51 03 EA 20 00 AF"),
//  Command("37 51 03 EA 20 01 AE"),
//  Command("37 51 02 EB 01 8E")
//};

void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  mySerial.begin(9600);
  Serial.begin (9600);

  mySerial.listen();
  
  Serial.println("Enabling IRin");
  IrReceiver.begin(IRPIN, ENABLE_LED_FEEDBACK);
  Serial.println("Enabled IRin");
}

void ProcessIRInput(const long hexInput)
{
  if ( IrReceiver.decodedIRData.decodedRawData == 0xBA45FF00 )
  {
    Serial.println("Keycode: 1");
    byte messageOne[] = {0x37, 0x51, 0x06, 0xEA, 0x62, 0x01, 0x00, 0x00, 0x00, 0xE9};
    Serial.print("Number of bytes written ");
    Serial.print(mySerial.write(messageOne, sizeof(messageOne)));
    Serial.println();
  }
  else if ( IrReceiver.decodedIRData.decodedRawData == 0xB946FF00) {
    Serial.println("Keycode: 2");
  }
  else if ( IrReceiver.decodedIRData.decodedRawData == 0xB847FF00) {
    Serial.println("Keycode: 3");
  }
  else if ( IrReceiver.decodedIRData.decodedRawData == 0xBB44FF00) {
    Serial.println("Keycode: 4");
  }
  else if ( IrReceiver.decodedIRData.decodedRawData == 0xBF40FF00) {
    Serial.println("Keycode: 5");
  }
  else if ( IrReceiver.decodedIRData.decodedRawData == 0xBC43FF00) {
    Serial.println("Keycode: 6");
  }
  else if ( IrReceiver.decodedIRData.decodedRawData == 0xF807FF00){
    Serial.println("Keycode: 7");
  }
  else if ( IrReceiver.decodedIRData.decodedRawData == 0xEA15FF00){
    Serial.println("Keycode: 8");
  }
  else if ( IrReceiver.decodedIRData.decodedRawData == 0xF609FF00){
    Serial.println("Keycode: 9");
  }
  else if ( IrReceiver.decodedIRData.decodedRawData == 0xE619FF00){
    Serial.println("Keycode: 0");
  }
  else if ( IrReceiver.decodedIRData.decodedRawData == 0xE916FF00){
    Serial.println("Keycode: *");
    byte messageStar[] = {0x37, 0x51, 0x03, 0xEA, 0x20, 0x01, 0xAE };
    Serial.print("Number of bytes written ");
    Serial.print(mySerial.write(messageStar, sizeof(messageStar)));
    Serial.println();
  }
  else if ( IrReceiver.decodedIRData.decodedRawData == 0xF20DFF00){
    Serial.println("Keycode: #");
    byte messageHash[] = {0x37, 0x51, 0x03, 0xEA, 0x20, 0x00, 0xAF};
    Serial.print("Number of bytes written ");
    Serial.print(mySerial.write(messageHash, sizeof(messageHash)));
    Serial.println();
  }
  else if ( IrReceiver.decodedIRData.decodedRawData == 0xE718FF00){
    Serial.println("Keycode: ^");
  }
  else if ( IrReceiver.decodedIRData.decodedRawData == 0xA55AFF00){
    Serial.println("Keycode: >");
  }
  else if ( IrReceiver.decodedIRData.decodedRawData == 0xAD52FF00){
    Serial.println("Keycode: v");
  }
  else if ( IrReceiver.decodedIRData.decodedRawData == 0xF708FF00){
    Serial.println("Keycode: <");
  }
  else if ( IrReceiver.decodedIRData.decodedRawData == 0xE31CFF00){
    Serial.println("Keycode: OK");
    byte messageOk[] = {0x37, 0x51, 0x02, 0xEB, 0x01, 0x8E};
    Serial.print("Number of bytes written ");
    Serial.print(mySerial.write(messageOk, sizeof(messageOk)));
    Serial.println();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (IrReceiver.decode())
  {
    ProcessIRInput(IrReceiver.decodedIRData.decodedRawData);
    IrReceiver.resume();
  }
  
  if (mySerial.available()>0){
    Serial.print((char)mySerial.read()); 
  }
  else {
  }
}
