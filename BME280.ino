#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <Wire.h>
#include "SparkFunBME280.h"

#define SEALEVELPRESSURE_HPA (1013.25)

BME280 mySensor;
float temp;
bool light;
int LED = 2;
void onLightChange();

const char THING_ID[]           = " ";    // Thing ID of Arduino Cloud
const char DEVICE_LOGIN_NAME[]  = " ";    // Device ID of Thing
const char DEVICE_KEY[]         = " ";    // Secret device password

const char SSID[]               = " ";    // Network SSID (name)
const char PASS[]               = " ";    // Network password (use for WPA, or use as key for WEP)

void initProperties(){
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.setThingId(THING_ID);
  ArduinoCloud.addProperty(temp, READ, 1 * SECONDS, NULL);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

void setup() { 
  pinMode(LED, OUTPUT); 
  Serial.begin(9600);
  delay(1500); 
  
  // Defined in thingProperties.h
  initProperties();
  
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  Wire.begin();
  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }
}

void loop() {
  ArduinoCloud.update();
  temp = mySensor.readTempC();
  delay(500);
}

void onLightChange() {
  if(light){
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }
}
