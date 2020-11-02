## Example Summary

This demo uses the MSP432 built-in eUSCI module in I2C mode to initialize and gather light data from the digital ambient light sensor, OPT3001, on the Educational BoosterPack MKII. The measured illuminance value (Lux) is displayed on the BoosterPack's colored 128x128 dot-matrix LCD. Using MSP Graphics Library, the MSP432 sends data to the LCD's controller through SPI communication to display the data.

## BoosterPack Requirements

This demo requires the [Educational BoosterPack MKII (BOOSTXL-EDUMKII)](http://www.ti.com/tool/BOOSTXL-EDUMKII)paired with the MSP-EXP432P401R LaunchPad

## Example Usage

Upon running the demo, the LCD on the BoosterPack displays the illuminance light sensor data in Lux.

> NOTE: Make sure that **J5 jumper** on the BOOSXL-EDUMKII is connected to **3.LCD BACKLT**

* When ambient light is altered, the MSP432 makes use of the illuminance data and changes the LCD brightness.
  * LCD backlight brightens when high illuminance value is detected.
  * LCD backlight dims when low illuminance value is detected.

## Application Design Details

* No-RTOS
  * Clock System is configured with MCLK = 48 MHz.
  * EUSCI_B0 is used for SPI communication with the LCD controller.
  * EUSCI_B1 is used for I2C communication with the OPT3001 digital light sensor.
