
#include <Button.h>

Button::Button(uint8_t buttonPin, uint8_t buttonNumber)
{
    this->_buttonPin = buttonPin;
    this->_buttonNumber = buttonNumber;
    pinMode(_buttonPin, INPUT);
}

bool Button::_readState(void)
{
    return !digitalRead(_buttonPin);
}

uint8_t Button::getButtonState(void)
{
    _isPressed = _readState();

    if (_isPressed)
    {
        if (_state == false && _isButtonReleased)
        {
            // also a little cool down?
            _state = true;
            _isButtonReleased = false;
        }
        else
        {
            if (_coolDownFlag == false)
            {
                _coolDownFlag = true;
                _cooldownStartTime = millis();
            }
            _currentTime = millis();

            if (_currentTime - _cooldownStartTime <= _coolDownTime)
            {
                _state = false;
            }
        }
    }
    else
    {
        if (_coolDownFlag)
        {
            _coolDownFlag = false;
            _isButtonReleased == true;
        }
    }

    return _state << _buttonNumber;
}
