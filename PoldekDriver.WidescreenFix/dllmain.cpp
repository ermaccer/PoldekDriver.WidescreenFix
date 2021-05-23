// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <iostream>
#include "MemoryMgr.h"
#include "poldek.h"
#include "IniReader.h"

using namespace Memory::VP;


bool bPatchHUD;
void WINAPI GetResolution(BOOL bShow)
{
	TheScreen.x = *(int*)0x4AA34C;
	TheScreen.y = *(int*)0x4AA350;
	TheScreen.aspectRatio = (float)TheScreen.x / (float)TheScreen.y;


	// ratio
	Patch<float>(0x40AB21 + 1, TheScreen.aspectRatio);
	// 2d x
	if (bPatchHUD)
		Patch<float>(0x474424, 1.0f / (float)TheScreen.x * ((float)TheScreen.y / 480.0f));

	ShowCursor(bShow);
}


void Init()
{
	CIniReader ini("");

	bool bSkipMovies = ini.ReadBoolean("Settings", "bSkipIntro", true);
	bool bSkipAds= ini.ReadBoolean("Settings", "bSkipAds", true);
	bPatchHUD = ini.ReadBoolean("Settings", "bPatchHUD", true);

	if (bSkipMovies)
	Nop(0x41C458, 5);
	if (bSkipAds)
	{
		Nop(0x41CD2C, 5);
		Nop(0x41CD47, 5);
	}

	// logo
	Patch<int>(0x41C7BF + 1, -1);
	Patch<int>(0x41C7D4 + 1, -1);


	Nop(0x41C5AC, 6);
	InjectHook(0x41C5AC, GetResolution, PATCH_CALL);
	if (bPatchHUD)
		Patch<int>(0x477FD8, (int)Draw2D);

}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
		Init();

    return TRUE;
}

