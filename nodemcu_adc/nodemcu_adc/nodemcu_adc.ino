const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0

int sensorValue = 0;  // value read from the pot
int outputValue = 0;  // value to output to a PWM pin
float temperature = 0;
void setup() {
  // initialize serial communication at 115200
  Serial.begin(9600);
}

void loop() {
  // read the analog in value
  sensorValue = analogRead(analogInPin);
  temperature = ((sensorValue*5.0)/1024)*100;
  // map it to the range of the PWM out
  //outputValue = map(sensorValue, 0, 1024, 0, 255);
  
  // print the readings in the Serial Monitor
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t temperature = ");
  Serial.println(temperature);

  delay(1000);
}
