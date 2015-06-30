/*
 *    PirSensorsWClient file written and maintained by Calin Cocan
 *    Created on: Jun 23, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#include <VirtualWire.h>

#define PIR_1               2
#define PIR_2               3
#define PIR_3               4
#define LED                13

enum W_CLIENT_EVENT {
  NONE,
  MOVE,
  POWER_CHECK
};


volatile int count;

void setup() {
  count = 0;
  pinMode(PIR_1, INPUT);
  pinMode(PIR_2, INPUT);
  pinMode(PIR_3, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  vw_set_tx_pin(9);
  vw_set_rx_pin(6);
  vw_set_ptt_pin(10);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);       // Bits per sec
  delay(10000); // deley for pir sensor calibration

  blinkLed(5);

}



void loop() {
  int rised = 1; //used for power check
  if (digitalRead(PIR_1) == HIGH){
    rised = PIR_1;
  }else if (digitalRead(PIR_2) == HIGH){
    rised = PIR_2;
  }else if (digitalRead(PIR_3) == HIGH){
    rised = PIR_3;
  }
  count++;
  if ((rised > 1) || (count >4)){
    sendMoveMessage(rised);  
    if (count >4){
      count = 0;  
    }
  }
  delay(1000); // Sleep for a second to prevent flooding wireless TX
  
}

void sendMoveMessage(int sensorsId)
{
  char msg[2];
  if (sensorsId >1){
    msg[0] = MOVE;
    msg[1] = sensorsId;
  }else{
    msg[0] = POWER_CHECK;
    msg[1] = 0;
  }
  for (int i =0 ; i<10; i++){
    vw_send((uint8_t *)msg, 2);
    vw_wait_tx(); // Wait until the whole message is gone
  }
  blinkLed(sensorsId);
}

void blinkLed(int value) {
  for (int i = 0; i < value; i++) {
    digitalWrite(LED, HIGH); // Flash a light to show transmitting
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
  }
}

