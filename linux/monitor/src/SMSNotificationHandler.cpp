/*
 *    SMSNotificationHandler.cpp file written and maintained by Calin Cocan
 *    Created on: Apr 23, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#include "SMSNotificationHandler.h"
#include "SMSHandler.h"
#include <stdio.h>

#define SMS_NOTIFICATION_INTERVAL 60 //60 seconds

SMSNotificationHandler::SMSNotificationHandler(const char* szdeviceName, unsigned long int speed, const char* szPhoneNo) :
        m_szPhoneNo(szPhoneNo), m_lastTime(0)
{
    this->m_handler = new SMSHandler();
    this->m_handler->init(szdeviceName, speed);
}

SMSNotificationHandler::~SMSNotificationHandler()
{
    delete m_handler;
}

void SMSNotificationHandler::alert(struct tm *ltime, int sensorId)
{
    time_t currentTime = 0;
    if (((time_t) -1) != time(&currentTime))
    {
        if ((currentTime - m_lastTime) > SMS_NOTIFICATION_INTERVAL)
        {
            strftime(cTimeBuff, 170, "%d.%m.%y %H:%M:%S", ltime);
            sprintf(cBuff, "Alert received at %s for sensor %d", cTimeBuff, sensorId);
            this->m_handler->sendMessage(this->m_szPhoneNo, cBuff);
            m_lastTime = currentTime;
        }
    }
}

void SMSNotificationHandler::status(struct tm *ltime)
{
    //DO nothing
}

