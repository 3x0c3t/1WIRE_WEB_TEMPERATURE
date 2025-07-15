/*
=============================================================
Fichier     : 1WIRE_WEB_TEMPERATURE.ino
Auteur      : 3x0c3t
Version     : 1.2
Date        : 20250715-23:45
Description : Thermomètre 1WIRE + WebServer + WebPage avec affichage adresse sonde
=============================================================
*/

#include <ESP8266WiFi.h>
#include <OneWire.h>
#include "wifi.h"
#include "css.h"

#define ONEWIRE_BUS_PIN 13
OneWire ds(ONEWIRE_BUS_PIN);

WiFiServer server(80);

#define DEVICE_DISCONNECTED -127.0

// Structure pour retourner température + adresse
struct SondeInfo {
  float temperature;
  byte address[8];
  bool found;
};

SondeInfo readTemperatureAndAddress() {
  SondeInfo si;
  si.found = false;
  if (!ds.search(si.address)) {
    ds.reset_search();
    Serial.println("Aucun appareil détecté sur le bus 1-Wire.");
    si.temperature = DEVICE_DISCONNECTED;
    return si;
  }

  if (si.address[0] != 0x28) {
    Serial.println("Appareil détecté mais ce n'est pas un DS18B20.");
    si.temperature = DEVICE_DISCONNECTED;
    return si;
  }

  si.found = true;

  ds.reset();
  ds.select(si.address);
  ds.write(0x44, 1); // start conversion avec parasite power

  delay(750);

  ds.reset();
  ds.select(si.address);
  ds.write(0xBE); // read scratchpad

  byte data[9];
  for (int i = 0; i < 9; i++) {
    data[i] = ds.read();
  }

  // Debug des données brutes
  Serial.print("Données brutes : ");
  for (int i = 0; i < 9; i++) {
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Vérification CRC
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
    if (addr[i] < 16) s += "0"; // zéro devant pour format hex à 2 chiffres
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
  if (!client) return;

  while (!client.available()) delay(1);

  String req = client.readStringUntil('\r');
  Serial.print("Requête reçue : ");
  Serial.println(req);
  client.flush();

  SondeInfo si = readTemperatureAndAddress();

  String response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  response += "<!DOCTYPE html><html><head><meta charset='utf-8'><title>Température DS18B20</title>";
  response += "<style>" + String(pageCSS) + "</style>";
  response += "</head><body>";
  response += "<h1>Température DS18B20</h1>";

  if (!si.found) {
    response += "<p class='error'>Sonde introuvable sur le bus 1-Wire.</p>";
  } else {
    response += "<p><strong>Adresse sonde :</strong> " + formatAddress(si.address) + "</p>";
    if (si.temperature == DEVICE_DISCONNECTED) {
      response += "<p class='error'>Erreur lecture température (CRC invalide).</p>";
    } else {
      response += "<p>Température : " + String(si.temperature, 2) + " &deg;C</p>";
    }
  }

  response += "</body></html>";

  client.print(response);
  delay(1);
  client.stop();
}
