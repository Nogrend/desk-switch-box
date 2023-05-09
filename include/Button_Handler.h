#ifndef Button_Handler_h
#define Button_Handler_h

#include <Arduino.h>
#include <PCF8574.h>

#define NUMBER_BUTTON_INPUTS 8
#define NUMBER_REMOTE_INPUTS 4

#define BUTTON_1 0
#define BUTTON_2 1
#define BUTTON_3 2
#define BUTTON_4 3
#define BUTTON_5 4
#define BUTTON_6 5
#define BUTTON_7 6
#define BUTTON_8 7

class Button_Handler
{
private:
    PCF8574 *_leds;
    PCF8574 *_relay;

    const uint8_t _button_inputs[NUMBER_BUTTON_INPUTS] = {
        8, // button 1
        7, // button 2
        6, // button 3
        5, // button 4
        4, // button 5
        3, // button 6
        2, // button 7
        9  // button 8
    };
    uint8_t _current_button_toggle_states = 0b11111111;
    uint8_t _previous_button_toggle_states = 0b00000000;

    const uint8_t _remote_inputs[NUMBER_REMOTE_INPUTS] = {
        13, // remote button A
        10, // remote button B
        11, // remote button C
        12  // remote button D
    };
    uint8_t _current_remote_toggle_states = 0b00000000;
    uint8_t _previous_remote_toggle_states = 0b00001100;

    uint8_t _button_delay = 100; // 100 == 1 second

    uint8_t _delay_time[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t _delay_flag[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t _off_time[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint8_t _off_flag[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    void _check_internal_buttons(void);
    void _check_external_buttons(void);
    void _set_relays(void);

    bool _delay_flag2 = false;
    void _reset_delay(void);
    bool _is_delay_done(uint8_t button_number);

public:
    Button_Handler(/* args */);
    ~Button_Handler();

    void init(PCF8574 *leds, PCF8574 *relay);

    void check_buttons(void);
    void set_button(uint8_t button_number, uint8_t button_state);

    uint8_t get_button_statuses(void);
};

#endif