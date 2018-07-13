#include "AIS_NB_BC95.h"
#include "TinyGPS++.h"
#include "SoftwareSerial.h"

String apnName = "devkit.nb";

//BigStream Config
String serverIP = "203.185.71.41"; // Your Server IP
String serverPort = "19150"; // Your Server Port
String bsKey = "<VONAME>:nbgps"; // BigStream Job KeyName ( VONAME:KEYNAME )
String udpData = "";

AIS_NB_BC95 AISnb;

const long interval = 20000;  //millisecond
unsigned long previousMillis = 0;

long cnt = 0;
SoftwareSerial serial_connection(10, 11); //RX=pin 10, TX=pin 11
TinyGPSPlus gps;
void setup()
{ 
  AISnb.debug = false;
  
  Serial.begin(9600);
  serial_connection.begin(9600);
  
  AISnb.setupDevice(serverPort);

  String ip1 = AISnb.getDeviceIP();  
  delay(1000);
  
  previousMillis = millis();

}
void loop()
{ 
  while(serial_connection.available())
  {
    gps.encode(serial_connection.read());
  }

  if(gps.location.isUpdated())
  {
    Serial.print("Satellite Count:");
    Serial.println(gps.satellites.value());
    Serial.print("Latitude:");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude:");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Speed KM/H:");
    Serial.println(gps.speed.kmph());
    Serial.print("Altitude Feet:");
    Serial.println(gps.altitude.feet());
    Serial.println("");
  }
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
    {
      cnt++;     

      udpData = String(gps.satellites.value()) + "," + String(gps.location.lat(),6) + "," + String(gps.location.lng(),6) + "," + String(gps.speed.kmph())  + "," + String(cnt);
      
      // Send data in String 
      String dataPackage = bsKey + "," + udpData;
      UDPSend udp = AISnb.sendUDPmsgStr(serverIP, serverPort, dataPackage);
   
      previousMillis = currentMillis;
  
    }
  UDPReceive resp = AISnb.waitResponse();
     
}



