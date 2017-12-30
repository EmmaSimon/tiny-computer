#include <SoftPWM.h>
#include <SoftPWM_timer.h>

#include <HID.h>


const int touchSensor = 3;
const int R = 8;
const int G = 12;
const int B = 13;

int Rval = 255;
int Gval = 0;
int Bval = 0;
int gaining = G;

void setup() {
  SoftPWMBegin();
  Serial.begin(9600);
}

void colorCycle(double intensity) {
  if (gaining == G) {
    Gval += 1;
    Rval -= 1;
    if (Gval >= 255) {
      gaining = B;
    }
  } else if (gaining == B) {
    Bval += 1;
    Gval -= 1;
    if (Bval >= 255) {
      gaining = R;
    }
  } else {
    Rval += 1;
    Bval -= 1;
    if (Rval >= 255) {
      gaining = G;
    }
  }

  int invert = digitalRead(touchSensor);
  if (invert) {
    intensity = 1 - intensity;
  }
  if (intensity < .03) {
    lightsOff();
    return;
  }
  int Rset = int(Rval * intensity);
  int Gset = int(Gval * intensity);
  int Bset = int(Bval * intensity);
  SoftPWMSet(R, Rset);
  SoftPWMSet(G, Gset);
  SoftPWMSet(B, Bset);
}

void lightsOff() {
  SoftPWMSet(R, 0);
  SoftPWMSet(G, 0);
  SoftPWMSet(B, 0);
}

double lightIntensity(int reading) {
  return double(reading) / 1023;
}

void loop() {
  int sensorValue = analogRead(A0);
  double intensity = lightIntensity(sensorValue);
  colorCycle(intensity);
  delay(1);
}
