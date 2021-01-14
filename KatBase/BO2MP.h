#pragma once

namespace BO2
{
	extern void SetupVariables();
	extern void Menu_PaintAll(int r3);
	extern DWORD XamInputGetState(int userIndex, int flags, PXINPUT_STATE pState);
	extern void leaderboard();
	extern void Cl_WritePacket(int a);
	extern DWORD* bdStatsInfoPtr();
}