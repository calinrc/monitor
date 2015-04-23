/*
 *    Conf.h file written and maintained by Calin Cocan
 *    Created on: Apr 24, 2015
 *
 * This work is free: you can redistribute it and/or modify it under the terms of GPL License Version 2.0
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the License for more details.
 * You should have received a copy of the License along with this program. If not, see <http://choosealicense.com/licenses/gpl-2.0/>.

 ********************************************************************************************************************* */

#ifndef INCLUDE_CONF_H_
#define INCLUDE_CONF_H_

#include <string>
#include <map>

using namespace std;

class Conf
{
    static string getString(string name);
    static void init(map<string, string> properties);

private:
    Conf();
    virtual ~Conf();

    static Conf* s_THIS;

    map<string, string> m_props;


};

#endif /* INCLUDE_CONF_H_ */
