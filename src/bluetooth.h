#ifndef BLE_API_H
#define BLE_API_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

//online uuid generator
// https://www.uuidgenerator.net
#define SERVICE_UUID     "29d39406-e846-4e53-b98b-c6065a41b21b"
#define CHARACTERISTIC_UUID "1b23ab7e-a2e6-4a90-be88-c65b28e92de4"

class CharacteristicCallbacks:public BLECharacteristicCallbacks {
  void onRead(BLECharacteristic *pCharacteristic);
  void onWrite(BLECharacteristic *pCharacteristic);
};

class ServerCallbacks:public BLEServerCallbacks {
	void onConnect(BLEServer* pServer); 

    void onDisconnect(BLEServer* pServer); 
}; // BLEServerCallbacks

class BleApi {
  private:
    BLEServer * bServer = NULL;
    BLEService * bService = NULL;
    BLECharacteristic * ledBuiltInChar = NULL;
    BLEAdvertising *pAdvertising = NULL; //BLEDevice::getAdvertising();
    int ledBuiltInState = 0;
  public:
    BleApi();
    ~BleApi();
    void setLedState(int);


};
#endif /* ifndef BLE_API_H */
