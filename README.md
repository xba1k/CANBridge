# CANBridge

## Overview

CANBridge is an Arduino microcontroller project that provides an easy mechanism to relay CAN messages from a variety of devices to a regular wifi network where messages can be inspected and processed.
CANBridge can be used as a development platform when troubleshooting CAN devices, writing frame parsers, or as a way to bridge one or multiple CAN networks for monitoring or alerting systems. Target audience is EV, IoT and renewable energy enthusiasts.

## Setup

This code was created using Eclipse IDE with Arduino plugin. It can also be used with the classic Arduino IDE by concatenating all project files together into a single .ino file.
CAN-BUS Shield library from arduino.cc was used for the integration with MCP2515.

See settings.h for wifi credentials and various other parameters.

Once deployed, frames can be received using tcpdump as demonstrated below, or using a dedicated application such as [can_frame_decoder_c](https://github.com/xba1k/can_frame_decoder_c), [can_frame_decoder_java](https://github.com/xba1k/can_frame_decoder_java) or  [can_frame_decoder_python](https://github.com/xba1k/can_frame_decoder_python)

When flashing Nano power and/or serial lines to ESP should be disconnected so there is no concurrent access to the Serial. Also MCP library tries to print some messages during initialization, they will error out in ESP but don't seem to confuse it. 

# Hardware

CANBridge targets Arduino Mega and Nano boards. Mega should be used for development due to the convenience of multiple Serial interfaces. ESP8266 and MCP2515 communication modules are required. ESP8266 with firmware version 1.5.4 (pretty old) was tested.

Mega Pinouts:

D21 -> MCP INT (optional)  
D52 -> MCP SCK  
D51 -> MCP SI  
D50 -> MCP SO  
D53 -> MCP CS  
  
D19 -> ESP TX  
D18 -> ESP RX  
  
Nano Pinouts:  
D02 -> MCP INT (optional)  
D13 -> MCP SCK  
D11 -> MCP SI  
D12 -> MCP SO  
D10 -> MCP CS  
  
D01 -> ESP TX  
D00 -> ESP RX  

## Demo

```
sudo tcpdump -n -A ip and udp and port 1080
tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
listening on enp0s25, link-type EN10MB (Ethernet), capture size 262144 bytes
18:13:51.615861 IP 192.168.1.61.43074 > 255.255.255.255.1080: UDP, length 12
E..(.a....w....=.....B.8..<._...Li............
18:13:52.222907 IP 192.168.1.61.43074 > 255.255.255.255.1080: UDP, length 12
E..(.b....w~...=.....B.8..JZQ...>.,...........
18:13:52.824926 IP 192.168.1.61.43074 > 255.255.255.255.1080: UDP, length 10
E..&.c....w....=.....B.8..cEU...U.P.4!........
18:14:02.128789 IP 192.168.1.61.43074 > 255.255.255.255.1080: UDP, length 12
E..(.d....w|...=.....B.8....^...SIConfig......
18:14:02.737450 IP 192.168.1.61.43074 > 255.255.255.255.1080: UDP, length 12
E..(.e....w{...=.....B.8..<._...Li............
18:14:03.341260 IP 192.168.1.61.43074 > 255.255.255.255.1080: UDP, length 10
E..&.f....w|...=.....B.8..cEU...U.P.4!........
```
