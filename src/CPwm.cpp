#include "CPwm.h"
#include "Linearize.h"
#include <Arduino.h>

CPwm::CPwm(int pin, int power){
    _pin = pin;
    _pwr = power;
    _enabled = 1;

    pinMode(_pin, OUTPUT);
}

char CPwm::Set(char pwr)
{
    _pwr = pwr;
    Add(0);
    write();
    return _pwr;
}

char CPwm::Add(int diff) {
    int n = _pwr + diff;
    if (n > 255)
        n = 255;
    if (n < 0)
        n = 0;
    _pwr = n;
    write();
    return _pwr; 
}

void CPwm::Enable(){
    _enabled = 1;
    write();
}
void CPwm::Disable(){
    _enabled = 0;
    write();
}
void CPwm::Toggle(){
    _enabled = !_enabled;
    write();
}
void CPwm::write(){
    int r = 0;
    if (_enabled)
        r = linearize(_pwr);
    analogWrite(_pin, r);
}