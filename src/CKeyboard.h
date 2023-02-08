#ifndef C_KEYBOARD
#define C_KEYBOARD

#define C_KEY_LAYERS 1
#define C_KEY_ROWS 5
#define C_KEY_COLS 4

#define LAYER_RAISE 0
#define LAYER_LOWER 0
#define LAYER_RESET 0
#define NO_ACTION 0

// #define C_KEY_DEBUG


#define SC_VOLUME_MUTE 0x7f // Keyboard Mute
#define SC_VOLUME_UP 0x80 // Keyboard Volume Up
#define SC_VOLUME_DOWN 0x81 // Keyboard Volume Down


#define SC_MEDIA_PLAYPAUSE 0xe8
#define SC_MEDIA_PREVIOUS 0xea
#define SC_MEDIA_NEXT 0xeb


#define SC_NUMLOCK 0x53 // Keyboard Num Lock and Clear
#define SC_KP_SLASH 0x54 // Keypad /
#define SC_KP_ASTERISK 0x55 // Keypad *
#define SC_KP_MINUS 0x56 // Keypad -
#define SC_KP_PLUS 0x57 // Keypad +
#define SC_KP_ENTER 0x58 // Keypad ENTER
#define SC_KP_1 0x59 // Keypad 1 and End
#define SC_KP_2 0x5a // Keypad 2 and Down Arrow
#define SC_KP_3 0x5b // Keypad 3 and PageDn
#define SC_KP_4 0x5c // Keypad 4 and Left Arrow
#define SC_KP_5 0x5d // Keypad 5
#define SC_KP_6 0x5e // Keypad 6 and Right Arrow
#define SC_KP_7 0x5f // Keypad 7 and Home
#define SC_KP_8 0x60 // Keypad 8 and Up Arrow
#define SC_KP_9 0x61 // Keypad 9 and Page Up
#define SC_KP_0 0x62 // Keypad 0 and Insert
#define SC_KP_DOT 0x63 // Keypad . and Delete

#include "keyboard.h"

class CKeyboard {
    public: 
        int colPins[C_KEY_ROWS];
        int rowPins[C_KEY_ROWS];
        #define _currentLayer 0 //TODO: add layer support

        char getLedState() { return Keyboard.getLedStatus(); };
        CKeyboard();
        void init() { Keyboard.begin(); };
        void tick();
        void releaseAll();
        void pressOnce(int key) { keyPress(key); keyRelease(key); };
    private:
        unsigned int _map[C_KEY_LAYERS][C_KEY_ROWS][C_KEY_COLS];
        bool _switches[C_KEY_ROWS][C_KEY_COLS];
        void keyChangeCheck(bool currentState, int row, int column);
        void keyPress(int key);
        void keyRelease(int key);
        #ifdef C_KEY_DEBUG
        void DebugKeyState(){
            Serial.println("Matrix State:");
            for(int y = 0; y < C_KEY_ROWS; y++){
                for(int z = 0; z < C_KEY_COLS; z++){
                    Serial.print(_switches[y][z]);  
                }
                Serial.println();
            }
        }
        #endif
};




#endif