#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

char auth[]="gxvW2FYI0pXdd8EspcRvxw51MssdpMpI";
char ssid[]="Sam";
char pass[]="madan123";
int flagB=0;
int flagT=0;

void Buttonstate()
{
  int isBS = digitalRead(5);
  int isTS = digitalRead(4);
 
  if (isBS==1 && flagB==0){
    Serial.println("water level above the Bottom sensor");
    Blynk.virtualWrite(V1,1);
    Blynk.virtualWrite(V2,50);
    flagB=1;
  }
  else if (isBS==0 && flagB==1)
  {
  
    Serial.println("Lower than Bottom sensor");
    Blynk.notify("Lower than Bottom sensor");
    Blynk.virtualWrite(V1,0);
    Blynk.virtualWrite(V2,0);
    flagB=0;
  }

  
 if (isTS==1 && flagT==0){
    Serial.println("Water level above the Top sensor");
    Blynk.notify("Water level above the Top sensor");
    Blynk.virtualWrite(V0,1);
    Blynk.virtualWrite(V2,100);
    flagT=1;
  }
  else if (isTS==0 && flagT==1)
  {
  
    Serial.println("Lower than Top sensor");
    Blynk.virtualWrite(V0,0);
    Blynk.virtualWrite(V2,50);
    flagT=0;
  }
  
}

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);

pinMode(5, INPUT_PULLUP);
pinMode(4, INPUT_PULLUP);

  
Blynk.begin(auth, ssid, pass);
Blynk.virtualWrite(V0,0);
Blynk.virtualWrite(V1,0);
Blynk.virtualWrite(V2,0);
      

timer.setInterval(2000L,Buttonstate);

delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  Buttonstate();
  timer.run();
}
