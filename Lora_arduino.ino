#include <SoftwareSerial.h>
SoftwareSerial lora(4,5);//tx,rx
SoftwareSerial mySerial(2,3);
int i;
  char delimiter[] = ",";
  char *p;
  char string[128];
  
  String words[50],latit="11.360040",longit="77.827370";
  float f[10];
 
void setup()
{
  // put your setup code here, to run once:
  mySerial.begin(9600);
  Serial.begin(115200);
  lora.begin(115200);

 
}
 
void loop()
{
  
  String inString;
  while (lora.available())
  {
    if(lora.available()){
    inString += String(char(lora.read()));
 
    }
 
  Serial.println(inString);
  }
  if(inString.length()>0)
  {
  // Serial.begin(9600);
  

  inString.toCharArray(string, sizeof(string));
  i = 0;
  
  p = strtok(string, delimiter);
  while(p && i < 4)
  {
    words[i] = p;
    p = strtok(NULL, delimiter);
    ++i;
  }
    Serial.println(inString);
    
    for(i = 0; i < 4; ++i)
    {
      f[i]= words[i].toFloat();
    }
    if((f[2]>11.00) && (f[2]<12.00))
    {latit=String(f[2],6);}
    if((f[3]>77.00)&&(f[3]<78.00))
    {longit=String(f[3],6);}
    /*for(i = 0; i < 4; ++i)
  {
    Serial.println(f[i]);
  }*/
   Serial.println(latit);
    Serial.println(longit);
  
  
  }
//  if((f[2]>11.362695)&&(f[3]>77.827780)){
 mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     mySerial.println("AT+CMGS=\"+917603820161\"\r"); // Replace x with mobile number
     delay(1000);
     mySerial.println("Latitude="+latit);// The SMS text you want to send
     delay(100);
      mySerial.println("Longitude="+longit);// The SMS text you want to send
     delay(100);
     mySerial.println("http://www.google.com/maps/place/"+latit+","+longit);// The SMS text you want to send
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(10000);}
//}
