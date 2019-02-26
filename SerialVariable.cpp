/*
  SerialVariable.h - Library for setting variables on the Arduino over Serial
  Created by Jan R. Fischer, July 2018.
  Assisted by Taylor Hearn
*/

#include "Arduino.h"
#include "SerialVariable.h"

SerialVariable::SerialVariable(int intSize, int doubleSize, int floatSize, int boolSize, int charSize)
{
  _intSize = intSize;
  _doubleSize = doubleSize;
  _floatSize = floatSize;
  _boolSize = boolSize;
  _charSize = charSize;


  _myInts = (int *) malloc(_intSize * sizeof(int));
  _myDoubles = (double *) malloc(_doubleSize * sizeof(double));
  _myFloats = (float *) malloc(_floatSize * sizeof(float));
  _myBools = (bool *) malloc(_boolSize * sizeof(bool));
  _myChars = (char *) malloc(_charSize * sizeof(char));


  _inData = "";
  _override = false;
  haveCallback = false;
}

SerialVariable::SerialVariable(int intSize)
{
  _intSize = intSize;
  _doubleSize = 0;
  _floatSize = 0;
  _boolSize = 0;
  _charSize = 0;


  _myInts = (int *) malloc(_intSize * sizeof(int));
  _myDoubles = (double *) malloc(_doubleSize * sizeof(double));
  _myFloats = (float *) malloc(_floatSize * sizeof(float));
  _myBools = (bool *) malloc(_boolSize * sizeof(bool));
  _myChars = (char *) malloc(_charSize * sizeof(char));


  _inData = "";
  _override = false;
  haveCallback = false;
}

SerialVariable::~SerialVariable() {
  free(_myInts);
  free(_myDoubles);
  free(_myFloats);
  free(_myBools);
  free(_myChars);
}
void SerialVariable::setCallback(void (* functionPointer)(int))
{
  _functionPointer = functionPointer;
  haveCallback = true;
}

int SerialVariable::getIntSize()
{
  return _intSize;
}

int SerialVariable::getDoubleSize()
{
  return _doubleSize;
}

int SerialVariable::getFloatSize()
{
  return _floatSize;
}

int SerialVariable::getBoolSize()
{
  return _boolSize;
}

int SerialVariable::getCharSize()
{
  return _charSize;
}



int SerialVariable::getInt(int index)
{
  if (index >= 0 && index < _intSize)
  {
    return _myInts[index];
  } else {
    return -1;
  }
}

double SerialVariable::getDouble(int index)
{
  if (index >= _intSize  && index < _intSize + _doubleSize)
  {
    return _myDoubles[index - _intSize];
  } else {
    return -1;
  }
}

float SerialVariable::getFloat(int index)
{
  if (index >= _intSize + _doubleSize  && index < _intSize + _doubleSize + _floatSize)
  {
    return _myFloats[index - (_intSize + _doubleSize)];
  } else {
    return -1;
  }
}

bool SerialVariable::getBool(int index)
{
  if (index >= _intSize + _doubleSize + _floatSize  && index < _intSize + _doubleSize + _floatSize + _boolSize)
  {
    return _myBools[index - (_intSize + _doubleSize + _floatSize)];
  } else {
    return -1;
  }
}

char SerialVariable::getChar(int index)
{
  if (index >= _intSize + _doubleSize + _floatSize + _boolSize  && index < _intSize + _doubleSize + _floatSize + _boolSize + _charSize)
  {
    return _myChars[index - (_intSize + _doubleSize + _floatSize + _boolSize)];
  } else {
    return "-1";
  }
}




void SerialVariable::update()
{
  //Serial.println("updating");
  while (Serial.available() > 0)
  {
    char _recieved = Serial.read();


    if(_recieved == '\n')
    {
      _recieved = "";
    }else if (_override)
    {
      _inData += _recieved;
      _override = false;
    }else if (_recieved == '\\')
    {
      _override = true;
    }else if (_recieved == ';')
    {

      /*
        if(String(iNumber).equals(sNumber)){
        Serial.write("equal");
        }else{
        Serial.write("not equal");
        }
      */

      //Serial.println(_inData);

      if (_binNum >= 0 && _binNum < _intSize) {
        _myInts[_binNum] = _inData.toInt();
        //        Serial.print("Bin: ");
        //        Serial.println(_binNum);
        //        Serial.print("Num: ");
        //        Serial.println(_myInts[_binNum]);
      } else if (_binNum >= _intSize && _binNum < _intSize + _doubleSize) {
        _myDoubles[_binNum - _intSize] = _inData.toDouble();
      } else if (_binNum >= _intSize + _doubleSize && _binNum < _intSize + _doubleSize + _floatSize) {
        _myFloats[_binNum - (_intSize + _doubleSize)] = _inData.toFloat();
      } else if (_binNum >= _intSize + _doubleSize + _floatSize && _binNum < _intSize + _doubleSize + _floatSize + _boolSize) {



        //Serial.print("In Data: ");
        //Serial.println(_inData);
        if (_inData.equalsIgnoreCase("false") || _inData.equals("0")) {
          _myBools[_binNum - (_intSize + _doubleSize + _floatSize)] = false;
          //Serial.println("f");
        } else if (_inData.equalsIgnoreCase("true") || _inData == "1") {
          _myBools[_binNum - (_intSize + _doubleSize + _floatSize)] = true;
          //Serial.println("t");
        }
        //Serial.println("e");
      } else if (_binNum >= _intSize + _doubleSize + _floatSize + _boolSize && _binNum < _intSize + _doubleSize + _floatSize + _boolSize + _charSize) {
        _myChars[_binNum - (_intSize + _doubleSize + _floatSize + _boolSize)] = _inData.charAt(0);
      }
      //execute(_binNum);

      _inData = ""; // Clear recieved buffer
      _functionPointer(_binNum);
    }
    else if (_recieved == ':')
    {

      _binNum = _inData.toInt();

      _inData = ""; // Clear recieved buffer
    }
    else
    {
      _inData += _recieved;
    }
  }

}
