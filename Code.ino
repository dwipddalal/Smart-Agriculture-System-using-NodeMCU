
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "entre your authentication token here";  
//code sent via email to verify the author for using the Blynk library
const int sensorPin = 17;
// the sensor is attached to the pin number 17
int sensorState = 0;
int lastState = 0;

void setup()
{
  Serial.begin(9600);
  //standard code to start the serial communication
  Blynk.begin(auth, "wifi name", "Wifi password"); 
  //wifi name and password
  pinMode(sensorPin, INPUT);
  Blynk.notify("Your plant is monitored");
  //we use the Blynk library to notify the user on in smartphone that his plant is being monitored  
}
void loop()
{
  Blynk.run();
  sensorState = analogRead(sensorPin);
  // we recieve analog input from the sensor
  Serial.println(sensorState);
  // we can have a look at the sensor state contiguously through the serial monitor

  if (sensorState >= 750 && lastState == 0)
  {
    Serial.println("needs water, send notification");
    Blynk.notify("water your plants");
    lastState = 1;
    delay(1000);
    //send notification
    // after repeated iterations I came to the conclusion that 750 was the Ideal state to send the message.
  }
  else if (sensorState >= 750 && lastState == 1)
  {
    //do nothing, has not been watered yet
    Serial.println("has not been watered yet");
    delay(1000);
  }
  else if (sensorState <= 750)
  {
    Serial.println("need not water plants");
    lastState = 0;
    delay(1000);
  }
  delay(100);
}
