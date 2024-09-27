#include <WiFi.h>
#include "ThingSpeak.h"


const char* ssid = "Ken &Cop";   // your network SSID (name) 
const char* password = "vitieubao0803";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 1474284;
const char * myWriteAPIKey = "NGQ1GJYDP4QKZ9SX";

String value = "";
// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;





void setup() {
  Serial.begin(9600);  //Initialize serial
  
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

    // Get a new temperature reading
    while (Serial.available() > 0)
    {
      int inChar = Serial.read();
      value += (char)inChar;
    }
    Serial.println("Da nhan duoc");
    //uncomment if you want to get temperature in Fahrenheit
    /*temperatureF = 1.8 * bme.readTemperature() + 32;
    Serial.print("Temperature (ºC): ");
    Serial.println(temperatureF);*/
    
    
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeField(myChannelNumber, 1, value, myWriteAPIKey);
    //uncomment if you want to get temperature in Fahrenheit
    //int x = ThingSpeak.writeField(myChannelNumber, 1, temperatureF, myWriteAPIKey);

    value = "";
    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
}
