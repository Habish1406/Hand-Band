#include <SoftwareSerial.h>
//#include <ESP8266WiFi.h>
#define LORA_BAUD_RATE     115200    
#include <TinyGPS++.h>


TinyGPSPlus gps;
SoftwareSerial SerialGPS(4, 5);//tx,rx 

SoftwareSerial lora(13, 15);//tx,rx
 
float Latitude,Longitude;
 String LatitudeString , LongitudeString;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("..");
  SerialGPS.begin(9600);
  lora.begin(115200);
  Serial.println(gps.satellites.value());
  
}
 
void loop()
{
   while (SerialGPS.available() > 0)
   
   if (gps.encode(SerialGPS.read()))
    {
      if (gps.location.isValid())
      {
        Latitude = gps.location.lat();
        Longitude = gps.location.lng();
      }}
      LatitudeString = String(Latitude , 6);
       LongitudeString = String(Longitude , 6);
 String val = String(LatitudeString)+","+String(LongitudeString);  
  String cmd = "AT+SEND=0,"+String(val.length()) +","+ String(val)+"\r";
 
  while(lora.available()){
    Serial.write(lora.read());
    lora.println(cmd);
Serial.println(cmd);
  
  }
  
delay(500);
}
