//
const int motorpinAa = 5; //PWM
const int motorpinAb = 6; //PWM
const int motorpinAc = 7; 
const int motorpinBa = 10; //PWM
const int motorpinBb = 9; //PWM
const int motorpinBc = 8; 

int tm=1000;
boolean r = true;
int value, valuemap;

void setup() {
pinMode(motorpinAa, OUTPUT);
pinMode(motorpinAb, OUTPUT);
pinMode(motorpinAc, OUTPUT);
pinMode(motorpinBa, OUTPUT);
pinMode(motorpinBb, OUTPUT);
pinMode(motorpinBc, OUTPUT);
pinMode(A0, INPUT);

Serial.begin(9600);
}

void loop() {
  value = analogRead(A0);
  
  
  
  if(value>512)
    {
      // R
      digitalWrite(motorpinAc, HIGH);
      digitalWrite(motorpinAb, LOW);
      digitalWrite(motorpinBc, HIGH);
      digitalWrite(motorpinBb, LOW);
      valuemap = (value-512)/2;
      Serial.print("R");
      Serial.println(valuemap);
      analogWrite(motorpinAa, valuemap);
      analogWrite(motorpinBa, valuemap);
    }
  else
    {
      // L
      digitalWrite(motorpinAc, LOW);
      digitalWrite(motorpinAa, LOW);
      digitalWrite(motorpinBc, LOW);
      digitalWrite(motorpinBa, LOW);
      valuemap = (512-value-1)/2;
      Serial.print("L");
      Serial.println(valuemap);
      analogWrite(motorpinAb, valuemap);
      analogWrite(motorpinBb, valuemap);
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
