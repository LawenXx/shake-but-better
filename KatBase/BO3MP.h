#pragma once
namespace BO3 {
	extern void R_RenderScene();
	extern void Menu_PaintAll();
	extern DWORD XamInputGetState(int userIndex, int flags, PXINPUT_STATE pState);
	extern void CL_ReadyToSendPacket(int local);
}