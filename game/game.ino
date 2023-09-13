
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
int locationX = 13;
int locationY = 13;
int prevLocX = 0; 
int prevLocY = 0;
int directionX = 1;
int directionY = 0;

Pair<int, int> point;
LinkedList<Pair<int, int>> snake;

// Screen settings, dimensions and scaling constants
#define LCD_RESET A4 // Define the RESET pin number
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

const int screenWidth = 100; // Pixels
const int screenHeight = 100; // Pixels

const int scaleX = screenWidth / d;
const int scaleY = screenHeight / d;



void setup() {
  Serial.begin(9600) ;
  game.start(locationX,locationY);
  tft.fillScreen(0); // Clear the screen
}

void loop() {
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
  delay(500);

  step();
 
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
  game.moveSnake(locationX, locationY);
}

void drawSnake(){
  tft.fillScreen(0); // Clear the screen
  point = game.getPoint();
  snake = game.getSnake();
  tft.fillCircle(point.first * scaleX, point.second* scaleY, 2, tft.color565(255, 255, 255));

  for (const Pair<int, int>& coordinate : snake) {
    int x = coordinate.first;
    int y = coordinate.second;

    // Calculate the screen coordinates based on the snake's coordinates and scaling factors
    int screenX = x * scaleX;
    int screenY = y * scaleY;
    Serial.print(x);
    Serial.println(y);

    // Draw a circle for each point of the snake's body
    tft.fillCircle(screenX, screenY, 2, tft.color565(255, 255, 255));
  }
  
}


 
