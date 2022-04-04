# Boosted Controller Area Network
## Overview
The following is the latest comprehensive reverse-engineering breakdown of Boosted's CAN protocol between V2/3 batteries & electronic speed controllers.

## Software Overview
The Boosted Board V2/3 CAN protocol between batteries & electronic speed controllers runs at 250kbaud with extended message IDs.

### Boosted CAN Protocol
On later firmware versions (i.e. XRB v2.5.1 & ESC v2.7.2), CAN Protocol breakdown is as follows:
* All messages have extended CAN IDs beginning with 8 bits `0b00010000` - hexadecimal `0x10`.
* The following 20 bits - 5 hexadecimal digits - of the CAN ID denote the message type.  
* The final 4 bits - 1 hexadecimal digit - of the CAN ID denote a node's overflowing send counter.
* CAN Message payloads contain message information and can have varying lengths (from 1 to 8 bytes).

### Example
The following CAN message is an example of the ESC sending a ping/power message to the battery to command the battery to turn off, as would be the case if the user holds full reverse on the thumbwheel & holds down the power button on the remote.

CAN Trace: `0x103434BA 8 0x02 0x00 0x00 0x00 0x00 0x00 0x00 0x00`
* CAN ID: `0x103434BA`
  * Message Header Prefix: `0x10`
  * Message Header: `0x3434B` (ESC to BTY Ping/Power)
  * Node Send Counter: `0xA` (11th message sent from ESC since last overflow of counter)
* LENGTH: `0x8`
* PAYLOAD: `0x02 0x00 0x00 0x00 0x00 0x00 0x00 0x00`
  * First Byte: `0x02` (denotes a power-off command from ESC)

### Boosted CAN Protocol Message Table
A complete list of reverse-engineered Boosted CAN protocol messages can be found [here (BoostedCANMessageTable.md)](https://github.com/axkrysl47/BoostedBreak/blob/main/CAN/BoostedCANMessageTable.md). 

### Note:
There is clear evidence that Boosted updated the Standard Range Battery (SRB)'s CAN protocol to more closely match the Extended Range Battery (XRB)'s protocol with later firmware versions. 

_(That is to say, I did not find the same protocol that [__rscullin's BeamBREak__](https://beambreak.org/) found on his SRB, likely due to mine being on a later firmware version.)_

## Hardware Overview
Most of the physical information of the CAN bus has already been published by [__rscullin's BeamBREak__](https://beambreak.org/), be sure to check that out as I (__axkrysl47__) credit it as my original source.

I will keep accessory port information brief here. If you would like to know more, check out this [__BeamBREak__ link](https://github.com/rscullin/beambreak/tree/master/Accessory).

## Quoted from [__rscullin's BeamBREak__](https://beambreak.org/):

> The Boosted Board has two CAN Buses, both running at 250kbaud. One is used for BMS<->ESC communication, and the other is used for the Accessory Port.

### Primary CANBus (BMS <-> ESC)
> Boosted uses a [5-Pin Higo L513AM](https://www.higoconnector.com/products/l313am-p-00-ar-1000/LK99K#title) connector, with two (larger) pins for power, and three pins for CAN/connection detection. The Battery uses a female Higo L513AM P 00 AT 1000, and the ESC uses a male Higo L513AM P 00 B0 1000.

> Electrical Connections: 
> All of the following are based on the colors used by Higo.
> * Red - Switched Battery Positive (~30-50v)
> * Black - Ground
> * Yellow - CAN High
> * Green - CAN Low
> * Blue - Connection Detection -- this is 3.3v when nothing is connected to the BMS, and pulled to ground by the ESC to let the BMS know that something is connected

### Secondary CANBus (ESC <-> Accessory)
> The CAN Bus runs at 250k baud, with extended message IDs. Without an accessory connected, nothing other than a heartbeat seems to be sent on the CAN Bus. The ESC will cut 15v power after ~10 seconds of no heartbeat replies, but will continue to send heartbeat CAN frames. Without the latest ESC firmware (V2.7.2), there is no traffic on the Accessory Bus, and 15v is never supplied.

