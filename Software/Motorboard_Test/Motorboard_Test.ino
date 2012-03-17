//
int motorpina = 2;
int motorpinb = 6; //PWM
int motorpinc = 5; //PWM

int tm=1000;
boolean r = true;
int value = 0;

void setup() {
pinMode(motorpina, OUTPUT);
pinMode(motorpinb, OUTPUT);
pinMode(motorpinc, OUTPUT);
pinMode(A0, INPUT);
pinMode(7, INPUT);
Serial.begin(9600);
}

void loop() {
  value = map(analogRead(A0),0,1024,-255,255);
  
  r = digitalRead(7);
  if(value<
  0)
  {
// R
digitalWrite(motorpina, HIGH);
digitalWrite(motorpinb, LOW);

Serial.println(value);
analogWrite(motorpinc, value);

  }
  else
  {
    // L
    digitalWrite(motorpinc, HIGH);
digitalWrite(motorpina, LOW);
int value2 = map(value,-255,0
,0,255);
Serial.println(value2);
analogWrite(motorpinb, value2);
  }
//Serial.println("SHORT: - 1: Both LOW");
//delay(tm);
//digitalWrite(motorpina, HIGH);
//Serial.println("RIGHT - 2: a HIGH, b LOW");
//delay(tm);
//digitalWrite(motorpina, LOW);
//digitalWrite(motorpinb, HIGH);
//Serial.println("OFF - 3: a LOW, b HIGH");
//delay(tm);
//digitalWrite(motorpina, HIGH);
//digitalWrite(motorpinb, HIGH);
//Serial.println("LEFT - 4: Both HIGH");
//delay(tm);
}
