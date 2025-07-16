/*
=============================================================
Fichier     : 1WIRE_WEB_TEMPERATURE.ino
Auteur      : 3x0c3t
Version     : 1.3
Date        : 20250716-14:00
Description : Thermomètre 1WIRE + WebServer + WebPage avec affichage adresse sonde
=============================================================
*/

#include <ESP8266WiFi.h>
#include <OneWire.h>
#include "wifi.h"
#include "css.h"
#include "js.h"
#include "html.h"

#define ONEWIRE_BUS_PIN 13
OneWire ds(ONEWIRE_BUS_PIN);

WiFiServer server(80);

#define DEVICE_DISCONNECTED -127.0

struct SondeInfo {
  float temperature;
  byte address[8];
  bool found;
};

SondeInfo readTemperatureAndAddress() {
  SondeInfo si;
  si.found = false;

  unsigned long searchStart = millis();
  while (!ds.search(si.address)) {
    ds.reset_search();
    if (millis() - searchStart > 1000) {
      Serial.println("Timeout recherche appareil 1-Wire.");
      si.temperature = DEVICE_DISCONNECTED;
      return si;
    }
    yield();
  }

  if (si.address[0] != 0x28) {
    Serial.println("Appareil détecté mais ce n'est pas un DS18B20.");
    si.temperature = DEVICE_DISCONNECTED;
    return si;
  }

  si.found = true;

  ds.reset();
  ds.select(si.address);
  ds.write(0x44, 1);

  unsigned long start = millis();
  while (millis() - start < 750) {
    yield();
    delay(10);
  }

  ds.reset();
  ds.select(si.address);
  ds.write(0xBE);

  byte data[9];
  for (int i = 0; i < 9; i++) {
    data[i] = ds.read();
  }

  if (OneWire::crc8(data, 8) != data[8]) {
    Serial.println("Erreur CRC - données corrompues");
    si.temperature = DEVICE_DISCONNECTED;
    return si;
  }

  int16_t raw = (data[1] << 8) | data[0];
  si.temperature = (float)raw / 16.0;

  return si;
}

String formatAddress(byte addr[8]) {
  String s = "";
  for (int i = 0; i < 8; i++) {
    if (addr[i] < 16) s += "0";
    s += String(addr[i], HEX);
    if (i < 7) s += ":";
  }
  s.toUpperCase();
  return s;
}

void setup() {
  Serial.begin(115200);
  delay(100);

  connectToWiFi();
  server.begin();

  Serial.println("Serveur démarré, attente de connexions...");
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    yield();
    return;
  }

  unsigned long startTime = millis();
  while (!client.available()) {
    if (millis() - startTime > 2000) {
      client.stop();
      return;
    }
    delay(1);
    yield();
  }

  String req = client.readStringUntil('\r');
  client.flush();

  String reqPath = "";
  if (req.startsWith("GET ")) {
    int sp1 = req.indexOf(' ');
    int sp2 = req.indexOf(' ', sp1 + 1);
    if (sp1 != -1 && sp2 != -1) {
      reqPath = req.substring(sp1 + 1, sp2);
    }
  }

  SondeInfo si = readTemperatureAndAddress();

  if (reqPath == "/temperature-data") {
    String json = "{";
    json += "\"temperature\":";
    json += (si.temperature == DEVICE_DISCONNECTED) ? "null" : String(si.temperature, 2);
    json += "}";

    String response = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" + json;
    client.print(response);
    delay(1);
    client.stop();
    return;
  }

  String page = String(pageHTML);

  if (!si.found) {
    page.replace("{{SONDE_STATUS}}", "<p class='error'>Sonde introuvable sur le bus 1-Wire.</p>");
    page.replace("{{SONDE_ADDRESS}}", "");
    page.replace("{{TEMPERATURE}}", "");
  } else {
    page.replace("{{SONDE_STATUS}}", "");
    page.replace("{{SONDE_ADDRESS}}", "<p><strong>Adresse sonde :</strong> " + formatAddress(si.address) + "</p>");
    if (si.temperature == DEVICE_DISCONNECTED) {
      page.replace("{{TEMPERATURE}}", "<p class='error'>Erreur lecture température (CRC invalide).</p>");
    } else {
      page.replace("{{TEMPERATURE}}", "<p>Température : " + String(si.temperature, 2) + " &deg;C</p>");
    }
  }

  page.replace("{{PAGE_CSS}}", pageCSS);
  page.replace("{{PAGE_JS}}", pageJS);

  String response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + page;
  client.print(response);
  delay(1);
  client.stop();
  yield();
}
