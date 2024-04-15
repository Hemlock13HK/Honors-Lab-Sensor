#include <SD.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>

// Data wire is connected to the Arduino digital pin 4
#define ONE_WIRE_BUS 3

File myFile;
float myTemp = 0.0;
String sentence = "nothing";

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to the Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup(void)
{
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
  while (!Serial) {
    ; // wait for the serial port to connect. Needed for the native USB port only
  }
  Serial.println("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("Initialization failed!");
    while (1)
      ;
  }
  Serial.println("Initialization done.");
}

void loop(void)
{ 
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  Serial.print("Celsius temperature: ");
  myTemp = sensors.getTempCByIndex(0);
  Serial.println(myTemp); 

  myFile = SD.open("test.txt", FILE_WRITE);

  unsigned long currentTimeInSeconds = millis() / 1000;

  sentence = "Time: " + String(currentTimeInSeconds) + "s, Temperature: " + String(myTemp);
  Serial.println(sentence);

  if (myFile) {
    Serial.println("Writing to test.txt...");
    myFile.println(sentence);
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("Error opening test.txt");
  }
  delay(120000);
}


