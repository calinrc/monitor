/*
 *    SMSHandler.cpp file written and maintained by Calin Cocan
 *    Created on: Mar 4, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

 ********************************************************************************************************************* */

#include "SMSHandler.h"

SMSHandler::SMSHandler()
{

}

SMSHandler::~SMSHandler()
{
}

SMSError SMSHandler::init(const char* szdeviceName)
{
    return SMSINIT_FAIL;

}
SMSError SMSHandler::sendMessage(const char* szPhoneNo, const char* szMessage)
{
    return SMSSEND_FAIL;
}
