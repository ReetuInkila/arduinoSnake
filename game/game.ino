
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include "Pair.h"
#include "Snake.h"

// Controller settings and variables
#define VRX_PIN  A4 // Arduino pin connected to VRX pin
#define VRY_PIN  A5 // Arduino pin connected to VRY pin
#define SW_PIN   10  // Arduino pin connected to SW  pin

int xValue = 0; // To store value of the controller X axis
int yValue = 0; // To store value of the controller Y axis

// Game variables
Snake game;
const int d = 25;
int locationX;
int locationY;
int prevLocX; 
int prevLocY;
int directionX;
int directionY;

Pair<int, int> point;
LinkedList<Pair<int, int>> snake;
Pair<int, int> removable = Pair<int, int>(-1,-1);
int speed;
int score;
bool running;
int difficulty = 1;  // 1: Easy, 2: Intermediate, 3: Hard

// Screen settings, dimensions and scaling constants
#define LCD_RESET 0 // Define the RESET pin number
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

const int screenWidth = 240; // Pixels (GAME area)
const int screenHeight = 240; // Pixels

const int scaleX = screenWidth / d;
const int scaleY = screenHeight / d;

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define WHITE   0xFFFF


// Function to start game
void startGame(){
  locationX = 13;
  locationY = 13;
  prevLocX = 0; 
  prevLocY = 0;
  directionX = 1;
  directionY = 0;
  game.start(locationX,locationY);
  tft.fillScreen(WHITE); // Clear the screen
  tft.drawRect(0, 0, screenWidth, screenHeight, RED); // draw borders
  tft.setCursor(5, screenHeight + 20); // Set the cursor to the bottom-left corner (adjust as needed)
  tft.setTextColor(BLACK);
  tft.setTextSize(4); // Adjust the text size as needed
  tft.print("Score:");
}

bool checkSwitch(){
  // Check if the switch is pressed
  int switchState = digitalRead(SW_PIN);
  Serial.println(switchState);
  if (switchState == HIGH) {
    return true;
  }
  return false;
}

// Ask from user game difficulty from 1-3
void selectDifficulty(){

  while(true){
    // read analog X and Y analog values
    xValue = analogRead(VRX_PIN);
    yValue = analogRead(VRY_PIN);
    if (yValue>600){
      break;
    }
    if(xValue < 600){
      difficulty++;
    }else if (xValue < 400){
      difficulty--;
    }
    if (difficulty<1){
      difficulty= 3;
    }else if (difficulty > 3){
      difficulty = 1;
    }

    tft.fillScreen(WHITE); // Clear the screen
    tft.setCursor(5, screenHeight/2); // Set the cursor to the bottom-left corner (adjust as needed)
    tft.setTextColor(BLACK);
    tft.setTextSize(3); // Adjust the text size as needed
    tft.print("Selected: ");
    tft.setCursor(5, screenHeight/2 +30); // Set the cursor to the bottom-left corner (adjust as needed)
    tft.print(getDifficultyString(difficulty));
    delay(100);
  }
  tft.fillScreen(WHITE); // Clear the screen
  
}

String getDifficultyString(int level) {
  if (level == 1) {
    return "Easy";
  } else if (level == 2) {
    return "Intermediate";
  } else {
    return "Hard";
  }
}

void setup() {
  Serial.begin(9600) ;
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);

  selectDifficulty();
  startGame();
}

// Pauses game until switch is pressed
void pause(){
  while (!checkSwitch()){
    delay(400);
  }
}

void loop() {
  
  //checkSwitch();
  drawSnake();

  // read analog X and Y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  if(xValue > 600 && directionX == 0){
    directionX = 1;
    directionY = 0;
  }else if (xValue < 400 && directionX == 0){
    directionX = -1;
    directionY = 0;
  }else if (yValue > 600 && directionY == 0){
    directionX = 0;
    directionY = 1;
  }else if (yValue < 400 && directionY == 0){
    directionX = 0;
    directionY = -1;
  }
  running = game.getState();
  if (running){
    speed = game.getDelay();
    delay(speed);
    step();
  }else{
    pause();
    startGame();
  }
}

void step(){
  prevLocX = locationX; 
  prevLocY = locationY; 
  locationX = locationX + directionX;
  locationY = locationY + directionY;
  if( locationX > d){
    locationX = 1;
  }else if(locationX < 1) {
    locationX = d;
  }
  if( locationY > d){
    locationY = 1;
  }else if(locationY < 1) {
    locationY = d;
  }
  removable = game.moveSnake(locationX, locationY);
}

void drawSnake(){
  tft.fillCircle(removable.first * scaleX, removable.second* scaleY, 4, WHITE); // Clear the screen


  point = game.getPoint();
  snake = game.getSnake();
  score = game.getScore();
  tft.fillCircle(point.first * scaleX, point.second* scaleY, 4, BLACK);

  for (const Pair<int, int>& coordinate : snake) {
    int x = coordinate.first;
    int y = coordinate.second;

    // Calculate the screen coordinates based on the snake's coordinates and scaling factors
    int screenX = x * scaleX;
    int screenY = y * scaleY;

    // Draw a circle for each point of the snake's body
    tft.fillCircle(screenX, screenY, 4, BLACK); 
  }
  // Erase the previous score by filling a rectangle over it
  tft.fillRect(140, screenHeight + 20 , screenWidth, 40, WHITE);
  /// Draw the score at the bottom of the screen
  tft.setCursor(150, screenHeight + 20); // Set the cursor to the bottom-left corner (adjust as needed)
  tft.setTextColor(BLACK);
  tft.setTextSize(4); // Adjust the text size as needed
  tft.print(score); 
}