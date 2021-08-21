#include <SPI.h>
#include <LoRa.h>

String value;
void setup() {
  Serial.begin(9600);
  while (!Serial);

    while (Serial.available() > 0)
    {
      int inChar = Serial.read();
      value += (char)inChar;
    }

  Serial.println(value);
  
  Serial.println("LoRa Receiver");

  LoRa.setPins(10,8,6);
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(500E3);
  LoRa.setCodingRate4(8);
  Serial.println("Starting LoRa succeed!");
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    Serial.println();
  }
}
