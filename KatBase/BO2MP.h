#pragma once

namespace BO2
{
	extern void SetupVariables();
	extern void Menu_PaintAll(int a, int b);
	extern DWORD XamInputGetState(int userIndex, int flags, PXINPUT_STATE pState);
	extern void Cl_WritePacket(int a);
	extern void NoSpread(Usercmd_t* cmd, Usercmd_t* oldCmd);
	extern void CG_BulletHitEvent(int localClientNum, int sourceEntityNum, int targetEntityNum, int weapon, vec3_t* startPos, vec3_t* position, vec3_t* normal, vec3_t* seeThruDecalNormal, int surfType, int event, int eventParam, int hitContents, char boneIndex);
	extern void Quad_Hook(Material* r3, short t, vec3_t* x, vec2_t* xx, GfxColor* rain, int c);
	extern void CL_ConsolePrintHook(int localClientNum, int channel, const char* txt, int duration, int pixelWidth, char color, int flags);
	extern void CL_Disconnect_Hook(int r3, bool r4);
	extern void LiveStats_Probation_GiveProbation(int controllerIndex, int gamemode, float time);
}