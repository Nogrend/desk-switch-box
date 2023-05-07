
#include <Button_Handler.h>

Button_Handler::Button_Handler(/* args */)
{
}

Button_Handler::~Button_Handler()
{
}

void Button_Handler::init(PCF8574 *leds, PCF8574 *relay)
{
    _leds = leds;
    _leds->begin();

    _relay = relay;
    _relay->begin();

    // for buttons on box itself
    for (uint8_t i = 0; i < NUMBER_BUTTON_INPUTS; i++)
    {
        pinMode(_button_inputs[i], INPUT);
    }
    // for buttons on remote controller
    for (uint8_t i = 0; i < NUMBER_REMOTE_INPUTS; i++)
    {
        pinMode(_remote_inputs[i], INPUT);
    }
}

void Button_Handler::check_buttons(void)
{
    _check_internal_buttons();
    _check_external_buttons();
    _set_relays();
}

void Button_Handler::_check_internal_buttons(void)
{
    for (uint8_t i = 0; i < NUMBER_BUTTON_INPUTS; i++)
    {
        if (!digitalRead(_button_inputs[i]) && _delay_flag[i] == false)
        {
            _delay_flag[i] = true;
            if (_delay_time[i] == 0)
            {
                if (_current_button_toggle_states & (0b1 << i))
                {
                    // set to 0 << i -> light and relay "on"
                    _current_button_toggle_states &= ~(0b1 << i); // set i relay on
                    _delay_time[i] = _button_delay;
                }
                else
                {
                    if (!_off_flag[i])
                    {
                        _off_flag[i] = true;
                        _off_time[i] = _button_delay;
                    }

                    if (!digitalRead(_button_inputs[i]) && _off_time[i] == 0)
                    {
                        // set to 1 << i -> light and relay "off"
                        _current_button_toggle_states |= 0b1 << i;
                        _delay_time[i] = _button_delay;
                    }
                }
            }
        }
    }

    static uint32_t previous_time = 0;
    uint32_t current_time = millis();

    if (current_time - previous_time > 10)
    {
        previous_time = current_time;
        for (uint8_t i = 0; i < NUMBER_BUTTON_INPUTS; i++)
        {
            if (digitalRead(_button_inputs[i]) && _delay_time[i] > 0) // button is released
            {
                _delay_time[i] -= 1;
            }
            if (_off_time[i] > 0)
            {
                if (!digitalRead(_button_inputs[i])) // button is released
                {
                    _off_time[i] -= 1;
                }
                else
                {
                    _off_time[i] = _button_delay;
                }
            }

            if (_delay_time[i] == 0 && _delay_flag[i] == true)
                _delay_flag[i] = false;
            if (_off_time[i] == 0 && _delay_flag[i] == true)
                _off_flag[i] = false;
        }
    }
}

void Button_Handler::_check_external_buttons(void)
{
    // buttons on the remote A and B for on and C and D for off
    for (uint8_t i = 0; i < NUMBER_REMOTE_INPUTS; i++)
    {
        if (digitalRead(_remote_inputs[i]))
        {
            switch (i)
            {
            case 0:
                _current_button_toggle_states |= 0b1 << 3;
                break;
            case 1:
                _current_button_toggle_states |= 0b1 << 4;
                break;
            case 2:
                _current_button_toggle_states &= ~(0b1 << 3);
                break;
            case 3:
                _current_button_toggle_states &= ~(0b1 << 4);
                break;
            default:
                break;
            }
        }
    }
}

void Button_Handler::set_button(uint8_t button_number, uint8_t button_state)
{
    if (button_state == HIGH)
        _current_button_toggle_states &= ~(0b1 << button_number);
    else
        _current_button_toggle_states |= 0b1 << button_number;

    _set_relays();
}

uint8_t Button_Handler::get_button_statuses(void)
{
    return _previous_button_toggle_states;
}

void Button_Handler::_set_relays(void)
{
    if (_current_button_toggle_states != _previous_button_toggle_states)
    {
        _previous_button_toggle_states = _current_button_toggle_states;
        _leds->write8(_current_button_toggle_states);
        _relay->write8(_current_button_toggle_states);
    }
}