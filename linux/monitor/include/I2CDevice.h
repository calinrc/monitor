/*
 *    I2CDevice.h file written and maintained by Calin Cocan
 *    Created on: Mar 4, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_I2CDEVICE_H_
#define INCLUDE_I2CDEVICE_H_

#include "gendef.h"

class I2CDevice
{
public:
    I2CDevice();
    virtual ~I2CDevice();
    virtual I2CError init(const char* szDeviceName, int i2cAddress);
    virtual I2CError receive(int& eventType, int& transmissionState, int& sensorsIds);
    virtual I2CError send(int commandId);
    virtual I2CError close();

private:
    int m_fd;
    char m_buff[3];
};

#endif /* INCLUDE_I2CDEVICE_H_ */
