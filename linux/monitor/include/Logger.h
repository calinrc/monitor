/*
 *    Logger.h file written and maintained by Calin Cocan
 *    Created on: Mar 4, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_LOGGER_H_
#define INCLUDE_LOGGER_H_

#include <stdio.h>

class Logger
{

public:
    inline static Logger* getInstance()
    {
        return s_instance;
    }

    void init(bool consoleEnable, bool fileEnable);
    void log(const char* msg, ...);
private:
    Logger();
    virtual ~Logger();

    char* buildMessage(const char* msg, va_list argList);
    bool m_isFileLoggingEnabled;
    bool m_isConsoleLoggingEnabled;
    FILE* m_file;
    static Logger* s_instance;
};

#define LOGGING(__MSG__, ...)  { Logger::getInstance()->log(__MSG__, ##__VA_ARGS__); }

#endif /* INCLUDE_LOGGER_H_ */
