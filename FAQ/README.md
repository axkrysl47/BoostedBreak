# __BoostedBreak Frequently Asked Questions__ (Work In Progress!)
## Overview
The following is a list of commonly asked questions & answers as found in the Boosted Board community.

The majority of from this list is a form of redundancy from Mario Parra's website Forever Boosted, which is an excellent resource on all things Boosted. 

## Please check out [Forever Boosted, here](https://foreverboosted.co/)!

# Table of Contents
* [Basic Information](#basic-information)
* [Technical Information](#technical-information)
* [Parts Information](#parts-information)

## Basic Information

### What is a personal light electric vehicle?
A personal electric vehicle (also known as personal transporter, powered transporter, electric rideable, personal mobility device, etc.) is any of a class of compact, mostly recent (21st century), motorised micromobility vehicle for transporting a single individual. They include electric skateboards, kick scooters, self-balancing unicycles and Segways. Many newer versions use recent advances in vehicle battery and electric motor-control technologies. 

### What is an electric skateboard/longboard?
An electric skateboard/longboard is a personal electric vehicle that comes in the form factor of a skateboard or longboard. Generally, all electric skateboards/longboards consist of all the basic components of a skateboard/longboard (deck, trucks, wheels, etc.), plus a battery, a motor driver, motors, and more. Typically, an electric skateboard/longboard rider controls acceleration & deceleration with a throttle on a wireless remote, and makes turns in the same manner as traditional skateboards/longboards. 

### What is/was Boosted?
Boosted (formerly Boosted Boards) was an American manufacturer of electric skateboards and electric scooters based in Mountain View, California. Boosted was founded in mid-2012 with financial backing by StartX by former Stanford University students Sanjay Dastoor, John Ulmen, and Matthew Tran. Boosted was widely recognized for popularizing the electric longboard, launching from an extraordinarily successful Kickstarter campaign.

### What is a Boosted Board?
A Boosted Board is an electrically motorized longboard or skateboard that was designed and manufactured by the now defunct company Boosted, Inc. Boosted created several different models of electric longboards, a list which can be found below.

* _First generation (V1)_
  * __Boosted Single, Boosted Dual (V1), Boosted Dual+ (V1)__
* _Second generation (V2)_
  * __Boosted Dual (V2), Boosted Dual+ (V2)__
* _Third generation (V3)_
  * __Boosted Mini S, Boosted Mini X, Boosted Plus, Boosted Stealth__

### What is the Boosted Rev / Scooter?
A Boosted Rev is an electrically motorized scooter that was designed and manufactured by the now defunct company Boosted, Inc. Boosted created only one electric scooter model called the __Boosted Rev__.

### What is an electric skateboard/longboard ESC / Motor Driver?
In general, the terms Motor driver (MD), motor controller, electronic speed controller (ESC), are all aliases for an embedded system that controls motors. On all Boosted Boards, the ESC is secured under the deck in front of the motors. If you would like to know more about Boosted Board ESCs, check out the [BoostedBreakESC folder]().

### What is an electric skateboard/longboard battery?
In general, an electric skateboard/longboard battery is a relatively high capacity (typically 100 to 1000 Watt-hours), high discharge (typically 20 - 100 amperes) designed for use in electric skateboard/longboard applications. Typically, electric skateboard/longboard batteries also consist of embedded systems that control charging, monitor discharging, perform cell balancing, and more. On all Boosted Boards, the battery is secured under the deck behind the front trucks. If you would like to know more about Boosted Board batteries, check out the [BoostedBreakBTY folder]().

### What is an electric skateboard/longboard remote?
In general, an electric skateboard/longboard remote is a wireless remote that provides a throttle for riders of electric longboards. Typically, the remote also gives riders basic information about the state of the electric skateboard/longboard, including state of charge, current speed mode, and more. If you would like to know more about Boosted Board remotes, check out the [BoostedBreakREM folder]().

## Technical Information

### What is battery cell balancing?
Battery cell balancing is the act of charging/discharging individual cells in a multi-series-cell battery such that all the cells are at a similar voltage. Put simply, individual cells in a battery need to be safely kept in a specific voltage range - battery cell balancing ensures this safety with the maximum margin of error.

In concept, a Boosted board battery is a high-voltage battery, created by 'stacking up' several 'normal' voltage identical lithium ion cells. (For example, the SRB is made up of 12 separate cells in series.) Despite an engineer's best efforts, each cell discharges slightly differently depending on differences in manufacturing and how the battery itself is assembled. 

When a multi-series-celled battery is charged & discharged several times over, those slight differences in discharge rate compound over time; as such, the difference between the highest cell's voltage and lowest cell's voltage can grow over time. This difference is often referred to as the 'voltage delta'.

General charging is the process of charging the battery as a whole to a specified voltage level. (In our SRB example, this voltage is 12 times an individual cell's charged voltage, as we have 12 cells in series.) What is important to note is the fact that the individual cells need not be at the same voltage/charge level in this case. 

(For example, let us consider a small 2 cell-in-series battery. Further, let us say a single cell is charged to 4 volts, so our 2 cell battery is fully charged when it is at 8 volts. While we may see 8 volts at the main terminals of our battery, the individual cells could be at 4 volts apiece (zero voltage delta), or they could be a 3 and 5 volts (2 volt delta), or they could be a 0 volts and 8 volts (8 volt delta, not good!). This information simply cannot be determined looking at the main terminals of our battery alone.)

By contrast, battery balancing is the process of ensuring that all 12 cells are individually charged to their specific charged voltage.

Individual cell voltage monitoring is paramount for multi-series-cell battery safety. Each individual lithium ion cell needs to be kept in a specific voltage range: too low and the cell begins to degrade very quickly, too high, and the cell can catch fire and explode. This is why individual cell monitoring is necessary.

Battery cell balancing takes cell monitoring a step further by eliminating the voltage delta, thereby mitigating the risk of cell explosion or degradation via high cell voltage delta. A battery with near-zero voltage delta requires the maximum amount of charge & discharge cycles (in other words, the maximum amount of time for cell differences to compound) before the it is back under the severe risk of cell explosion or degradation. 

### What is Controller Area Network (CAN bus)?
CAN bus is a message-based serial communications protocol typically used in embedded systems where there are several nodes that all must communicate with one another (also known as a multiplex system). Using CAN bus in this design scenario generally simplifies on electrical wiring, message prioritization, and error handling. 

In the context of Boosted Boards, CAN is used for communications between the ESC and battery, as well as the ESC and the accessory port. If you would like to know more about Boosted Board batteries, check out the [BoostedBreakCAN folder](https://github.com/axkrysl47/BoostedBreak/tree/main/CAN).

## Parts Information

### Does Boosted use different ESCs?
From Forever Boosted:
> All Boosted boards, except for the v1, use the same ESC printed circuit board, which is interchangeable across all v3/v2 boards. The speed modes are determined by the firmware. NOTE: While the longboard ESCs will technically work on the Mini boards, they use a different enclosure, so they are not a direct swap.

### What motors did Boosted use and are they interchangeable?
From Forever Boosted:
> The V2 & V3 boards use brushless 5035 192kv motors with custom Hall effect sensors and a 17T motor pulley (the V1 motor has a 14T pulley). They are interchangeable between both sides of the board (left and right) and between V2 and all V3 boards (Stealth, Plus, and Mini).

The T2 motor that came with V2 and most V3 boards has been known to have motor shaft failures. The later T3 motor was manufactured to resolve the issue.

### What battery cells did Boosted use, and are they interchangeable?
From Forever Boosted:
> The standard range (SRB) battery uses A123 26650 LiFePO4 cells in a 12S1P configuration (12 cells total) and the extended range (XRB) battery uses LG HG2 18650 Lithium Ion cells in a 13S2P configuration (26 cells total).

> All standard range batteries across all V2 & V3 boards are the same. Likewise, all extended range batteries across all V2 & V3 boards are the same. This means that the standard range battery works on all V2 & V3 boards while the extended range battery can be installed on all V2 & V3 boards, except for the Mini S as it does not fit on the deck due to the motor driver placement. The V1 battery was not designed to be removeable or swappable. NOTE: Older V2 boards need to be manually updated to ESC firmware v2.1.9 or later to work with an extended range battery.

### What charger did Boosted use, and are they interchangeable?
V2 & V3 chargers are 13S (54.4V, 2A) chargers.

From Forever Boosted:
> The V1 charger can also charge a standard range battery, but cannot charge an extended range battery; the V2 & V3 charger can charge all Boosted batteries.

### What belts did Boosted use?
From Forever Boosted:
> V2 & V3 boards use custom Gates 225-15-3m belts lined with felt to reduce noise. V1 boards use 219-15-3m. (Belts follow the naming convention of length-width-tooth pitch)

### What decks did Boosted use, and what are their weight limits?
From Forever Boosted:
> The V3 longboards (Stealth/Plus) use a slightly stiffer 38" (L)/11.3" (W) composite deck and the Mini (X/S) boards use a "Deep Dish" 29.5" (L)/11" (W) composite deck. Both have a poplar spine wrapped in triaxial fibreglass and edges reinforced with a polymer sidewall. The longboard deck also contains vibration-dampending foam.
>
> The V1 & V2 boards use a custom Loaded Flex 3 Vanguard (38"/98cm) deck, which is intended for speeds between 0 and 25 mph (0-40km/h). Due to the flexibility, they were not intended for higher speeds.
>
> All decks are rated for use by riders up to 250 lbs (113 kg).

### What trucks did Boosted use, and can I use third party trucks?
From Forever Boosted:
> The V2 & V3 boards use custom 190mm (hangar width)/50° (baseplate angle) trucks with a rakeless hangar while the V1 uses 50° Caliber IIs. “Rakeless” denotes that the hanger can face either direction, but for visual reasons, it is installed with the circle facing down. The V2 trucks were cast while the V3 trucks were forged.

> You can use a 180mm/50° truck on the front, such as a Paris truck from Loaded boards, but the rear truck assembly uses Boosted’s custom motor mounts. 180mm is the closest size as 190mm is not a common longboard truck width. You can also use a third-party baseplate with the V2 & V3 rear truck, such as a 50° Caliber baseplate to match the front.

### What wheels did Boosted use?
From Forever Boosted:
> * __Boosted Single, Boosted Dual (V1), Boosted Dual+ (V1)__
>   * Orangatang 75mm/80a In Heat wheels (orange) with custom drilled pulleys
> * __Boosted Dual (V2), Boosted Dual+ (V2)__
>   * Orangatang 80mm/80a Kegel wheels (orange)
> * __Boosted Mini S__
>   * Boosted 80mm/78a Lunar wheels (orange)
> * __Boosted Mini X__
>   * Boosted 80mm/78a Lunar wheels (grey)
> * __Boosted Plus__
>   * Boosted 85mm/78a Stratus wheels (orange)
> * __Boosted Stealth__
>   * Boosted 85mm/78a Stratus wheels (grey)

Boosted also released the Boosted 105mm/72a '105s' (black/multi-color) which were only sold separately, not standard with any given board.

### What pulleys did Boosted use?
From Forever Boosted:
> V1 Boards used custom aluminum 50T pulleys that came standard with the Orangatang In Heat wheels.

> Most V2/V3 Boards used a plastic 56T pulley that was compatible with all kegel cores.

The Boosted Stealth and Boosted 105s came with a similar plastic 56T pulley, compatible with all kegel cores, but had metal teeth instead of plastic.

### What hardware did Boosted use?
From Forever Boosted:
> Battery: The battery screws are M6 x 12mm (diameter)/20mm (length), which are 90° countersunk and take a 4mm Allen wrench.
>
> ESC/Motor Driver: The motor driver wing plate screws are M6 x 12mm (diameter)/18mm (length), which are 90° countersunk and take a 4mm Allen wrench.
>
> Motor Caps (Belt Covers): The socket cap screws for the motor cap are M4 x 0.7mm (thread pitch)/10mm (length), which take a 3mm Allen wrench (the v1 socket cap screws take a 9/64" Allen wrench). 
> 
> Skid Plates: The skid plate screws are M4 x 0.7mm (thread pitch)/6mm (length), which take a 3mm Allen wrench. 
> 
> Belt Tensioning Screws: The belt tensioning screws on the motor mounts are M4 x 0.7mm (thread pitch)/6mm (length) and take a 3mm Allen wrench. 
> 
> Truck Hardware: The stock truck hardware on boards with a standard range battery is 1.25” (length) and on extended range boards, it's 1.5” (length). 
> 
> Truck Mounting Nuts: The truck mounting nuts are standard skateboard/longbord truck mounting nuts, which #10-32 (diameter - thread count) and take a 3/8" wrench. 
> 
> Truck Kingpin Nuts: The truck mounting nuts are standard skateboard/longbord truck mounting nuts, which are 3/8"-24 (diameter - thread count) and take a 9/16" wrench. 
> 
> Wheel Pulley Bearings: The V2 & V3 pulleys use 6903-2RS bearings on the inside; the V1 uses 6804-2RS. 
> 
> Wheel Pulley Washers: The big silver wheel/drive pulley washers on v3/v2 trucks are 18.25mm (approximate inside diameter) x 25mm (outside diameter) x 0.5mm (thickness). 
> 
> Long Axle Spacers (only used on V1 & V2 trucks): The long cylindrical axle spacers are 8mm x 19mm (length).
> 
> Wheel Bearings: The wheels use standard 10.29mm (0.405", width) skateboard/longboard bearings for 8mm axles, however, the rear wheels cannot use bearings with built-in spacers on the inside, such as Zealous. Other options, such as Bones Reds, don't have built-in spacers.
> 
> Bearing Spacers (only used on front wheels): The bearing spacers are 8mm x 10mm (made for 8mm axles), which are commonly used on skateboards/longboards. 
> 
> Speed Rings: The speed rings sit on the inside and outside of the front wheel bearings, but only on the outside of the rear wheel bearings. They are standard skateboard/longboard speed rings. 
> 
> Axle Nuts: The axle/wheel nuts are standard skateboard/longbord axle nuts, which are 5/16"-24 (diameter - thread count) and take a 1/2" wrench. 
