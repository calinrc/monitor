/*
 *    PDUMessage.cpp file written and maintained by Calin Cocan
 *    Created on: Mar 23, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

 ********************************************************************************************************************* */

#include "PDUMessage.h"
#include <string.h>
#include "GSMUtils.h"
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <stdio.h>

PDUMessage::PDUMessage(const char* szPhoneNo, const char* szSmsc) :
        m_metaDataLen(0)
{
    size_t dPhoneFormat = 0;
    size_t dSMSCFormat = 0;
    dPhoneFormat = (szPhoneNo[0] == '+' || (szPhoneNo[0] == '0' && szPhoneNo[1] == '0')) ? INTERNATIONAL_PHONE_FORMAT : LOCAL_PHONE_FORMAT;
    dSMSCFormat = (szSmsc[0] == '+' || (szSmsc[0] == '0' && szSmsc[1] == '0')) ? INTERNATIONAL_PHONE_FORMAT : LOCAL_PHONE_FORMAT;

    char smscAdress[MAX_PDU_LEN];
    char phoneAdress[MAX_PDU_LEN];
    memset(m_szPduMessage, 0, sizeof(m_szPduMessage));
    memset(smscAdress, 0, sizeof(smscAdress));
    size_t encodedBytesSmsc = sizeof(smscAdress);
    size_t encodedBytesPhoneNo = sizeof(phoneAdress);

    GSMUtils::semiDecimalOctets(szSmsc, strlen(szSmsc), smscAdress, &encodedBytesSmsc);
    smscAdress[encodedBytesSmsc] = '\0';
    size_t smscLeng = (encodedBytesSmsc + 2) / 2;

    size_t phoneNoLen = strlen(szPhoneNo);
    GSMUtils::semiDecimalOctets(szPhoneNo, phoneNoLen, phoneAdress, &encodedBytesPhoneNo);
    phoneAdress[encodedBytesPhoneNo] = '\0';

    sprintf(m_szPduMessage, "%.2X%.2X%s%.2X%.2X%.2X%s%.2X%.2X", (uint) smscLeng, (uint) dSMSCFormat, smscAdress, 0x04, (uint) phoneNoLen, (uint) dPhoneFormat, phoneAdress,
    PROTOCOL_ID,
            DATA_ENC_SCHEME);
    m_metaDataLen = strlen(m_szPduMessage);

}

PDUMessage::~PDUMessage()
{

}

char* PDUMessage::getTimeString()
{
    char* cBuff = new char[15];
    time_t zaman;
    struct tm *gmttime;
    static struct timeval _t;
    static struct timezone tz;

    time(&zaman);
    gmttime = (struct tm *) gmtime(&zaman);
    gettimeofday(&_t, &tz);

    sprintf(cBuff, "%.2d%.2d%.2d%.2d%.2d%.2d%.2d", (gmttime->tm_year % 100), gmttime->tm_mon, gmttime->tm_mday, gmttime->tm_hour, gmttime->tm_min, gmttime->tm_sec, 0);
    cBuff[14] = '\0';
    return cBuff;

}

char* const PDUMessage::getPDU(char* szMessage, size_t* pduLenght)
{
    m_szPduMessage[m_metaDataLen] = '\0';
    char* szTime = getTimeString();
    size_t msgLen = strlen(szMessage);
    char asciiMsg[MAX_PDU_LEN];
    size_t asciiLen = MAX_PDU_LEN;
    size_t asciiLen2= MAX_PDU_LEN;

    GSMUtils::asciiToGsmCode(szMessage, msgLen, asciiMsg, &asciiLen);
    asciiMsg[asciiLen] = '\0';
    GSMUtils::encodeinGsm7Bit(asciiMsg, asciiLen, asciiMsg, &asciiLen2);

    sprintf(m_szPduMessage, "%s%s%.2X%s",m_szPduMessage, szTime, (uint) msgLen, asciiMsg);
    delete[] szTime;
    *pduLenght = strlen(m_szPduMessage);
    return m_szPduMessage;
}
