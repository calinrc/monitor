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

#ifndef INCLUDE_CSVNOTIFICATIONHANDLER_H_
#define INCLUDE_CSVNOTIFICATIONHANDLER_H_

#include "NotificationHandler.h"
#include "gendef.h"
#include <stddef.h>

class CsvNotificationHandler : public NotificationHandler
{
public:
    CsvNotificationHandler() :
            m_file(NULL)
    {
        m_file = fopen(CSV_FILE, "a");
    }
    virtual ~CsvNotificationHandler()
    {
        if (m_file != NULL)
        {
            fclose(m_file);
            m_file = NULL;
        }
    }

    virtual void alert(struct tm *ltime, int sensorId)
    {
        writeLine(ltime, false, sensorId);
    }

    virtual void status(struct tm *ltime)
    {
        writeLine(ltime, true, 0);
    }

private:
    void writeLine(struct tm *ltime, bool isStatus, int sensorId)
    {
        if (m_file != NULL)
        {
            strftime(cTimeBuff, 170, "%y.%m.%d %H:%M:%S", ltime);
            fprintf(m_file, "%s,%d,%s\n", isStatus ? "Status" : "Alert", sensorId, cTimeBuff);
            fflush(m_file);
        }
    }

    char cTimeBuff[170];
    FILE* m_file;

};

#endif /* INCLUDE_CSVNOTIFICATIONHANDLER_H_ */
