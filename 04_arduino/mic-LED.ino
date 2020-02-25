//int pin_val;
  int ledPin1 = 12;
  int ledPin2 = 11;
  int ledPin3 = 10;
  int gate = 2;
  int env = A0;

void soundISR()
{
  int pin_val;
  int ledPin = 13;
  int gate = 2;
  int env = A0;

  pin_val = digitalRead(gate);
  digitalWrite(ledPin, pin_val);  
  Serial.println("interrupted"); 
}

void setup()
{
  Serial.begin(9600);

  //  Configure LED pin as output
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  // configure input to interrupt
  pinMode(gate, INPUT);
  attachInterrupt(0, soundISR, CHANGE);

  // Display status
  Serial.println("Initialized");
}

void loop()
{
  int value;

  // Check the envelope input
  value = analogRead(env);

  // Convert envelope value into a message
  Serial.println(value);
  
  if(value == 0)
  {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    Serial.println("0.");
  }
  else if( (value > 0) && (value <= 18))
  {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    Serial.println("0-20.");
  }
  else if( (value >18) && (value <= 32) )
  {
    Serial.println("Low.");
   digitalWrite(ledPin1, HIGH);
   digitalWrite(ledPin2, LOW);
   digitalWrite(ledPin3, LOW);
  }
  else if( (value > 32) && ( value <= 70) )
  {
    Serial.println("Moderate.");
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
  }
 else if(value > 70)
  {
   Serial.println("Loud.");
   digitalWrite(ledPin3, HIGH);
   digitalWrite(ledPin2, HIGH);
   digitalWrite(ledPin3, HIGH);
  }
}
