#include <main.h>
#include <Button.h>

PCF8574 pcfLed(ADDRESS_LED);
PCF8574 pcfRelay(ADDRESS_RELAY);
Button_Handler btn_hand;

Button buttonA = Button(12, 0);
Button buttonB = Button(2, 1);
// Button

void setup()
{
  btn_hand.init(&pcfLed, &pcfRelay);

  if (DEBUG)
    Serial.begin(9600);

  debugln("Started Serial communication");
}

uint8_t previousButtonStates = 0x00;

void loop()
{
  uint8_t buttonStates = 0x00;

  buttonStates |= buttonA.getButtonState();
  buttonStates |= buttonB.getButtonState();

  if (previousButtonStates != buttonStates)
  {
    previousButtonStates = buttonStates;

    pcfLed.write8(buttonStates);
    // pcfRelay.write8(buttonStates);
  }
}