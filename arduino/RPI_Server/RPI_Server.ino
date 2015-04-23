/*
 *     RPI_Server file written and maintained by Calin Cocan
 *     Created on: Feb 2, 2015
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

*/

#include <VirtualWire.h>
#include <Wire.h>

const int LED_PIN = 13;
#define SLAVE_ADDRESS 0x08

enum STATE {
  EMPTY,
  RECEIVED,
  SENT
};

enum W_CLIENT_EVENT {
  NONE,
  MOVE,
  POWER_CHECK
};

int state = EMPTY;
int eventType = NONE;
int sensorId = 0;
unsigned char wireBuff[3];
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;


void setup()
{
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

  // Initialise the IO and ISR
  vw_set_tx_pin(6);
  vw_set_rx_pin(10);
  vw_set_ptt_pin(9);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec

  vw_rx_start();       // Start the receiver PLL running

  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    eventType = buf[0];
    switch (buf[0])
    {
      case MOVE:
        state = RECEIVED;
        sensorId = buf[1];
        break;
      case POWER_CHECK:
        //TODO update this code
        break;
    }
    digitalWrite(LED_PIN, HIGH); // Flash a light to show received good message
    // Message with a good checksum received, dump it.
    delay(100);
    digitalWrite(LED_PIN, LOW);
  }
}

// callback for received data
void receiveData(int byteCount) {
  while (Wire.available()) {
    int number = Wire.read();
  }
}

// callback for sending data
void sendData() {
  wireBuff[0] = eventType;
  wireBuff[1] = state;
  wireBuff[2] = sensorId;
  Wire.write(wireBuff, sizeof(wireBuff));
  state = SENT;
}
