//biblioteca responsável pela comunicação com o Cartão SD
#include <SD.h>

#define CS_PIN  D8


void setup()
{
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");

    // see if the card is present and can be initialized:
  if (!SD.begin(CS_PIN))
  {
    Serial.println("Card failed, or not present");
      // don't do anything more:
      while (1);
  }
  else
  {
    Serial.print("SD card initialized...");
  }
 
}

void loop()
{
  char dataBuff[600];
  int i=0;
  File dataFile = SD.open("10_2_20.txt");

  // if the file is available, write to it:
  if (dataFile) {
    Serial.println(sizeof(dataFile));
    while (dataFile.available()) {
      dataBuff[i] = dataFile.read();
      i++;
      //Serial.write(dataFile.read());
    }
    dataFile.close();
    i=0;
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

  delay(2000);
  Serial.println(dataBuff);
}

