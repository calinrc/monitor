/*
 *    Serial.h file written and maintained by Calin Cocan
 *    Created on: Oct 20, 2014
 *
 * This work is free: you can redistribute it and/or modify it under the terms of Apache License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/apache-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_DEVICES_SERIAL_H_
#define INCLUDE_DEVICES_SERIAL_H_

class Serial
{
public:
    Serial();
    virtual ~Serial();


    //use numeric values for error code . Usually -1 means error.
    int open(char *port, unsigned long speed);
    int write(char *buf, int size);
    int read(char *buf, int size);
    int close();

private:
    int m_fd;
};

#endif /* INCLUDE_DEVICES_SERIAL_H_ */
