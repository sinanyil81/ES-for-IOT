# Common Problems

## Programming Error    

          Flash Programmer: Reading device TLV failed. CORTEX_M4_0: Error initializing flash programming: Your XMS432P401R material is no longer supported.
- Install [Uniflash](https://www.ti.com/tool/UNIFLASH) tool.
- Select your device (MSP432...)
- Select *Settings & Utilities*
- Scroll down *Device Security Configuration*
- **Unlock Device**.  


After these steps, you should be able to programming your launchpad again.
