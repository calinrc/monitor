/*
 *    PirSensorsWClient file written and maintained by Calin Cocan
 *    Created on: Feb 3, 2015
 *
 * Based on: http://arduino.cc/playground/Main/PinChangeIntExample
 * and  http://www.rocketscream.com/blog/2011/07/04/lightweight-low-power-arduino-library/
 ********************************************************************************************************************* */


#include <JeeLib.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <PinChangeInt.h>
#include <avr/wdt.h>

#include <VirtualWire.h>

ISR(WDT_vect) {
  Sleepy::watchdogEvent();
}

#define PIR_1               2
#define PIR_2               3
#define PIR_3               4
#define LED                13

volatile int rised = 0;


enum W_CLIENT_EVENT {
  NONE,
  MOVE,
  POWER_CHECK
};

void setup() {
  pinMode(PIR_1, INPUT);
  pinMode(PIR_2, INPUT);
  pinMode(PIR_3, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  wdt_disable();
  vw_set_tx_pin(9);
  vw_set_rx_pin(6);
  vw_set_ptt_pin(10);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);       // Bits per sec
  delay(10000); // deley for pir sensor calibration

  blinkLed(5);


  //PRR = bit(PRTIM1);                           // only keep timer 0 going
  //  PRR &= (uint8_t)~(1 << PRTIM1);
  //power_timer1_enable(); // do not disable all timers because are used in VirtualWire library
  ADCSRA &= ~ bit(ADEN);
  //  bitSet(PRR, PRADC);   // Disable the ADC to save power

  power_adc_disable();
  power_spi_disable();
  power_twi_disable();
  power_usart0_disable();

  PCintPort::attachInterrupt(PIR_1, wakeUpPir1, RISING);
  PCintPort::attachInterrupt(PIR_2, wakeUpPir2, RISING);
  PCintPort::attachInterrupt(PIR_3, wakeUpPir3, RISING);
}

void wakeUp(int risedPir) {
  PCintPort::detachInterrupt(PIR_1);
  PCintPort::detachInterrupt(PIR_2);
  PCintPort::detachInterrupt(PIR_3);
  rised |=risedPir;
}

void wakeUpPir1() {
  wakeUp(1);
}

void wakeUpPir2() {
  wakeUp(2);
}

void wakeUpPir3() {
  wakeUp(4);
}


void loop() {
  if ( rised > 0 ) {
    sendMoveMessage(rised);
  }
  rised = 0;
  PCintPort::attachInterrupt(PIR_1, wakeUpPir1, RISING);
  PCintPort::attachInterrupt(PIR_2, wakeUpPir2, RISING);
  PCintPort::attachInterrupt(PIR_3, wakeUpPir3, RISING);
  Sleepy::powerDown();
}

void sendMoveMessage(int sensorsIds)
{
  char msg[2] = {MOVE, '#'};
  msg[1] = sensorsIds;
  vw_send((uint8_t *)msg, 2);
  vw_wait_tx(); // Wait until the whole message is gone
  blinkLed(sensorsIds);
}

void blinkLed(int value) {
  for (int i = 0; i < value; i++) {
    digitalWrite(LED, HIGH); // Flash a light to show transmitting
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
  }
}

