//
int motorpina = 2;
int motorpinb = 3;

int tm=1000;

void setup() {
pinMode(motorpina, OUTPUT);
pinMode(motorpinb, OUTPUT);
Serial.begin(9600);
}

void loop() {
digitalWrite(motorpina, LOW);
digitalWrite(motorpinb, LOW);
Serial.println("SHORT: - 1: Both LOW");
delay(tm);
digitalWrite(motorpina, HIGH);
Serial.println("RIGHT - 2: a HIGH, b LOW");
delay(tm);
digitalWrite(motorpina, LOW);
digitalWrite(motorpinb, HIGH);
Serial.println("OFF - 3: a LOW, b HIGH");
delay(tm);
digitalWrite(motorpina, HIGH);
digitalWrite(motorpinb, HIGH);
Serial.println("LEFT - 4: Both HIGH");
delay(tm);
}
