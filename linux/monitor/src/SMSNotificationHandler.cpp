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
#include <sys/time.h>
#include <time.h>


SMSNotificationHandler::SMSNotificationHandler(const char* szdeviceName, unsigned long int speed, const char* szPhoneNo, const char* szMessageHeader):
        m_szPhoneNo(szPhoneNo), m_szMessageHeader(szMessageHeader)
{
    this->m_handler = new SMSHandler();
    this->m_handler->init(szdeviceName, speed);
}

SMSNotificationHandler::~SMSNotificationHandler()
{
    delete m_handler;
}

void SMSNotificationHandler::notify()
{
    char cBuff[170];
    char cTimeBuff[170];

    time_t zaman;
    struct tm *ltime;
    static struct timeval _t;
    static struct timezone tz;

    time(&zaman);
    ltime = (struct tm *) localtime(&zaman);
    gettimeofday(&_t, &tz);

    strftime(cTimeBuff, 170, "%d.%m.%y %H:%M:%S", ltime);
    sprintf(cBuff, "%s %s.%d", m_szMessageHeader, cTimeBuff, (int) _t.tv_usec);

    this->m_handler->sendMessage(this->m_szPhoneNo, cBuff);
}

