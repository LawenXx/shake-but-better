#pragma once

namespace Minecraft {
	typedef void(*DrawText_t)(DWORD* renderType, int textIndex, int x, int y, int colo, int a6, int a7);
	extern DrawText_t Drawtext;

	extern void print(DWORD* renderType, int textIndex, int x, int y, int colo, int a6, int a7);
	extern void HookMc(DWORD b);
	extern void fill();
}