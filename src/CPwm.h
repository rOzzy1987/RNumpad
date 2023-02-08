#ifndef C_PWM
#define C_PWM

class CPwm {
  private:
    int _pwr;
    char _pin;
    char _enabled = 1;
    void write();
  public:
    CPwm(int pin, int power);

    char Set(char pwr);
    char Add(int diff);
    void Enable();
    void Disable();
    void Toggle();
};
#endif