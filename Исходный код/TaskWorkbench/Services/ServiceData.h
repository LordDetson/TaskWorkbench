/*
 * ServiceData.h
 *
 *  Created on: 14 но€б. 2017 г.
 *      Author: ƒмитрий
 */

#ifndef SERVICES_SERVICEDATA_H_
#define SERVICES_SERVICEDATA_H_

#include <iostream>
#include <list>
#include "../Data_Classes/UserAccount.h"
#include "../Data_Classes/Task.h"
using namespace std;

template<class T>
void showList(list<T> List) {
	for (T ptr : List) {
		cout << ptr << endl;
	}
}

#endif /* SERVICES_SERVICEDATA_H_ */
