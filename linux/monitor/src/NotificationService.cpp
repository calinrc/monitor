/*
 *    NotificationFactory.cpp file written and maintained by Calin Cocan
 *    Created on: Apr 23, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#include "NotificationService.h"
#include "SMSNotificationHandler.h"
#include "LoggerNotificationHandler.h"
#include "gendef.h"

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

NotificationService* NotificationService::s_THIS = new NotificationService();

NotificationService::NotificationService()
{
    //TODO update this code with a more generic one
#pragma message "Using phone number " PHONE_NO
    m_NotifHandlers.push_back(new SMSNotificationHandler(GSM_DEVICE_ADDRESS, 115200, PHONE_NO));
    m_NotifHandlers.push_back(new LoggerNotificationHandler());
}

NotificationService::~NotificationService()
{
}

NotificationService* NotificationService::getService()
{
    return s_THIS;
}

void NotificationService::notify()
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
    sprintf(cBuff, "%s %s.%d", "Alert send at ", cTimeBuff, (int) _t.tv_usec);


    for (list<NotificationHandler*>::iterator it = m_NotifHandlers.begin(); it != m_NotifHandlers.end(); it++)
    {
        (*it)->notify(cBuff);
    }
}
