#include "7Semi_INA240.h"

/**
 * Constructor
 *
 * - Initializes INA240 configuration
 * - Default offset is ADC reference / 2
 * - Suitable for bidirectional current sensing
 */
INA240_7Semi::INA240_7Semi(
    uint8_t analogPin,
    Gain gain,
    float shuntResistance,
    float adcReference,
    uint16_t adcResolution)
{
    analog_pin = analogPin;

    sensor_gain = (float)gain;

    shunt_resistance = shuntResistance;

    vref = adcReference;
    max_adc_value = adcResolution;

    // Default midpoint reference
    offset_voltage = adcReference / 2.0f;
}

/**
 * Read averaged ADC value
 *
 * - Returns averaged ADC count
 * - Reduces ADC noise
 */
uint16_t INA240_7Semi::readAnalog(uint8_t samples)
{
    if (samples == 0)
    {
        samples = 1;
    }

    if (samples > 250)
    {
        samples = 250;
    }

    uint32_t adc = 0;

    for (uint16_t i = 0; i < samples; i++)
    {
        adc += analogRead(analog_pin);
    }

    return adc / samples;
}

/**
 * Read INA240 output voltage
 *
 * - Returns amplifier output voltage
 */
float INA240_7Semi::readVoltage(uint8_t samples)
{
    uint16_t adc = readAnalog(samples);

    return ((float)adc * vref) / max_adc_value;
}

/**
 * Read shunt voltage without offset compensation
 *
 * - Useful for debugging
 */
float INA240_7Semi::readRawShuntVoltage(uint8_t samples)
{
    return readVoltage(samples) / sensor_gain;
}

/**
 * Calculate shunt voltage
 *
 * - Removes output offset voltage
 * - Converts amplifier output back to shunt voltage
 * - Supports bidirectional current measurement
 */
float INA240_7Semi::readShuntVoltage(uint8_t samples)
{
    return (readVoltage(samples) - offset_voltage) / sensor_gain;
}

/**
 * Calculate current
 *
 * - Uses Ohm's law
 * - Positive and negative current supported
 */
float INA240_7Semi::readCurrent(uint8_t samples)
{
    if (shunt_resistance == 0.0f)
    {
        return 0.0f;
    }

    return readShuntVoltage(samples) / shunt_resistance;
}

/**
 * Set custom offset voltage
 *
 * - Useful when REF pin is externally driven
 */
void INA240_7Semi::setOffsetVoltage(float offsetVoltage)
{
    offset_voltage = offsetVoltage;
}

/**
 * Get current offset voltage
 */
float INA240_7Semi::getOffsetVoltage()
{
    return offset_voltage;
}

/**
 * Auto-calibrate offset
 *
 * - Run with zero current flowing
 * - Stores measured output voltage as offset
 */
void INA240_7Semi::calibrate(uint16_t samples)
{
    uint16_t adc = readAnalog(samples);

    offset_voltage = ((float)adc * vref) / max_adc_value;
}