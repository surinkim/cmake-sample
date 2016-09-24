#include "Wrapper.h"
#include "core.h"

namespace lib
{

bool Create(LibInst& inst)
{
	if (inst != nullptr )
		return false;

	inst = static_cast<LibInst>(new Core());
	return true;
}

bool Delete(LibInst& inst)
{
	if(inst == nullptr)
		return false;

	delete inst;
	return true;
}

bool CallWeb( LibInst& inst )
{
	if ( inst == nullptr )
		return false;

	return static_cast<Core*>(inst)->CallWeb();
}

} //namesapce