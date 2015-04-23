/*
 *    GSMUtils.cpp file written and maintained by Calin Cocan
 *    Created on: Mar 12, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#include <stddef.h>
#include "GSMUtils.h"
#include <math.h>
#include <sys/types.h>

#define EXTEND_ESC  0x1B

char const GSMUtils::ASCII_GSM_alfabeth[] = { 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,

'\n', 0x11, 0x1B, '\r', 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,

0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,

0x11, 0x11, ' ', '!', '"', '#', 0x02, '%', '&', '\'',

'(', ')', '*', '+', ',', '-', '.', '/', '0', '1',

'2', '3', '4', '5', '6', '7', '8', '9', ':', ';',

'<', '=', '>', '?', 0x00, 'A', 'B', 'C', 'D', 'E',

'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',

'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y',

'Z', 0x1B, 0x1B, 0x1B, 0x1B, 0x11, 0x11, 'a', 'b', 'c',

'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',

'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w',

'x', 'y', 'z', 0x1B, 0x1B, 0x1B, 0x1B, 0x11 };

char const GSMUtils::ASCII_GSM_extended_alfabeth[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

0, 0, 0x0A, 0, 0, 0, 0, 0, 0, 0,

0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

0, 0x3C, 0x2F, 0x3E, 0x14, 0, 0, 0, 0, 0,

0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

0, 0, 0, 0x28, 0x40, 0x29, 0x3D, 0 };

int GSMUtils::asciiToGsmCode(const char* bytesList, size_t bytesLenght, char* encoddedBytes, size_t* encodedLength)
{
    if (*encodedLength < bytesLenght)
    {
        return -1;
    }

    int extendeUsedBytes = 0;
    for (size_t i = 0; i < bytesLenght; i++)
    {
        if (bytesList[i] > 127)
        {
            return -2; // we do not support extended ascii or other encoding
        }
        encoddedBytes[i + extendeUsedBytes] = ASCII_GSM_alfabeth[(uint) bytesList[i]];
        if (ASCII_GSM_alfabeth[(uint) bytesList[i]] == EXTEND_ESC)
        {
            extendeUsedBytes++;
            if (*encodedLength < bytesLenght + extendeUsedBytes)
            {
                return -3; // not enough space in output buffer;
            }
            encoddedBytes[i + extendeUsedBytes] = ASCII_GSM_extended_alfabeth[(uint) bytesList[i]];
        }

    }
    *encodedLength = bytesLenght + extendeUsedBytes;
    return 0;

}

int GSMUtils::bytesToHex(const char* const bytesList, size_t bytesLenght, char* const encoddedBytes, size_t* encodedLength)
{
    if (*encodedLength < 2 * bytesLenght)
    {
        return -1;
    }
    *encodedLength = 2 * bytesLenght;
    for (size_t i = 0; i < bytesLenght; i++)
    {
        unsigned char val = (unsigned char) bytesList[i] >> 4;
        encoddedBytes[2 * i] = (val <= 9) ? '0' + val : 55 + val; //55 = 'A'-10

        val = (unsigned char) (bytesList[i] & 0x0F);
        encoddedBytes[2 * i + 1] = (val <= 9) ? '0' + val : 55 + val;
    }
    return 0;
}

int GSMUtils::encodeinGsm7Bit(const char* const bytesList, size_t bytesLenght, char* const encoddedBytes, size_t* encodedLength)
{
    if (*encodedLength < ceil(7 * bytesLenght) / 8) //round up the input length multiplies with 7/8
    {
        return -1;
    }

    size_t index = 0;
    for (size_t i = 0; i < bytesLenght; i++)
    {
        //assume that each value from array is already from gsm 7 bit alphabet so only last 7 bits are used
        char val = bytesList[i] & 0x7F;
        size_t shiftSize = i % 8;
        encoddedBytes[index] = val >> shiftSize;
        if (index > 0)
        {
            encoddedBytes[index - 1] |= val << (8 - shiftSize);
        }
        if (i == 0 || (i + 1) % 8 != 0)
        {
            index++;
        }
    }
    *encodedLength = index;

    return 0;
}

int GSMUtils::semiDecimalOctets(const char* sdOctets, size_t sdSize, char* const encodedBytes, size_t* encodedLength)
{
    size_t finalLength = sdSize;
    bool odd = false;
    if (sdSize % 2 == 1)
    {
        odd = true;
        finalLength++;
    }
    if (*encodedLength < finalLength)
    {
        return -1;
    }
    *encodedLength = finalLength;

    for (size_t i = 0; i < (finalLength / 2); i++)
    {
        char oddPosVal = sdOctets[2 * i];
        if (odd && (i * 2 == finalLength - 2))
        {
            encodedBytes[2 * i] = 'F';
        } else
        {
            encodedBytes[2 * i] = sdOctets[2 * i + 1];
        }
        encodedBytes[2 * i + 1] = oddPosVal;
    }

    return 0;
}
