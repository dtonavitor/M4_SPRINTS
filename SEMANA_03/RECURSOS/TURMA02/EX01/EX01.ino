const int pinLED1 = 4;

void setup() {
  pinMode(pinLED1,OUTPUT);
}

void loop() {
  digitalWrite(pinLED1,HIGH);
  delay(500);
  digitalWrite(pinLED1,LOW);
   delay(500);
}
