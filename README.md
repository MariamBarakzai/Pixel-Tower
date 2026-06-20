# Pixel Tower 
Arduino LED-Stapelspiel mit MAX7219 8×8 LED-Matrix

Eine interaktive Spielekonsole, bei der der Spieler Blöcke präzise übereinander stapelt. Mit jedem erfolgreich platzierten Block wird das Spiel schneller und schwieriger.

-Projektbeschreibung

Pixel Tower ist ein klassisches Stapelspiel im Arduino-Format. Der Spieler steuert mit einem Taster einen beweglichen Block und muss diesen im richtigen Moment auf dem Turm platzieren.

-Spielprinzip:
- Blöcke fallen von oben und bewegen sich automatisch hin und her
- Spieler drückt den Taster, um einen Block zu platzieren
- Jeder neue Block muss auf dem vorherigen Block landen
- Je präziser die Platzierung, desto stabiler der Turm
- Mit jedem Level wird das Spiel schneller
- 8 Level müssen erfolgreich abgeschlossen werden, um zu gewinnen

-Features

Progressive Schwierigkeit** - Das Spiel wird mit jedem Level schneller  
Kollisionserkennung** - Erkennt, ob der Block richtig platziert wurde  
Level-System** - 8 unterschiedliche Ebenen zum Stapeln  
Gewinn-Animation** - Spezielle LED-Animation beim Sieg  
Game Over Animation** - Visuelles Feedback bei Fehler  
Einfache Steuerung** - Nur ein Taster erforderlich  

-Hardware

Komponenten:

| Komponente | Beschreibung | Anzahl |
|-----------|------------|--------|
| **Grove Beginner Kit / Seeeduino Lotus** | Mikrocontroller (Arduino-kompatibel) | 1 |
| **MAX7219 LED-Matrix** | 8×8 LED-Display zur Spielanzeige | 1 |
| **Taster/Button** | Zur Steuerung des Spiels | 1 |
| **USB-Kabel** | Stromversorgung und Programmierung | 1 |
| **Jumper-Kabel** | Zur Verbindung der Komponenten | mehrere |

### Pin-Konfiguration (Arduino):
MAX7219 LED-Matrix:
VCC   → 5V (oder 3V3)
GND   → GND
DIN   → Pin 11 (MOSI)
CS    → Pin 10 (Chip Select)
CLK   → Pin 13 (SCK)
Button/Taster:
Signal → Pin 6
GND    → GND


Software & Libraries
Erforderliche Library:

```cpp
#include "LedControl.h"  // Zur Steuerung der MAX7219 LED-Matrix
```

Installation in Arduino IDE:
1. Sketch → Include Library → Manage Libraries
2. Nach "LedControl" suchen
3. Von Eelkool installieren

Programmiersprache:
- C++ (Arduino IDE)
- Arduino IDE Version 1.8.0 oder höher empfohlen

 
Installation & Aufbau

Schritt 1: Hardware zusammenstellen
- Grove Beginner Kit anschließen
- MAX7219 LED-Matrix mit den oben genannten Pins verbinden
- Taster anschließen

Schritt 2: Arduino IDE einrichten
1. [Arduino IDE herunterladen](https://www.arduino.cc/en/software)
2. LedControl Library installieren
3. Board-Typ auswählen: Arduino Uno (oder Seeeduino Lotus)

Schritt 3: Code hochladen
1. `PixelTower.ino` öffnen
2. Upload drücken (oder Ctrl+U)
3. Serial Monitor öffnen (optional)

 
Wie man spielt

1. Spiel starten: Nach dem Upload startet das Spiel automatisch
2. Block bewegen: Der Block bewegt sich automatisch hin und her
3. Block platzieren: Taster drücken, um den Block zu platzieren
4. Nächstes Level: Nach erfolgreichem Platzieren geht es zum nächsten Level
5. Gewinnen: Alle 8 Level erfolgreich absolvieren → Win-Animation
6. Game Over: Block rutscht ab → Game Over Animation
7. Neustart: Taster drücken nach Game Over zum Neustarten

Tipps:
- Je näher der Block am vorherigen Block platziert wird, desto breiter wird der nächste Block
- Die Geschwindigkeit nimmt kontinuierlich zu
- Präzision ist wichtiger als Schnelligkeit!


Projektstruktur

Technische Details:

Hauptfunktionen:

- `setup()` - Initialisiert LED-Matrix und Taster
- `loop()` - Hauptspiel-Schleife
- `moveBlock()` - Bewegt den Block automatisch
- `drawBlock()` - Zeigt Block auf LED-Matrix an
- `placeBlock()` - Platziert Block und prüft Kollision
- `resetGame()` - Setzt Spiel zurück
- `showGameOver()` - Game Over Animation
- `showWin()` - Win Animation

Autoren:

Maryam Akbari - Hardware & Konzept  
Mariam Barakzai - Software & Programmierung

HTL Wien | Schuljahr 2025/2026

Lizenz:

Dieses Projekt ist unter der MIT License lizenziert.

Viel Spaß beim Spielen!
