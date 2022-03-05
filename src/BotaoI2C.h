#pragma once
#include <Arduino.h>
#include <Wire.h>

class BotaoI2C
{
private:
    bool pinos[8] = {false, false, false, false, false, false, false, false};
    bool leds[8] = {false, false, false, false, false, false, false, false};
    bool enabledLeds = false;
    int addressBot;
    int addressLed;
    byte ledbuffer = B00000000;

    /* data */
public:
    BotaoI2C();
    BotaoI2C(int address, int id);
    BotaoI2C(int addressBot, int id, int addressLed);
    int ler();
    void acenderLed(int id);
    void apagarLed(int id);

    ~BotaoI2C();
};

