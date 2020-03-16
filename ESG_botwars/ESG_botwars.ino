void setup() {
  // put your setup code here, to run once:
  pinMode(8, INPUT);  //sensor Left
  pinMode(2, OUTPUT); //motor right
  pinMode(3, OUTPUT); //motor right
   pinMode(4, OUTPUT); //motor left
  pinMode(5, OUTPUT); //motor left
  pinMode(9, INPUT);  //sensor Right
  

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(8) == HIGH && digitalRead(9) == HIGH)
  { //it means both the sensors are on a black line. loop cross. Go straight
      digitalWrite(2,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
  }
  else if(digitalRead(8) == HIGH && digitalRead(9) == LOW)
  { //Left sensor is on black line. So turn left
      digitalWrite(2,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      digitalWrite(5,HIGH);;
  }
  else if(digitalRead(8) == LOW && digitalRead(9) == HIGH)
  { //Right sensor is on black line. So turn right
      digitalWrite(2,LOW);
      digitalWrite(3,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
  }
  if(digitalRead(8) == LOW && digitalRead(9) == LOW)
  {//it means both the sensors are on white. Go straight
      digitalWrite(2,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
  }
}
