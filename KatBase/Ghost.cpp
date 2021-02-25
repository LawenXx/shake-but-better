#include "pch.h"

namespace Ghost {

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
			DrawButton("Test");
			break;
		case AIMBOT:
			DrawButton("Test");
			DrawButton("Test");
			DrawButton("Test");
			DrawButton("Test");
			break;
		case VISUALS:
			DrawButton("Test");
			DrawButton("Test");
			DrawButton("Test");
			DrawButton("Test");
			DrawButton("Test");
			break;
		case PLAYERS:
			DrawButton("Test");
			DrawButton("Test");
			DrawButton("Test");
			DrawButton("Test");
			DrawButton("Test");
			break;

		case SETTINGS:
			DrawIntSlider("Menu X", &options.menuX, "%i");
			DrawIntSlider("Menu Y", &options.menuY, "%i");
			DrawFloatSlider("Font Size", &options.menuFontSize, "%f");
			DrawStringSlider("Font", &options.menuFontIndex, FontForIndex(options.menuFontIndex.current));
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

	void Esp() {
		for (int i = 0; i < 18; i++)
		{

			/*if (!(cg_entitiesArray[i].pose.eType == ET_PLAYER && (cg_entitiesArray[i].pose.eType != ET_PLAYER_CORPSE)))
				continue;
			if (!(cg_entitiesArray[i].nextState.ClientNumber != 0))
				continue;
			if (!(cg_entitiesArray[i].nextState.Alive))
				continue;
			if (!cg_entitiesArray[i].nextState.State & (1 << 6) != 0)
				continue;
			if (cgGame->ps.health < 1)
				return;*/
			if (!(cg_entitiesarray[i].State == ET_PLAYER && (cg_entitiesarray[i].State != ET_PLAYER_CORPSE)))
				continue;
		/*	if (!cg_entitiesarray[i].state & (1 << 6) != 0)
				continue;*/

			vec2_t Pos = vec2_t();
			vec2_t head = vec2_t();
			vec3_t origin = cg_entitiesarray[i].mPos;

			vec3_t headPos = AimTarget_GetTagPos(&cg_entitiesarray[i], "j_head");
			headPos.z += 10;
			origin.z -= 5;

			if (!WorldToScreen(origin, &Pos))
				continue;
			if (!WorldToScreen(headPos, &head))
				continue;

			float playerHeight = fabsf(head.y - Pos.y);
			float playerWidth = (fabsf(head.y - Pos.y) * 0.65f);

			//if (options.EspBoxToggle.state)
				BoundingBox(Pos.x - (playerWidth / 2.f) - 6.f, head.y - 4.f, playerWidth, playerHeight, Red, 1.f);
			
		}
	}


	void Menu_Paint_All(int b) {
		MinHook[0].Stub(b);
		ReadStructs();

		options.menuHeight = options.menuTabHeight + (options.menuMaxScroll * (R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current)) + (options.menuBorder.current * 2) + 2;
		if (options.menuOpen)
			DrawMenu();

		Esp();
	}
	void Cl_WritePacket(int a) {
		MinHook[2].Stub(a);

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
				options.menuScroll = 0;
				if (options.menuPageIndex < 5)
					options.menuPageIndex++;
				if (options.menuPageIndex > 4)
					options.menuPageIndex = 0;
			}

			if (KeyIsDown(Buttons, XINPUT_GAMEPAD_LEFT_SHOULDER))
			{
				options.menuScroll = 0;
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