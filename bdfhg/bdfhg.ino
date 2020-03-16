#include<string.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);
  char buf;
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  char buf[2];
  String data="";
  String str = "ON";
  if (Serial.available() > 0) {
      Serial.readBytesUntil( '\n',buf,100);
     //Serial.print(buf);
     str = (char *)buf;
     //Serial.print(str);
     if(str.equals("on"))
       Serial.print("yes");
       else
       Serial.print("no");
   }

}
