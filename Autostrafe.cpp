#include <Windows.h>

#include "Autostrafe.h"

void do_input(UINT keycode, bool b)
{
	if (b)
		keybd_event(0, MapVirtualKey(keycode, MAPVK_VK_TO_VSC), KEYEVENTF_SCANCODE, 0);
	else
		keybd_event(0, MapVirtualKey(keycode, MAPVK_VK_TO_VSC), KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP, 0);
}

int cur_dx = 0;
bool should_strafe = false;
std::string cur_key = "...";

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
				cur_key = "...";
			}
			else if (cur_dx == 1 && cur_key != "D") //mousedx > 0
			{
				do_input(0x41, false);
				Sleep(rand() % 6 + 4);
				do_input(0x44, true);
				cur_key = "D";
			}
			else if (cur_dx == 2 && cur_key != "A") //mousedx < 0
			{
				do_input(0x44, false);
				Sleep(rand() % 6 + 4);
				do_input(0x41, true);
				cur_key = "A";
			}
		}
	}
}

void autostrafe(CUserCmd* cmd)
{
	if (!should_strafe && cmd->buttons & (1 << 1)) //(1 << 1) == IN_JUMP
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