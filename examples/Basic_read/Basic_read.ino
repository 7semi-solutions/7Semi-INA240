/**
 * 7Semi INA240 Current Sensor Example
 *
 * Library:
 * - Name    : 7Semi_INA240
 * - Platform: Arduino / ESP32 / ESP8266
 *
 * Description:
 * - Initializes INA240 current sense amplifier
 * - Supports INA240A1, INA240A2 and INA240A3
 * - Performs automatic offset calibration
 * - Reads output voltage
 * - Reads shunt voltage
 * - Calculates bidirectional current
 * - Prints results to Serial Monitor
 *
 * Connections:
 * -----------------------------
 * INA240    →   MCU
 * -----------------------------
 * VS        →   3.3V / 5V
 * GND       →   GND
 * OUT       →   ADC Pin
 * REF       →   Optional
 *
 * Notes:
 * - Run calibration with zero current flowing
 * - Shunt resistor value must match hardware
 * - ADC reference voltage must match system
 * - Positive and negative current supported
 */

#include <7Semi_INA240.h>

INA240_7Semi currentSensor(
    A0,                        // ADC pin
    INA240_7Semi::INA240_A3,   // Gain Variant
    0.01f,                     // 10mΩ shunt resistor
    5.0f,                      // ADC reference voltage
    1023                       // ADC max value (UNO)
);

void setup()
{
    Serial.begin(115200);

    Serial.println();
    Serial.println("7Semi INA240 Example");
    Serial.println("Calibrating...");

    // Ensure no current is flowing
    currentSensor.calibrate();

    Serial.print("Offset Voltage: ");
    Serial.print(currentSensor.getOffsetVoltage(), 4);
    Serial.println(" V");

    Serial.println("Calibration Complete");
}

void loop()
{
    Serial.print("Current: ");
    Serial.print(currentSensor.readCurrent(), 4);
    Serial.print(" A");

    Serial.print(" | Shunt: ");
    Serial.print(currentSensor.readShuntVoltage() * 1000.0f, 3);
    Serial.print(" mV");

    Serial.print(" | Vout: ");
    Serial.print(currentSensor.readVoltage(), 4);
    Serial.print(" V");

    Serial.print(" | ADC: ");
    Serial.println(currentSensor.readAnalog());

    delay(500);
}