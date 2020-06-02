void setup() {
  // put your setup code here, to run once:

  #define analogValue 100
  pinMode(8, INPUT);  //sensor Left
  pinMode(2, OUTPUT); //motor right
  pinMode(3, OUTPUT); //motor right
   pinMode(4, OUTPUT); //motor left
  pinMode(5, OUTPUT); //motor left
  pinMode(9, INPUT);  //sensor Right
        digitalWrite(2,LOW);
              digitalWrite(4,LOW);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(8) == HIGH && digitalRead(9) == HIGH)
  { //it means both the sensors are on a black line. loop cross. Go straight
      analogWrite(3,analogValue);

      analogWrite(5,analogValue);
  }
  else if(digitalRead(8) == HIGH && digitalRead(9) == LOW)
  { //Left sensor is on black line. So turn left
      analogWrite(3,analogValue);
      analogWrite(5,0);
  }
  else if(digitalRead(8) == LOW && digitalRead(9) == HIGH)
  { //Right sensor is on black line. So turn right
      analogWrite(3,0);
      analogWrite(5,analogValue);
  }
  if(digitalRead(8) == LOW && digitalRead(9) == LOW)
  {//it means both the sensors are on white. Go straight
      analogWrite(3,analogValue);
      analogWrite(5,analogValue);
  }
}
