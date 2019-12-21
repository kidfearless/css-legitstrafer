#include "SDK.h"

Interfaces interfaces;

createinterfaceFn get_factory(HMODULE hModule)
{
	return (createinterfaceFn)GetProcAddress(hModule, "CreateInterface");
}

template <typename Fn> __forceinline Fn call_vfunc(void* class_base, int idx)
{
	return (Fn)((PDWORD)*(PDWORD*)class_base)[idx];
}

bool IVEngineClient::is_connected()
{
	typedef bool(__thiscall* connectedFn)(void*);
	return call_vfunc<connectedFn>(this, 27)(this);
}

//snip a bit of useless code