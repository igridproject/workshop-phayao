#include "AIS_NB_BC95.h"

String apnName = "devkit.nb";

//BigStream Config
String serverIP = "203.185.71.41"; // BigStream Server IP
String serverPort = "19150"; // BigStream Server Port
String bsKey = "<VONAME>:testnb"; // BigStream Job KeyName ( VONAME:KEYNAME )
String udpData = "HelloWorld ";

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
  
  //pingRESP pingR = AISnb.pingIP(serverIP);
  previousMillis = millis();

}
void loop()
{ 
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
    {
      cnt++;     
           
      // Send data in String 
      String dataPackage = bsKey + "," + udpData + String(cnt);
      UDPSend udp = AISnb.sendUDPmsgStr(serverIP, serverPort, dataPackage);
   
      //Send data in HexString     
      //udpDataHEX = AISnb.str2HexStr(udpData);
      //UDPSend udp = AISnb.sendUDPmsg(serverIP, serverPort, udpDataHEX);
      previousMillis = currentMillis;
  
    }
  UDPReceive resp = AISnb.waitResponse();
     
}



