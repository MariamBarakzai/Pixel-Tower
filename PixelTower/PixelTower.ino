// ======================================
// PIXEL TOWER - LED Stacking Game
// Arduino + MAX7219 LED Matrix
// ======================================

#include "LedControl.h"  // Library to control the MAX7219 LED matrix

// Pin setup for Arduino
// DIN -> 11, CLK -> 13, CS -> 10, number of modules -> 1
LedControl lc = LedControl(11, 13, 10, 1);

const int buttonPin = 6;  // Button to place blocks
unsigned long lastMoveTime = 0;
int moveDelay = 200;  // Speed of block movement (smaller = faster)

// Game variables
int currentLevel = 0;   // Which row the player is stacking on
int blockWidth = 3;     // How wide the current block is
int blockPos = 0;       // Current horizontal position of the block
int direction = 1;      // Moving direction (1 = right, -1 = left)
bool isGameOver = false;  // Flag for end of game

// Arrays to store tower information
int stackWidth[8];      // Width of block on each level
int stackPos[8];        // Position of block on each level

// ===================== Setup =====================
void setup() {
  pinMode(buttonPin, INPUT);  // Set the button as input
  
  // Initialize LED matrix
  lc.shutdown(0, false);   // Wake up display
  lc.setIntensity(0, 8);   // Set brightness (0-15)
  lc.clearDisplay(0);      // Clear all LEDs
  
  resetGame();  // Start the game in initial state
}

// ===================== Main Loop =====================
void loop() {
  if (isGameOver) {
    showGameOver();  // Show Game Over animation
    if (digitalRead(buttonPin) == HIGH) {  // Restart if button pressed
      resetGame();
      delay(500);  // Small pause to prevent accidental double press
    }
    return;  // Stop further execution if game is over
  }
  
  // Move block automatically based on time
  if (millis() - lastMoveTime > moveDelay) {
    moveBlock();
    lastMoveTime = millis();
  }
  
  // Check if player pressed the button to place block
  if (digitalRead(buttonPin) == HIGH) {
    placeBlock();  // Place block on tower
    delay(200);  // Debounce: prevent multiple presses
    while (digitalRead(buttonPin) == HIGH);  // Wait until button release
  }
}

// ===================== Move Block =====================
void moveBlock() {
  lc.setRow(0, currentLevel, 0);  // Clear the current row
  
  blockPos += direction;  // Move block in current direction
  
  // Reverse direction if hitting left or right edge
  if (blockPos + blockWidth >= 8) {
    blockPos = 8 - blockWidth;
    direction = -1;
  } else if (blockPos <= 0) {
    blockPos = 0;
    direction = 1;
  }
  
  drawBlock(currentLevel, blockPos, blockWidth);  // Show block on LED
}

// ===================== Draw Block =====================
void drawBlock(int row, int pos, int width) {
  byte data = 0;
  for (int i = 0; i < width; i++) {
    data |= (1 << (7 - (pos + i)));  // Convert block position to LED bits
  }
  lc.setRow(0, row, data);  // Update the row on LED matrix
}

// ===================== Place Block =====================
void placeBlock() {
  // Check overlap with previous block (if not first level)
  if (currentLevel > 0) {
    int prevPos = stackPos[currentLevel - 1];
    int prevWidth = stackWidth[currentLevel - 1];
    
    int startMax = max(blockPos, prevPos);  // Left edge of overlap
    int endMin = min(blockPos + blockWidth, prevPos + prevWidth);  // Right edge of overlap
    int overlap = endMin - startMax;  // Width of overlapping area
    
    if (overlap <= 0) {
      isGameOver = true;  // No overlap -> game over
      return;
    }
    
    blockWidth = overlap;  // Adjust block width for next level
    blockPos = startMax;  // Adjust position
  }
  
  // Save current block info to tower
  stackPos[currentLevel] = blockPos;
  stackWidth[currentLevel] = blockWidth;
  
  currentLevel++;      // Go to next level
  moveDelay -= 20;     // Increase speed slightly
  
  if (currentLevel >= 8) {
    showWin();  // Player won by stacking all levels
  }
}

// ===================== Reset Game =====================
void resetGame() {
  lc.clearDisplay(0);  // Clear LEDs
  currentLevel = 0;
  blockWidth = 3;
  blockPos = 0;
  moveDelay = 200;
  isGameOver = false;
}

// ===================== Game Over Animation =====================
void showGameOver() {
  lc.clearDisplay(0);
  for (int i = 0; i < 3; i++) {
    lc.setRow(0, 3, B00111100);  // Cross shape
    lc.setRow(0, 4, B00111100);
    delay(200);
    lc.clearDisplay(0);
    delay(200);
  }
}

// ===================== Win Animation =====================
void showWin() {
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, B11111111);  // Fill LED matrix
    delay(100);
  }
  delay(1000);
  resetGame();  // Start new game
}
