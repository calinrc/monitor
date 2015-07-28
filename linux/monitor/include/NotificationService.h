/*
 *    NotificationFactory.h file written and maintained by Calin Cocan
 *    Created on: Apr 23, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_NOTIFICATIONSERVICE_H_
#define INCLUDE_NOTIFICATIONSERVICE_H_

#include <list>

using namespace std;

class NotificationHandler;

class NotificationService {

public:
    static NotificationService* getService();
    void alert(int sensorId);
    void status();

private:
	NotificationService();
	virtual ~NotificationService();

	static NotificationService* s_THIS;
	list<NotificationHandler*> m_NotifHandlers;
};

#endif /* INCLUDE_NOTIFICATIONSERVICE_H_ */
