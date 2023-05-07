// includes
#include <Arduino.h>
#include <PCF8574.h>

#include <Button_Handler.h>

// defines
#define SDA A4
#define SCL A5

#define ADDRESS_LED 0x20
#define ADDRESS_RELAY 0x38

// Debugging in console
#define DEBUG 0

#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif