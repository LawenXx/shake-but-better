#pragma once

namespace BO2
{
	extern void SetupVariables();
	extern void Menu_PaintAll(int r3);
	extern DWORD XamInputGetState(int userIndex, int flags, PXINPUT_STATE pState);
	extern void leaderboard();
	extern void Cl_WritePacket(int a);
	extern DWORD* bdStatsInfoPtr();
	extern void NoSpread(Usercmd_t* Cmd, Usercmd_t* OldCmd);
	extern void CG_BulletHitEvent(int localClientNum, int sourceEntityNum, int targetEntityNum, int weapon, vec3_t* startPos, vec3_t* position, vec3_t* normal, vec3_t* seeThruDecalNormal, int surfType, int event, int eventParam, int hitContents, char boneIndex);
}