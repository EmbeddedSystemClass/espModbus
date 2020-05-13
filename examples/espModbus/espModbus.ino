#include <Arduino.h>
#include <WiFi.h>

#include <ModbusTCPSlave.h>

#define SSID "ssid"
#define PASS "pass"

ModbusTCPSlave modbus(1, 502);

void onRequest(void* arg, espModbus::Request* request) {
  Serial.printf("New request arrived!\n");
  /*
  Serial.printf("New request %d\n", request->Functioncode());
  switch (request->Functioncode()) {
    case espModbus::READ_HOLD_REGISTER:
      size_t length = request->length() * 2;  // request is in registers x2, for number of bytes
      uint8_t* data = new uint8_t[length];  
      memset(data, 0, length);
      request->sendResponse(espModbus::SUCCES, data, length));
      return;
    case espModbus::WRITE_HOLD_REGISTER:
      request->sendResponse(espModbus::SUCCES));
      return;
    default:
      Serial.printf("Request not implemented");
      request->sendResponse(espModbus::ILLEGAL_FUNCTION);
      return;
  }
  */
}


void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.print("Starting ESP\n");
  WiFi.persistent(false);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1);
  }

  Serial.print("WiFi connected\n");

  modbus.onRequest(onRequest);
  modbus.begin();
}

void loop() {
  static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 10000) {
    lastMillis = millis();
    Serial.printf("free heap: %d\n", ESP.getFreeHeap());
  }
  delay(1);
}