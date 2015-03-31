/*
 *    Serial.cpp file written and maintained by Calin Cocan
 *    Created on: Oct 20, 2014
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

 ********************************************************************************************************************* */

#include "Serial.h"
#include <stdint.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

Serial::Serial() :
        m_fd(0)
{

}

Serial::~Serial()
{
    this->close();
}

int Serial::open(char *port, unsigned long speed)
{
    m_fd = ::open(port, O_RDWR | O_NOCTTY | O_NDELAY);
    if (m_fd == -1)
    {
        return -1;
    }
    struct termios t_opt;
    unsigned long baud;
    switch (speed)
    {
        case 921600:
        case 115200:
        case 1000000:
        case 1500000:
            baud = speed;
            break;
        default:
            baud = 115200;
            break;
    }
    fcntl(m_fd, F_SETFL, 0);
    tcgetattr(m_fd, &t_opt);
    cfsetispeed(&t_opt, baud);
    cfsetospeed(&t_opt, baud);
    t_opt.c_cflag |= (CLOCAL | CREAD);
    t_opt.c_cflag &= ~PARENB;
    t_opt.c_cflag &= ~CSTOPB;
    t_opt.c_cflag &= ~CSIZE;
    t_opt.c_cflag |= CS8;
    t_opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    t_opt.c_iflag &= ~(IXON | IXOFF | IXANY);
    t_opt.c_iflag &= ~(ICRNL | INLCR);
    t_opt.c_oflag &= ~(OCRNL | ONLCR);
    t_opt.c_oflag &= ~OPOST;
    t_opt.c_cc[VMIN] = 0;
    t_opt.c_cc[VTIME] = 10;
    tcflush(m_fd, TCIOFLUSH);

    return tcsetattr(m_fd, TCSANOW, &t_opt);
}

int Serial::write(char *buf, int size)
{
    return ::write(m_fd, buf, size);
}

int Serial::read(char *buf, int size)
{
    int len = 0;
    int ret = 0;

    int count = 0;
    while (len < size && count < 10)
    {
        ret = ::read(m_fd, buf + len, size - len);
        if (ret == -1)
        {
            return -1;
        }

        if (ret == 0)
        {
            count++;
        } else
        {
            len += ret;
            count = 0;
        }
    }

    return len;
}

int Serial::close()
{
    if (m_fd != 0 || m_fd != -1)
    {
        ::close(m_fd);
        m_fd = 0;
    }
    return 0;
}
