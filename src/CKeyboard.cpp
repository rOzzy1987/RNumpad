#include "CKeyboard.h"

CKeyboard::CKeyboard() {
    const unsigned int map[C_KEY_LAYERS][C_KEY_ROWS][C_KEY_COLS] = {{
    {
      SC_NUMLOCK,
      SC_KP_SLASH,
      SC_KP_ASTERISK,
      SC_KP_MINUS
    },
    {
      SC_KP_7,
      SC_KP_8,
      SC_KP_9,
      SC_KP_PLUS
    },
    {
      SC_KP_4,
      SC_KP_5,
      SC_KP_6,
      SC_KP_PLUS
    },
    {
      SC_KP_1,
      SC_KP_2,
      SC_KP_3,
      SC_KP_ENTER
    },
    {
      SC_KP_0,
      SC_KP_0,
      SC_KP_DOT,
      SC_KP_ENTER
    }
  }};

  memcpy((void*)&_map, (void*)&map, sizeof(unsigned int) *  C_KEY_LAYERS * C_KEY_ROWS * C_KEY_COLS);
  

  
  for(int i = 0; i < C_KEY_COLS; i++){
    pinMode(colPins[i], INPUT_PULLUP);
  }

  for(int i = 0; i < C_KEY_ROWS; i++){
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
}

void CKeyboard::releaseAll()
{
  for(int y = 0; y < C_KEY_ROWS; y++){
    for(int z = 0; z < C_KEY_COLS; z++){
      _switches[y][z] = false;
    }
  }
}

void CKeyboard::keyPress(int key)
{
    //TODO: layer handling
    if(key == NO_ACTION) return;
    Keyboard.pressScancode(key);
    #ifdef C_KEY_DEBUG
    DebugKeyState()
    #endif
}

void CKeyboard::keyRelease(int key)
{
    //TODO: layer handling
    if(key == NO_ACTION) return;
    Keyboard.releaseScancode(key);
    #ifdef C_KEY_DEBUG
    DebugKeyState()
    #endif
}

void CKeyboard::tick() {
  for(int row = 0; row < C_KEY_ROWS; row++) 
  {
    digitalWrite(rowPins[row], LOW);
    for(int column = 0; column < C_KEY_COLS; column++)
    {
      keyChangeCheck(!digitalRead(colPins[column]), row, column);       
    }
    digitalWrite(rowPins[row], HIGH);
    delayMicroseconds(1000);
  }
}

void CKeyboard::keyChangeCheck(bool currentState, int row, int column) 
{  
  bool previousState = _switches[row][column];
  if(currentState == previousState) return;
  if (currentState == HIGH)
  {
    _switches[row][column] = true;
    keyPress(_map[_currentLayer][row][column]);
  }
  else
  {
    _switches[row][column] = false;
    keyRelease(_map[_currentLayer][row][column]);
  }
}