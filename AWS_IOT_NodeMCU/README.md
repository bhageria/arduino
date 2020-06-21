Connect NodeMCU to AWS IoT Core.
Publish Messages from NodeMCU to the Core
 
Tutorial by https://nerdyelectronics.com:

1)  AWS IoT - Create a Thing
    https://nerdyelectronics.com/iot/how-to-create-a-thing-in-aws-iot/
2)  Convert Certificates from .pem to .der format
    https://nerdyelectronics.com/iot/how-to-convert-certificates-from-pem-to-der-format/
3)  Connect NodeMCU to AWS IoT Core
    https://nerdyelectronics.com/iot/how-to-connect-nodemcu-to-aws-iot-core/
	
Do make sure to update the following lines:

Line number 23 - const char* ssid = "XXXXXXXXX"; - Add your Wifi Name here
Line number 24 - const char* password = "XXXXXXXXXXXXXx";  Add your Wifi password here
Line number 29 - const char* AWS_endpoint = "XXXXXXXXXXX-ats.iot.us-east-2.amazonaws.com"; Add your AWS Endpoint here.

Line number 193 - snprintf (msg, 75, "{\"Message\": \"Hello from NerdyElectronics.com\" - %d}", count); 
This is the line where we create the message which we want to send.

Line number 198 - client.publish("outTopic", msg); - 

In this line we publish the message we created in line 175. 
We publish it to the topic "outTopic". 
If you want to publish the message to some other topic, edit the topic name here.