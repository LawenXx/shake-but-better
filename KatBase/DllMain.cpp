#include "pch.h"

std::uintptr_t CurrentId;
bool unloading, onDash, firstDash;
HANDLE Thread;
DWORD ThreadId;
LPCWSTR buttons[2] = { L"Zone likes big PP",L"Davide likes big PP" };
MESSAGEBOX_RESULT result;
XOVERLAPPED overlapped;

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
		XNotify("Shake [BO2] Loaded", XNOTIFYUI_TYPE_SONGPLAYING);

		BO2::InitAddress();
		BO2::SetupVariables();
		ReadImage();
		//cg_hitevent
		*(DWORD*)(0x822585F8) = 0x60000000;

		//R_EndFrame
		*(DWORD*)(0x828B9F64) = 0x60000000;
		*(DWORD*)(0x828B9F68) = 0x60000000;

		MinHook[0] = MinHook_t(BO2::MP_Menu_PaintAll, (std::uint64_t)BO2::Menu_PaintAll, true);
		MinHook[1] = MinHook_t(BO2::MP_XamInputGetKeyState, (std::uint64_t)BO2::XamInputGetState, false);
		MinHook[2] = MinHook_t(0x8293E5C4, (std::uint64_t)BO2::NetDll_XNetGetTitleXnAddrHook, true);
		MinHook[3] = MinHook_t(0x8226C9C8, (std::uint64_t)BO2::Cl_WritePacket, true);
		MinHook[4] = MinHook_t(0x828AF5A0, (std::uint64_t)BO2::RenderScene, true);
		MinHook[5] = MinHook_t(0x828BA040, (std::uint64_t)BO2::Quad_Hook, true);
		MinHook[6] = MinHook_t(0x82267520, (std::uint64_t)BO2::CL_ConsolePrintHook, true);
		MinHook[7] = MinHook_t(0x82278A00, (std::uint64_t)BO2::CL_Disconnect_Hook, true);
		break;
	case COD_BLACK_OPS_3:
		while (*(int*)0x82A92094 == 0)
		{
			Sleep(100);
		}
		XNotify("Shake [BO3] Loaded", XNOTIFYUI_TYPE_SONGPLAYING);

		BO3::InitAddress();
		BO3::SetupVariables();

		MinHook[0] = MinHook_t(0x82A92094, (std::uint64_t)BO3::XamInputGetState, false);
		MinHook[1] = MinHook_t(0x822A06F0, (std::uint64_t)BO3::R_RenderScene, true);
		MinHook[2] = MinHook_t(0x822E58F8, (std::uint64_t)BO3::CL_ReadyToSendPacket, true);
		MinHook[3] = MinHook_t(0x8227CA40, (std::uint64_t)BO3::CG_BulletHitEvent, true);
		break;
	case COD_GHOSTS:
		while (*(int*)Ghost::XamInputGetKeyState == 0)
		{
			Sleep(100);
		}
		XNotify("Shake [Ghost] Loaded", XNOTIFYUI_TYPE_SONGPLAYING);
		
		Ghost::InitAddress();
		Ghost::SetupVariables();

		/*MinHook[0] = MinHook_t(Ghost::Menu_PaintAll_MP, (std::uint64_t)Ghost::Menu_Paint_All, true);
		MinHook[1] = MinHook_t(Ghost::XamInputGetKeyState, (std::uint64_t)Ghost::XamInputGetState, false);
		MinHook[2] = MinHook_t(Ghost::Cl_WritePacket_MP, (std::uint64_t)Ghost::Cl_WritePacket, true);*/
		break;
	case MINECRAFT:
		while (*(int*)Minecraft::XamInputGetKeyState == 0)
		{
			Sleep(100);
		}
		XNotify("Shake [Minecraft] Loaded", XNOTIFYUI_TYPE_SONGPLAYING);
		Minecraft::fill();

		//MinHook[0] = MinHook_t(0x8247D000, (std::uint64_t)Minecraft::HookMc, true);
		MinHook[0] = MinHook_t(0x82A11D78, (std::uint64_t)Minecraft::print, true);
		break;
	default:
		goto done;
	nogame:
		if (!onDash)
		{
			if (!firstDash)
			{
				XShowMessageBoxUI(0, L"Shake", L"Shake by Kat xKoVx\nYoutube/kat xkovx\nThis wouldnt be possible without the help from:\nReeko for making the base\nSmokey xKoVx for wallhack and laser\nSoul for radar", 2, buttons, 0, XMB_ERRORICON, &result, &overlapped);

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