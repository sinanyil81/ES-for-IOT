## Example Summary

This demo uses the MSP432 built-in ADC14 to sample from the 3-axis acceleration data output of the analog accelerometer on the Educational BoosterPack MKII. The measured 14-bit acceleration data are displayed on the BoosterPack's colored 128x128 dot-matrix LCD. Using MSP Graphics Library, the MSP432 sends data to the LCD's controller through SPI communication to display the data.

## BoosterPack Requirements

This demo requires the [Educational BoosterPack MKII (BOOSTXL-EDUMKII)](http://www.ti.com/tool/BOOSTXL-EDUMKII)paired with the MSP-EXP432P401R LaunchPad

## Example Usage

Upon running the demo, the LCD on the BoosterPack displays X-axis, Y-axis, and Z-axis acceleration data

* When the BoosterPack is rotated, the MSP432 makes use of the acceleration data and changes the LCD to the corresponding orientation.

## Application Design Details

* No-RTOS
  * ADC14 is configured to sample accelerometer data from A11, A13, and A14 analog input channels.
  * Clock System is configured with MCLK = 48 MHz.
  * EUSCI_B0 is used for SPI communication with the LCD controller.
