
#include <Servo.h>

Servo myservo; 

void setup() {
  pinMode(7, INPUT_PULLUP); 
  myservo.attach(9);  
  Serial.begin(0);
  Serial1.begin(9600);
}

void loop() {
  Serial.begin(0);
  Serial1.begin(9600);
  
  while(!Serial1.available()) {
   // while Serial1 feed isn't available, do nothing
  }

  byte rec_byte = Serial1.read();
  int degree = rec_byte*90/255;
  Serial.println(degree);
  if (digitalRead(7)) myservo.write(degree); 
}
