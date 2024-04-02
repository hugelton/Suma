#ifndef SUMA_H
#define SUMA_H

#include <Arduino.h>


uint32_t 

class Oscillator
{
public:
    Oscillator(uint16_t (*tickFunc)(Oscillator &), float frequency, uint32_t length);
    float getPhase();
    uint16_t tick();

private:
    uint16_t (*_tickFunc)(Oscillator &);
    float _frequency;
    uint32_t _length;
    float _phaseIncrement;
    float _phase;
};

void sumaBegin(uint32_t sampleRate);
void configureDac();
void writeDAC(uint16_t sample);
void audioLoop();

#endif