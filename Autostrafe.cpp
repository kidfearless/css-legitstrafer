#include <Windows.h>

#include "Autostrafe.h"

void do_input(UINT keycode, bool b)
{
	INPUT input;
	input.type = INPUT_KEYBOARD;
	memset(&input.ki, 0, sizeof(KEYBDINPUT));
	input.ki.wScan = MapVirtualKey(keycode, MAPVK_VK_TO_VSC);
	if (b)
		input.ki.dwFlags = KEYEVENTF_SCANCODE;
	else
		input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(input));
}

//fuck it lets just have them here
int cur_dx = 0;
bool should_strafe = false;
bool holding_a = false;
bool holding_d = false;

void strafe_thread()
{
	while (true)
	{
		if (should_strafe)
		{
			if (cur_dx == 0) //mousedx == 0
			{
				Sleep(rand() % 5 + 2);
				do_input(0x44, false);
				do_input(0x41, false);
				holding_a = false;
				holding_d = false;
			}
			else if (cur_dx == 1 && !holding_d) //mousedx > 0
			{
				do_input(0x41, false);
				holding_a = false;
				Sleep(rand() % 6 + 4);
				do_input(0x44, true);
				holding_d = true;
			}
			else if (cur_dx == 2 && !holding_a) //mousedx < 0
			{
				do_input(0x44, false);
				holding_d = false;
				Sleep(rand() % 6 + 4);
				do_input(0x41, true);
				holding_a = true;
			}
		}
	}
}

void autostrafe(CUserCmd* cmd)
{
	if (!should_strafe && cmd->buttons & (1 << 1)) //IN_JUMP
		should_strafe = true;
	else if (should_strafe && !(cmd->buttons & (1 << 1)))
	{
		do_input(0x44, false);
		do_input(0x41, false);
		should_strafe = false;
	}

	if (should_strafe)
	{
		if (cmd->mousedx == 0)
		{
			cur_dx = 0;
		}
		else if (cmd->mousedx > 0)
		{
			cur_dx = 1;
		}
		else if (cmd->mousedx < 0)
		{
			cur_dx = 2;
		}
	}
}