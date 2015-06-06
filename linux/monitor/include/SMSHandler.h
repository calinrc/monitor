/*
 *    SMSHandler.h file written and maintained by Calin Cocan
 *    Created on: Mar 4, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_SMSHANDLER_H_
#define INCLUDE_SMSHANDLER_H_

#include "gendef.h"
#include "Serial.h"

class SMSHandler
{
public:
    SMSHandler();
    virtual ~SMSHandler();
    virtual SMSError init(const char* szdeviceName, unsigned long int speed = 115200);
    virtual SMSError sendMessage(const char* szPhoneNo, const char* szMessage);
private:

    int sendAtCommand(const char* szAtCommand, bool read = true);

    char m_buff[MAX_PDU_LEN];

    char m_smscNo[20];
    Serial m_serial;
};

#endif /* INCLUDE_SMSHANDLER_H_ */
