/*
=============================================================
Fichier     : html.h
Auteur      : 3x0c3t
Version     : 1.3
Date        : 20250716-14:00
Description : Page HTML pour 1WIRE_WEB_TEMPERATURE avec placeholders
=============================================================
*/

#ifndef HTML_H
#define HTML_H

const char* pageHTML = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="utf-8" />
  <title>Température DS18B20</title>
  <style>
  {{PAGE_CSS}}
  </style>
</head>
<body>
  <h1>Température DS18B20</h1>
  {{SONDE_STATUS}}
  {{SONDE_ADDRESS}}
  {{TEMPERATURE}}
  <canvas id="tempChart" width="600" height="300"></canvas>
  {{PAGE_JS}}
</body>
</html>
)rawliteral";

#endif
