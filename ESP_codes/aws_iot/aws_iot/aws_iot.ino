#include <ESP8266WiFi.h>

#include <AmazonIOTClient.h>

#include "ESP8266AWSImplementations.h"

Esp8266HttpClient httpClient;

Esp8266DateTimeProvider dateTimeProvider;

AmazonIOTClient iotClient;

ActionError actionError;

char *ssid="xxxxx";

char *password="xxxxxx";

void setup() {

  Serial.begin(115200);

  delay(10);

  // Connect to WAP

  Serial.print("Connecting to ");

  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println("");

  Serial.println("WiFi connected");

  Serial.println("IP address: ");

  Serial.println(WiFi.localIP());

 

  iotClient.setAWSRegion("ap-south-1");

  iotClient.setAWSEndpoint("amazonaws.com");

  iotClient.setAWSDomain("axxxxxxxx-ats.iot.ap-south-1.amazonaws.com");

  iotClient.setAWSPath("things/test/shadow");

  iotClient.setAWSKeyID("xxxxxxx");

  iotClient.setAWSSecretKey("xxxxxxxxxxxxxxxxx");

  iotClient.setHttpClient(&httpClient);

  iotClient.setDateTimeProvider(&dateTimeProvider);

}

 

void loop(){

  char* shadow = "{\"state\":{\"reported\": {\"foobar\": \"bar\"}}}";

  char* result = iotClient.update_shadow(shadow, actionError);

  Serial.println(result);

  delay(60000);

}
