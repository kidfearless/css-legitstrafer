#include <Windows.h>

#include "SDK\SDK.h"
#include "CreateMove.h"

std::shared_ptr<Hook> clientmodehook = nullptr;

void main()
{
	createinterfaceFn client_factory = get_factory(GetModuleHandle("client.dll"));
	createinterfaceFn engine_factory = get_factory(GetModuleHandle("engine.dll"));

	interfaces.client = (IBaseClientDLL*)(client_factory("VClient017", nullptr));
	interfaces.engine = (IVEngineClient*)(engine_factory("VEngineClient014", nullptr));

	void** table = *(void***)(interfaces.client);
	interfaces.clientmode = **(IClientMode***)((DWORD)(table[10]) + 5);
	clientmodehook = std::shared_ptr<Hook>(new Hook(interfaces.clientmode));
	clientmodehook->hook(&hooked_createmove, 21);

	Beep(500, 200);
}

bool __stdcall DllMain(HMODULE hModule, DWORD Reason, LPVOID lpReserved)
{
	if (Reason == DLL_PROCESS_ATTACH)
	{
		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(main), NULL, NULL, nullptr);
		CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(strafe_thread), NULL, NULL, nullptr);
	}
	return TRUE;
}