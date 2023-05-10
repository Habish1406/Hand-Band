#include <SoftwareSerial.h>
SoftwareSerial lora(13,15);//tx,rx
 
int i;
  char delimiter[] = ",";
  char *p;
  char string[128];
  
  String words[50],latit="11.360040",longit="77.827370",LatitudeString,LongitudeString;
  float f[10];
void setup()
{
  // put your setup code here, to run once:
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
    //Serial.println(inString);+
    
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
   //Serial.println(latit);
   // Serial.println(longit);
  }
  LatitudeString = latit;
       LongitudeString = longit;
 String val = String(LatitudeString)+","+String(LongitudeString);
 
   
  String cmd = "AT+SEND=0,"+String(val.length()) +","+ String(val)+"\r";
  lora.println(cmd);
 Serial.println(cmd);
  
  }
  delay(500);
}
