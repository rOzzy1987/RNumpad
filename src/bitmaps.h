#include <Arduino.h>

#define LOGO_H 44
#define LOGO_W 46

static const unsigned char PROGMEM rgndLogo[] = {
    0x00, 0x00, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x07, 0xFF, 0xE0, 0x00, 0x00,
    0x00, 0x3F, 0xFF, 0xF8, 0x00, 0x00,
    0x00, 0x7F, 0x00, 0xFE, 0x00, 0x00,
    0x01, 0xF8, 0x00, 0x1F, 0x00, 0x00,
    0x03, 0xE0, 0x00, 0x07, 0xC0, 0x00,
    0x07, 0xC0, 0x00, 0x03, 0xE0, 0x00,
    0x0F, 0x80, 0x78, 0x01, 0xE0, 0x00,
    0x0F, 0x03, 0xFF, 0x00, 0xF0, 0x00,
    0x1E, 0x1F, 0xFF, 0x80, 0x78, 0x00,
    0x3C, 0x7F, 0x87, 0xC0, 0x38, 0x00,
    0x38, 0xFC, 0x01, 0xC0, 0x1C, 0x00,
    0x78, 0xE0, 0x01, 0xC0, 0x1C, 0x00,
    0x70, 0x70, 0x00, 0xE0, 0x0E, 0x00,
    0x70, 0x70, 0x00, 0xE0, 0x0E, 0x00,
    0x70, 0x78, 0x00, 0xE0, 0x0E, 0x00,
    0xE0, 0x38, 0x01, 0xE0, 0x07, 0x00,
    0xE0, 0x38, 0x01, 0xC0, 0x07, 0x00,
    0xE0, 0x3C, 0x01, 0xC0, 0x07, 0x00,
    0xE0, 0x1C, 0x07, 0xC0, 0x07, 0x00,
    0xE0, 0x1C, 0x0F, 0x80, 0x07, 0x00,
    0xE0, 0x1E, 0x3F, 0xC0, 0x07, 0x00,
    0xE0, 0x0F, 0xFF, 0xE0, 0x07, 0x00,
    0xE0, 0x0F, 0xF1, 0xF0, 0x07, 0x00,
    0x70, 0x07, 0xC0, 0xF8, 0x0E, 0x00,
    0x70, 0x07, 0x00, 0x7C, 0x0E, 0x00,
    0x70, 0x07, 0x80, 0x3E, 0x0E, 0x00,
    0x78, 0x03, 0x80, 0x1F, 0x1C, 0x00,
    0x38, 0x03, 0x80, 0x0F, 0x9C, 0x00,
    0x3C, 0x03, 0xC0, 0x07, 0xFC, 0x00,
    0x1E, 0x01, 0xC0, 0x03, 0xF8, 0x00,
    0x0E, 0x01, 0xC0, 0x01, 0xF0, 0x40,
    0x0F, 0x01, 0xE0, 0x01, 0xF8, 0xE0,
    0x07, 0xC0, 0xE0, 0x03, 0xFD, 0xC0,
    0x03, 0xE0, 0xC0, 0x07, 0xFF, 0x80,
    0x01, 0xF8, 0x00, 0x1F, 0x9F, 0x00,
    0x00, 0x7F, 0x00, 0xFE, 0x0E, 0x30,
    0x00, 0x3F, 0xFF, 0xFC, 0x1C, 0x70,
    0x00, 0x0F, 0xFF, 0xF0, 0x38, 0xE0,
    0x00, 0x00, 0xFF, 0x00, 0x71, 0xC0,
    0x00, 0x00, 0x00, 0x00, 0x23, 0x88,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x1C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x38,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x10
  };

  static const unsigned char PROGMEM numLockIcon[] = {
    0xFF, 0xFF,
    0x80, 0x40,
    0x8C, 0x40,
    0x9C, 0x40,
    0x8C, 0x40,
    0x8C, 0x40,
    0x8C, 0x40,
    0x9E, 0x40,
    0x80, 0x40,
    0xFF, 0xFF
  }; 
  
  static const unsigned char PROGMEM capsLockIcon[] = {
    0xFF, 0xFF,
    0x80, 0x40,
    0x9E, 0x40,
    0xB3, 0x40,
    0xB3, 0x40,
    0xB3, 0x40,
    0xBF, 0x40,
    0xB3, 0x40,
    0x80, 0x40,
    0xFF, 0xFF
  }; 
  
  static const unsigned char PROGMEM scrlLockIcon[] = {
    0xFF, 0xFF,
    0x80, 0x40,
    0x8C, 0x40,
    0x8C, 0x40,
    0x8C, 0x40,
    0xBF, 0x40,
    0x9E, 0x40,
    0x8C, 0x40,
    0x80, 0x40,
    0xFF, 0xFF
  };

