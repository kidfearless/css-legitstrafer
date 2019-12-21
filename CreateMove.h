#pragma once

#include <Windows.h>

#include "SDK\SDK.h"
#include "Autostrafe.h"

bool __fastcall hooked_createmove(void* ecx, void* edx, float frametime, CUserCmd* cmd);