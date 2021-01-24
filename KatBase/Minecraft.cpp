#include "pch.h"

namespace Minecraft {
	int yes = 0;
	void HookMc(int a, int b)
	{
		printf("Minecraft all these blocks just form this way");
		if (yes > 0) {
			printf("Fuck Off Davide");
			printf("Fuck Off Zone");
		}
		MinHook[0].Stub(a, b);
	}

}