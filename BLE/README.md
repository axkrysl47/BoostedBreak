# Boosted Bluetooth Low Energy
## Overview
The following is the latest work-in-progress reverse-engineering breakdown of Boosted's Bluetooth Low Energy (BLE) protocol between V2/3 remotes & electronic speed controllers.

## Software Overview
The Boosted Board V2/3 remotes & electronic speed controllers communicate using Bluetooth Low Energy Core Specification v4.1. Boosted, Inc. created several in-house services & characteristics, each with non-generic universally unique identifiers (UUIDs).

### Boosted Remote BLE Services
The Boosted remote contains many services, characteristics, and descriptors. The following is a list of the most important ones:
* `afc05da0-0cd4-11e6-a148-3e1d05defe78` "Boosted Remote" Service
  * `afc0653e-0cd4-11e6-a148-3e1d05defe78` "Boosted Remote Control Input" Characteristic
    * `0x2902` Client Characteristic Configuration Descriptor
* `f4c4772c-0056-11e6-8d22-5e5517507c66` "Boosted Board" Service
  * `f4c47a4c-0056-11e6-8d22-5e5517507c66` "Boosted Board Speed Mode" Characteristic
    * `0x2904` Characteristic Presentation Format Descriptor
  * `f4c47e66-0056-11e6-8d22-5e5517507c66` "Boosted Board State of Charge" Characteristic
    * `0x2904` Characteristic Presentation Format Descriptor
* `0x180A` Device Information Service
  * `0x2A25` Serial Number String Characteristic
    * `0x2902` Client Characteristic Configuration Descriptor
  * `0x2A27` Firmware Revision String Characteristic
    * `0x2902` Client Characteristic Configuration Descriptor

### Boosted Board BLE Services
TODO

### Boosted BLE Connection & Security
TODO

### Boosted Remote BLE Application
TODO

## Hardware Overview
Boosted used the Ehong EH-MC10 for all Bluetooth applications. The Boosted Remote utilized the built-in 8051 microcontroller feature on the EH-MC10 to perform all remote functions (such as throttle, button, trigger, LEDs). On the motor driver, there are two EH-MC10's; one is designated as a BLE client of the Boosted Remote, the other is designated as the BLE server for the Boosted smartphone application. The primary dsPIC microcontroller on the motor driver directs the EH-MC10s via Hayes (AT) serial commands. 
