
/* This will only plot one data point per frame and will dispose all data in between two frames. */


import processing.serial.*;
import org.gwoptics.graphics.graph2D.Graph2D;
import org.gwoptics.graphics.graph2D.traces.ILine2DEquation;
import org.gwoptics.graphics.graph2D.traces.RollingLine2DTrace;
 
Serial myPort;
float gyro = 0;
float acc = 0;

PFont f; // Font


// Color scheme
color colorBg = #3F3F3F;
color colorFg = #DCDCCC;
color colorGyro = #CC9393;
color colorAcc = #7F9F7F;
color blue = #8CD0D3;

// Graph equations
class lineGyro implements ILine2DEquation{
	public double computePoint(double x,int pos) {
		return gyro;
	}		
}
class lineAcc implements ILine2DEquation{
	public double computePoint(double x,int pos) {
		return acc;
	}		
}

RollingLine2DTrace rollingGyro,rollingAcc;
Graph2D g;

void setup () {
  // Environment
  size(300, 400);
  frameRate(100);

  // Serial
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n'); // don't generate a serialEvent() unless you get a newline character:

  // Font
  f = loadFont("DejaVuSansMono-16.vlw");

  // Rolling line traces
  rollingGyro  = new RollingLine2DTrace(new lineGyro() ,10,0.01f);
  rollingGyro.setTraceColour(int(red(colorGyro)),int(green(colorGyro)),int(blue(colorGyro)));
	
  rollingAcc = new RollingLine2DTrace(new lineAcc(),10,0.01f);
  rollingAcc.setTraceColour(int(red(colorAcc)),int(green(colorAcc)),int(blue(colorAcc)));

  // Graph
  g = new Graph2D(this, width-150, height-100, false);
  g.addTrace(rollingGyro);
  g.addTrace(rollingAcc);

  g.position.y = 50;
  g.position.x = 100;

  g.setYAxisMin(-90);
  g.setYAxisMax(90);
  g.setYAxisTickSpacing(10);
  g.setXAxisMax(1f);

  g.setNoBorder();
  g.setAxisColour(int(red(colorFg)),int(green(colorFg)),int(blue(colorFg)));
  g.setFontColour(int(red(colorFg)),int(green(colorFg)),int(blue(colorFg)));
}

void draw () {
  textFont(f,16);
  background(colorBg);
  g.draw();

  // Print data
  fill(colorGyro);
  textAlign(RIGHT);
  text(gyro,125,15);
  textAlign(LEFT);
  text("gyro",5,15);
  fill(colorAcc);
  text("acc",5,30);
  textAlign(RIGHT);
  text(acc,125,30);


  // Print fps
  textFont(f,10);
  fill(colorFg);
  text(frameRate,width-25,15);
  textAlign(LEFT);
  text("fps",width-25,15);
}


void serialEvent (Serial myPort) {
  String inString = myPort.readStringUntil('\n'); // get the ASCII string:
  
  if (inString != null) {
    // Clean the input
    String inList[] = split(inString, ',');
    gyro = float(inList[0]);
    acc = float(inList[1]);
  }
}

