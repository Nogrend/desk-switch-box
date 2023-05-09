#include <main.h>
#include <Button.h>

PCF8574 pcfLed(ADDRESS_LED);
PCF8574 pcfRelay(ADDRESS_RELAY);
Button_Handler btn_hand;

Button buttonA = Button(8, 0);
Button buttonB = Button(7, 1);
Button buttonC = Button(6, 2);
Button buttonD = Button(5, 3);
Button buttonE = Button(4, 4);
Button buttonF = Button(3, 5);
Button buttonG = Button(2, 6);
Button buttonH = Button(9, 7);
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
  buttonStates |= buttonC.getButtonState();
  buttonStates |= buttonD.getButtonState();
  buttonStates |= buttonE.getButtonState();
  buttonStates |= buttonF.getButtonState();
  buttonStates |= buttonG.getButtonState();
  buttonStates |= buttonH.getButtonState();

  if (previousButtonStates != buttonStates)
  {
    previousButtonStates = buttonStates;

    pcfLed.write8(~buttonStates);
    Serial.println(~buttonStates, BIN);
    // pcfRelay.write8(buttonStates);
  }
}