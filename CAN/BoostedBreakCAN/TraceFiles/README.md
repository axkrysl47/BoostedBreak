### Trace Files should be created in this directory.
#### PCAN Trace File Example
From the [PEAK CAN TRC File Format Specification](https://www.peak-system.com/produktcd/Pdf/English/PEAK_CAN_TRC_File_Format.pdf): 
```
;##########################################################################
; C:\TraceFile.trc
;
; CAN activities recorded by PCAN Explorer
; Start time: 11.09.2002 16:00:20.682
; PCAN-Net: PCI1
;
; Columns description:
; ~~~~~~~~~~~~~~~~~~~~~
; +-current number in actual sample
; | +time offset of message (ms)
; | | +ID of message (hex)
; | | | +data length code
; | | | | +data bytes (hex) ...
; | | | | |
;----+- ---+--- ----+--- + -+ -- -- ...
 1) 1841 0001 8 00 00 00 00 00 00 00 00
 2) 1842 0008 4 ERROR 00 19 08 08
 3) 1843 FFFFFFFF 4 00 00 00 04 -- -- -- -- BUSLIGHT
 4) 1844 0100 3 RTR
 ```
 
