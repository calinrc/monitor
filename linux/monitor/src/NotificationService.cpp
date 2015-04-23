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
#include "gendef.h"

NotificationService* NotificationService::m_THIS = new NotificationService();

NotificationService::NotificationService()
{
    //TODO update this code with a more generic one
    m_NotifHandlers.push_back(new SMSNotificationHandler(GSM_DEVICE_ADDRESS, 115200, PHONE_NO, "Alert send at "));
}

NotificationService::~NotificationService()
{
}

NotificationService* NotificationService::getService()
{
    return m_THIS;
}

void NotificationService::notify()
{
    for (list<NotificationHandler*>::iterator it = m_NotifHandlers.begin(); it != m_NotifHandlers.end(); it++)
    {
        (*it)->notify();
    }
}
