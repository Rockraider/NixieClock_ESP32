# NixieClock_ESP32
Nixie Clock with ESP32 for NTP time

## CAUTION - DANGER!
Do not touch the PCB if it is connected to a power source. Input voltage gets transformed to 170V DC!!

Always use with housing and keep away from children!

## Nixie Tubes:
IN-14 Nixie tubes are used with SN74141 drivers. Nixies need high voltage so NCH8200HV is used as DC-DC converter.

## Brain
The brain is a ESP32 (NodeMCU-32SLUA) which is stacked on bottom side for easy outside flashing.
It connects to wifi and synchronizes the time via NTP. You might have to edit the time zone.
Daylight Saving Time is recognized.

## Flashing
Flashing is simple on NodeMCU-32SLUA with onboard USB. Plug it in, open project with Arduino IDE. Enter your Wifi SSID and password and upload.
For your own safety do not flash while stacked to the PCB!

Note: The PCB onboard Micro-USB is only used for powering the device, flashing is not possible.

## Power Supply
5V Power supply is needed.

A common (phone) USB charger could be used to power the device. Connector is a Micro-USB. 

For battery powered see optional features.

## Housing
I designed a simple 3D-printable housing, where the PCB could be attached inside.

Get it on thingiverse: https://www.thingiverse.com/thing:5441650

## Optional features

### USB out
There is a optional USB-A output which is just a passthrough of the input. 

You could use it to power another device, if your supply is powerful enough.

### WS2812B
There are pads under the tube sockets to put on WS2812B LEDs for coloring the tubes. 

I didn't used them, cause the tubes had a nice blue flair itself. 
Feature is untested.

### Battery supply
If you want to power the device without the Micro-USB connector you could use the "H1" 2x1 header.
It's directly connected to Vcc and GND similar to the power connector.

### Additional IOs
Got your own idea to extend functionality? Do you want to use it as alarm clock and attach a bell or something fancy?
There is a 3x2 header "J1" which containes Vcc, GND and two IOs connected to NodeMcu Pins P32/33.
