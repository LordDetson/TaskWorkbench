/*
 * HashPasswordWithSal.h
 *
 *  Created on: 16 но€б. 2017 г.
 *      Author: ƒмитрий
 */

#ifndef HASHPASSWORDWITHSAL_H_
#define HASHPASSWORDWITHSAL_H_

#include <string>
#include <functional>
using namespace std;

class HashPasswordWithSal{
public:
	string operator()(const string password, const string sal) const{
		size_t h1 = hash<string>()(password);
		size_t h2 = hash<string>()(sal);
		return to_string(h1^(h2 << 1));
	}
};

#endif /* HASHPASSWORDWITHSAL_H_ */
