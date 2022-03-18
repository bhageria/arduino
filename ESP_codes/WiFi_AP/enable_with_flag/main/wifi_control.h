/*
 * In this code, it creates an AP with the mentioned SSID and password and sends the IP to serial
 * Connect to the IP from a browser and it opens a form for username and password
 * 
 * On clicking login, the username and the password from the form are sent to serial
 */




#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "config.h"

#define DATA_SIZE 2500

void handleNotFound();
void handleFileRequest();
void handleRoot();
void wifiInit(uint8_t *wifiConnectStatus);

uint8_t wifiConnect = 0;
uint8_t wifiConnectStatus=0;

//SSID and Password to your ESP Access Point


ESP8266WebServer server(80); //Server on port 80
IPAddress    apIP(42, 42, 42, 42);
 
//==============================================================
//     This rutine is exicuted when you open its IP in browser
//==============================================================
void handleRoot() {
  server.send(200, "text/html", "<form action=\"/getfile\" method=\"POST\"><input type=\"text\" name=\"username\" placeholder=\"Username\"></br><input type=\"password\" name=\"password\" placeholder=\"Password\"></br><input type=\"text\" name=\"filename\" placeholder=\"FileName\"></br><input type=\"submit\" value=\"getfile\"></form>");
}
 
//===============================================================
//                  SETUP
//===============================================================
void wifiInit(uint8_t *wifiConnectStatus){
  WiFi.mode(WIFI_AP);           //Only Access point
  
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);  //Start HOTspot removing password will disable security
 
  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(myIP);
  *wifiConnectStatus = 1;
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/", handleRoot);      //Which routine to handle at root location
  server.on("/getfile", HTTP_POST, handleFileRequest);
  server.onNotFound(handleNotFound);
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");
  digitalWrite(2, HIGH);
}
//===============================================================
//                     LOOP
//===============================================================


void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}


void handleFileRequest() {                         // If a POST request is made to URI /login

  //String fileToSend="";
  char dataBuff[DATA_SIZE];
  int i=0;
  //File dataFile;
  
  Serial.println(server.arg("username"));
  Serial.println(server.arg("password"));
  Serial.println(server.arg("filename"));
 // Serial.println(server.arg("date"));
  
  if( ! server.hasArg("username") || ! server.hasArg("password") || server.arg("username") == NULL || server.arg("password") == NULL)  // If the POST request doesn't have username and password data
  {  
    server.send(400, "text/plain", "400 : Invalid Request");         // The request is invalid, so send HTTP status 400
    Serial.println(server.arg("username"));
    Serial.println(server.arg("password"));
    return;
  }
  if((server.arg("username") == formUser && server.arg("password") == formPassword)&& (server.arg("filename") == NULL ))
  { // If both the username and the password are correct
    //Serial.println("Entered the date and month null");

    server.send(422, "text/json", "422 : No filename Sent");
  } 
  else if((server.arg("username") == formUser && server.arg("password") == formPassword)&& (!(server.arg("filename") == NULL)))
  {
    //open the file from SD card
    if((server.arg("filename")=="hello"))
    {
      Serial.print("Opening Hello:  ");
      Serial.println(server.arg("filename"));
      server.send(200, "plain/text", "Hello from Vivek");
    }
    else if((server.arg("username") == formUser && server.arg("password") == formPassword)&& ((server.arg("filename") == "END")))
    {
      wifiConnectStatus = 0;
      wifiConnect = 0;
      WiFi.softAPdisconnect (true);
      Serial.print("begin");
      Serial.println("Wifi End");
    }
    else
    {
      Serial.print("error opening ");
      Serial.println(server.arg("filename"));
      server.send(404, "plain/text", "404 : file not found");
    }
    
    for(i=0;i<6000;i++)
    {
      dataBuff[i] = 0;
    }
    i=0;
  }
  
  else
  {                                                                              // Username and password don't match
    server.send(401, "text/json", "401 : Unauthorized");
    Serial.println(server.arg("username"));
    Serial.println(server.arg("password"));
  }
}
