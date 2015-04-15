/*
 *    SMSHandler.cpp file written and maintained by Calin Cocan
 *    Created on: Mar 4, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#include "SMSHandler.h"
#include <string.h>
#include <stdio.h>
#include "PDUMessage.h"
#include "Logger.h"

SMSHandler::SMSHandler()
{

}

SMSHandler::~SMSHandler()
{
    m_serial.close();
}

SMSError SMSHandler::init(const char* szdeviceName, unsigned long int speed)
{
    m_serial.open(szdeviceName, speed);
    sendAtCommand(GET_SMSC);
    int readBytes = m_serial.read(m_buff, sizeof(m_buff));
    if (readBytes >=0){
        m_buff[readBytes] = '\0';
        //TODO extract here smsc number
    }
    return SMS_OK;

}
SMSError SMSHandler::sendMessage(const char* szPhoneNo, const char* szMessage)
{
    char cmgs[20];
    char ctrl_z_seq[2] = {26, 0};//send Ctrl+z

    sendAtCommand("");
    sendAtCommand(AT_SET_PDU);

    PDUMessage pdu(m_smscNo, szPhoneNo);
    size_t smscInfoLen = pdu.getSmscInfoLen();
    const char* const pduMsg = pdu.getPDU(szMessage);
    LOGGING("Sending message. PDU: %s", pduMsg);

    sprintf(cmgs, "+CMGS=%d", (int)((strlen(pduMsg)/2) - smscInfoLen -1));
    sendAtCommand(cmgs);
    sendAtCommand(pduMsg);
    sendAtCommand(ctrl_z_seq);
    return SMS_OK;
}

void SMSHandler::sendAtCommand(const char* szAtCommand)
{
    sprintf(m_buff, "%s%s\r", AT_COMMAND, szAtCommand);
    size_t lSend = strlen(m_buff);
    size_t writeBytes= m_serial.write(m_buff, lSend);
    if (lSend != writeBytes){
        LOGGING("Actual written % bytes, expected &d bytes", writeBytes, lSend);
    }
}
