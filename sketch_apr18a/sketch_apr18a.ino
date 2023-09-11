#include <TFT.h> 
#include <SPI.h>

#define CS   10
#define DC   7
#define RESET  8
TFT myScreen = TFT(CS, DC, RESET);

#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin

int d = 25;
int locationX = 13;
int locationY = 13;
int prevLocX = 0; 
int prevLocY = 0; 

int directionX = 1;
int directionY = 0;
int xValue = 0; // To store value of the controller X axis
int yValue = 0; // To store value of the controller Y axis


// Define screen dimensions
const int screenWidth = 100;
const int screenHeight = 100;

// Calculate scale factors
const int scaleX = screenWidth / d;
const int scaleY = screenHeight / d;

void setup() {
  Serial.begin(9600) ;
  
  myScreen.begin();
  myScreen.background(0,0,0); // clear the screen
}

void loop() {
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
  delay(1000);

  step();
  drawSnake();
  Serial.print("x = ");
  Serial.print(locationX);
  Serial.print(", y = ");
  Serial.println(locationY);
 
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
}

void drawSnake(){
  myScreen.stroke(0,0,0); // set the stroke color to white
  myScreen.point(prevLocX * scaleX, prevLocY * scaleY);

  myScreen.stroke(255,255,255);
  myScreen.point(locationX * scaleX, locationY * scaleY);
  
}


 
