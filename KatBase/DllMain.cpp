#include "pch.h"

std::uintptr_t CurrentId;
bool unloading, onDash, firstDash;
HANDLE Thread;
DWORD ThreadId;

DWORD CheckUnload()
{
	while (XamGetCurrentTitleId() == CurrentId && !unloading)
	{
		//just keep this thread from ending, you can do any thing you want to loop aka memory editing while ingame here
	}
	if (unloading)
	{
		StopHooks();
		CleanHooks();
	}
	else
		CleanHooks();

	return 0;
}
void checkTitleId(std::uintptr_t id)
{
	CurrentId = id;

	switch (id)
	{
	case DASHBOARD:
		goto nogame;
		break;
	case FREESTYLEDASH:
		goto nogame;
		break;
	case COD_BLACK_OPS_2:

		while (*(int*)BO2::MP_XamInputGetKeyState == 0) //I Check XamInputGetState make sure the games xex is fully loaded before hooking
		{
			Sleep(100);
		}
		XNotify("Shake [Bo2] By Kat And Reeko", XNOTIFYUI_TYPE_SONGPLAYING);

		BO2::InitAddress();
		BO2::SetupVariables();

		MinHook[0] = MinHook_t(BO2::MP_Menu_PaintAll, (std::uint64_t)BO2::Menu_PaintAll, true);
		MinHook[1] = MinHook_t(BO2::MP_XamInputGetKeyState, (std::uint64_t)BO2::XamInputGetState, false);
		MinHook[2] = MinHook_t(0x8293E5C4, (std::uint64_t)BO2::NetDll_XNetGetTitleXnAddrHook, true);
		break;
	case COD_BLACK_OPS_3:
		while (*(int*)0x82A92094 == 0) 
		{
			Sleep(100);
		}
		XNotify("Shake [Bo3] By Kat And Reeko", XNOTIFYUI_TYPE_SONGPLAYING);

		BO3::InitAddress();
		BO3::SetupVariables();

		MinHook[0] = MinHook_t(0x82A92094, (std::uint64_t)BO3::XamInputGetState, false);
		MinHook[1] = MinHook_t(0x822A06F0, (std::uint64_t)BO3::R_RenderScene, true);
		MinHook[2] = MinHook_t(0x822112F0, (std::uint16_t)BO3::Menu_PaintAll, true);
		break;

	default:
		goto done;
	nogame:
		if (!onDash)
		{
			if (!firstDash)
			{
				XNotify("Shake Unloaded Hooks");
				firstDash = true;
			}
			onDash = true;
		}
		goto done;
		break;
	}

	StartHooks();

	ExCreateThread(&Thread, 0, &ThreadId, (PVOID)XapiThreadStartup, (LPTHREAD_START_ROUTINE)CheckUnload, 0, 2);
	XSetThreadProcessor(Thread, 4);
	ResumeThread(Thread);
	CloseHandle(Thread);

done:
	return;
}

DWORD TitleID()
{
	while (!unloading)
	{
		if (XamGetCurrentTitleId() != CurrentId)
			checkTitleId(XamGetCurrentTitleId());
	}
	return 0;
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		HANDLE hThread; 
		DWORD dwThreadId;
		ExCreateThread(&hThread, NULL, &dwThreadId, (PVOID)XapiThreadStartup, (LPTHREAD_START_ROUTINE)TitleID, 0, 2 | CREATE_SUSPENDED);
		XSetThreadProcessor(hThread, 4);
		SetThreadPriority(hThread, THREAD_PRIORITY_NORMAL);
		ResumeThread(hThread);

		checkTitleId(XamGetCurrentTitleId());
	}
	if (dwReason == DLL_PROCESS_DETACH)
	{
		unloading = true;
		Sleep(250);
	}
	return true;
}