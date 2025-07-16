# 1WIRE_WEB_TEMPERATURE

**Auteur :** 3x0c3t  
**Version :** 1.3  
**Date :** 2025-07-16 | 10:25  
**Description :** Thermomètre 1-Wire DS18B20 avec serveur Web intégré pour affichage de la température.

---

## Fonctionnalités

- Lecture de la température d’une sonde DS18B20 via bus 1-Wire sur ESP8266
- Serveur Web HTTP qui affiche la température en °C
- Affichage dynamique et graphique via JavaScript (mise à jour automatique sans rechargement)
- Message d’erreur si aucune sonde détectée ou si erreur de lecture
- Affichage de l’adresse unique de la sonde détectée
- CSS et interface Web améliorées
- Connexion WiFi configurée via fichier séparé `wifi.h`

---

## Matériel nécessaire

- ESP8266 (NodeMCU, Wemos D1 mini, etc.)
- Sonde de température DS18B20
- Résistance de pull-up 4.7kΩ entre le bus DATA et le +3.3V

---

## Branches Git

- `main` : Branche principale stable (v1.1)
- `V1.2` : Ancienne branche de développement
- `V1.3` : Dernière version avec interface web améliorée et affichage graphique

---

## Installation et déploiement

1. Cloner ce dépôt git :  
   ```bash
   git clone https://github.com/3x0c3t/1WIRE_WEB_TEMPERATURE.git
   cd 1WIRE_WEB_TEMPERATURE
