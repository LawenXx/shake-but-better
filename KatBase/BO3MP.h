#pragma once
namespace BO3 {
	extern HRESULT R_RenderScene();
	extern DWORD XamInputGetState(int userIndex, int flags, PXINPUT_STATE pState);
	extern void CL_ReadyToSendPacket(int local);
	extern void PaintAllHook(int r3);
}