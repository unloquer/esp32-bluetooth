#ifndef BLE_API_H
#define BLE_API_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

//online uuid generator
// https://www.uuidgenerator.net
#define SERVICE_UUID     "29d39406-e846-4e53-b98b-c6065a41b21b"
#define CHARACTERISTIC_UUID "1b23ab7e-a2e6-4a90-be88-c65b28e92de4"
#define NOTIFY_CHARACHTERISTIC_UUID "02c2e30b-e695-4321-bd1b-9cede85ad52c"

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
    BLECharacteristic * notifyChar = NULL;
    BLEAdvertising *pAdvertising = NULL; //BLEDevice::getAdvertising();
    int ledBuiltInState = 0;
  public:
    BleApi();
    ~BleApi();
    void notifyValue(int);


};
#endif /* ifndef BLE_API_H */
