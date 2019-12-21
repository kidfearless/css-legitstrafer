#include "CreateMove.h"

bool __fastcall hooked_createmove(void* ecx, void* edx, float frametime, CUserCmd* cmd)
{
	if (cmd->command_number == 0)
		return false;

	if (interfaces.engine->is_connected())
		autostrafe(cmd);

	return false;
}