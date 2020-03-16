#include <Wire.h>

int i;
void setup() {
 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(requestEvent); /* register request event */
 Serial.begin(9600);           /* start serial for debug */
 pinMode(8,OUTPUT);
}

void loop() {
 if(Serial.available() > 0)
 {
    if(Serial.read()=='h')
      digitalWrite(8,HIGH);
    else
      digitalWrite(8,LOW);
 }
}

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    Serial.print(c); 
  }
 Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
  i++;
  Serial.println(i);
 Wire.write(i);  /*send string on request */
}
