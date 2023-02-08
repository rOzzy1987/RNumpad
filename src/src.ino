#include "bitmaps.h"
#include "CEncoder.h"
#include "CMenu.h"
#include "CKeyboard.h"
#include "CPwm.h"
//#include <HID-Project.h>

CMenu* menu = new CMenu();
CKeyboard* keyboard = new CKeyboard();
CEncoder encoder(7, 4, 6);
// CPwm backlight(5, 255);
char ledState;

void setup() {
  menu->initMenu();

  keyboard->rowPins[0] = 8;
  keyboard->rowPins[1] = 9;
  keyboard->rowPins[2] = 10;
  keyboard->rowPins[3] = 14;
  keyboard->rowPins[4] = 15;
  
  keyboard->colPins[0] = 16;
  keyboard->colPins[1] = A0;
  keyboard->colPins[2] = A1;
  keyboard->colPins[3] = A2;

  keyboard->init();

  // backlight.Set(255);
}

void loop() {
  char rot = encoder.Rotation();
  char btn = encoder.ButtonPress();
  menu->tick(rot, btn);
  menu->tick(0,0);
  keyboard->tick();

  //backlight.Set(menu->brightness);
  char state = keyboard->getLedState();
  menu->setKeyboardStatus(state);

  if (!menu->isActive()){
    if (rot != 0){
      switch (menu->knobBehavior) {
        case KNOB_MEDIA:
          keyboard->pressOnce(rot > 0 ? SC_MEDIA_NEXT : SC_MEDIA_PREVIOUS);
          break;
        case KNOB_VOLUME:
          keyboard->pressOnce(rot > 0 ? SC_VOLUME_UP : SC_VOLUME_DOWN);
          break;
        case KNOB_BACKLIGHT:
          menu->brightness += rot * 16;
          if(menu->brightness > 255) menu->brightness = 255;
          if(menu->brightness < 0) menu->brightness = 0;
          break;
      }
    }
    if (btn == 1){
      switch (menu->knobBehavior) {
        case KNOB_MEDIA:
          keyboard->pressOnce(SC_MEDIA_PLAYPAUSE);
          break;
        case KNOB_VOLUME:
          keyboard->pressOnce(SC_VOLUME_MUTE);
          break;
        case KNOB_BACKLIGHT:
          menu->backlightEnabled = !menu->backlightEnabled;
          break;
      }
    }
  }
}
