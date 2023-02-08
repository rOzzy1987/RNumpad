#include "CEncoder.h"
#include <Arduino.h>


CEncoder::CEncoder(int buttonPin, int clockPin, int dirPin){
  _bPin = buttonPin;
  _cPin = clockPin;
  _dPin = dirPin; 

  pinMode(_bPin, INPUT_PULLUP);
  pinMode(_cPin, INPUT_PULLUP);
  pinMode(_dPin, INPUT_PULLUP);
}

// Returns ENC_STEP, can be negative, or 0 if the know is not turned 
int CEncoder::Rotation()
{
  int result = 0;
  char cPin = digitalRead(_cPin);
  char dPin = digitalRead(_dPin);
  if (!cPin)
  {
    if (_state & 0x01)
    {
      _state ^= 0x01;
      result = ENC_STEP;

      if (!dPin)
        result = -result;
    }
  }
  else 
  {
    _state |= 0x01;
  }

  return result;
}

// Returns 1 for single click, 2 for double click, or 0 for no clicks
char CEncoder::ButtonPress(){
  unsigned long currentTime = micros();
  char count = (_state & 0x18) >> 3; 
  char result = 0; 
  if (!digitalRead(_bPin))
  {
    if (_state & 0x02)
    {
      _state ^= 0x02;
      _state |= 0x04;
      if (count < 7)
        count++;

      _state ^= _state & 0x18;
      _state |= count << 3;

      _lastButtonPress = currentTime;
    }
  }
  else 
  {
    _state |= 0x02;
    if (_state & 0x04 && (currentTime - _lastButtonPress > FastClickThreshold))
    {
      result = count;
      _state ^= 0x04;
      _state ^= count << 3;
    }
  }
  return result;
}