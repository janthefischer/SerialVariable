/*
  SerialVariable.h - Library for setting variables on the Arduino over Serial
  Created by Jan R. Fischer, July 2018.
*/
#ifndef SerialVariable_h
#define SerialVariable_h

#include "Arduino.h"

class SerialVariable
{
  public:
    SerialVariable(int intSize, int doubleSize, int floatSize, int boolSize, int charSize);
    SerialVariable(int intSize);
    ~SerialVariable();
    int getInt(int index);
    double getDouble(int index);
    float getFloat(int index);
    bool getBool(int index);
    char getChar(int index);
    void setCallback(void (* functionPointer)(int));


    void update();

    int getIntSize();
    int getDoubleSize();
    int getFloatSize();
    int getBoolSize();
    int getCharSize();

  private:
    int _binNum;
    String _inData;
    bool _override;

    int _intSize;
    int _doubleSize;
    int _floatSize;
    int _boolSize;
    int _charSize;

    int *_myInts;
    double *_myDoubles;
    float *_myFloats;
    bool *_myBools;
    char *_myChars;

    void (* _functionPointer)(int);
    bool haveCallback;
};
#endif
