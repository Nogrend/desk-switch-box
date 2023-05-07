#ifndef Button_h
#define Button_h

#include <Arduino.h>

class Button
{
private:
    uint8_t _buttonPin;
    uint8_t _buttonNumber;
    bool _isPressed = false;
    bool _isActive = false;
    bool _coolDownFlag = false;    // ?
    bool _isButtonReleased = true; //?
    bool _state = false;
    uint32_t _cooldownStartTime = 0;
    uint32_t _currentTime = 0;
    const uint16_t _coolDownTime = 1000;

    bool _readState(void);

public:
    Button(uint8_t buttonPin, uint8_t buttonNumber);

    uint8_t getButtonState(void);
};

#endif