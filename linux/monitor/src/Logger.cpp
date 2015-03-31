/*
 *    Logger.cpp file written and maintained by Calin Cocan
 *    Created on: Mar 4, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

 ********************************************************************************************************************* */

#include "Logger.h"
#include <fcntl.h>
#include <stdarg.h>
#include <sys/time.h>
#include <time.h>

Logger* Logger::s_instance = new Logger();

Logger::Logger() :
        m_isFileLoggingEnabled(true), m_isConsoleLoggingEnabled(true), m_file(NULL)
{
}

Logger::~Logger()
{
    if (m_isFileLoggingEnabled && m_file != NULL)
    {
        fclose(m_file);
    }

}

void Logger::init(bool consoleEnable, bool fileEnable)
{
    this->m_isConsoleLoggingEnabled = consoleEnable;
    this->m_isFileLoggingEnabled = fileEnable;
    if (m_isFileLoggingEnabled)
    {
        m_file = fopen(LOG_FILE, "a");
    }
}

void Logger::log(const char* msg, ...)
{
    if (m_isFileLoggingEnabled == true || m_isConsoleLoggingEnabled == true)
    {
        va_list args;
        va_start(args, msg);
        char * displayMsg = buildMessage(msg, args);
        if (m_isFileLoggingEnabled)
        {
            fprintf(m_file, "%s", displayMsg);
            fprintf(m_file, "\n");
            fflush(m_file);
        }
        if (m_isConsoleLoggingEnabled)
        {
            fprintf(stdout, "%s", displayMsg);
            fprintf(stdout, "\n");

        }
        va_end(args);
        delete[] displayMsg;
    }
}

char* Logger::buildMessage(const char* msg, va_list argList)
{
    int len = 0, count = 300;
    char* buff = new char[count];
    char * cBuff = new char[count];

    time_t zaman;
    struct tm *ltime;
    static struct timeval _t;
    static struct timezone tz;

    time(&zaman);
    ltime = (struct tm *) localtime(&zaman);
    gettimeofday(&_t, &tz);

    strftime(cBuff, count, "%d.%m.%y %H:%M:%S", ltime);
    sprintf(cBuff, "%s.%d - %s", cBuff, (int) _t.tv_usec, msg);

    len = vsnprintf(buff, count - 1, cBuff, argList);
    if (len >= count)
    {
        delete[] buff;
        count = len + 1;
        buff = new char[count];
        len = vsnprintf(buff, count - 1, cBuff, argList);
    }
    if (len == -1)
    {
        delete[] buff;
        count = count * 10;
        buff = new char[count];
        len = vsnprintf(buff, count - 1, cBuff, argList);
    }
    delete[] cBuff;
    return buff;
}
