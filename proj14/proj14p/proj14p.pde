import processing.serial.*;
Serial myPort;

PImage logo;
int bgcolor = 0;

void setup () {
  colorMode(HSB, 255);
  logo = loadImage("http://www.logospike.com/wp-content/uploads/2015/11/Logo_Image_01.png");
  size(150, 150);
  
  println("Available serial ports: ");
  println(Serial.list());
  
  myPort = new Serial(this, Serial.list()[0], 9600);
}

void draw() {
  if(myPort.available() > 0) {
    bgcolor = myPort.read();
    println(bgcolor);
  }
  background(bgcolor, 255, 255);
  image(logo, 0, 0);
}