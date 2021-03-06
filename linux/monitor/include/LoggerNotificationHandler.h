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

#ifndef INCLUDE_LOGGERNOTIFICATIONHANDLER_H_
#define INCLUDE_LOGGERNOTIFICATIONHANDLER_H_

#include "NotificationHandler.h"
#include "Logger.h"

class LoggerNotificationHandler : public NotificationHandler
{
public:
    LoggerNotificationHandler()
    {
    }
    virtual ~LoggerNotificationHandler()
    {
    }
    virtual void alert(struct tm *ltime, int sensorId)
    {
        strftime(cTimeBuff, 170, "%d.%m.%y %H:%M:%S", ltime);
        sprintf(cBuff, "Alert received at %s for sensor %d", cTimeBuff, sensorId);
        LOGGING(cBuff);
    }

    virtual void status(struct tm *ltime)
    {
        strftime(cTimeBuff, 170, "%d.%m.%y %H:%M:%S", ltime);
        sprintf(cBuff, "%s %s", "Status received at ", cTimeBuff);
        LOGGING(cBuff);
    }

private:
    char cBuff[170];
    char cTimeBuff[170];

};

#endif /* INCLUDE_LOGGERNOTIFICATIONHANDLER_H_ */
