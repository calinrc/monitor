/*
 *    GSMUtils.h file written and maintained by Calin Cocan
 *    Created on: Mar 12, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_GSMUTILS_H_
#define INCLUDE_GSMUTILS_H_

class GSMUtils
{

public:
    static int asciiToGsmCode(const char* bytesList, size_t bytesLenght, char* encoddedBytes, size_t* encodedLength);

    static int bytesToHex(const char* const bytesList, size_t bytesLenght, char* const encoddedBytes, size_t* encodedLength);

    static int encodeinGsm7Bit(const char* const bytesList, size_t bytesLenght, char* const encoddedBytes, size_t* encodedLength);

    static int semiDecimalOctets(const char* sdOctets, size_t sdSize, char* const encodedBytes, size_t* encodedLength);

private:
    //try to represent as much of the ascii table characters in GSM 7 bit alphabet. Some of the characters are the same , having the same index , other might  be different.
    //when a char from ascii table have no correspondent in GSM code , is replaced with underscore code (0x11)
    //for chars having value ox1b there is a continuation code
    static char const ASCII_GSM_alfabeth[];
    static char const ASCII_GSM_extended_alfabeth[];

};

#endif /* INCLUDE_GSMUTILS_H_ */
