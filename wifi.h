/*
=============================================================
Fichier     : 1WIRE_WEB_TEMPERATURE | wifi.h
Auteur      : 3x0c3t
Version     : 1.1
Date        : 20250715-23:45
Description : Thermomètre 1WIRE + WebServer + WebPage
=============================================================
*/

#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>

const char* ssid = "N0wifiHere";
const char* password = "@PassWeurd";

const char* ap_name = "3x0c3t-TEMPERATURE";


void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connexion à ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnecté au WiFi !");
  Serial.print("IP locale : ");
  Serial.println(WiFi.localIP());
}

#endif
