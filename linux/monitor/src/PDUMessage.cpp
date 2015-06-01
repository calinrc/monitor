/*
 *    PDUMessage.cpp file written and maintained by Calin Cocan
 *    Created on: Mar 23, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#include "PDUMessage.h"
#include <string.h>
#include "GSMUtils.h"
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <stdio.h>
#include "Logger.h"

PDUMessage::PDUMessage(const char* szPhoneNo, const char* szSmsc) :
        m_metaDataLen(0),smscLeng(0)
{
    Logger::getInstance()->log("Used Phone Number %s , SMSC %s", szPhoneNo, szSmsc);
    size_t dPhoneFormat = 0;
    size_t dSMSCFormat = 0;

    dPhoneFormat = (szPhoneNo[0] == '+' || (szPhoneNo[0] == '0' && szPhoneNo[1] == '0')) ? INTERNATIONAL_PHONE_FORMAT : LOCAL_PHONE_FORMAT;
    dSMSCFormat = (szSmsc[0] == '+' || (szSmsc[0] == '0' && szSmsc[1] == '0')) ? INTERNATIONAL_PHONE_FORMAT : LOCAL_PHONE_FORMAT;

    const char* szPhoneNoNew = (dPhoneFormat == LOCAL_PHONE_FORMAT) ? szPhoneNo : (szPhoneNo[0] == '+') ? szPhoneNo + 1 : szPhoneNo + 2;
    const char* szSmscNew = (dSMSCFormat == LOCAL_PHONE_FORMAT) ? szSmsc : (szSmsc[0] == '+') ? szSmsc + 1 : szSmsc + 2;

    char smscAdress[MAX_PDU_LEN];
    char phoneAdress[MAX_PDU_LEN];
    memset(m_szPduMessage, 0, sizeof(m_szPduMessage));
    memset(smscAdress, 0, sizeof(smscAdress));
    size_t encodedBytesSmsc = sizeof(smscAdress);
    size_t encodedBytesPhoneNo = sizeof(phoneAdress);

    GSMUtils::semiDecimalOctets(szSmscNew, strlen(szSmscNew), smscAdress, &encodedBytesSmsc);
    smscAdress[encodedBytesSmsc] = '\0';
    smscLeng = (encodedBytesSmsc + 2) / 2;

    size_t phoneNoLen = strlen(szPhoneNoNew);
    GSMUtils::semiDecimalOctets(szPhoneNoNew, phoneNoLen, phoneAdress, &encodedBytesPhoneNo);
    phoneAdress[encodedBytesPhoneNo] = '\0';

    //0x01 - TP-MTI = SMS-SEND TP-VPF = Relative format used for the Validity Period.
    //0x00 - TP-MR
    sprintf(m_szPduMessage, "%.2X%.2X%s%.2X%.2X%.2X%.2X%s%.2X%.2X", (uint) smscLeng, (uint) dSMSCFormat, smscAdress, 0x01, 0x00, (uint) phoneNoLen, (uint) dPhoneFormat,
            phoneAdress,
            PROTOCOL_ID,
            DATA_ENC_SCHEME);
    m_metaDataLen = strlen(m_szPduMessage);

}

PDUMessage::~PDUMessage()
{

}

const char* const PDUMessage::getPDU(const char* szMessage)
{
    m_szPduMessage[m_metaDataLen] = '\0';
    size_t msgLen = strlen(szMessage);
    char asciiMsg[MAX_PDU_LEN];
    char gsm7BitMsg[MAX_PDU_LEN];
    char hexBytesMsg[2 * MAX_PDU_LEN];
    size_t asciiLen = MAX_PDU_LEN;
    size_t gsm7BitsLen = MAX_PDU_LEN;
    size_t hexBytesMsgLen = 2 * MAX_PDU_LEN;

    GSMUtils::asciiToGsmCode(szMessage, msgLen, asciiMsg, &asciiLen);
    asciiMsg[asciiLen] = '\0';
    GSMUtils::encodeinGsm7Bit(asciiMsg, asciiLen, gsm7BitMsg, &gsm7BitsLen);

    GSMUtils::bytesToHex(gsm7BitMsg, gsm7BitsLen, hexBytesMsg, &hexBytesMsgLen);
    hexBytesMsg[hexBytesMsgLen] = '\0';

    sprintf(m_szPduMessage, "%s%.2X%s", m_szPduMessage, (uint) msgLen, hexBytesMsg);
    return m_szPduMessage;
}

size_t PDUMessage::getSmscInfoLen(){
    return smscLeng;
}
