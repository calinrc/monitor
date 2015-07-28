/*
 *    SMSNotificationHandler.h file written and maintained by Calin Cocan
 *    Created on: Apr 23, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_SMSNOTIFICATIONHANDLER_H_
#define INCLUDE_SMSNOTIFICATIONHANDLER_H_

#include "NotificationHandler.h"
#include <time.h>

class SMSHandler;

class SMSNotificationHandler : public NotificationHandler
{
public:
    SMSNotificationHandler(const char* szdeviceName, unsigned long int speed, const char* szPhoneNo);
    virtual ~SMSNotificationHandler();
    virtual void alert(struct tm *ltime, int sensorId);
    virtual void status(struct tm *ltime);

private:
    SMSHandler* m_handler;
    const char* m_szPhoneNo;
    time_t m_lastTime;

    char cBuff[170];
    char cTimeBuff[170];
};

#endif /* INCLUDE_SMSNOTIFICATIONHANDLER_H_ */
