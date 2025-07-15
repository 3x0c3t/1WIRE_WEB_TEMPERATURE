/*
=============================================================
Fichier     : 1WIRE_WEB_TEMPERATURE | css.h
Auteur      : 3x0c3t
Version     : 1.1
Date        : 20250715-23:45
Description : Thermomètre 1WIRE + WebServer + WebPage
=============================================================
*/

#ifndef CSS_H
#define CSS_H

const char* pageCSS = R"rawliteral(
  body {
    font-family: Arial, sans-serif;
    background-color: #f0f8ff;
    color: #333;
    margin: 20px;
    padding: 0;
  }

  h1 {
    color: #0066cc;
  }

  p {
    font-size: 1.5em;
    margin-top: 20px;
  }

  .error {
    color: red;
  }
)rawliteral";

#endif
