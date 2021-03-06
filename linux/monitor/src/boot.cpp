/*
 *    main.cpp file written and maintained by Calin Cocan
 *    Created on: Mar 4, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "Logger.h"
#include "I2CDevice.h"
#include "gendef.h"

#include "GSMUtils.h"
#include "PDUMessage.h"
#include "NotificationService.h"

#include "SMSNotificationHandler.h"
#include "LoggerNotificationHandler.h"
#include "CsvNotificationHandler.h"

/*
 * Information received from I2C
 *
 * 3 bytes data
 * byte 1 - event type [ NONE,  MOVE, POWER_CHECK]
 * byte 2 - transmission state (for event type MOVE (1))- EMPTY, RECEIVED, SENT
 * byte 3 - sensorID ( for state type RECEIVED (1)) - 1, 2, 3
 };
 *
 * */

const char* eventTypeToMsg(W_CLIENT_EVENT event){
    switch (event){
        case NONE: return CLIENT_EVENT_NONE;
        case MOVE: return CLIENT_EVENT_MOVE;
        case POWER_CHECK: return CLIENT_EVENT_POWER_CHECK;
        default: return CLIENT_EVENT_UNNOWN;
    }
}

const char* i2CStateToMsg(I2C_CLIENT_STATE state){
    switch(state){
        case EMPTY: return I2C_CLIENT_STATE_EMPTY;
        case RECEIVED: return I2C_CLIENT_STATE_RECEIVED;
        case SENT : return I2C_CLIENT_STATE_SENT;
        default: return I2C_CLIENT_STATE_UNKNOWN;
    }
}

int main()
{
    Logger::getInstance()->init(true, true);
    LOGGING("Starting monitoring application...")
    I2CDevice i2c_device;
    I2CError i2cerr = i2c_device.init(I2C_DEVICE_ADDRESS, I2C_ADDR);
#pragma message "Using phone number " PHONE_NO

    //NotificationService::getService()->registerHandler(new SMSNotificationHandler(GSM_DEVICE_ADDRESS, 115200, PHONE_NO));
    NotificationService::getService()->registerHandler(new LoggerNotificationHandler());
    NotificationService::getService()->registerHandler(new CsvNotificationHandler());
    if (i2cerr == I2C_OK)
    {
        int eventType = 0;
        int transmissionState = 0;
        int sensorsId = 0;

        int oldStateEventType = 0;
        int oldStateTransmissionState = 0;
        int oldStateSensorsIds = 0;
        bool first = true;
        LOGGING("Start monitoring")
        while (1)
        {
            sleep(2); // do the i2c requests every 2 second
            if (i2c_device.send(1) == I2C_OK)
            {
                usleep(10000);
                i2c_device.receive(eventType, transmissionState, sensorsId);
                if (first || eventType != oldStateEventType || transmissionState != oldStateTransmissionState || sensorsId != oldStateSensorsIds)
                {
                    switch (eventType){
                        case MOVE:
                            NotificationService::getService()->alert(sensorsId);
                            break;
                        case POWER_CHECK:
                            NotificationService::getService()->status();
                            break;
                        case NONE:
                            LOGGING("Received first event")
                            break;
                    }
                    if (eventType == MOVE){

                    }
                    LOGGING("SensorsData: EventType %s \t\tI2CState:%s \t\t Sensors IDS: %d", eventTypeToMsg(static_cast<W_CLIENT_EVENT>(eventType)), i2CStateToMsg(static_cast<I2C_CLIENT_STATE>(transmissionState)), sensorsId)
                    oldStateEventType = eventType;
                    oldStateTransmissionState = transmissionState;
                    oldStateSensorsIds = sensorsId;
                }
                first = false;
            }
        }
    }

    LOGGING("End monitoring")
    return 0;
}
