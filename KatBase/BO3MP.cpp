#include "pch.h"

namespace BO3
{

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
			DrawButton("Button Testing");
			DrawToggle("Button Testing", &options.testing);
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			DrawIntSlider("Testing Int", &options.menuX, "%i");
			DrawStringSlider("Font", &options.menuFontIndex, FontForIndex(options.menuFontIndex.current));
			break;
		case AIMBOT:
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			break;
		case VISUALS:
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			break;
		case PLAYERS:
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			break;
		case SETTINGS:
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			DrawButton("Button Testing");
			DrawButton("Button Testing");
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

	void DrawLine(vec2_t start, vec2_t end, float* color, float size)
	{
		vec2_t  delta = start - end;
		vec_t angle = atan2(delta.y, delta.x) * (180 / 3.141592654f);
		vec_t length = delta.Length();
		vec2_t  coords(end.x + ((delta.x - length) / 2), end.y + (delta.y / 2));
		CG_DrawRotatedPicPhysical(0x83088EC0, coords.x, coords.y, length, size, angle, color, Material_RegisterHandle("white"));
	}

	vec3_t AimTarget_GetTagPos(int client, const char* tag)
	{
		vec3_t Vect;
		int Dobj = Com_ClientDObj(client, 0);

		if (!Dobj) 
			return vec3_t(0, 0, 0);
		else {
			if (!CG_DobjGetWorldTagPos(&cg_entitiesArray[client], Dobj, Sl_GetString(tag, 0), &Vect))
				printf("AimTarget_GetTagPos: Failed to locate tag: [%s] on [%i]\n", tag, client);
			else
				return Vect;
		}

		return vec3_t();
	}

	void drawBones(Centity* entity, float* color)
	{
		for (int i = 0; i < ARRAYSIZE(Bones) - 1; i++)
		{
			vec2_t Screen, Screen2;
			if (WorldToScreen(0, AimTarget_GetTagPos(i, Bones[i]), &Screen) && WorldToScreen(0, AimTarget_GetTagPos(i, Bones[i + 1]), &Screen2))
				DrawLine(Screen, Screen2, color, 1);

		}
	}

	bool isTeam(int cen)
	{
		if (Cinfo[cen].Team == Cinfo[cgGame->MyClientNum].Team)
			return true;
		return false;
	}

	int nearestClient;
	bool playerReady;
	vec3_t anglesOut;

	int GetNearestPlayer()
	{
		float max = FLT_MAX;
		nearestClient = -1;

		for (int i = 0; i < 18; i++) {

			if (i != cgGame->MyClientNum) {
				if (!isTeam(i)) {
					if (Cinfo[i].Health > 0) {
						if (AimTarget_IsVisible(AimTarget_GetTagPos(i, "j_neck"), i)) {
							float Distance = cg_entitiesArray[i].Origin.GetDistance(cg_entitiesArray[cgGame->MyClientNum].Origin);

							if (Distance < max)
							{
								max = Distance;
								nearestClient = i;
								//options.Fire.state = true;
							}
						}
					}
				}
			}
		}
		return nearestClient;
	}

	void doAimbot()
	{
		GetNearestPlayer();
	
			int Nearest = GetNearestPlayer();
			if (Cinfo[Nearest].Health > 0) {
				if (Nearest != -1) {
					vec3_t Bone = AimTarget_GetTagPos(Nearest, "j_neck");
					vec3_t Angle = Bone - Ref->ViewOrigin;
					VecToAngels(Angle, anglesOut);
					ClientActive->ViewAngles = anglesOut - ClientActive->SpawnAngles;
					playerReady = false;
				}
			
		}
	}

	void R_RenderScene()
	{
		MinHook[1].Stub();
		readStructs();

		options.menuHeight = options.menuTabHeight + (options.menuMaxScroll * (R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current)) + (options.menuBorder.current * 2) + 2;
		if (options.menuOpen)
		DrawMenu();

		
			//doAimbot();
		
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