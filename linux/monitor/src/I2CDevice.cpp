/*
 *    I2CDevice.cpp file written and maintained by Calin Cocan
 *    Created on: Mar 4, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#include "I2CDevice.h"
#include "Logger.h"
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>

I2CDevice::I2CDevice() :
        m_fd(-1)
{
}

I2CDevice::~I2CDevice()
{
    close();
}
I2CError I2CDevice::init(const char* szDeviceName, int i2cAddress)
{
    m_fd = open(szDeviceName, O_RDWR);

    if (m_fd < 0)
    {
        LOGGING("Error opening file: %s", strerror(errno));
        return I2CINIT_FAIL;
    }
    if (ioctl(m_fd, I2C_SLAVE, i2cAddress) < 0)
    {
        LOGGING("ioctl error: %s", strerror(errno));
        return I2CINIT_FAIL;
    }

    return I2C_OK;
}
I2CError I2CDevice::receive(int& eventType, int& transmissionState, int& sensorsIds)
{
    if (read(m_fd, m_buff, 3) == 3)
    {
        eventType = m_buff[0];
        transmissionState = m_buff[1];
        sensorsIds = m_buff[2];
        return I2C_OK;
    } else
    {
        LOGGING("Fail to receive bytes because %s", strerror(errno));
        return I2CREAD_FAIL;
    }

}

I2CError I2CDevice::send(int commandId)
{
    m_buff[0] = commandId;
    if (write(m_fd, m_buff, 1) != 1)
    {
        LOGGING("Error writing file: %s", strerror(errno));
        return I2CWRITE_FAIL;
    }
    return I2C_OK;

}

I2CError I2CDevice::close()
{
    if (m_fd >= 0)
    {
        ::close(m_fd);
        m_fd = -1;
    }
    return I2C_OK;
}
