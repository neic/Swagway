// --- PROCESSING ----
import processing.serial.*;

Serial myPort;  // The serial port

int count = 0;

void setup() {
  size(300, 300);
  myPort = new Serial(this, Serial.list()[0], 9600);
}

void draw() {
  background(count);

  if (myPort.available() > 0) {
    count = myPort.read();
  }
 

//  count++;
//  count %= 255;
}