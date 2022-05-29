# __BoostedBreak Frequently Asked Questions__ (Work In Progress!)
## 1. Overview
The following is a list of commonly asked questions & answers as found in the Boosted Board community.

The majority of from this list is a form of redundancy from Mario Parra's website Forever Boosted, which is an excellent resource on all things Boosted. 

### Please check out [Forever Boosted, here](https://foreverboosted.co/)!

# Table of Contents
1. [Overview](#1-overview)
   1. [Link to Forever Boosted](#please-check-out-forever-boosted-here)
3. [Basic Information](#2-basic-information)
   1. [What is a personal light electric vehicle?](#1-what-is-a-personal-light-electric-vehicle)
   2. [What is an electric skateboard/longboard?](#2-what-is-an-electric-skateboardlongboard)
   3. [What is/was Boosted?](#3-what-iswas-boosted)
   4. [What is a Boosted Board?](#4-what-is-a-boosted-board)
   5. [What is the Boosted Rev / Scooter?](#5-what-is-the-boosted-rev--scooter)
   6. [What is an electric skateboard/longboard ESC / Motor Driver?](#6-what-is-an-electric-skateboardlongboard-esc--motor-driver)
   7. [What is an electric skateboard/longboard battery?](#7-what-is-an-electric-skateboardlongboard-battery)
   8. [What is an electric skateboard/longboard remote?](#8-what-is-an-electric-skateboardlongboard-remote)
4. [Technical Information](#3-technical-information)
   1. [What is battery cell balancing?](#1-what-is-battery-cell-balancing)
   2. [What is Controller Area Network (CAN bus)?](#2-what-is-controller-area-network-can-bus)
5. [Parts Information](#4-parts-information)
   1. [Does Boosted use different ESCs?](#1-does-boosted-use-different-escs)
   2. [What motors did Boosted use, and are they interchangeable?](#2-what-motors-did-boosted-use-and-are-they-interchangeable)
   3. [What battery cells did Boosted use, and are they interchangeable?](#3-what-battery-cells-did-boosted-use-and-are-they-interchangeable)
   4. [What charger did Boosted use, and are they interchangeable?](#4-what-charger-did-boosted-use-and-are-they-interchangeable)
   5. [What belts did Boosted use?](#5-what-belts-did-boosted-use)
   6. [What decks did Boosted use, and what are their weight limits?](#6-what-decks-did-boosted-use-and-what-are-their-weight-limits)
   7. [What trucks did Boosted use, and can I use third party trucks?](#7-what-trucks-did-boosted-use-and-can-i-use-third-party-trucks)
   8. [What wheels did Boosted use?](#8-what-wheels-did-boosted-use)
   9. [What pulleys did Boosted use?](#9-what-pulleys-did-boosted-use)
   10. [What hardware did Boosted use?](#10-what-hardware-did-boosted-use)

## 2. Basic Information

### 1. What is a personal light electric vehicle?
A personal electric vehicle (also known as personal transporter, powered transporter, electric rideable, personal mobility device, etc.) is any of a class of compact, mostly recent (21st century), motorised micromobility vehicle for transporting a single individual. They include electric skateboards, kick scooters, self-balancing unicycles and Segways. Many newer versions use recent advances in vehicle battery and electric motor-control technologies. 

### 2. What is an electric skateboard/longboard?
An electric skateboard/longboard is a personal electric vehicle that comes in the form factor of a skateboard or longboard. Generally, all electric skateboards/longboards consist of all the basic components of a skateboard/longboard (deck, trucks, wheels, etc.), plus a battery, a motor driver, motors, and more. Typically, an electric skateboard/longboard rider controls acceleration & deceleration with a throttle on a wireless remote, and makes turns in the same manner as traditional skateboards/longboards. 

### 3. What is/was Boosted?
Boosted (formerly Boosted Boards) was an American manufacturer of electric skateboards and electric scooters based in Mountain View, California. Boosted was founded in mid-2012 with financial backing by StartX by former Stanford University students Sanjay Dastoor, John Ulmen, and Matthew Tran. Boosted was widely recognized for popularizing the electric longboard, launching from an extraordinarily successful Kickstarter campaign.

### 4. What is a Boosted Board?
A Boosted Board is an electrically motorized longboard or skateboard that was designed and manufactured by the now defunct company Boosted, Inc. Boosted created several different models of electric longboards, a list which can be found below.

* _First generation_ (V1)
  * __Boosted Single__
  * __Boosted Dual (V1)__
  * __Boosted Dual+ (V1)__
* _Second generation_ (V2)
  * __Boosted Dual (V2)__
  * __Boosted Dual+ (V2)__
* _Third generation_ (V3)
  * __Boosted Mini S__
  * __Boosted Mini X__
  * __Boosted Plus__
  * __Boosted Stealth__

### 5. What is the Boosted Rev / Scooter?
A __Boosted Rev__ is an electrically motorized scooter that was designed and manufactured by the now defunct company Boosted, Inc. Boosted created only one electric scooter model before the company ended operations.

### 6. What is an electric skateboard/longboard ESC / Motor Driver?
In general, the terms motor driver (MD), motor controller, electronic speed controller (ESC), are all aliases for an embedded system that controls motors. On all Boosted Boards, the ESC is secured under the deck in front of the motors. If you would like to know more about Boosted Board ESCs, check out the [BoostedBreakESC folder]().

### 7. What is an electric skateboard/longboard battery?
In general, an electric skateboard/longboard battery is a relatively high capacity (typically 100 to 1000 Watt-hours), high discharge (typically 20 - 100 amperes) designed for use in electric skateboard/longboard applications. Typically, electric skateboard/longboard batteries also consist of embedded systems that control charging, monitor discharging, perform cell balancing, and more. On all Boosted Boards, the battery is secured under the deck behind the front trucks. If you would like to know more about Boosted Board batteries, check out the [BoostedBreakBTY folder]().

### 8. What is an electric skateboard/longboard remote?
In general, an electric skateboard/longboard remote is a wireless remote that provides a throttle for riders of electric longboards. Typically, the remote also gives riders basic information about the state of the electric skateboard/longboard, including state of charge, current speed mode, and more. If you would like to know more about Boosted Board remotes, check out the [BoostedBreakREM folder]().

## 3. Technical Information

### 1. What is battery cell balancing?
Battery cell balancing is the act of charging/discharging individual cells in a multi-series-cell battery such that all the cells are at a similar voltage. Put simply, individual cells in a battery need to be safely kept in a specific voltage range - battery cell balancing ensures this safety with the maximum margin of error.

In concept, a Boosted board battery is a high-voltage battery, created by 'stacking up' several 'normal' voltage identical lithium ion cells. (For example, the SRB is made up of 12 separate cells in series.) Despite an engineer's best efforts, each cell discharges slightly differently depending on differences in manufacturing and how the battery itself is assembled. 

When a multi-series-celled battery is charged & discharged several times over, those slight differences in discharge rate compound over time; as such, the difference between the highest cell's voltage and lowest cell's voltage can grow over time. This difference is often referred to as the 'voltage delta'.

General charging is the process of charging the battery as a whole to a specified voltage level. (In our SRB example, this voltage is 12 times an individual cell's charged voltage, as we have 12 cells in series.) What is important to note is the fact that the individual cells need not be at the same voltage/charge level in this case. 

(For example, let us consider a small 2 cell-in-series battery. Further, let us say a single cell is charged to 4 volts, so our 2 cell battery is fully charged when it is at 8 volts. While we may see 8 volts at the main terminals of our battery, the individual cells could be at 4 volts apiece (zero voltage delta), or they could be a 3 and 5 volts (2 volt delta), or they could be a 0 volts and 8 volts (8 volt delta, not good!). This information simply cannot be determined looking at the main terminals of our battery alone.)

By contrast, battery balancing is the process of ensuring that all 12 cells are individually charged to their specific charged voltage.

Individual cell voltage monitoring is extremely important for multi-series-cell battery safety. Each individual lithium ion cell needs to be kept in a specific voltage range: too low and the cell begins to degrade very quickly, too high, and the cell can catch fire and explode. This is why individual cell monitoring is necessary.

Battery cell balancing takes cell monitoring a step further by eliminating the voltage delta, thereby mitigating the risk of cell explosion or degradation via high cell voltage delta. A battery with near-zero voltage delta requires the maximum amount of charge & discharge cycles (in other words, the maximum amount of time for cell differences to compound) before the it is back under the severe risk of cell explosion or degradation. 

As such, battery cell balancing is paramount to maintain the safety of a multi-cell-battery.

### 2. What is Controller Area Network (CAN) bus?
CAN bus is a message-based serial communications protocol typically used in embedded systems where there are several nodes that all must communicate with one another (also known as a multiplex system). Using CAN bus in this design scenario generally simplifies on electrical wiring, message prioritization, and error handling. 

In the context of Boosted Boards, CAN is used for communications between the ESC and battery, as well as the ESC and the accessory port. The choice to use CAN infers that one day Boosted was interested in creating a multi-ESC, all wheel drive electric longboard (thereby a multiplex embedded system). If you would like to know more about Boosted Board batteries, check out the [BoostedBreakCAN folder](https://github.com/axkrysl47/BoostedBreak/tree/main/CAN).

## 4. Parts Information

### 1. Does Boosted use different ESCs?
From Forever Boosted:
> All Boosted boards, except for the V1, use the same ESC printed circuit board, which is interchangeable across all V2 & V3 boards. The speed modes are determined by the firmware. NOTE: While the longboard ESCs will technically work on the Mini boards, they use a different enclosure, so they are not a direct swap.

The V1 was originally designed with single & dual motors in mind. A V1 Dual ESC will look like two ESCs, each on their own half of the whole printed circuit board.

With the release of the V2, Boosted went away with single motor electric longboards, and as such consolidated their ESC design with a single dsPIC microcontroller for both motors. The original V2 was likely over-engineered for the rated amperages/power of the V2 boards; when it came time to release the V3 boards, raising the software limits on the same ESC design for the Boosted Stealth was both safe and cost-effective for Boosted.

### 2. What motors did Boosted use, and are they interchangeable?
From Forever Boosted:

The V1 boards use standard sensorless (I think) brushless 5035 192KV motors with 14T motor pulleys.
> The V2 & V3 boards use brushless 5035 192KV motors with custom Hall effect sensors and a 17T motor pulley. They are interchangeable between both sides of the board (left and right) and between V2 and all V3 boards (Stealth, Plus, and Mini).

The T2 motor that came with V2 and most V3 boards has been known to have motor shaft failures. The later T3 motor was manufactured to resolve the issue.

I believe the choice to use 5035 motors was made such that 1) the trucks could be very similar to standard width, and 2) the smaller size more comfortably fits under the deck, leading to a sleeker, more conventional & attractive longboard design. 

### 3. What battery cells did Boosted use, and are they interchangeable?
From Forever Boosted:
> The standard range (SRB) battery uses A123 26650 LiFePO4 cells in a 12S1P configuration (12 cells total) and the extended range (XRB) battery uses LG HG2 18650 Lithium Ion cells in a 13S2P configuration (26 cells total).

The A123 cell for the SRB was a very reasonable choice. LiFePO4 cells are generally more stable than their Li-ion cell counterparts, leading to less-likely-to-explode battery. Furthermore, the A123 has a highly rated discharge rate of 50 amperes, making a 12S A123 battery have a nominal power rating of 1980 watts. The only downside is that the energy rating of the SRB was under 100 watt-hours, which meant the range was at most a handful of miles.

Th HG2 cell for the XRB was chosen to resolve the energy downside of the SRB. With the XRB, Boosted moved to the more popular Li-ion cell, and one with a rated continuous discharge rate of only 20 amperes. The power rating of a 13S2P HG2 battery only got up to 1872 watts, notably lower than the SRB. I suspect that Boosted went over that power specification, especially with hyper mode on the Boosted Stealth. Perhaps to compensate for this, the energy rating of the XRB is under specification, rated at 199 watt-hours, which is still double the SRB's energy rating.

> All standard range batteries across all V2 & V3 boards are the same. Likewise, all extended range batteries across all V2 & V3 boards are the same. This means that the standard range battery works on all V2 & V3 boards while the extended range battery can be installed on all V2 & V3 boards, except for the Mini S as it does not fit on the deck due to the motor driver placement. The V1 battery was not designed to be removeable or swappable. NOTE: Older V2 boards need to be manually updated to ESC firmware v2.1.9 or later to work with an extended range battery.

### 4. What charger did Boosted use, and are they interchangeable?
V2 & V3 chargers are 13S (54.4V, 2A) chargers.

From Forever Boosted:
> The V1 charger can also charge a standard range battery, but cannot charge an extended range battery; the V2 & V3 charger can charge all Boosted batteries.

### 5. What belts did Boosted use?
From Forever Boosted:
> V2 & V3 boards use custom Gates 225-15-3m belts lined with felt to reduce noise. V1 boards use 219-15-3m. (Belts follow the naming convention of length-width-tooth pitch)

### 6. What decks did Boosted use, and what are their weight limits?
From Forever Boosted:
> The V3 longboards (Stealth/Plus) use a slightly stiffer 38" (L)/11.3" (W) composite deck and the Mini (X/S) boards use a "Deep Dish" 29.5" (L)/11" (W) composite deck. Both have a poplar spine wrapped in triaxial fibreglass and edges reinforced with a polymer sidewall. The longboard deck also contains vibration-dampending foam.
>
> The V1 & V2 boards use a custom Loaded Flex 3 Vanguard (38"/98cm) deck, which is intended for speeds between 0 and 25 mph (0-40km/h). Due to the flexibility, they were not intended for higher speeds.
>
> All decks are rated for use by riders up to 250 lbs (113 kg).

### 7. What trucks did Boosted use, and can I use third party trucks?
From Forever Boosted:
> The V2 & V3 boards use custom 190mm (hangar width)/50° (baseplate angle) trucks with a rakeless hangar while the V1 uses 50° Caliber IIs. “Rakeless” denotes that the hanger can face either direction, but for visual reasons, it is installed with the circle facing down. The V2 trucks were cast while the V3 trucks were forged.

> You can use a 180mm/50° truck on the front, such as a Paris truck from Loaded boards, but the rear truck assembly uses Boosted’s custom motor mounts. 180mm is the closest size as 190mm is not a common longboard truck width. You can also use a third-party baseplate with the V2 & V3 rear truck, such as a 50° Caliber baseplate to match the front.

### 8. What wheels did Boosted use?
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

Boosted also released the Boosted 105mm/72a '105s' wheels (black/multi-color) which were only sold separately, not standard with any given board.

### 9. What pulleys did Boosted use?
From Forever Boosted:
> V1 Boards used custom aluminum 50T pulleys that came standard with the Orangatang In Heat wheels.

> Most V2/V3 Boards used a plastic 56T pulley that was compatible with all kegel cores.

The Boosted Stealth and Boosted 105s came with a similar plastic 56T pulley, compatible with all kegel cores, but had metal teeth instead of plastic.

### 10. What hardware did Boosted use?
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
