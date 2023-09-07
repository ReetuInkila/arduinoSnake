#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin

int d = 25;
int locationX = 13;
int locationY = 13; 
int directionX = 1;
int directionY = 0;
int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis

void setup() {
  Serial.begin(9600) ;
}

void loop() {
  // read analog X and Y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  if(xValue > 600){
    directionX = 1;
    directionY = 0;
  }else if (xValue < 400){
    directionX = -1;
    directionY = 0;
  }else if (yValue > 600){
    directionX = 0;
    directionY = 1;
  }else if (yValue < 400){
    directionX = 0;
    directionY = -1;
  }
  delay(2000);

  step();

  Serial.print("x = ");
  Serial.print(locationX);
  Serial.print(", y = ");
  Serial.println(locationY);
 
}

void step(){
  locationX = locationX + directionX;
  locationY = locationY + directionY;
}


 
