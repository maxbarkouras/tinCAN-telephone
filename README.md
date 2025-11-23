# tinCAN-telephone
Remotely send and receive CAN messages over WiFi.

**Hardware Requirements:**
- ESP32 (TWAI enabled)
- CAN Transceiver (CAN FD not currently suppported)
  
**For OBD connections, you must also include:**
  - Converter (buck/linear; minimum 12V at 1A)
  - OBD2 Breakout Cable


**Very rought wiring example using ESP32 Wroom, SN65HVD230, and LM2596:**
![Drawing](https://github.com/user-attachments/assets/0d26ffbe-fc6c-458e-8f4b-40c9e4c3c759)
