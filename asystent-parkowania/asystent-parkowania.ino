#include <LiquidCrystal.h> // includes the LiquidCrystal Library
LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
const int trigPin = 9;
const int echoPin = 10;
int redLED = 11;
int yellowLED = 12; // Yellow LED connected to pin D3
int greenLED = 13; // Green LED connected to pin D4
int buzzer = A0; // Buzzer connected to Analogue pin A0
long duration;
int distance;
long TempDistance = 0; // A variable to store the temporary distance

int counter = 0; // Counter value to check if the object has stopped moving


void setup() {
  lcd.begin(16, 2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
}
  void turnThemAllOff(){

    digitalWrite(redLED, LOW);
    digitalWrite(greenLED,LOW);
    digitalWrite(yellowLED, LOW);
    noTone(buzzer);

}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;


//******************************************************************************************************************************************
  if(counter < 20){ // Do the rest if the car is still moving

if (distance > 200) { // Nothing in the garrage

turnThemAllOff();

}

if ((distance > 55) && (distance <= 200)) { // Turn on Green LED

digitalWrite(greenLED, HIGH);

digitalWrite(yellowLED, LOW);

digitalWrite(redLED, LOW);

noTone(buzzer);

}

if ((distance > 15) && (distance <= 55)) { // Turn on Yellow LED

digitalWrite(yellowLED, HIGH);

digitalWrite(redLED, LOW);

digitalWrite(greenLED,LOW);

noTone(buzzer);

}

if (distance <= 15) { // Turn on Red LED

digitalWrite(redLED, HIGH);

digitalWrite(greenLED,LOW);

digitalWrite(yellowLED, LOW);

noTone(buzzer);

}

if (distance < 8) { // Item is way to close - start the buzzer

tone(buzzer, 500);

}

}

if ((distance == TempDistance) || ((distance+1) == TempDistance) || ((distance-1) == TempDistance)){

if(counter >= 20){ // Turn off the lights if the object hasn't moved for 20 cycles (no change in distance)

Serial.println("No movement detected, turning off the lights");

turnThemAllOff();

} else {

counter++;

}

} else {

counter = 0; // Reset counter if there is a movement

}

  TempDistance = distance; 

  lcd.clear();
  lcd.setCursor(0, 0); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("Distance: "); // Prints string "Distance" on the LCD
  lcd.print(distance); // Prints the distance value from the sensor
  lcd.print(" cm");
  delay(500);




}
