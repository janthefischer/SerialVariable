#include<SerialVariable.h>

SerialVariable myVals(20);

void setup() {
  Serial.begin(115200);
  myVals.setCallback(&doStuff);
}

void loop() {
  myVals.update();
}


void doStuff(int bin){
  Serial.print("Integer ");
  Serial.print(bin);
  Serial.print(" has been set to ");
  Serial.println(myVals.getInt(bin));
}
