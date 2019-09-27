#include <nuovoIoTWebConfig.h>

#define BLYNK_PRINT Serial

#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

Nuovo nuovo;

bool setupStatus = false;

void setup() {
  Serial.begin(9600);
  nuovo.setResetButton(23, LOW);
  nuovo.init();
  nuovo.begin("Blynk");
  setupStatus = nuovo.getCheckSetup();

  if (setupStatus)
    Blynk.begin(nuovo.getBToken().c_str(), nuovo.getWiFiSSID().c_str(), nuovo.getWiFiPasswd().c_str());
}

void loop() {
  if (setupStatus) Blynk.run();
  nuovo.handle();
}
