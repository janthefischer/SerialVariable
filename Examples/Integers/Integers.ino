#include<SerialVariable.h>

SerialVariable myVals(20);

void setup() {
  Serial.begin(115200);
  myVals.setCallback(&doStuff);
}

void loop() {
  myVals.update();
}


void doStuff(int index){
  Serial.print("Integer ");
  Serial.print(index);
  Serial.print(" has been set to ");
  Serial.println(myVals.getInt(index));
}
