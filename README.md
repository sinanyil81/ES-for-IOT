# Embedded Software for the Internet of Things

This is the repository for the hands-on work during our lectures.

*** 

## 1 - Installing TI CSS and ARM compiler for [MSP432P401R](https://www.ti.com/product/MSP432P401R)

We will use [Code Composer Studio (CCS) Integrated Development Environment (IDE)](https://www.ti.com/tool/CCSTUDIO) from Texas Instruments. 

### Download
Download TI CCS using the following link (choose the link for your operating system):
- [Download TI CSS](https://www.ti.com/tool/download/CCSTUDIO)

### Installation
Follow the stap-by-step installation tutorial from TI: 
- [Installation](https://software-dl.ti.com/ccs/esd/documents/users_guide_10.1.0/ccs_installation.html).

Shortly: 
- choose an installation location;
- then in the next step select custom installation and tick *SimpleLink MSP432 low power + performance MCUs*.

### Update 
After installation:
- start TI CSS and create a new workspace
- Update CCS by selecting *ARM Compiler Tools* and *ARM GCC Compiler Tools* (You can click on the icon in the bottom right corner). 

* * *
## Energia IDE

[Energia](https://energia.nu/) brings the Wiring and Arduino framework to the Texas Instruments MSP432 LaunchPad. Alternatively, you can develop your project by using this IDE and use Ardnuino-like programming. Energia is problematic on new 64-bit MACOS platforms, therefore you might need to use a Linux/Windows virtual machine to run it on MACOS. 

There are a lot of examples on Internet, sample programs and applications. We are not going to cover programming Launchpad using Energia. But you can develop your projects with it. 

* * *

## 2 - Software Examples
[The SimpleLink MSP432 SDK](http://dev.ti.com/tirex/explore/node?devtools=MSP-EXP432P401R&node=ADoDWIZc5WTuUbxxkAgevQ__z-lQYNj__LATEST) 
delivers components that enable engineers to develop applications on Texas Instruments MSP432 microcontroller devices.

* * *

## 3 - MSP432 Technical Reference Material
The latest versions of the following documents can be accesed from the TI's website.
- [MSP432P401R LaunchPad Development Kit](slau597f.pdf)
- [MSP432P401R Datasheet](msp432p401r.pdf)
- [MSP432P4xx Technical Reference Manual](slau356i.pdf)

Some nice tutorials can be found at [MSP430 Workshop Series](https://training.ti.com/msp430-workshop-series). You can check:
- [Course Workbook:	MSP_Design_Workshop.pdf](http://software-dl.ti.com/trainingTTO/trainingTTO_public_sw/MSP_Design_Workshop/MSP_Design_Workshop.pdf)

* * *

## 4 - Texas Instruments MSP432 Driver Library
- [DriverLib's User Guide](MSP432_DriverLib_Users_Guide-MSP432P4xx-4_40_00_03.pdf)
- [DriverLib Examples](http://dev.ti.com/tirex/explore/node?devtools=MSP-EXP432P401R&node=AIaHSvjn.KjUNRDtdnUpsg__z-lQYNj__LATEST)

* * *

## 5 - BOOSTXL-EDUMKII Educational BoosterPack

- [BOOSTXL-EDUMKII BoosterPack Documentation](slau599a.pdf)
- [Code examples](http://dev.ti.com/tirex/explore/node?devtools=MSP-EXP432P401R&node=APxIJQJwn4jim9wefowLvw__z-lQYNj__LATEST&search=BOOSTXL)

## 6 - Troubleshooting
- See [this](Problems.md)
