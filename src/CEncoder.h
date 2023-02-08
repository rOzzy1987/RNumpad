#ifndef C_ENCODER
#define C_ENCODER

#ifndef ENC_STEP
#define ENC_STEP 1
#endif

class CEncoder {
private:
  int _dPin, _cPin, _bPin;
  unsigned long _lastButtonPress;

  // 0000 000X shows if we need to listen for the encoder rotation or not
  // 0000 00X0 shows if we need to listen for the button press or not
  // 0000 0X00 shows if we have a pending button press
  // 000X X000 stores the pending button press count

  char _state = 0x03;


public:
  unsigned long FastClickThreshold = 300000;
  CEncoder(int buttonPin, int clockPin, int dirPin);
  int Rotation();
  char ButtonPress();
  static void encoderInterrupt();
};


#endif