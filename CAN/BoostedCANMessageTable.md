# Boosted CAN Message Table
The following is representation of all reverse-engineered CAN messages on the latest Boosted V2/3 battery & electronic speed controller firmwares.

## Template Message 
* CAN ID: `0x10 [Header : 20 bits] [Counter : 4 bits]`
* LENGTH: `[Len]` 
* DATA: `[D0] [D1] [D2] [D3] [D4] [D5] [D6] [D7]`

## Message Table
| Header  | Source  | Len |  Context  | Description                 | Interpretation                                                                                                                                                     |
|:-------:|:-------:|:---:|:---------:|:--------------------------- |:---------------------------------------------------------------------------------------------------------------------------------------                            |
|`0x02402`|   ESC   | `8` |   Event   | Version / Serial (to SRB)   | `v[D6].[D7].[D0]` / `BoostedBoard[D5][D4][D3][D2][D1]`                                                                                                             |
|`0x02411`|   SRB   | `8` |   Event   | Debug Message (Continued)   | ASCII Message                                                                                                                                                      |
|`0x05415`|   XRB   | `8` |   Event   | Version Registration        | `v[D2].[D3].[D4]` / `[D6:7]` = `[BTY Code]`                                                                                                                        |
|`0x12402`|   SRB   | `1` |   Event   | Software/Hardware Release?  | IF `[D0]` == `02`, Public?                                                                                                                                         |
|`0x12411`|   SRB   | `8` |   Event   | Debug Message (End)         | ASCII Message                                                                                                                                                      |
|`0x13417`|   XRB   | `8` |   20 ms   | Debug Code (End)            | Unknown (Null-terminated coded string?)                                                                                                                            |
|`0x15415`|   XRB   | `3` |   Event   | Software/Hardware Release?  | IF `[D2]` == `02`, Public?                                                                                                                                         |
|`0x22402`|   SRB   | `8` |   Event   | Unknown (Incrementer?)      | `[D3:0]` = `int32_t`? / `[D4]` = `03`                                                                                                                                |
|`0x22411`|   SRB   | `8` |   Event   | Debug Message (Start)       | ASCII Message                                                                                                                                                      |
|`0x23417`|   XRB   | `8` |   20 ms   | Debug Code (Start)          | Unknown (Null-terminated coded string?)                                                                                                                            |
|`0x25415`|   XRB   | `8` |   Event   | Serial Registration         | `BoostedBattery[D2][D3][D4][D5]`                                                                                                                                   |
|`0x32411`|   SRB   | `8` |   Event   | Debug Message (Address)     | ASCII Message                                                                                                                                                      |
|`0x33417`|   XRB   |  *  |   Event   | Registration State (to ESC) | IF `[D0:1]` == `010A`, Standby ------------------------------------------ IF `[D0:6]` == `007D0064006400`, Registration Request; [_See notes below_](#table-notes) |
|`0x33440`|   BTY   | `8` |   Event   | Version                     | `v[D0].[D1].[D2]`                                                                                                                                                  |
|`0x33441`|   BTY   | `8` |   Event   | Serial                      | `BoostedBattery[D0][D1][D2][D3]`                                                                                                                                   |
|`0x33442`|   BTY   | `8` |   250 ms  | Ping                        | `[D2:3]` = `[BTY Code]`                                                                                                                                            |
|`0x33443`|   BTY   | `8` |   250 ms  | Indentifier                 | IF `[D0:7]` == `D20FCA080C000000`, SRB ID ----------------------------- IF `[D0:7]` == `8110C4090D000000`, XRB ID                                                  |
|`0x33445`|   BTY   | `8` |   20 ms   | Voltages (mV)               | `[D1:0]` = Lowest Cell Voltage - `[D3:2]` = Highest Cell Voltage - `[D7:4]` = Total Pack Voltage                                                                   |
|`0x33446`|   BTY   | `8` |   20 ms   | Unknown (Calibration?)      | `[D3:0]` = `int32_t`? / `[D7:4]` = `int32_t`?                                                                                                                          |
|`0x33447`|   BTY   | `8` |   250 ms  | Amperages (mA)              | `[D3:0]` = 10 second Average Current --------------------------------- `[D7:4]` = Instantaneous Current; [_See notes below_](#table-notes)                         |
|`0x33448`|   BTY   | `8` |   20 ms   | Unknown (Counter?)          | [_See example below_](#message-examples)                                                                                                                           |
|`0x33449`|   BTY   | `8` |   250 ms  | State of Charge             | `[D4]` = Percentage; [_See example below_](#message-examples)                                                                                                      |
|`0x3344A`|   BTY   | `8` |   100 ms  | State / Timer / Millis(LSB) | [_See example below_](#message-examples)                                                                                                                           |
|`0x3344C`|   SRB   | `8` |   Event   | Button State                | [_See example below_](#message-examples)                                                                                                                           |
|`0x3344E`|   BTY   | `8` |  1000 ms  | Current Timestamp           | `[D6]` / `[D5]` / `[D3]`, `[D4]`, `[D2]` : `[D1]` : `[D0]` ------------------- = YYYY / MM / DD, DoW, HH : MM : SS; [_See example below_](#message-examples)       |
|`0x34316`|   ESC   | `3` |   Event   | Registration State (to BTY) | IF `[D0:2]` == `010C00`, BTY Registration Command ------------------ IF `[D0:2]` == `020600`, ESC Registration Notification                                        |
|`0x34344`|   ESC   | `8` |   Event   | Version / Serial (to BTY)   | `v[D2].[D1].[D0]` / `BoostedBoard[D7][D6][D5][D4][D3]`                                                                                                             |
|`0x3434B`|   ESC   | `8` |   100 ms  | Ping / Power Command        | IF `[D0]` == `00`, Ping --------------------------------------------------- IF `[D0]` == `02`, Power Off (via Remote Command)                                      |
|`0x3434D`|   SRB   | `8` |  1000 ms* | Pairing State               | IF `[D0:1]` == `0000`, Not Pairing -------------------------------------- IF `[D0:1]` == `01D7`, Pairing Mode; [_See notes below_](#table-notes)                   |
|`0x3B31A`|   ESC   | `3` |   Event   | Mode                        | [_See example below_](#message-examples)                                                                                                                           |
|`0x3B41A`|   XRB   | `8` |   Event   | Button / Charge State       | [_See example below_](#message-examples)                                                                                                                           |
|`0x33920`|   ACC   | `8` |   Event   | Accessory Registration      | [_See example below_](#message-examples)                                                                                                                           |
|`0x39320`|   ESC   | `8` |   Event   | Command (to ACC)            | [_See example below_](#message-examples)                                                                                                                           |

### Table Notes
* All numbers above are represented in hexadecimal.
* Where `x < y`, `[Dx:y]` represents a big endian integer, `[Dy:x]` represents a little endian integer.
* BTY denotes both the SRB and/or XRB.
* ACC denotes a connected accessory.
* `[BTY Code]` = `C409` for SRB or `A20F` for XRB.
* `int32_t` & `int16_t` denote 32-bit & 16-bit integers, respectively.
* __XRB Registration State (to ESC)__ has variable payload length.
* __BTY Amperages (mA)__ are represented as negative integers during discharging or as positive integers during charging.
* __SRB Pairing State__ is sent every 1 second if pairing is in progress.

## Message Examples
### `0x33448` - BTY Unknown (Counter?)
```
D0 D1 D2 D3 D4 D5 D6 D7
B8 88 00 00 D8 59 00 00
            ^^ ^^ ^^ ^^ Counter (Little Endian) - Ex. 0x000059D8 = 23000
^^ ^^ State - 0x0000 = Unavailable?,
            - 0x50C8 = Active (SRB)?,
            - 0xB888 = Active (XRB)?;
```

### `0x33449` - BTY State of Charge
```
D0 D1 D2 D3 D4 D5 D6 D7
E4 0D A2 0F 59 00 05 00
                  ^^ Charge State - 0x05 = Normal, 0x03 = `Was charging when last powered`;
            ^^ State of Charge Percentage  - Ex. 0x59 = 3556 / 4002 = 89%
      ^^ ^^ Denominator (Little Endian)    - Ex. 0x0FA2 = 4002
^^ ^^ Numerator (Little Endian)            - Ex. 0x0DE4 = 3556
```

### `0x3344A` - BTY State / Timer / Millis(LSB)
```
D0 D1 D2 D3 D4 D5 D6 D7
00 00 73 78 00 00 56 00
                  ^^ Current Timestamp Milliseconds (Least Significant Byte Only) - Ex. 86 ms
            ^^ Power State - 0x00 = On (Startup timer),   0x02 = ESC Shutdown Command, 
                             0x03 = Charger Disconnected, 0x05 = Power Button Held;
      ^^ ^^ State Timer Milliseconds (Little Endian) - Ex. 30835 ms left on Startup timer
^^ Charger Connection State (XRB Only) - 0x00 = Normal, 0x01 = Charger Connected;
```

### `0x3344C` - SRB Button State
```
D0 D1 D2 D3 D4 D5 D6 D7
0A 00 00 00 00 00 00 00
   ^^ Pairing Mode Acknowledgment - 0x00 = Normal, 0x01 = Acknowledged;
^^ Button State - 0x01 = Was pressed once,
                  0x02 = Was pressed twice,
                  0x03 = Was pressed three times,
                  0x04 = Was pressed four times,
                  0x05 = Was pressed five times,
                  0x06 = Currently pressed now,
                  0x07 = Currently held down for less than 1 second,
                  0x08 = Currently held down for less than 2 seconds,
                  0x09 = Currently held down for more than 2 seconds,
                  0x0A = Was held down for less than 1.5 seconds,
                  0x0B = Was held down for less than 2 seconds,
                  0x0C = Was held down for more than 2 seconds;
```

### `0x3344E` - BTY Current Timestamp
Batteries seem to acquire the latest timestamp from the ESC / from the Boosted Phone Application.

On occasion (likely tied to removing the battery/power source), a board will lose the current timestamp; 
in that case, the battery will count up from an all zeroes timestamp.

```
D0 D1 D2 D3 D4 D5 D6 D7
33 34 10 0B 05 02 16 00
                  ^^ Year (+ 2000) - Ex. 0x16 = 22 = *2022*
               ^^ Month - Ex. 0x02 = 2 = *February*
            ^^ Day of Week - 0x00 = Sunday, 0x01 = Monday, 0x02 = Tuesday, 0x03 = Wednesday, 
                             0x04 = Thursday, 0x05 = Friday, 0x06 Saturday;
         ^^ Date - Ex. 0x0B = 11 = *11th*
      ^^ Hour - Ex. 0x10 = 16 = *4:00 PM*
   ^^ Minute - Ex. 0x34 = 52
^^ Second - Ex. 0x33 = 51
Complete Example - 2022/02/11, Friday, 04:52:51 PM
```

### `0x3B31A` - ESC Mode
```
D0 D1 D2
00 04 04 
      ^^ ESC Mode Support? - 0x00 = Up to Mode 1 Supported,
                             0x01 = Up to Mode 2 Supported,
                             0x02 = Up to Mode 3 Supported,
                             0x03 = Up to Mode 4 Supported,
                             0x04 = Up to Mode 5 Supported;
         *** ESC Mode Support is speculative, more testing needed ***     
   ^^ Current ESC Mode - 0x00 = Mode 1 (Beginner),
                         0x01 = Mode 2 (Eco),
                         0x02 = Mode 3 (Expert),
                         0x03 = Mode 4 (Pro),
                         0x04 = Mode 5 (Hyper),
                         0x05 = Disengaged (SRB Only - Charging Acknowledgment),
                         0x06 = Shutting Down (SRB Only),
                         0x15 = Pairing Mode,
                         0x16 = Exited Pairing Mode;
```

### `0x3B41A` - XRB Button / Charge State
```
D0 D1 D2
00 08 04
      ^^ ESC Support Acknowledgement? - Reference ESC Mode above
         *** ESC Support Acknowledgement is speculative, more testing needed ***     
   ^^ Button State - 0x05 = Charging,
                     0x06 = Shutting down,
                     0x07 = Currently pressed now,
                     0x08 = Waiting to finalize button state,
                     0x09 = Was pressed once,
                     0x0A = Was pressed twice,
                     0x0B = Was pressed three times,
                     0x0C = Was pressed four times,
                     0x0D = Was pressed five times,
                     0x0E = Currently held down for less than 1 second,
                     0x0F = Currently held down for less than 1.5 seconds,
                     0x10 = Currently held down for less than 2 seconds,
                     0x11 = Currently held down for less than 2.5 seconds,
                     0x12 = Was held down for less than 1.5 seconds,
                     0x13 = Was held down for less than 2 seconds,
                     0x14 = Was held down for more than 2.5 seconds;
```

### `0x33920` - ACC Accessory Registration
Using [rscullin's BeamBREak example](https://github.com/rscullin/beambreak/tree/master/Accessory):
```
D0 D1 D2 D3 D4 D5 D6 D7
FE 00 00 00 00 01 37 13
                  ^^ ^^ Accessory Serial Number (Little Endian) - Ex. 0x1337 = BoostedBeams1337
               ^^ Accessory Type - 0x00 = Headlights, 0x01 Taillights;
^^ Accessory Registration Request - 0xFE
```

### `0x33920` - ESC Command (to ACC)
Using [rscullin's BeamBREak example](https://github.com/rscullin/beambreak/tree/master/Accessory):
```
D0 D1 D2 D3 D4 D5 D6 D7
00 04 22 FF 00 00 00 00
         ^^ Command Parameter 2 - Brightness Level
                                - Headlight Range - 0x00-0xFF or 0-255
                                - Taillight Range - 0x00-0x33,0x64 or 0-51,100
                                  (Taillight Braking Brightness is 100)
      ^^ Command Parameter 1 - Light State
                               0x22 = Light On, 0x23 = Light Off,
                               0x62 = Blink On, 0x42 = Blink Off;
   ^^ Command Type - 0x04 = Light Command
^^ Accessory Address - 0x00 = First Registered Accessory,
                       0x01 = Second Registered Accessory;
```
