#include <SimpleDHT.h>
#include<Servo.h>
// Define Pins

#define BLUE 3
#define GREEN 5
#define RED 6

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
int pos = 0;

Servo myServo;
SimpleDHT11 dht11;

void setup() {
int motorPin = 9;
myServo.attach(9);
pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT);
//pinMode(buttonPin, INPUT);
Serial.begin(9600);
}

void loop() {


  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read with raw sample data.
  byte temperature = 0;
  byte humidity = 0;
  byte data[40] = {0};
  if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
    Serial.print("Read DHT11 failed"); //if something is wrong with the temperature sensor from a hardware standpoint, print the error message
    return;
  }
  
  Serial.print("Sample RAW Bits: ");
  for (int i = 0; i < 40; i++) {
    Serial.print((int)data[i]);
    if (i > 0 && ((i + 1) % 4) == 0) {
      Serial.print(' ');
    }
  }
  Serial.println("");
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); //print the temperature to the serial monitor in degrees celsius
  Serial.print((int)humidity); Serial.println(" %"); //print the humidity levels to the serial monitor
  delay(1000); //wait one second

 
if((int)temperature < 22){ //if temperature of room is less than 22 degrees celsius, turn LED blue and move motor to specific point on dial
  digitalWrite(BLUE, 255);
  digitalWrite(RED, 0);
  digitalWrite(GREEN,0);
  myServo.write(-90);
}

  
if((int)temperature >= 22 && (int)temperature <= 26){ //if temperature of room is between 22 and 26 degrees celsius, turn LED green and move motor to specific point on dial
  digitalWrite(BLUE, 0);
  digitalWrite(RED,0);
  digitalWrite(GREEN,255);
  myServo.write(0);
}


if((int)temperature > 26 && (int)temperature <= 32 ){ //if temperature of room is between 26 and 32 degrees celsius, turn LED yellow and move motor to specific point on dial
  digitalWrite(BLUE, 0);
  digitalWrite(RED,255);
  digitalWrite(GREEN,255);
  myServo.write(45);
}
delay(2000);
if((int)temperature > 32 && (int)temperature <= 38){ //if temperature is between 32 and 38 degrees celsius, turn LED purple and move motor to specific point on dial
  digitalWrite(RED, 255);
  digitalWrite(BLUE,165);
  digitalWrite(GREEN,0);
  myServo.write(90);
}
delay(2000);

 if((int)temperature > 38) { //if temperature is greater than 38 degrees celsius, turn LED red and move motor to specific point on dial
  digitalWrite(RED, 255);
  digitalWrite(GREEN,0);
  digitalWrite(BLUE,0);
  myServo.write(180);
}
  // DHT11 sampling rate is 1HZ.
  delay(1000); 
}
  
  
