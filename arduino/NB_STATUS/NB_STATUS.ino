#include "AIS_NB_BC95.h"

String apnName = "devkit.nb";

//BigStream Config
String serverIP = "203.185.71.41"; // Your Server IP
String serverPort = "19150"; // Your Server Port
String bsKey = "<VONAME>:nbstatus"; // BigStream Job KeyName ( VONAME:KEYNAME )
String udpData = "";

AIS_NB_BC95 AISnb;

const long interval = 20000;  //millisecond
unsigned long previousMillis = 0;

long cnt = 0;
void setup()
{ 
  AISnb.debug = true;
  
  Serial.begin(9600);

  AISnb.setupDevice(serverPort);

  String ip1 = AISnb.getDeviceIP();  
  delay(1000);
  
  previousMillis = millis();

}
void loop()
{ 
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
    {
      cnt++;     

      String ip = AISnb.getDeviceIP();
      signal sig = AISnb.getSignal();

      udpData = sig.csq + "," + sig.rssi + "," + String(cnt);
      
      // Send data in String 
      String dataPackage = bsKey + "," + udpData;
      UDPSend udp = AISnb.sendUDPmsgStr(serverIP, serverPort, dataPackage);
   
      previousMillis = currentMillis;
  
    }
  UDPReceive resp = AISnb.waitResponse();
     
}



