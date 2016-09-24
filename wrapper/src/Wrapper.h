#ifndef WRAPPER_H_
#define WRAPPER_H_

#include <iostream>

namespace lib
{

typedef void* LibInst;

extern "C" {

	bool Create(LibInst& inst);
	bool Delete(LibInst& inst);

	bool CallHttp(LibInst& inst, const std::wstring& url);

}

} //namespace lib

#endif // WRAPPER_H_
