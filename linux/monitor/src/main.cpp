/*
 *    main.cpp file written and maintained by Calin Cocan
 *    Created on: Mar 4, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

 ********************************************************************************************************************* */

#include <unistd.h>
#include <string.h>

#include "Logger.h"
#include "I2CDevice.h"
#include "gendef.h"

#include "GSMUtils.h"
#include "PDUMessage.h"

#define I2C_ADDR 0x08
#define I2C_DEVICE_NAME "/dev/i2c-1"
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

int main2()
{
    Logger::getInstance()->init(true, true);
    I2CDevice i2c_device;
    I2CError i2cerr = i2c_device.init(I2C_DEVICE_NAME, I2C_ADDR);
    if (i2cerr == I2C_OK)
    {
        int eventType = 0;
        int transmissionState = 0;
        int sensorsIds = 0;

        int oldStateEventType = 0;
        int oldStateTransmissionState = 0;
        int oldStateSensorsIds = 0;
        bool first = true;
        LOGGING("Start monitoring")
        while (1)
        {
            sleep(1); // do the i2c requests every 1 second
            if (i2c_device.send(1) == I2C_OK)
            {
                usleep(10000);
                i2c_device.receive(eventType, transmissionState, sensorsIds);
                if (first || eventType != oldStateEventType || transmissionState != oldStateTransmissionState || sensorsIds != oldStateSensorsIds)
                {
                    LOGGING("SensorsData: %d:%d%d", eventType, transmissionState, sensorsIds)
                    oldStateEventType = eventType;
                    oldStateTransmissionState = transmissionState;
                    oldStateSensorsIds = sensorsIds;
                }
                first = false;
            }
        }
    }

    LOGGING("End monitoring")
    return 0;
}

int main()
{

    printf("Enter ...\n");

    char bytes[] = { '1', '2', '3', '4', '5', '6', '7', '8', '1', '2', '3', '4', '5', '6', '7', '8', '1' };
    char encodedBytes[257];
    char gSM7BitBytes[257];
    char decimalSemiOctets[257];

//    for (size_t i = 0; i < 128; i++)
//    {
//        bytes[i] = i;
//    }

    size_t convertedBytes = 257;
    size_t gsmConvertedBytes = 257;
    size_t decimalSemiOctetsSize = 257;
    encodedBytes[256] = '\0';

    int result = GSMUtils::encodeinGsm7Bit(bytes, sizeof(bytes), gSM7BitBytes, &gsmConvertedBytes);

    result = GSMUtils::bytesToHex(gSM7BitBytes, gsmConvertedBytes, encodedBytes, &convertedBytes);
    if (result == 0)
    {
        printf("Result: ...\n");
        char buff[3];
        buff[2] = '\0';
        for (size_t i = 0; i < convertedBytes - 1; i = i + 2)
        {
            buff[0] = encodedBytes[i];
            buff[1] = encodedBytes[i + 1];
            printf("0x%s ", buff);

            if (i > 0 && (i + 2) % 14 == 0)
            {
                printf("\n");
            }
        }
    } else
    {
        printf("\nFail to compute hex bytes\n");
    }

    result = GSMUtils::semiDecimalOctets(bytes, sizeof(bytes), decimalSemiOctets, &decimalSemiOctetsSize);
    if (result == 0)
    {
        decimalSemiOctets[decimalSemiOctetsSize] = '\0';
        printf("\nDecimal semi octets: %s", decimalSemiOctets);
    } else
    {
        printf("\nFail to compute decimal semi octets\n");
    }

    PDUMessage* msg = new PDUMessage("0040123450102", "+331213141516");
    char* const szMsg= (char*)"TestMessage";
    const char* const pdu = msg->getPDU(szMsg);
    printf("PDU for TestMessage is: %s", pdu);

    return 0;

}
