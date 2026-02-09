# 📅 MyDS1302 - Bibliothèque RTC DS1302 pour ESP32

![Platform](https://img.shields.io/badge/Platform-ESP32-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Version](https://img.shields.io/badge/Version-1.0.0-orange.svg)

Une bibliothèque Arduino complète pour le module DS1302 RTC, développée from scratch avec une compréhension approfondie du protocole de communication.

## 🎯 Caractéristiques

- ✅ Développée from scratch sans bibliothèques externes
- ✅ Support complet du DS1302 (heure, date, RAM)
- ✅ Optimisée pour ESP32
- ✅ Code minimal et efficace (< 300 lignes)
- ✅ Documentation complète en français
- ✅ Exemples prêts à l'emploi

## 📦 Installation

### Méthode 1 : Via Arduino IDE
1. Téléchargez ce repository (Code → Download ZIP)
2. Dans Arduino IDE : Croquis → Inclure une bibliothèque → Ajouter une bibliothèque .ZIP
3. Sélectionnez le fichier ZIP téléchargé

### Méthode 2 : Manuellement
Copiez le dossier `MyDS1302_Library` dans votre dossier `Arduino/libraries/`

## 🔌 Câblage
ESP32 DS1302
3.3V → VCC
GND → GND
GPIO5 → CE/RST
GPIO18 → DAT/IO
GPIO19 → CLK/SCLK