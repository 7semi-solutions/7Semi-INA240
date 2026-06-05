# 7Semi INA240 Arduino Library

Arduino library for the Texas Instruments INA240 high-side current sense amplifier.

The INA240 is a precision bidirectional current-sense amplifier designed for motor control, power monitoring, battery management systems, and other applications requiring accurate current measurements in noisy environments.

---

## Features

* Supports INA240A1 (20 V/V Gain)

* Supports INA240A2 (50 V/V Gain)

* Supports INA240A3 (100 V/V Gain)

* Bidirectional current measurement

  * Positive and negative current detection

* Output voltage measurement

* Shunt voltage calculation

* Current calculation

* Automatic offset calibration

* Manual offset adjustment

* ADC averaging support

  * Reduces measurement noise

* Compatible with:

  * Arduino AVR
  * ESP32
  * ESP8266
  * RP2040
  * STM32
  * Any platform supporting analogRead()

---

## Connections / Wiring

The INA240 output is connected to an ADC-capable input pin.

---

## Typical Connection

| INA240 Pin | MCU Connection | Notes                                      |
| ---------- | -------------- | ------------------------------------------ |
| VS         | 3.3V / 5V      | Device supply                              |
| GND        | GND            | Common ground                              |
| OUT        | ADC Pin        | Analog output                              |
| REF1/REF2  | Optional       | Offset reference for bidirectional sensing |

---

## Bidirectional Current Measurement

For bidirectional current sensing:

```text
VOUT = VREF + (VSHUNT × GAIN)
```

Where:

* VREF is typically VCC / 2
* Positive current increases output voltage
* Negative current decreases output voltage

The library supports:

* Automatic offset calibration
* Manual offset voltage configuration

---

## Installation

### Arduino Library Manager

1. Open Arduino IDE
2. Open Library Manager
3. Search for **7Semi INA240**
4. Click Install

---

### Manual Installation

1. Download repository ZIP
2. Arduino IDE → Sketch → Include Library → Add ZIP Library

---

## Library Overview

### Initialize Sensor

```cpp
INA240_7Semi sensor(
    A0,
    INA240_7Semi::INA240_A1,
    0.01f,
    5.0f,
    1023);
```

Parameters:

* ADC pin
* Gain variant
* Shunt resistor value
* ADC reference voltage
* Maximum ADC value

---

### Supported Gain Variants

```cpp
INA240_7Semi::INA240_A1
INA240_7Semi::INA240_A2
INA240_7Semi::INA240_A3
```

| Variant   | Gain |
| --------- | ---- |
| INA240_A1 | 20   |
| INA240_A2 | 50   |
| INA240_A3 | 100  |

---

### Read ADC Value

```cpp
uint16_t adc = sensor.readAnalog();
```

Returns averaged ADC reading.

---

### Read Output Voltage

```cpp
float voltage = sensor.readVoltage();
```

Returns INA240 output voltage.

---

### Read Shunt Voltage

```cpp
float shuntVoltage = sensor.readShuntVoltage();
```

Returns voltage across the shunt resistor after offset compensation.

---

### Read Current

```cpp
float current = sensor.readCurrent();
```

Returns measured current in amperes.

---

### Automatic Calibration

```cpp
sensor.calibrate();
```

Performs automatic offset calibration.

Run this with zero current flowing.

---

### Manual Offset Adjustment

```cpp
sensor.setOffsetVoltage(2.500f);
```

Useful when REF is externally driven.

---

### Get Offset Voltage

```cpp
float offset = sensor.getOffsetVoltage();
```

Returns stored offset voltage.

---

## Basic Example

```cpp
#include <7Semi_INA240.h>

INA240_7Semi CurrentSensor(
    A0,
    INA240_7Semi::INA240_A1,
    0.01f,
    5.0f,
    1023);

void setup()
{
    Serial.begin(115200);

    Serial.println("INA240 Calibration");

    delay(2000);

    // Ensure zero current during calibration
    CurrentSensor.calibrate();

    Serial.print("Offset Voltage: ");
    Serial.println(CurrentSensor.getOffsetVoltage(), 4);
}

void loop()
{
    Serial.print("ADC: ");
    Serial.print(CurrentSensor.readAnalog());

    Serial.print(" | Vout: ");
    Serial.print(CurrentSensor.readVoltage(), 4);

    Serial.print(" V | Current: ");
    Serial.print(CurrentSensor.readCurrent(), 4);

    Serial.println(" A");

    delay(500);
}
```

---

## Applications

* Battery monitoring
* Motor current sensing
* Solar power systems
* DC power monitoring
* Power supply testing
* Robotics
* Industrial automation
* Energy measurement systems

---

## Notes

* Use an appropriate shunt resistor for your current range.
* For best accuracy, run offset calibration after power-up.
* ADC quality affects measurement resolution.
* ESP32 users may benefit from ADC calibration for improved accuracy.

---

## License

MIT License

Copyright (c) 7Semi
