#pragma once

namespace BO2
{
	extern void SetupVariables();
	extern void Menu_PaintAll(int r3);
	extern DWORD XamInputGetState(int userIndex, int flags, PXINPUT_STATE pState);
	extern void leaderboard();

	typedef DWORD(*someshit)(void*);
	extern someshit some;
	extern DWORD* bdStatsInfoPtr();
}