# tinCAN-telephone
**Getting Started:**

The tinCAN telephone project allows for the remote sending and receiving of CAN messages over WiFi. It allows for a plug-and-play solution to be dropped into any CAN network, or through OBD2, and easily allow external communication over the device's WiFi access point. Once connected to the tinCAN WiFi network, you can navigate to the gateway *192.168.1.1* to send messages to the network and monitor/recieve all incoming traffic. On the PCB designed for the project, the blue LED will blink on successful send and red LED will blink on successful recieve; the LED specification in the firmware will most likely have to be changed depending on the MCU you choose to use. 

You can also use the alternative firmware package to connect to an existing WiFi network and have the device act as a client, with the web interface being reachable via the devices IP address (output over serial or check routers arp table). This may be more practical in stable lab environments or if you want to chain multiple tinCANs together; one device being the host and the rest being clients, each with their own accessible web portal.

Automation and custom scripting is also very easy to develop for this enviornment, as a simple POST request can be used to send a message. Any request sent to ***interface_ip*/set** with the data of *'id'* (CAN ID) and *'msg'* (8 byte CAN frame) specified, will be transmitted through the CAN network.

All hardware companents required can be found below, and custom PCB KiCAD files are in */pcb-designs*. If you would like to print the custom board, you can do so with an online service like JLCPCB or by contacting a local fab company.

See your specific MCU/ESPs documentation on flashing the device.

**Firmware Requirements:** 
- Firmware can utilize *any* two undefined GPIO pins on your MCU for sending/recieving data to/from the transceiver; 21 and 22 are used in my code.
- Ensure you change WiFi password *before* testing to ≥ 8 characters as per WPA standard.

**Hardware Requirements:**
- ESP32 (TWAI enabled)
- CAN Transceiver (CAN FD not currently suppported)
  
**For OBD connections, you must also include:**
  - Converter (buck/linear; minimum 12V at 1A)
  - OBD2 Breakout Cable


**VERY rough wiring example using ESP32 Wroom, SN65HVD230, and LM2596:**
![Drawing](https://github.com/user-attachments/assets/0d26ffbe-fc6c-458e-8f4b-40c9e4c3c759)
