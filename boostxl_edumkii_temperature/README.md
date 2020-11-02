## Example Summary

This demo uses the MSP432 built-in eUSCI module in I2C mode to initialize and gather temperature data from the digital infrared temperature sensor, TMP006, on the Educational BoosterPack MKII. The measured temperature (F) is displayed on the BoosterPack's colored 128x128 dot-matrix LCD. Using MSP Graphics Library, the MSP432 sends data to the LCD's controller through SPI communication to display the data.

## BoosterPack Requirements

This demo requires the [Educational BoosterPack MKII (BOOSTXL-EDUMKII)](http://www.ti.com/tool/BOOSTXL-EDUMKII) paired with the MSP-EXP432P401R LaunchPad

## Example Usage

Upon running the demo, the LCD on the BoosterPack displays the temperature sensor data in Fahrenheit.

## Application Design Details

* No-RTOS
  * Clock System is configured with MCLK = 48 MHz.
  * EUSCI_B0 is used for SPI communication with the LCD controller.
  * EUSCI_B1 is used for I2C communication with the TMP006 infrared temperature sensor.
