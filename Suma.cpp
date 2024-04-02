#include "Suma.h"

#ifdef ARDUINO_ARCH_SAMD
#include <sam.h>
#else
#error "This library only supports SAMD21 processors."
#endif

Oscillator::Oscillator(uint16_t (*tickFunc)(Oscillator &), float frequency, uint32_t length)
{
    _tickFunc = tickFunc;
    _frequency = frequency;
    _length = length;
    _phaseIncrement = (float)((frequency * _length) / 48000);
    _phase = 0;
}

float Oscillator::getPhase()
{
    _phase += _phaseIncrement;
    if (_phase >= _length)
    {
        _phase -= _length;
    }
    return _phase;
}

uint16_t Oscillator::tick()
{
    return _tickFunc(*this);
}

void sumaBegin(uint32_t sampleRate)
{
    // Configure TC4
    REG_GCLK_GENDIV = GCLK_GENDIV_DIV(1) | GCLK_GENDIV_ID(3);
    REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC | GCLK_GENCTRL_GENEN | GCLK_GENCTRL_SRC_DFLL48M | GCLK_GENCTRL_ID(3);
    REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK3 | GCLK_CLKCTRL_ID_TC4_TC5;

    uint32_t sampling_interval = 47972352 / sampleRate;
    REG_TC4_COUNT16_CC0 = sampling_interval;
    NVIC_SetPriority(TC4_IRQn, 0);
    NVIC_EnableIRQ(TC4_IRQn);
    REG_TC4_INTFLAG |= TC_INTFLAG_OVF;
    REG_TC4_INTENSET = TC_INTENCLR_OVF;
    REG_TC4_CTRLA |= TC_CTRLA_PRESCALER_DIV1 | TC_CTRLA_WAVEGEN_MFRQ;
    REG_TC4_CTRLA |= TC_CTRLA_ENABLE;

    delay(50);
}

void configureDac()
{
    // Configure DAC
    // SAMD21 : A0
    DAC->CTRLA.bit.ENABLE = 0x01;
}

void writeDAC(uint16_t sample)
{
    DAC->DATA.reg = sample;
}

void TC4_Handler()
{
    audioLoop();
    REG_TC4_INTFLAG = TC_INTFLAG_OVF;
}