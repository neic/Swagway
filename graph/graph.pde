
 // This program takes ASCII-encoded strings
 // from the serial port at 9600 baud and graphs them. It expects values in the
 // range 0 to 1023, followed by a newline, or newline and carriage return
 
 // Created 20 Apr 2005
 // Updated 18 Jan 2008
 // by Tom Igoe
 // This example code is in the public domain.
 
import processing.serial.*;
 
Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph

PFont f;

void setup () {
  // set the window size:
  size(800, 600);        
 
  // List all the available serial ports
  println(Serial.list());
  // I know that the first port in the serial list on my mac
  // is always my  Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[0], 19200);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  // set inital background:
  background(0);
  f = loadFont("ArialUnicodeMS-48.vlw");
}
void draw () {
  // everything happens in the serialEvent()

  textFont(f,16);                 // STEP 4 Specify font to be used
                          // STEP 5 Specify font color 
  
}
void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  
  if (inString != null) {
    // trim off any whitespace:
    String inList[] = split(inString, ',');
    // convert to an int and map to the screen height:
    float gyro = float(inList[0]);
    float acc = float(inList[1]);
    stroke(0);
    fill(0);
    rect(10,0,100,45);
    fill(255);
    text(gyro,10,15);
    text(acc,10,30);
    
    gyro = map(gyro, -180, 180, 0, height);
    acc = map(acc, -180, 180, 0, height);
    
    // draw the line:
    stroke(255,0,0);
    line(xPos, height-gyro, xPos, height - gyro);
    
    stroke(0,255,0);
    line(xPos, height-acc, xPos, height - acc);
    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      background(0);
    }
    else {
      // increment the horizontal position:
      xPos++;
    }

  
  }
}

