
#include <Button.h>

Button::Button(uint8_t buttonPin, uint8_t buttonNumber)
{
    this->_buttonPin = buttonPin;
    this->_buttonNumber = buttonNumber;
    pinMode(_buttonPin, INPUT);
}

bool Button::_getButtonState(void)
{
    return !digitalRead(_buttonPin);
}

uint8_t Button::getButtonState(void)
{
    _isPressed = _getButtonState();

    if (_isPressed)
    {
        if (_state == false && _isButtonOnceReleased == true)
        {
            _isButtonOnceReleased = false;
            Serial.println("turn on");

            _state = true;
        }
        else if (_state == true)
        {
            _isButtonOnceReleased = false;
            if (_coolDownFlag == false)
            {
                Serial.println("set cool down flag");
                _coolDownFlag = true;
                _coolDownStartTime = millis();
            }
            _currentTime = millis();

            if (_currentTime - _coolDownStartTime >= _coolDownTime)
            {
                _state = false;
                _coolingDown = true;
                Serial.println("turn off");
            }
        }
    }
    else
    {
        _coolDownFlag = false;

        if (_coolingDown == true)
        {
            _coolingDown = false;
            _coolingDownStartTime = millis();
        }
        else if (_isButtonOnceReleased == false)
        {
            _coolingDownCurrentTime = millis();
            if (_coolingDownCurrentTime - _coolingDownStartTime >= _coolingDownTime)
            {
                _isButtonOnceReleased = true;
            }
        }
    }

    return _state << _buttonNumber;
}