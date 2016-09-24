#include "wrapper/src/Wrapper.h"

#include <iostream>

int main()
{
	lib::LibInst inst = nullptr;
	bool ret = lib::Create(inst);
	if ( ret == false )
		return -1;

	ret = lib::CallWeb(inst);
	if ( ret == false )
		return -1;

	ret = lib::Delete(inst);
	if ( ret == false )
		return -1;

	getchar();

	return 0;
}