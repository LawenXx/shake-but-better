#include "pch.h"

namespace Minecraft {
	int yes = 0;
	void yesnew() {
		if (yes > 0) {
			printf("Fuck Off Davide");
			printf("Fuck Off Zone");
			printf("Fuck Off Kontrol");
			printf("Why you looking here lol");
		}
	}

	DrawText_t Drawtext;

	void fill() {
		Drawtext = DrawText_t(0x82A11D78);
	}

	void HookMc(DWORD b)
	{
		//printf("Minecraft all these blocks just form this way");
		
		MinHook[1].Stub( b);
	}
	void print(DWORD* renderType, int textIndex, int x, int y, int colo, int a6, int a7) {
	
		printf("0x%X");

		MinHook[0].Stub(renderType, textIndex, x, y, colo, a6, a7);
	}
}