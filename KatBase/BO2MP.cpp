#include "pch.h"

namespace BO2
{

#define LODWORD(x)  (*((DWORD*)&(x)))  // low dword
#define HIDWORD(x)  (*((DWORD*)&(x)+1))
	DWORD* bdTaskResult()
	{
		DWORD* result;
		*result = 0x820F6E58;
		return result;
	}
	DWORD* bdStatsInfoPtr() {
		DWORD* result;
		*result = 0x820FB3B0;
		return result;
	}

	int bdStatsInfo(int a1)
	{
		__int64 v2; // r11

		bdTaskResult();
		LODWORD(v2) = 0;
		HIDWORD(v2);
		*(DWORD*)(a1 + 4) = 0; //leaderboard id
		*(DWORD*)a1;
		*(QWORD*)(a1 + 8) = v2;
		*(DWORD*)(a1 + 16) = 1;
		*(QWORD*)(a1 + 24) = v2;
		*(QWORD*)(a1 + 32) = v2;
		*(DWORD*)(a1 + 108) = 0;
		memset(&a1 + 40, 0, 65);
		return a1;
	}
	void leaderboard() {}

	void SpoofLevel() {
		if (options.BoolRank.state) {
			PlayerCmd_SetPrestige(1337, cgGame->clientNum);
			PlayerCmd_SetRank(1337, cgGame->clientNum);
		}
	}

	void DrawMenuText()
	{
		options.menuMaxScroll = 0;
		options.menuOptionIndex = 0;

		SubMenuMenuOption_List.clear();
		BoolMenuOption_List.clear();
		IntMenuOption_List.clear();
		FloatMenuOption_List.clear();

		switch (options.menuPageIndex)
		{
		case MAIN:
			DrawToggle("Spoof Rank", &options.BoolRank);
			DrawStringSlider("Font", &options.menuFontIndex, FontForIndex(options.menuFontIndex.current));
			break;
		case AIMBOT:
			DrawToggle("Aimbot", &options.AimbotToggle);
			break;
		case VISUALS:
			DrawToggle("Esp Box", &options.EspBoxToggle);
			DrawToggle("Esp Bones", &options.EspDrawBones);
			DrawToggle("Esp BoxFrog", &options.EspFrogChan);
			break;
		case PLAYERS:
			for (int i = 0; i < 18; i++) {
				if (!strcmp(cgGame->clientInfo[i].name, ""))
					DrawButton("N/A");
				else
					DrawButton(va("[%i] %s [%s]", i, cgGame->clientInfo[i].name, isTeam(&cg_entitiesArray[i]) ? "^2Friendly^7" : "^1Enemy^7"));
			}
			break;

		case SETTINGS:
			DrawIntSlider("Menu X", &options.menuX, "%i");
			break;
		}
	}

	void DrawMenu()
	{
		DrawMenuShader();
		DrawMenuTabs();

		//Options
		DrawMenuText();

	}

	int nearestClient;
	bool playerReady;
	vec3_t anglesOut;

	int GetNearestPlayer(int client)
	{
		nearestClient = -1;
		float nearestDistance = FLT_MAX;
		for (int i = 0; i < 18; ++i)
		{
			if (cgGame->clientNum == i)
				continue;
			if (cg_entitiesArray[i].pose.eType != ET_PLAYER)
				continue;

			if (isTeam(&cg_entitiesArray[i]))
				continue;

			float Distance = cg_entitiesArray[client].pose.Origin.GetDistance(cg_entitiesArray[i].pose.Origin);
			if (AimTarget_IsTargetVisible(0, &cg_entitiesArray[i]))
			{
				if (Distance < nearestDistance)
				{
					nearestDistance = Distance;
					nearestClient = i;
					playerReady = true;
				}
			}
		}
		return nearestClient;
	}

	void doAimbot()
	{
		if (options.AimbotToggle.state) {
			if (!Dvar_GetBool("cl_ingame"))
				return;
			if (cgGame->ps.health < 1)
				return;

			int nearestClient = GetNearestPlayer(cgGame->clientNum);
			if (playerReady && nearestClient != -1)
			{
				vec3_t Difference = AimTarget_GetTagPos(&cg_entitiesArray[nearestClient], "j_neck");
				vec3_t Angles = Difference - cgGame->refdef.viewOrigin;
				VecToAngels(Angles, anglesOut);
				if (nearestClient != cgGame->clientNum)
					ClientActive->viewAngle = anglesOut - ClientActive->baseAngle;
			}
			playerReady = false;
		}
	}

	void Menu_PaintAll(int r3)
	{
		MinHook[0].Stub(r3);
		readStructs();

		options.menuHeight = options.menuTabHeight + (options.menuMaxScroll * (R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current)) + (options.menuBorder.current * 2) + 2;
		if (options.menuOpen)
			DrawMenu();

		if (Dvar_GetBool("cl_ingame"))
		{

			for (int i = 0; i < 18; i++)
			{
				if (!(cg_entitiesArray[i].pose.eType == ET_PLAYER && (cg_entitiesArray[i].pose.eType != ET_PLAYER_CORPSE)))
					continue;
				if (!(cg_entitiesArray[i].nextState.ClientNumber != 0))
					continue;
				if (!(cg_entitiesArray[i].nextState.Alive))
					continue;
				if (!cg_entitiesArray[i].nextState.State & (1 << 6) != 0)
					continue;

				vec2_t Pos = vec2_t();
				vec2_t head = vec2_t();
				vec3_t origin = cg_entitiesArray[i].pose.Origin;

				vec3_t headPos = AimTarget_GetTagPos(&cg_entitiesArray[i], "j_helmet");
				headPos.z += 10;
				origin.z -= 5;

				if (!WorldToScreen(0, origin, &Pos))
					continue;
				if (!WorldToScreen(0, headPos, &head))
					continue;

				float playerHeight = fabsf(head.y - Pos.y);
				float playerWidth = (fabsf(head.y - Pos.y) * 0.65f);

				if (options.EspBoxToggle.state)
					BoundingBox(Pos.x - (playerWidth / 2.f) - 6.f, head.y - 4.f, playerWidth, playerHeight, white, 1.f);
				if (options.EspDrawBones.state)
					drawBones(&cg_entitiesArray[i], white);
				if (options.EspDrawLine.state)
					DrawLine(vec2_t(cgDC->screenWidth / 2, cgDC->screenHeight - 5), Pos, white, 1);
				if (options.EspFrogChan.state)
					drawHeart(Pos.x - (playerWidth / 2.f) - 6.f, head.y - 4.f, playerWidth, playerHeight, Red, Red);
			}
			SpoofLevel();
			doAimbot();
		}
	}

	int speed = 0;
	int ticks = 0;
	bool run = false;
	short PreviousButton;

	DWORD XamInputGetState(int userIndex, int flags, PXINPUT_STATE pState)
	{
		run = false;

		DWORD result = XInputGetStateEx(userIndex, flags, pState);

		if (pState->Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
			run = true;

		pState->Gamepad.wButtons = 0;

		if (run)
			pState->Gamepad.wButtons = XINPUT_GAMEPAD_LEFT_THUMB;
		if (userIndex != 0)
			return XInputGetStateEx(userIndex, flags, pState);

		XInputGetState(0, &Buttons);

		if (PreviousButton != Buttons.Gamepad.wButtons)
		{
			PreviousButton = Buttons.Gamepad.wButtons;

			if (Buttons.Gamepad.bLeftTrigger > 100 && KeyIsDown(Buttons, XINPUT_GAMEPAD_RIGHT_THUMB))
			{
				options.menuOpen = !options.menuOpen;
			}

			if (!options.menuOpen)
				return XInputGetStateEx(userIndex, flags, pState);


			if (KeyIsDown(Buttons, XINPUT_GAMEPAD_DPAD_DOWN))
			{
				if (options.menuScroll < options.menuMaxScroll)
					options.menuScroll++;
				if (options.menuScroll == options.menuMaxScroll)
					options.menuScroll = 0;
			}

			if (KeyIsDown(Buttons, XINPUT_GAMEPAD_DPAD_UP))
			{
				if (options.menuScroll > -1)
					options.menuScroll--;
				if (options.menuScroll == -1)
					options.menuScroll = options.menuMaxScroll - 1;
			}
			if (KeyIsDown(Buttons, XINPUT_GAMEPAD_RIGHT_SHOULDER))
			{
				if (options.menuPageIndex < 5)
					options.menuPageIndex++;
				if (options.menuPageIndex > 4)
					options.menuPageIndex = 0;
			}

			if (KeyIsDown(Buttons, XINPUT_GAMEPAD_LEFT_SHOULDER))
			{
				if (options.menuPageIndex > -1)
					options.menuPageIndex--;
				if (options.menuPageIndex == -1)
					options.menuPageIndex = 4;
			}


			if (KeyIsDown(Buttons, XINPUT_GAMEPAD_X))
			{
				ToggleBool_List(options.menuScroll);
				ResetInt_List(options.menuScroll);
				ResetFloat_List(options.menuScroll);
				SwitchToSubMenu_List(options.menuScroll, options.menuPageIndex, options.isInSubMenu, options.menuScroll, options.previousPageIndex, options.previousScroll);
			}

			if (KeyIsDown(Buttons, XINPUT_GAMEPAD_B))
			{
				options.menuOpen = !options.menuOpen;
			}

			if (KeyIsDown(Buttons, XINPUT_GAMEPAD_DPAD_RIGHT))
			{
				AddInt_List(options.menuScroll);
				AddFloat_List(options.menuScroll);
			}

			if (KeyIsDown(Buttons, XINPUT_GAMEPAD_DPAD_LEFT))
			{
				SubInt_List(options.menuScroll);
				SubFloat_List(options.menuScroll);
			}

			if (!KeyIsDown(Buttons, XINPUT_GAMEPAD_DPAD_RIGHT))
			{
				speed = 0;
				ticks = 0;
			}

			if (!KeyIsDown(Buttons, XINPUT_GAMEPAD_DPAD_LEFT))
			{
				speed = 0;
				ticks = 0;
			}

			if (!options.menuOpen)
				return XInputGetStateEx(userIndex, flags, pState);
		}

		if (!options.menuOpen)
			return XInputGetStateEx(userIndex, flags, pState);

		if (KeyIsDown(Buttons, XINPUT_GAMEPAD_DPAD_RIGHT))
		{
			speed++;

			if (ticks < 50)
			{
				ticks += speed;
				return result;
			}

			AddInt_List(options.menuScroll);
			AddFloat_List(options.menuScroll);

			ticks = 0;
		}

		if (KeyIsDown(Buttons, XINPUT_GAMEPAD_DPAD_LEFT))
		{
			speed++;

			if (ticks < 50)
			{
				ticks += speed;
				return result;
			}

			SubInt_List(options.menuScroll);
			SubFloat_List(options.menuScroll);

			ticks = 0;
		}

		if (!options.menuOpen)
			return XInputGetStateEx(userIndex, flags, pState);

		return result;
	}
}