# __BoostedBreak Frequently Asked Questions__ (Work In Progress!)
## Overview
The following is a list of commonly asked questions & answers as found in the Boosted Board community.

The majority of from this list is a form of redundancy from Mario Parra's website Forever Boosted, which is an excellent resource on all things Boosted. 

## Please check out [Forever Boosted, here](https://foreverboosted.co/)!

# Table of Contents
* [Basic Information](#basic-information)
* [Technical Information](#technical-information)

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
