#include <SoftPWM.h>
#include <SoftPWM_timer.h>
#include <HID.h>


const int lightSensor = A0;
const int tempSensor = A1;
const int R = 8;
const int G = 12;
const int B = 13;

void setup() {
  SoftPWMBegin();
  Serial.begin(9600);
}

double getCelsius(double reading) {
  // MCP9700 conversion
  return (reading * 3.25 / 1024 - 0.5) / 0.01;
}

void setColor() {
  int Rval = 0;
  int Gval = 0;
  int Bval = 0;

  double temp = getCelsius(analogRead(tempSensor));
  int maxTemp = 35;
  int minTemp = -10;
  double colorRatio = (temp - minTemp) / (maxTemp - minTemp);
  Rval = colorRatio >= 0 ? int(255 * colorRatio) : 0;
  Bval = colorRatio >= 0 ? int(255 * (1 - colorRatio)) : 255;

  int sensorValue = analogRead(lightSensor);
  double intensity = lightIntensity(sensorValue);
  Gval += int(255 * intensity);

  SoftPWMSet(R, min(Rval, 255));
  SoftPWMSet(G, min(Gval, 255));
  SoftPWMSet(B, min(Bval, 255));
}

double lightIntensity(int reading) {
  return double(reading) / 1023;
}

void loop() {
  setColor();
  delay(1);
}
