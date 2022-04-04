### Analysis spreadsheet files should go here.

# Boosted CAN Message Protocol 

Template Message : `0x10 [Type : 20 bits] [Counter : 4 bits] [Len] [D0] [D1] [D2] [D3] [D4] [D5] [D6] [D7]`

[SRB-or-XRB Code] : `0xC409` for SRB, `0xA20F` for XRB

| Type    | Source  | Len |  Context  | Description                 | Interpretation                                                                                 |
| ------- | ------- | --- | --------- | --------------------------  | ---------------------------------------------------------------------------------------------- |
| 0x02402 |   ESC   |  8  |   Event   | Version / Serial (to SRB)   | `v[D6].[D7].[D0]` / `BoostedBoard[D5][D4][D3][D2][D1]`                                         |
| 0x02411 |   SRB   |  8  |   Event   | Debug Message (Continued)   | ASCII Message                                                                                  |
| 0x05415 |   XRB   |  8  |   Event   | Version Registration        | `v[D2].[D3].[D4]` / `[D6:7]` = [SRB-or-XRB Code]                                               |
| 0x12402 |   SRB   |  1  |   Event   | Software/Hardware Release?  | IF `[D0]` == `02`, Public?                                                                     |
| 0x12411 |   SRB   |  8  |   Event   | Debug Message (End)         | ASCII Message                                                                                  |
| 0x13417 |   XRB   |  8  |   20 ms   | Debug Code (End)            | Unknown (Null-terminated coded string?)                                                        |
| 0x15415 |   XRB   |  3  |   Event   | Software/Hardware Release?  | IF `[D2]` == `02`, Public?                                                                     |
| 0x22402 |   SRB   |  8  |   Event   | Unknown (Incrementer?)      | `[D3:0]` = INT32? / `[D4]` = `03`                                                              |
| 0x22411 |   SRB   |  8  |   Event   | Debug Message (Start)       | ASCII Message                                                                                  |
| 0x23417 |   XRB   |  8  |   20 ms   | Debug Code (Start)          | Unknown (Null-terminated coded string?)                                                        |
| 0x25415 |   XRB   |  8  |   20 ms   | Serial Registration         | `BoostedBattery[D2][D3][D4][D5]`                                                               |
| 0x32411 |   SRB   |  8  |   Event   | Debug Message (Address)     | ASCII Message                                                                                  |
| 0x33417 |   XRB   | VAR |   Event   | Registration State (to ESC) | IF `[D0:1]` == `010A`, Standby; IF `[D0:6]` == `007D0064006400`, ESC Registration Request      |
| 0x33440 |   BTY   |  8  |   Event   | Version                     | `v[D0].[D1].[D2]`                                                                              |
| 0x33441 |   BTY   |  8  |   Event   | Serial                      | `BoostedBattery[D0][D1][D2][D3]`                                                               |
| 0x33442 |   BTY   |  8  |   250 ms  | Ping                        | `[D2:3]` = [SRB-or-XRB Code]                                                                   |
| 0x33443 |   BTY   |  8  |   250 ms  | Indentifier                 | IF `[D0:7]` = `D20FCA080C000000`, SRB ID; IF `[D0:7]` = `8110C4090D000000`, XRB ID             |
| 0x33445 |   BTY   |  8  |   20 ms   | Voltages (mV)               | `[D1:0]` = Lowest Cell Voltage; `[D3:2]` = Highest Cell Voltage, `[D7:4]` = Total Pack Voltage |
| 0x33446 |   BTY   |  8  |   20 ms   | Unknown (Calibration?)      | `[D3:0]` = INT32? / `[D7:4]` = INT32?                                                          |
| 0x33447 |   BTY   |  8  |   250 ms  | Amperages (mA)              | `[D3:0]` = 10 second Average Current; `[D7:4]` = Instantaneous Current; _See notes_            |
| 0x33448 |   BTY   |  8  |   20 ms   | Unknown (Counter?)          | IF `[D0:1]` = `0000`, Standby; IF `[D0:1]` = `50C3`, Active (SRB); IF `[D0:1]` = `B888`, Active (XRB) / `D[5:4]` = INT16 |
| 0x33449 |   BTY   |  8  |   250 ms  | State of Charge             | `[D4]` = Percentage; `[D1:0]` = Numerator; `[D3:2]` = Denominator; IF `[D6]` == `05`, Normal; IF `[D6]` = `03`, Charged Previously |




* Amperages (mA) are represented with a positive number for charge current, and a negative for discharge current.
