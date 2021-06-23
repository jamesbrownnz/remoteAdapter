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
SoftwareSerial mySerial(6, 7);

struct CommandTuple {
  int *rs232Command;
  long irCommand;

  CommandTuple(int *newRS232Command, long newIRCommand ) : rs232Command{newRS232Command}, irCommand{newIRCommand} {}
};

CommandTuple commandMap[] = 
{
  CommandTuple(new int[10]{0x37, 0x51, 0x06, 0xEA, 0x62, 0x01, 0x00, 0x00, 0x00, 0xE9}, 0xBA45FF00),
  CommandTuple(new int[10]{0x37, 0x51, 0x06, 0xEA, 0x62, 0x02, 0x00, 0x00, 0x00, 0xEA}, 0xB946FF00),
  CommandTuple(new int[10]{0x37, 0x51, 0x06, 0xEA, 0x62, 0x08, 0x00, 0x00, 0x00, 0xE0}, 0xB847FF00),
  CommandTuple(new int[10]{0x37, 0x51, 0x06, 0xEA, 0x62, 0x10, 0x00, 0x00, 0x00, 0xF8}, 0xBB44FF00),
  CommandTuple(new int[6]{0x37, 0x51, 0x02, 0xEB, 0x20, 0xAF}, 0xE916FF00),
  CommandTuple(new int[7]{0x37, 0x51, 0x03, 0xEA, 0x20, 0x00, 0xAF}, 0xE916FF00)
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
        break;
      case 0xB946FF00:
        // Send data command SetVideoInput 60h 2 62h W 4, 0x00000002 - HDMI2/MHL2 37-51-06-EA-62-[Data0]-…-[Data3]-CHK 
        Serial.println("Keycode: 2");
        break;
      case 0xB847FF00:
        // Send data command SetVideoInput 60h 2 62h W 4, 0x00000008 - DP1 37-51-06-EA-62-[Data0]-…-[Data3]-CHK 
        Serial.println("Keycode: 3");
        break;
      case 0xBB44FF00:
        // Send data command SetVideoInput 60h 2 62h W 4, 0x00000010 - DP2 37-51-06-EA-62-[Data0]-…-[Data3]-CHK 
        Serial.println("Keycode: 4");
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
        break;
      case 0xF20DFF00:
        Serial.println("Keycode: #");
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
//    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    IrReceiver.resume();
  }
  delay(250);
}
