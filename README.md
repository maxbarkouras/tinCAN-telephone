# tinCAN-telephone
Remotely send and receive CAN messages over WiFi.

All hardware companents required can be found below, and custom PCB KiCAD files are in /pcb-designs. If you would like to print the custom board, you can do so with an online service like JLCPCB or by contacting a local fab company.

**Hardware Requirements:**
- ESP32 (TWAI enabled)
- CAN Transceiver (CAN FD not currently suppported)
  
**For OBD connections, you must also include:**
  - Converter (buck/linear; minimum 12V at 1A)
  - OBD2 Breakout Cable


**VERY rough wiring example using ESP32 Wroom, SN65HVD230, and LM2596:**
![Drawing](https://github.com/user-attachments/assets/0d26ffbe-fc6c-458e-8f4b-40c9e4c3c759)
