# Suma

須磨 Sound Utillities for Microprocessor Audio

## Overview

Suma is easy way to make sound device by modern Arduino.

**Now supported only SAMD21 mcu**


### TODO
- Support other samd/rp2040/esp
- clip function
- waveshaper/phase-distortion/cross-fade synthesis
- portament function
- hz-midi convertion

### Supported board

| Board                          | Tested | CPU    | DAC       |
| ------------------------------ | ------ | ------ | --------- |
| Seeed XIAO M0+                 | ☑️     | SAMD21 | 1ch/10bit |
| Sparkfun SAMD21 Mini Breakout  | -      | SAMD21 | 1ch/10bit |
| Adafruit QT Py                 | -      | SAMD21 | 1ch/10bit |
| Adafruit Itsy Bitsy M0 Express | -      | SAMD21 | 1ch/10bit |
| Arduino MKR WiFi 1010          | -      | SAMD21 | 1ch/10bit |
| Adafruit ItsyBitsy M4 Express  | -      | SAMD51 | 2ch/12bit |
| RaspberryPi Pico               | -      | RP2040 | PWM       |


## API Reference

### Oscillator

The Oscillator class represents a digital oscillator that generates audio samples based on a specified frequency and waveform.

```
Oscillator::Oscillator(uint16_t (*tickFunc)(Oscillator &), float frequency, uint32_t length)
```

- `tickFunc`: A pointer to a function that generates the next sample value for the oscillator. The function should take an Oscillator reference as an argument and return a uint16_t value.
- `frequency`: The frequency of the oscillator in Hz.
- `length`: The length of the waveform table used by the oscillator.

### getPhase

```
float Oscillator::getPhase()
```

Returns the current phase of the oscillator as a floating-point value.

### tick

```
uint16_t Oscillator::tick()
```

Generates the next sample value for the oscillator by calling the `tickFunc` provided in the constructor. Returns the generated sample as a `uint16_t` value.

### sumaBegin

```
void sumaBegin(uint32_t sampleRate)
```

Initializes the Suma audio library and sets the sample rate for audio processing.

- `sampleRate`: The desired sample rate in Hz.

### configureDac

```
void configureDac()
```

Configures the digital-to-analog converter (DAC) for audio output. This function sets up the necessary pins and initializes the DAC.

### writeDAC

```
void writeDAC(uint16_t sample)
```

Writes a sample value to the DAC for audio output.

**Currently it only supports samd21, so it's inevitably A0.**

- `sample`: The sample value to be written to the DAC. The value should be in the range of 0 to 4095 for a 12-bit DAC.
  These functions provide the core functionality for generating and outputting audio samples using the Suma audio library. The `Oscillator` class allows for the creation of custom oscillators with specified frequencies and waveforms, while the global functions handle the initialization and configuration of the audio system and the output of samples to the DAC.

## Lisence

This work is licensed under the Creative Commons Attribution-ShareAlike 4.0 International License.
http://creativecommons.org/licenses/by-sa/4.0/
