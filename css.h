/*
=============================================================
Fichier     : css.h
Auteur      : 3x0c3t
Version     : 1.3
Date        : 20250716-14:00
Description : Thermomètre 1WIRE + WebServer + WebPage - Dark Mode CSS
=============================================================
*/

#ifndef CSS_H
#define CSS_H

const char* pageCSS = R"rawliteral(
  body {
    font-family: Arial, sans-serif;
    background-color: #121212;
    color: #e0e0e0;
    margin: 20px;
    padding: 0;
  }

  h1 {
    color: #64b5f6;
  }

  p {
    font-size: 1.5em;
    margin-top: 20px;
  }

  .error {
    color: #ff5252;
  }

  strong {
    color: #90caf9;
  }
)rawliteral";

#endif
