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
    bool _isButtonOnceReleased = true;
    bool _state = false;

    bool _coolingDown = false;
    uint32_t _coolingDownStartTime = 0;
    uint32_t _coolingDownCurrentTime = 0;
    const uint16_t _coolingDownTime = 200;

    uint32_t _coolDownStartTime = 0;
    uint32_t _currentTime = 0;
    const uint16_t _coolDownTime = 1000;

    bool _getButtonState(void);
    bool _buttonCoolDown(void);

public:
    Button(uint8_t buttonPin, uint8_t buttonNumber);

    uint8_t getButtonState(void);
};

#endif