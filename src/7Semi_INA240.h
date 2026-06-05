#pragma once
#ifndef _7SEMI_INA240_H_
#define _7SEMI_INA240_H_

#include <Arduino.h>

/**
 * INA240 Current Sense Amplifier Library
 *
 * - Supports INA240A1, INA240A2, INA240A3
 * - Supports bidirectional current measurement
 * - Supports manual and automatic offset calibration
 * - Supports ADC averaging
 * - Calculates output voltage, shunt voltage and current
 */
class INA240_7Semi
{
public:

    enum Gain
    {
        INA240_A1 = 20,
        INA240_A2 = 50,
        INA240_A3 = 100
    };

    /**
     * Constructor
     *
     * - analogPin        : ADC pin connected to INA240 output
     * - gain             : INA240 gain variant
     * - shuntResistance  : Shunt resistor value in ohms
     * - adcReference     : ADC reference voltage
     * - adcResolution    : Maximum ADC value
     */
    INA240_7Semi(
        uint8_t analogPin,
        Gain gain = INA240_A1,
        float shuntResistance = 0.01f,
        float adcReference = 3.3f,
        uint16_t adcResolution = 1023);

    /**
     * Read averaged ADC value
     */
    uint16_t readAnalog(uint8_t samples = 100);

    /**
     * Read INA240 output voltage
     */
    float readVoltage(uint8_t samples = 100);

    /**
     * Read shunt voltage without offset removal
     */
    float readRawShuntVoltage(uint8_t samples = 100);

    /**
     * Read shunt voltage with offset removal
     */
    float readShuntVoltage(uint8_t samples = 100);

    /**
     * Read current in amperes
     */
    float readCurrent(uint8_t samples = 100);

    /**
     * Set custom offset voltage
     */
    void setOffsetVoltage(float offsetVoltage);

    /**
     * Get stored offset voltage
     */
    float getOffsetVoltage();

    /**
     * Calibrate offset voltage
     *
     * - Run with zero current flowing
     */
    void calibrate(uint16_t samples = 100);

private:

    uint8_t analog_pin;

    float sensor_gain;
    float shunt_resistance;

    float vref;
    uint16_t max_adc_value;

    float offset_voltage;
};

#endif