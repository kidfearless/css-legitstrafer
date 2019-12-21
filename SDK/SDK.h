#pragma once

#include <Windows.h>

#include "vector.h"

typedef void*(*createinterfaceFn)(const char*, int*);

createinterfaceFn get_factory(HMODULE hModule);

template <typename T> __forceinline T call_vfunc(void* class_base, int idx);

class IVEngineClient
{
public:
	bool is_connected();
};

class IBaseClientDLL
{
};

class IClientMode
{
public:
	char _pad[28];
};

class Interfaces
{
public:
	IVEngineClient* engine = nullptr;
	IBaseClientDLL* client = nullptr;
	IClientMode* clientmode = nullptr;
}; extern Interfaces interfaces;

class CUserCmd
{
	virtual ~CUserCmd() {};
public:
	int command_number;
	int tick_count;
	Vector3 viewangles;
	float forwardmove;
	float sidemove;
	float upmove;
	int buttons;
	unsigned char impulse;
	int weaponselect;
	int weaponsubtype;
	int random_seed;
	short mousedx;
	short mousedy;
	bool hasbeenpredicted;
};