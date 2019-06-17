#include "OV2640.h"
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "bluetooth.h"

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

//#define SERVICE_UUID     "29d39406-e846-4e53-b98b-c6065a41b21b"
//#define CHARACTERISTIC_UUID "1b23ab7e-a2e6-4a90-be88-c65b28e92de4"


BleApi * bApi;
int dummy_sensor_value = 0;
void setup()
{
  Serial.begin(115200);
  while (!Serial) { ; }

  Serial.println("Starting BLE work!");
  bApi = new BleApi();
  pinMode(2, OUTPUT);

}

void loop()
{
  Serial.println("in LOOP");
  delay(5000);
  dummy_sensor_value++;
  bApi->notifyValue(dummy_sensor_value);
  delay(5);
/*
  digitalWrite(2, HIGH);
  delay(100);
  digitalWrite(2, LOW);
  delay(100);
  */
}
