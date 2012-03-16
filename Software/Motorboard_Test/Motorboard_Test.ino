//
int motorpina = 2;
int motorpinb = 3;

void setup() {
pinMode(motorpina, OUTPUT);
pinMode(motorpinb, OUTPUT);

}

void loop() {
digitalWrite(motorpina, LOW);
digitalWrite(motorpinb, LOW);
delay(500);
digitalWrite(motorpina, HIGH);
delay(500);
digitalWrite(motorpina, LOW);
digitalWrite(motorpinb, HIGH);
delay(500);
digitalWrite(motorpina, HIGH);
digitalWrite(motorpinb, HIGH);
delay(500);
}
