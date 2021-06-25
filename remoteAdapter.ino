#include <IRremote.h>
#include <SoftwareSerial.h>
#include <Dictionary.h>

#define bit9600Delay 100  
#define halfBit9600Delay 50
#define bit4800Delay 188
#define halfBit4800Delay 94

// https://www.arduino.cc/en/Reference/softwareSerial
/*
 * byte message[] = {0xAA, 0xBB, 0x06, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03 };
 * Serial.write(message, sizeof(message));
 */

int IRPIN = 2;
int rxPin = 7;
int txPin = 6;
SoftwareSerial mySerial(rxPin, txPin);

//struct CommandTuple {
//  public:
//  uint8_t *rs232Command;
//
//  CommandTuple(uint8_t *newRS232Command ) : rs232Command{newRS232Command} {}
//};

struct Command {
  char *rs232Command;

  Command(char *newRS232Command ) : rs232Command{newRS232Command} {}
};

//CommandTuple commandList[] = 
//{
//  CommandTuple(new uint8_t[10]{0x37, 0x51, 0x06, 0xEA, 0x62, 0x01, 0x00, 0x00, 0x00, 0xE9}), // HDMI1 // 0
//  CommandTuple(new uint8_t[10]{0x37, 0x51, 0x06, 0xEA, 0x62, 0x02, 0x00, 0x00, 0x00, 0xEA}), // HDMI2 // 1
//  CommandTuple(new uint8_t[10]{0x37, 0x51, 0x06, 0xEA, 0x62, 0x08, 0x00, 0x00, 0x00, 0xE0}), // DP1   // 2
//  CommandTuple(new uint8_t[10]{0x37, 0x51, 0x06, 0xEA, 0x62, 0x10, 0x00, 0x00, 0x00, 0xF8}), // DP2   // 3
//  CommandTuple(new uint8_t[6]{0x37, 0x51, 0x02, 0xEB, 0x20, 0xAF}), // GetPowerState                  // 4
//  CommandTuple(new uint8_t[7]{0x37, 0x51, 0x03, 0xEA, 0x20, 0x01, 0xAE }), // SetPowerStateOn         // 5
//  CommandTuple(new uint8_t[7]{0x37, 0x51, 0x03, 0xEA, 0x20, 0x00, 0xAF}) // SetPowerStateOff          // 6
//};

Command commandList[] = 
{
  Command("37 51 06 EA 62 01 00 00 00 E9"),
  Command("37 51 06 EA 62 02 00 00 00 EA"),
  Command("37 51 06 EA 62 08 00 00 00 E0"),
  Command("37 51 06 EA 62 10 00 00 00 F8"),
  Command("37 51 02 EB 20 AF"),
  Command("37 51 03 EA 20 00 AF"),
  Command("37 51 03 EA 20 01 AE")
};

void setup() {
  mySerial.begin(9600);
  Serial.begin (9600);
  Serial.println("Enabling IRin");
  IrReceiver.begin(IRPIN, ENABLE_LED_FEEDBACK);
  Serial.println("Enabled IRin");
}

void ProcessIRInput(const long hexInput)
{
  switch ( IrReceiver.decodedIRData.decodedRawData )
    {
      case 0xBA45FF00:
        // Send data command SetVideoInput 60h 2 62h W 4, 0x00000001 - HDMI1/MHL1 37-51-06-EA-62-[Data0]-…-[Data3]-CHK 
        Serial.println("Keycode: 1");
//        mySerial.write(commandList[1].rs232Command, sizeof(commandList[1].rs232Command));
        mySerial.write(commandList[1].rs232Command);
        Serial.println(commandList[1].rs232Command);
        break;
      case 0xB946FF00:
        // Send data command SetVideoInput 60h 2 62h W 4, 0x00000002 - HDMI2/MHL2 37-51-06-EA-62-[Data0]-…-[Data3]-CHK 
        Serial.println("Keycode: 2");
//        mySerial.write(commandList[2].rs232Command, sizeof(commandList[2].rs232Command));
        mySerial.write(commandList[2].rs232Command);
        break;
      case 0xB847FF00:
        // Send data command SetVideoInput 60h 2 62h W 4, 0x00000008 - DP1 37-51-06-EA-62-[Data0]-…-[Data3]-CHK 
        Serial.println("Keycode: 3");
//        mySerial.write(commandList[3].rs232Command, sizeof(commandList[3].rs232Command));
        mySerial.write(commandList[3].rs232Command);
        break;
      case 0xBB44FF00:
        // Send data command SetVideoInput 60h 2 62h W 4, 0x00000010 - DP2 37-51-06-EA-62-[Data0]-…-[Data3]-CHK 
        Serial.println("Keycode: 4");
//        mySerial.write(commandList[4].rs232Command, sizeof(commandList[4].rs232Command));
        mySerial.write(commandList[4].rs232Command);
        break;
      case 0xBF40FF00:
        Serial.println("Keycode: 5");
        break;
      case 0xBC43FF00:
        Serial.println("Keycode: 6");
        break;
      case 0xF807FF00:
        Serial.println("Keycode: 7");
        break;
      case 0xEA15FF00:
        Serial.println("Keycode: 8");
        break;
      case 0xF609FF00:
        Serial.println("Keycode: 9");
        break;
      case 0xE619FF00:
        Serial.println("Keycode: 0");
        break;
      case 0xE916FF00:
        // GetPowerState 20h 0 20h R 0 , Power State (BYTE) 0 - off 1 - on , 37-51-02-EB-20-CHK , 1 , 6F-37-04-02-[RC]-20-[Data0]-CHK
        // SetPowerState 20h 0 20h W 1 , Power State (BYTE) 0 - off 1 - on , 37-51-03-EA-20-[Data0]-CHK , 0 , 6F-37-03-02-[RC]-20-CHK
        Serial.println("Keycode: *");
//        mySerial.write(commandList[5].rs232Command, sizeof(commandList[5].rs232Command));
        mySerial.write(commandList[5].rs232Command);
        break;
      case 0xF20DFF00:
        Serial.println("Keycode: #");
//        mySerial.write(commandList[6].rs232Command, sizeof(commandList[6].rs232Command));
        mySerial.write(commandList[6].rs232Command);
        break;
      case 0xE718FF00:
        Serial.println("Keycode: ^");
        break;
      case 0xA55AFF00:
        Serial.println("Keycode: >");
        break;
      case 0xAD52FF00:
        Serial.println("Keycode: v");
        break;
      case 0xF708FF00:
        Serial.println("Keycode: <");
        break;
      case 0xE31CFF00:
        Serial.println("Keycode: OK");
        break;
    }
}



void loop() {
  // put your main code here, to run repeatedly:
  if (IrReceiver.decode())
  {
    ProcessIRInput(IrReceiver.decodedIRData.decodedRawData);
    IrReceiver.resume();
  }
  
//  if (mySerial.available()>0){
//    mySerial.read();
//  }
}
