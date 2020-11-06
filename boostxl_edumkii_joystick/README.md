## Example Summary

This demo uses the MSP432 built-in ADC14 to sample from the 2-axis of the analog joystick on the Educational BoosterPack MKII. The measured 14-bit X and Y axis data are displayed on the BoosterPack's colored 128x128 dot-matrix LCD. Using MSP Graphics Library, the MSP432 sends data to the LCD's controller through SPI communication to display the data.

## BoosterPack Requirements

This demo requires the [Educational BoosterPack MKII (BOOSTXL-EDUMKII)](http://www.ti.com/tool/BOOSTXL-EDUMKII)paired with the MSP-EXP432P401R LaunchPad

## Example Usage

Upon running the demo, the LCD on the BoosterPack displays X-axis, Y-axis, and Joystick button raw data

* Tilt and press the Joystick to see raw data on the LCD

## Application Design Details

* No-RTOS
  * ADC14 is configured to sample Joystick data from A9 and A15 analog input channels.
  * Clock System is configured with MCLK = 48 MHz.
  * EUSCI_B0 is used for SPI communication with the LCD controller.
  * GPIO is configured for Joystick button input
