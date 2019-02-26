#include <SerialVariable.h >

int In = 5;        //indecies 0-4 will be ints
int Do = 5;        //indecies 5-9 will be doubles
int Fl = 5;        //indecies 10-14 will be floats
int Bo = 5;        //indecies 15-19 will be bools
int Ch = 5;        //indecies 20-24 will be chars

SerialVariable myVals(In, Do, Fl, Bo, Ch);

void setup() {
  Serial.begin(115200);
  myVals.setCallback(&doStuff);
}

void loop() {
  myVals.update();
}


void doStuff(int bin) {
  if (bin < In) {
    Serial.println(myVals.getInt(bin));
  } else if (bin < In + Do) {
    Serial.println(myVals.getDouble(bin));
  } else if (bin < In + Do + Fl) {
    Serial.println(myVals.getFloat(bin));
  } else if (bin < In + Do + Fl + Bo) {
    Serial.println(myVals.getBool(bin));
  } else if (bin < In + Do + Fl + Bo + Ch) {
    Serial.println(myVals.getChar(bin));
  }
}
