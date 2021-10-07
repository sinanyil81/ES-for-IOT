# Embedded Software for the Internet of Things

This is the repository for the hands-on work during our lectures.

There are two options to run the necessary tools for the course:
- [Virtual machine installation](#virtual-machine-installation) (**recommended**) uses a virtual machine that has already been set-up by us. We recommend this option if you are less experienced with setting up your own tool chains. For this, you will have to install a virtual machine manager called *VirtualBox* and can then directly run the required software (*Code Composer Studio*) inside the virtual machine.
- [Native installation](#native-installation) (**without support**) uses your normal operating system and directly installs the necessary libraries and tools through an installer script. 
Please notice that this might change the configurations of your machine. We do not officially support such installations; if you run into problems, please try using a [VM](#virtual-machine-installation) before asking us for help.

*** 

## Virtual machine installation

A *virtual machine* (VM) emulates a complete computer system on top of your normal operating system. In such a case, you run a *guest* system (which we previously prepared for you) on top of your own *host* system (just as you run any other programs). For this course, we use Linux [Ubuntu 20.04.1 LTS](https://releases.ubuntu.com/20.04.1/) as a guest system.

The VM is available [from this google drive](will be released soon) and requires 12 GB of free disk space as well as at least 2 GB of RAM.

To run the VM, we use [VirtualBox](https://www.virtualbox.org/). This program is a so-called *virtual machine manager* that provides the link between all common host systems (Windows, macOS, Linux) and the guest system (in our case Linux Ubuntu).

### Installing Virtualbox

The installation process of VirtualBox depends on your host operating system. For further information, we refer to the [official installation guides](https://www.virtualbox.org/wiki/Downloads).

#### Windows

Simply download the VirtualBox installer from the [official servers](https://download.virtualbox.org/virtualbox/6.1.26/VirtualBox-6.1.26-145957-Win.exe). 
After the download finished, click on the executable to install the program. 
During the installation, make sure that the option `VirtualBox USB Support` is enabled. 

#### macOS

Simply download the VirtualBox installer from the [official servers](https://download.virtualbox.org/virtualbox/6.1.26/VirtualBox-6.1.26-145957-OSX.dmg). 
After the download finished, click on the file to install the program.

#### Linux

The installation of VirtualBox depends on your Linux flavour. You can find an overview over various distributions [online](https://www.virtualbox.org/wiki/Linux_Downloads).

#### Extension Pack (optional)

In case you should run into problems using devices which are connected through USB, consider installing the [VirtualBox Extension Pack](https://download.virtualbox.org/virtualbox/6.1.26/Oracle_VM_VirtualBox_Extension_Pack-6.1.26.vbox-extpack).
The extension pack allows you to make use of USB 2.0 and 3.0 features, which increases the speed of your interactions with the LaunchPad.

Simply download the file and double-click on it; VirtualBox should then automatically install the extensions.

### Running your virtual machine

After having downloaded the VM [from the google drive](will be released soon) as an `.ova` file, you can import the machine into VirtualBox by double-clicking on the downloaded `.ova` file and VirtualBox will ask to import the VM. 
During the import, make sure that the box next to `Import hard drives as VDI` is ticked.

Before you start the VM, consider adapting the VirtualBox VM settings in the VirtualBox Manager. We recommend the following configuration:
 * Base Memory (RAM): 4096 MB
 * Processors: 2 or more
 * Video Memory: 64 MB or more

#### Windows: Hyper-V configuration

If you are using Windows, make sure that Hyper-V is disabled. This is especially important if you previously used Docker or WSL2, as they prevent VirtualBox from booting a VM; for further information, see the [WSL issue](https://github.com/MicrosoftDocs/WSL/issues/536), the [VirtualBox issue](https://forums.virtualbox.org/viewtopic.php?t=99335) and an overall discussion on [Hyper-V and VirtualBox](https://forums.virtualbox.org/viewtopic.php?t=62339).

To disable Hyper-V, go to `Control Panel` &rarr; `Programs` &rarr; `Turn Windows features on or off` and make sure that the following features are disabled:
- `Hyper-V`
- `Virtual Machine Platform`
- `Windows Hypervisor Platform`
- `Windows Subsystem for Linux`

You might have to restart your system for these changes to take effect.
After you successfully disabled Hyper-V, you should see a blue "V" as the third icon on the bottom right of the VirtualBox window once you started the VM. If there is a green turtle, then Hyper-V is still enabled!

#### Linux: Establishing USB connections

For the USB devices to be available on Ubuntu and other Linux distributions, you must add your user (on the host OS) to the `vboxusers` group.

To do so, perform the following action in your Ubuntu host OS (replace `yourusername` with your personal username on the host OS, *not* `student`):

    sudo adduser yourusername vboxusers
    
**Log out and back in again** for the changes to take effect. You can verify that your user was successfully added to the group by running:

    groups yourusername
    
More information on connecting USB devices to VMs can be found in the [official Ubuntu documentation](https://help.ubuntu.com/community/VirtualBox/USB).

#### Ubuntu VM

Now, you are ready to start your VM by double-clicking on it in the VirtualBox Manager. The provided virtual machine is built on Linux [Ubuntu 20.04.1 LTS](https://releases.ubuntu.com/20.04.1/). As with any physical machine, you will see the normal desktop screen after booting up.
You should be logged in automatically. However, in case you are required to authenticate yourself (e.g. to run the `sudo` command), we prepared a user `student` with password `student`.

The VM should automatically scale its resolution to fit your window size; if not, make sure that `View` &rarr; `Auto-resize Guest Display` is ticked in your VM menu bar. To manually change your screen resolution, open your VM and inside the guest OS go to `Settings` &rarr; `Displays` &rarr; `Resolution`. The VM should automatically adjust its window size thereafter.

The default keyboard layout for the VM is "German (Switzerland)". If you would like to change this, follow the [official guide for alternative keyboard layouts](https://help.ubuntu.com/stable/ubuntu-help/keyboard-layouts.html.en): inside the guest OS go to `Settings` &rarr; `Regions & Languages` &rarr; `Input Sources` and use the `+` button to add the language that is associated with the desired layout.

To start the integrated development environment (IDE) for the ES labs, [Code Composer Studio](#code-composer-studio-ccs), simply either double-click on the corresponding desktop icon or left-click on the icon in the task bar. You can find the labs already pre-downloaded in `~/Embedded_Systems` (use the `Files` program to browse through them).

## Native installation

### 1 - Installing TI CSS and ARM compiler for [MSP432P401R](https://www.ti.com/product/MSP432P401R)

We will use [Code Composer Studio (CCS) Integrated Development Environment (IDE)](https://www.ti.com/tool/CCSTUDIO) from Texas Instruments. 

#### Download
Download TI CCS using the following link (choose the link for your operating system):
- [Download TI CSS](https://www.ti.com/tool/download/CCSTUDIO)

#### Installation
Follow the step-by-step installation tutorial from TI: 
- [Installation](https://software-dl.ti.com/ccs/esd/documents/users_guide_10.1.0/ccs_installation.html).

Shortly: 
- choose an installation location;
- then in the next step select custom installation and tick *SimpleLink MSP432 low power + performance MCUs*.

#### Update 
After installation:
- start TI CSS and create a new workspace
- update CCS by selecting *ARM Compiler Tools* and *ARM GCC Compiler Tools* (You can click on the icon in the bottom right corner). 

* * *
### Energia IDE

[Energia](https://energia.nu/) brings the Wiring and Arduino framework to the Texas Instruments MSP432 LaunchPad. Alternatively, you can develop your project by using this IDE and use Ardnuino-like programming. Energia is problematic on new 64-bit MACOS platforms, therefore you might need to use a Linux/Windows virtual machine to run it on MACOS. 

There are a lot of examples on Internet, sample programs and applications. We are not going to cover programming Launchpad using Energia. But you can develop your projects with it. 
Also, you can find already downloaded Energia IDE in the Downloads directory of the Ubuntu VM. Follow the parent directory and launch the IDE:
	
	cd Downloads/energia-1.8.10E23-linux64/energia-1.8.10E23
	
	sudo ./energia
	
There, you can check the examples, uploading them to the target LaunchPad, which has been already configured. 

* * *

### 2 - Software Examples
[The SimpleLink MSP432 SDK](http://dev.ti.com/tirex/explore/node?devtools=MSP-EXP432P401R&node=ADoDWIZc5WTuUbxxkAgevQ__z-lQYNj__LATEST) 
delivers components that enable engineers to develop applications on Texas Instruments MSP432 microcontroller devices.

* * *

### 3 - MSP432 Technical Reference Material
The latest versions of the following documents can be accesed from the TI's website.
- [MSP432P401R LaunchPad Development Kit](slau597f.pdf)
- [MSP432P401R Datasheet](msp432p401r.pdf)
- [MSP432P4xx Technical Reference Manual](slau356i.pdf)

Some nice tutorials can be found at [MSP430 Workshop Series](https://training.ti.com/msp430-workshop-series). You can check:
- [Course Workbook:	MSP_Design_Workshop.pdf](http://software-dl.ti.com/trainingTTO/trainingTTO_public_sw/MSP_Design_Workshop/MSP_Design_Workshop.pdf)

* * *

### 4 - Texas Instruments MSP432 Driver Library
- [DriverLib's User Guide](MSP432_DriverLib_Users_Guide-MSP432P4xx-4_40_00_03.pdf)
- [DriverLib Examples](http://dev.ti.com/tirex/explore/node?devtools=MSP-EXP432P401R&node=AIaHSvjn.KjUNRDtdnUpsg__z-lQYNj__LATEST)

Ubuntu VM contains standalone installed MSP432Ware (a collection of code examples, datasheets and other design resources for all MSP432 devices delivered in a convenient package). 
MSP432 Driver Library is also released as a component of MSP432Ware. You can import and run examples from driver library when you have MSP432Ware installed.

* * *

### 5 - BOOSTXL-EDUMKII Educational BoosterPack

- [BOOSTXL-EDUMKII BoosterPack Documentation](slau599a.pdf)
- [Code examples](http://dev.ti.com/tirex/explore/node?devtools=MSP-EXP432P401R&node=APxIJQJwn4jim9wefowLvw__z-lQYNj__LATEST&search=BOOSTXL)

### 6 - Troubleshooting
- See [this](Problems.md)
