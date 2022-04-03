# __BoostedBreakCAN__ Visual Studio Project
__BoostedBreakCAN__ is a Visual Studio C++ project that interfaces with a [PCAN-USB adapter from PEAK-System](https://www.peak-system.com/PCAN-USB.199.0.html?&L=1).

## Installation
To use this program, you must first acquire the [PCAN-Basic API from PEAK-System](https://www.peak-system.com/PCAN-Basic.239.0.html?&L=1). 
* Place `PCANBasic.lib` in the following folder - `\BoostedBreakCAN\lib\x64\PCANBasic.lib`
* Place `PCANBasic.h` in the following folder - `\BoostedBreakCAN\`.

## Features
* Latest Boosted CAN Protocol Message breakdown - reference `BoostedCANMsgInfo.h`.
* Acquiring real-time data from sniffing the CANBus communications between a real Boosted V2/3 battery & electronic speed controller.
* Emulating a Boosted ESC over CANBus.
* Emulating a Boosted SRB with older firmware (derived from [__rscullin's BeamBREak__ project](https://beambreak.org/) python script).

Features to be added:
* Emulating a Boosted SRB with later firmware.
* Emulating a Boosted XRB with latest firmware.
* Implementing an easy-to-read 'brief mode'.

__BoostedBreakCAN__ was developed via testing with an ESC on v2.7.2, XRB on v2.5.1, & SRB on v1.5.6. (A special credit goes to __David Wang__, founder of [__XR General Hospital__](https://www.xrgeneralhospital.com/), who helped source me the parts I needed to get this project off the ground.)

## Releases
### Latest Release - v0.0.1
v0.0.1 is the initial published release of __BoostedBreakCAN__. 
