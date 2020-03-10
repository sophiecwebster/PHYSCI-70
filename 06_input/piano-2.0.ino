#include <CapacitiveSensor.h>
// can also #include <pitches.h> if desired

// Set vars, define pins, I/O for capacitive sensors
int piezoPin = 13;
int potPin = A0;
int val;
CapacitiveSensor note_c3 = CapacitiveSensor(2,3);
CapacitiveSensor note_d = CapacitiveSensor(2,4);
CapacitiveSensor note_e = CapacitiveSensor(2,5);
CapacitiveSensor note_f = CapacitiveSensor(2,6);
CapacitiveSensor note_g = CapacitiveSensor(2,8);
CapacitiveSensor note_a = CapacitiveSensor(2,9);
CapacitiveSensor note_b = CapacitiveSensor(2,11);
CapacitiveSensor note_c4 = CapacitiveSensor(2,10);

void setup() {
note_c3.set_CS_AutocaL_Millis(0xFFFFFFFF);
note_d.set_CS_AutocaL_Millis(0xFFFFFFFF);
note_e.set_CS_AutocaL_Millis(0xFFFFFFFF);
note_f.set_CS_AutocaL_Millis(0xFFFFFFFF);
note_g.set_CS_AutocaL_Millis(0xFFFFFFFF);
note_a.set_CS_AutocaL_Millis(0xFFFFFFFF);
note_b.set_CS_AutocaL_Millis(0xFFFFFFFF);
note_c4.set_CS_AutocaL_Millis(0xFFFFFFFF);

pinMode(piezoPin, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // starting timer
  // collecting measurements from each capacitor's pin
  long start = millis();
  
  long total1 = note_c3.capacitiveSensor(9000);
  long total2 = note_d.capacitiveSensor(9000);
  long total3 = note_e.capacitiveSensor(9000);
  long total4 = note_f.capacitiveSensor(9000);
  long total5 = note_g.capacitiveSensor(9000);
  long total6 = note_a.capacitiveSensor(9000);
  long total7 = note_b.capacitiveSensor(9000);
  long total8 = note_c4.capacitiveSensor(9000);

  // printing measurements from each capacitor's pin

  Serial.print(millis() - start);
  Serial.print("\t");
  Serial.println(total1);
  Serial.print("\t");
  Serial.println(total2);
  Serial.print("\t");
  Serial.println(total3);
  Serial.print("\t");
  Serial.println(total4);
  Serial.print("\t");
  Serial.println(total5);
  Serial.print("\t");
  Serial.println(total6);
  Serial.print("\t");
  Serial.println(total7);
  Serial.print("\t");
  Serial.print(total8);

  // defining potentiometer output
  int val = analogRead(potPin);
  float voltage = val * (5.0/1023.0);
  Serial.print(val);
  analogWrite(piezoPin, voltage);
  delay(1);

  // assigning pitch to capacitor's pin
  if (total1 > 500) tone(piezoPin, 131);
  if (total2 > 500) tone(piezoPin, 147);
  if (total3 > 500) tone(piezoPin, 165);
  if (total4 > 500) tone(piezoPin, 175); //110 for Truth Hurts (A2)
  if (total5 > 500) tone(piezoPin, 196);
  if (total6 > 500) tone(piezoPin, 220);
  if (total7 > 500) tone(piezoPin, 247);
  if (total8 > 500) tone(piezoPin, 262);

  // no sound if not touched
  if (total1 <= 500 &  total2 <= 500 & total3 <= 500 & total4 <= 500 & total5 <= 500 & total6 <= 500 & total7 <= 500 & total8 <= 800) noTone(piezoPin);
  delay(10);

}
