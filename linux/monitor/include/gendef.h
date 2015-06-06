/*
 *    gendef.h file written and maintained by Calin Cocan
 *    Created on: Mar 4, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_GENDEF_H_
#define INCLUDE_GENDEF_H_

enum I2CError
{
    I2C_OK,
    I2CINIT_FAIL,
    I2CREAD_FAIL,
    I2CWRITE_FAIL,
    I2CCLOSE_FAIL
};

enum SMSError
{
    SMS_OK,
    SMSINIT_FAIL,
    SMSSEND_FAIL
};

enum I2C_CLIENT_STATE
{
    EMPTY,
    RECEIVED,
    SENT
};

enum W_CLIENT_EVENT
{
    NONE,
    MOVE,
    POWER_CHECK
};

#define LOCAL_PHONE_FORMAT 0x81
#define INTERNATIONAL_PHONE_FORMAT 0x91
#define MAX_PDU_LEN 170
#define PROTOCOL_ID 0x00 //default SMS protocol
#define DATA_ENC_SCHEME 0x11 // 0x11 default GSM 7 bit alphabet //try with 0x10 as well - this is Flash msg
#define AT_SET_PDU "+CMGF=0" //Command to set the dongle into PDU mode
#define GET_SMSC "+CSCA?"
#define CTRL_Z 26

#define PHONE_NAME "phoneNo"

#ifdef PREDEFINED_PHONE_NO
#define PHONE_NO PREDEFINED_PHONE_NO
#else
#define PHONE_NO "123"
#endif

#define I2C_ADDR 0x08

#define I2C_DEVICE_NAME "i2cDeviceName"
#define I2C_DEVICE_ADDRESS "/dev/i2c-1"

#define GSM_DEVICE_NAME "gsmDeviceName"
#define GSM_DEVICE_ADDRESS "/dev/ttyUSB0"

#endif /* INCLUDE_GENDEF_H_ */
