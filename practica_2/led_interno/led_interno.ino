void setup() {
  Serial.begin(9600);
  pinMode(1, OUTPUT);
}

void loop() {
  digitalWrite(1, HIGH);
  delay(2500);
  digitalWrite(1, LOW);
  delay(2500);
  
}
