/*
 *    NotificationHandler.h file written and maintained by Calin Cocan
 *    Created on: Apr 23, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_NOTIFICATIONHANDLER_H_
#define INCLUDE_NOTIFICATIONHANDLER_H_

class NotificationHandler {
public:
	virtual ~NotificationHandler(){};

	virtual void notify()=0;

};

#endif /* INCLUDE_NOTIFICATIONHANDLER_H_ */
