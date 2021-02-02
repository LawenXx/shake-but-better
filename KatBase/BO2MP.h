#pragma once

namespace BO2
{
	extern void SetupVariables();
	extern void Menu_PaintAll(int a, int b);
	extern DWORD XamInputGetState(int userIndex, int flags, PXINPUT_STATE pState);
	extern void Cl_WritePacket(int a);
	extern void NoSpread(Usercmd_t* cmd, Usercmd_t* oldCmd);
	extern void CG_BulletHitEvent(int localClientNum, int sourceEntityNum, int targetEntityNum, int weapon, vec3_t* startPos, vec3_t* position, vec3_t* normal, vec3_t* seeThruDecalNormal, int surfType, int event, int eventParam, int hitContents, char boneIndex);
	extern HRESULT RenderScene(DWORD a1);
}