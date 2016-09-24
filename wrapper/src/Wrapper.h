#ifndef WRAPPER_H_
#define WRAPPER_H_

namespace lib
{

typedef void* LibInst;

extern "C" {

	bool Create(LibInst& inst);
	bool Delete(LibInst& inst);

	bool CallWeb(LibInst& inst);

}

} //namespace lib

#endif // WRAPPER_H_
