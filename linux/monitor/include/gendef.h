/*
 *    gendef.h file written and maintained by Calin Cocan
 *    Created on: Mar 4, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

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
#define DATA_ENC_SCHEME 0x00 //default GSM alphabet

#endif /* INCLUDE_GENDEF_H_ */
