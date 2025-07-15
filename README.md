# 1WIRE_WEB_TEMPERATURE

**Auteur :** 3x0c3t  
**Version :** 1.1  
**Date :** 2025-07-15 | 00:31
**Description :** Thermomètre 1-Wire DS18B20 avec serveur Web intégré pour affichage de la température.

---

## Fonctionnalités

- Lecture de la température d’une sonde DS18B20 via bus 1-Wire sur ESP8266
- Serveur Web HTTP qui affiche la température en °C
- Affichage d’un message d’erreur si aucune sonde détectée ou erreur de lecture
- CSS simple pour mise en forme de la page web
- Connexion WiFi configurée via fichier séparé `wifi.h`

---

## Matériel nécessaire

- ESP8266 (NodeMCU, Wemos D1 mini, etc.)
- Sonde de température DS18B20
- Résistance de pull-up 4.7kΩ entre le bus DATA et le +3.3V

---

## Branches Git

- `main`: Branche principale stable (v1.1)
- `V1.2` : Branche en développement pour la prochaine version

---

## Installation et déploiement

1. Cloner ce dépôt git :  
   ```bash
   git clone https://github.com/3x0c3t/1WIRE_WEB_TEMPERATURE.git
   cd 1WIRE_WEB_TEMPERATURE
