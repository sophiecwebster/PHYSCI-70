
const int out_pin = 9;
const int button_pin = 7;
const int pot_pin = 4;

void setup() {
  pinMode(button_pin, INPUT_PULLUP); 
  pinMode(out_pin, OUTPUT);        

  Serial.begin(9600);        
  Serial1.begin(9600);
}

void loop() {
  int pot_value = analogRead(pot_pin);
  Serial.println(pot_value);
  Serial1.write(pot_value/4);
  int buttonState = digitalRead(button_pin);
  Serial.println(buttonState);
  digitalWrite(out_pin, buttonState);
  delay(10);
  }
