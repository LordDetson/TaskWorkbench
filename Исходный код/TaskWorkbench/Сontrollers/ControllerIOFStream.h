/*
 * ControllerIOFStream.h
 *
 *  Created on: 12 но€б. 2017 г.
 *      Author: ƒмитрий
 */

#ifndef COMTROLLERS_CONTROLLERIOFSTREAM_H_
#define COMTROLLERS_CONTROLLERIOFSTREAM_H_

#include <string>
#include <list>
#include <fstream>
using namespace std;

template<class T>
list<T> readFile(string path, list<T>& List) {
	List.clear();
	ifstream inputStream(path);
	size_t size;
	T buf;
	inputStream >> size;
	for (size_t i = 0; i < size; i++) {
		inputStream >> buf;
		List.push_back(buf);
	}
	inputStream.close();
	return List;
}

template<class T>
void writeFile(string path, list<T>& List) {
	ofstream outputStream(path);
	outputStream << List.size() << "\n";
	for (T ptr : List) {
		outputStream << ptr << endl;
	}
	outputStream.close();
}

#endif /* COMTROLLERS_CONTROLLERIOFSTREAM_H_ */
