#include <ESP8266WiFi.h>
#include <PubSubClient.h>


// Update these with values suitable for your network.
const char* ssid = "Vk";
const char* password = "AsdZxc@123";
const char* mqtt_server = "io.adafruit.com";
#define mqtt_port 1883
#define MQTT_USER "bhageria"
#define MQTT_PASSWORD "274edc6774534d25a429fa3706606cd3"
#define MQTT_SERIAL_PUBLISH_CH "bhageria/feeds/room-temp"
#define MQTT_SERIAL_RECEIVER_CH "USER/feeds/ledBrightness"

const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0

int sensorValue = 0;  // value read from the pot
int outputValue = 0;  // value to output to a PWM pin

char data[5];
float temperature = 0;

WiFiClient wifiClient;

int wifiCredentials = 0;

PubSubClient client(wifiClient);

void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "NodeMCUClient-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(),MQTT_USER,MQTT_PASSWORD)) {
      Serial.println("connected");
      //Once connected, publish an announcement...
      //client.publish(MQTT_SERIAL_PUBLISH_CH, "hello world");
      // ... and resubscribe
      client.subscribe(MQTT_SERIAL_PUBLISH_CH);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void callback(char* topic, byte *payload, unsigned int length) {
    Serial.println("-------new message from broker-----");
    Serial.print("channel:");
    Serial.println(topic);
    Serial.print("data:");  
    //Serial.write(48);  
    Serial.write(payload, length);
    if(*payload == 'O' && *(payload+1)== 'N')
    {
      digitalWrite(13, HIGH);
    }
    else
    {
      digitalWrite(13, LOW);
    }
}

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.setTimeout(500);// Set time out for 
  //getCredentials(); 

    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);
    delay(1000);
    reconnect();
}

/*void getCredentials()
{
    Serial.println("Enter the Wifi Name:");
    while(!Serial.available());
    char ssidbfr[50];
    memset(ssidbfr,0, 50);
    Serial.readBytesUntil( '\n',ssidbfr,50);
    ssid = ssidbfr;
    Serial.println(ssid);

    Serial.println("Enter the Wifi Password:");
    while(!Serial.available());
    char passbfr[50];
    memset(passbfr,0, 50);
    Serial.readBytesUntil( '\n',passbfr,50);
    password = passbfr;
    Serial.println(password);
}
*/
void publishSerialData(char *serialData){
  if (!client.connected()) {
    reconnect();
  }
  client.publish(MQTT_SERIAL_PUBLISH_CH, serialData);
}
void loop() {
  
  sensorValue = analogRead(analogInPin);
  temperature = ((sensorValue*3.3)/1024)*100;
   memset(data,0, 5);
  // map it to the range of the PWM out
  outputValue = map(sensorValue, 0, 1024, 0, 255);
  
  // print the readings in the Serial Monitor
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t temperature = ");
  Serial.println(String(temperature));
  itoa(temperature,data,10);
  publishSerialData(data);
  delay(60000);
   client.loop();
   
     if (Serial.available() > 0) {
     char bfr[101];
     memset(bfr,0, 101);
     Serial.readBytesUntil( '\n',bfr,100);
     publishSerialData(bfr);
   }
 }

