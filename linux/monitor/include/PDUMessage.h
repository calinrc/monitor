/*
 *    PDUMessage.h file written and maintained by Calin Cocan
 *    Created on: Mar 23, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_PDUMESSAGE_H_
#define INCLUDE_PDUMESSAGE_H_

#include "gendef.h"

#include <stddef.h>

class PDUMessage
{
public:
    PDUMessage(const char* szPhoneNo, const char* szSmsc);
    virtual ~PDUMessage();
    const char* const getPDU(char* szMessage);

private:
    char m_szPduMessage[MAX_PDU_LEN];
    size_t m_metaDataLen;
};

#endif /* INCLUDE_PDUMESSAGE_H_ */
