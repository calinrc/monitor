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
#include "NotificationHandler.h"

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

NotificationService* NotificationService::s_THIS = new NotificationService();

NotificationService::NotificationService()
{
}

NotificationService::~NotificationService()
{
}

NotificationService* NotificationService::getService()
{
    return s_THIS;
}

void NotificationService::registerHandler(NotificationHandler* notificationHandler)
{
    m_NotifHandlers.push_back(notificationHandler);
}

void NotificationService::alert(int sensorId)
{
    time_t zaman;
    struct tm *ltime;

    time(&zaman);
    ltime = (struct tm *) localtime(&zaman);

    for (list<NotificationHandler*>::iterator it = m_NotifHandlers.begin(); it != m_NotifHandlers.end(); it++)
    {
        (*it)->alert(ltime, sensorId);
    }
}

void NotificationService::status()
{
    time_t zaman;
    struct tm *ltime;

    time(&zaman);
    ltime = (struct tm *) localtime(&zaman);

    for (list<NotificationHandler*>::iterator it = m_NotifHandlers.begin(); it != m_NotifHandlers.end(); it++)
    {
        (*it)->status(ltime);
    }
}
