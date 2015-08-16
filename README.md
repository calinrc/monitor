# monitor
=====

Description:
------------
Simple home monitor system based on two Arduino (Pro mini),  three PIR sensonrs, one wireles transmitter , one receiver, one RPI board (version B) and one USB GSM/GPRS dongle.

Version
-----------

0.0.1  

Notes:
-----

The project is in early stages but is functional.

The project structure is the following:

- The three pir sensors are connected to one arduino (Pro mini) along with wifi transmitter.
- The second Arduino boars is wired to RPI board via I2c pins and has attached to it the wireless receiver.
- Via I2C protcol RPI monitors every several (2) second the arduino board to check if has received any message. If an alert (move) message is received from primary arduino (via second arduino board) than a SMS alert is sent to a precompiled phone number via USB dongle. 
(No more than 1 sms / 5 min are send to avoid SMS receiver flooding)
- In my current configuration the USB GSM dongle is a Huawei E173 and the SMS are sent via AT command using PDU messages


Prerequires:
-----

	Arduiono and RPI are configured to run on I2C on 8th port. The user running monitor process has access to /dev/i2c-1
	RPI communicates with USB dongle via AT command and the monitor running process has access to /dev/ttyUSB0. 
	Also the USB modem is correctly initialized in the sense that was taken out from its initial cd mode. This was done using usb_modeswitch tool