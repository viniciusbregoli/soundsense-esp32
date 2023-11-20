#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Arduino.h>

// Define UUIDs para o serviço BLE e a característica
#define SERVICE_UUID        "12345678-1234-5678-1234-56789abcdef0" // UUID do Serviço
#define CHARACTERISTIC_UUID "abcdef12-3456-7890-abcd-ef1234567890" // UUID da Característica

void setup() {
  Serial.begin(9600);

  // Inicializa o dispositivo BLE
  BLEDevice::init("ESP32_BLE");

  // Cria um servidor BLE
  BLEServer *pServer = BLEDevice::createServer();

  // Cria um serviço BLE
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Cria uma característica BLE
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ | 
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY
                                       );

  // Inicia o serviço
  pService->start();

  // Inicia a publicidade do BLE
  pServer->getAdvertising()->start();
  Serial.println("Servidor BLE Iniciado");
}

void loop() {
  // Aqui você pode adicionar código para atualizar a característica com novos dados
}
