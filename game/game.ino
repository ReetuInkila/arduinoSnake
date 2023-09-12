#include <TFT.h> 
#include <SPI.h>
#include "Pair.h"
#include "Snake.h"

// Controller settings and variables
#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin

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
#define CS   10
#define DC   7
#define RESET  8
TFT myScreen = TFT(CS, DC, RESET);

const int screenWidth = 100; // Pixels
const int screenHeight = 100; // Pixels

const int scaleX = screenWidth / d;
const int scaleY = screenHeight / d;



void setup() {
  Serial.begin(9600) ;
  game.start(locationX,locationY);
  myScreen.begin();
  myScreen.background(0,0,0); // clear the screen
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
  myScreen.background(0,0,0); // clear the screen
  point = game.getPoint();
  snake = game.getSnake();
  myScreen.stroke(255, 255, 255);
  myScreen.circle(point.first * scaleX, point.second* scaleY, 2);

  for (const Pair<int, int>& coordinate : snake) {
    int x = coordinate.first;
    int y = coordinate.second;

    // Calculate the screen coordinates based on the snake's coordinates and scaling factors
    int screenX = x * scaleX;
    int screenY = y * scaleY;

    // Draw a circle for each point of the snake's body
    myScreen.stroke(255, 255, 255);
    myScreen.fill(255, 255, 255);
    myScreen.circle(screenX, screenY, 2);
  }

  myScreen.stroke(0,0,0); // set the stroke color to white
  myScreen.fill(0, 0, 0);
  myScreen.circle(prevLocX * scaleX, prevLocY * scaleY, 2); // Clear previous segment

  myScreen.stroke(255, 255, 255);
  myScreen.fill(255, 255, 255); 
  myScreen.circle(locationX * scaleX, locationY * scaleY, 2); // Draw new segment
  
}


 
