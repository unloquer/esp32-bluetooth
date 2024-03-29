#include "bluetooth.h"
#include<stdlib.h>

BleApi::BleApi ()
{
  Serial.println("Starting BLE API......");

  BLEDevice::init("ESP_BLE");
  bServer = BLEDevice::createServer();
  bServer->setCallbacks(new ServerCallbacks());

  bService = bServer->createService(SERVICE_UUID);
  notifyChar = bService->createCharacteristic(
      NOTIFY_CHARACHTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_NOTIFY 
      );
  ledBuiltInChar = bService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE 
      );

//  Serial.print(char_value.c_str() + " ");
 // Serial.println(char_value.to_string().c_str());


  // set callback functions
  ledBuiltInChar->setCallbacks(new CharacteristicCallbacks());
  notifyChar->setValue("0");
  ledBuiltInChar->setValue("ledOff");
  
  // set descriptor
  ledBuiltInChar->addDescriptor(new BLE2902());
  notifyChar->addDescriptor(new BLE2902());


  bService->start();

  pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
 
  BLEAdvertisementData  pAdvertisementData;
  // this will be a descriptor for the service
  std::string advData = "AGRO_IOT";//"{\"serviceName\": \"CARE_POPO\"}";
  pAdvertisementData.setServiceData(bService->getUUID(), advData);

  // these are working weird
//  pAdvertisementData.setShortName("ESP_IOT");
 // pAdvertisementData.setName("ESP_IOT");

  pAdvertising->setAdvertisementData(pAdvertisementData);

  /*
  char * advPayload = &pAdvertisementData.getPayload()[0];
  Serial.print("ADV Data Payload fuck.......");
  Serial.println(advPayload);
 */
  
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("BLE API DONE!");
}

BleApi::~BleApi()
{
  delete []bServer;
  delete []bService;
  delete []ledBuiltInChar;
  delete []pAdvertising;
  delete []notifyChar;
}

void BleApi::notifyValue(int value) 
{
  Serial.println("notifying.........");
  //String valuetoString = String(value);
  char buffer[30];
  itoa(value, buffer, 10);
  notifyChar->setValue(buffer);
  notifyChar->notify();
  Serial.print("set and notifying: ");
  Serial.println(buffer);
}

std::string BleApi::getCharValue()
{
  return ledBuiltInChar->getValue();
}

/*
 * SERVER AND CHARACTERISTICS CALLBACKS
 * 
 */
void CharacteristicCallbacks::onRead(BLECharacteristic * pChar)
{
    Serial.println("Reading..... ");
/*
    uint8_t* value = pChar->getData();
    Serial.println("*********");
    Serial.print("Reading New value: ");
    Serial.print(value);
    Serial.println("*********");
  */  
    std::string value = pChar->getValue();

    if (value.length() > 0) {
      Serial.println("*********");
      Serial.print("Reading New value: ");
      for (int i = 0; i < value.length(); i++)
        Serial.print(value[i]);

      Serial.println();
      Serial.println("*********");
    }
      
}

void CharacteristicCallbacks::onWrite(BLECharacteristic * pChar)
{
  /*
    Serial.print("Writing.......  ");
    uint8_t* value = pChar->getData();
    Serial.println("*********");
    Serial.print("Reading New value: ");
    Serial.print(value);
    Serial.println("*********");
    */
    
    std::string value = pChar->getValue();

    if (value.length() > 0) {
      Serial.println("*********");
      Serial.print("Writing New value: ");
      for (int i = 0; i < value.length(); i++)
        Serial.print(value[i]);

      Serial.println();
      Serial.println("*********");
    }
    pChar->notify();
    
}


void ServerCallbacks::onConnect(BLEServer * pServer)
{
  Serial.println("-->[BLE] onConnect");
  // statusOn(bit_paired);
  //deviceConnected = true;
}

void ServerCallbacks::onDisconnect(BLEServer * pServer)
{
  Serial.println("-->[BLE] onDisconnect");
  // statusOn(bit_paired);
  //deviceConnected = true;
}
