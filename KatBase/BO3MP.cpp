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
			DrawToggle("No Recoil", &options.NoRecoil);
			DrawToggle("No Sway", &options.NoSway);
			DrawStringSlider("Font", &options.menuFontIndex, FontForIndex(options.menuFontIndex.current));
			break;
		case AIMBOT:
			DrawToggle("Aimbot", &options.Aimbot);
			DrawToggle("AutoShoot", &options.AutoShoot);
			break;
		case VISUALS:
			DrawToggle("Esp BoxFrog", &options.EspHeart);
			DrawToggle("Esp Bones", &options.EspBones);
			DrawToggle("Esp Snaplines", &options.EspSnap);
			DrawToggle("Esp Names", &options.EspNames);
			DrawToggle("Esp Healthbar", &options.EspHealth);
			DrawToggle("OverHeadNames", &options.OverHeadNames);
			DrawToggle("Tracer Rounds", &options.Tracers);
			break;
		case PLAYERS:
			for (int i = 0; i < 18; i++) {
				if (!strcmp(Cinfo[i].Name, ""))
					DrawButton("N/A");
				else
					DrawButton(va("[%i] %s [%s]", i, Cinfo[i].Name, isTeam(i) ? "^2Friendly^7" : "^1Enemy^7"));
			}
			break;
		case SETTINGS:
			DrawIntSlider("MenuX", &options.menuX, "%i");
			DrawIntSlider("MenuY", &options.menuY, "%i");
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

	void drawBones(Centity* entity, float* color)
	{
		for (int i = 0; i < ARRAYSIZE(Bones) - 1; i++)
		{
			vec2_t Screen, Screen2;
			if (WorldToScreen(0, AimTarget_GetTagPos(i, Bones[i]), &Screen) && WorldToScreen(0, AimTarget_GetTagPos(i, Bones[i + 1]), &Screen2))
				DrawLine(Screen, Screen2, color, 1);

		}
	}
	std::vector<cTracer> GlobalTrace;

	float deltaFade(int ms, int tracerTime)
	{
		return float(1 - (cgGame->CmdTime - tracerTime) / ms);
	}
	void DrawTracer() {
		if (options.Tracers.state) {
			auto it = GlobalTrace.begin();
			while (it != GlobalTrace.end())
			{
				vec2_t Hit2D = vec2_t();
				vec2_t Start2D = vec2_t();
				WorldToScreen(0, it->hit3D, &Hit2D);
				WorldToScreen(0, it->start3D, &Start2D);

				DrawLine(Hit2D, Start2D, blue, 2);
				//SoulStar(Hit2D.x, Hit2D.y, 40, 40, 2, Black2);
				if (deltaFade(2000, it->startTime) <= 0)
					it = GlobalTrace.erase(it);
				else
					++it;
			}
		}
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
								options.Fire.state = true;
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
		if (options.Aimbot.state) {
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
	}

	void R_RenderScene()
	{
		MinHook[1].Stub();
		readStructs();
		vec2_t BoxPos, BoxPos2, Screen, Screen2, Spine;

		const char* Tag = "j_head";

		if (inGame) {
			for (int i = 0; i < 18; i++) {

				if (!(cg_entitiesArray[i].EType == 1))
					continue;

				if (!(cg_entitiesArray[i].ClientNum != 0))
					continue;

				if (Cinfo[i].Health < 1)
					continue;

				if (!WorldToScreen(0, cg_entitiesArray[i].Origin, &BoxPos))
					continue;

				if (!WorldToScreen(0, AimTarget_GetTagPos(i, Tag), &BoxPos2))
					continue;
				if (!WorldToScreen(0, AimTarget_GetTagPos(i, "j_spinelower"), &Spine))
					continue;

				float Width = (fabsf(BoxPos2.y - BoxPos.y) * 0.65f), Height = fabsf(BoxPos2.y - BoxPos.y);
				float Distance = cg_entitiesArray[i].Origin.GetDistance(cg_entitiesArray[cgGame->MyClientNum].Origin);

				//SoulsAmazingStar Esp
				/*if (options.EspStar.state)
					SoulStar(BoxPos.x - (Width)-6.f, BoxPos2.y - 4.f - Height / 2, Width * 2, Height * 2, 2, blue);*/
				//Souls amazing heart esp
				if (options.EspHeart.state)
					drawHeart(BoxPos.x - (Width)-6.f, BoxPos2.y - 4.f - Height / 2, Width * 2, Height * 2, Red, Red);
				//Esp Name
				if (options.EspNames.state)
					DrawText(va("%s", Cinfo[i].Name), BoxPos.x, BoxPos2.y, "fonts/normalfont", 0.6, black, align_center);
				//Esp Health
				if (options.EspHealth.state)
					ESP_ClientHealth(i);

				//SnapLines
				if (options.EspSnap.state)
					DrawLine(vec2_t(cgDC->screenWidth / 2, cgDC->screenHeight), Spine, Red, 2);

				//Bones
				for (int j = 0; j < ARRAYSIZE(Bones) - 1; j++) {
					if (WorldToScreen(0, AimTarget_GetTagPos(i, Bones[j]), &Screen) && WorldToScreen(0, AimTarget_GetTagPos(i, Bones[j + 1]), &Screen2)) {
						if (options.EspBones.state)
							DrawLine(vec2_t(Screen.x, Screen.y), vec2_t(Screen2.x, Screen2.y), white, 2);
					}
				}
			}
		*(uint32_t*)0x82214C5C = options.OverHeadNames.state ? 0x60000000 : 0x4BFFE9E5;
		//No recoil
		*(uint32_t*)0x82279CB8 = options.NoRecoil.state ? 0x60000000 : 0x4BF79239;
		//No Sway
		*(uint32_t*)0x82201008 = options.NoSway.state ? 0x60000000 : 0x4BFFE659;

		
			doAimbot();
			DrawTracer();
		}

		options.menuHeight = options.menuTabHeight + (options.menuMaxScroll * (R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current)) + (options.menuBorder.current * 2) + 2;
		if (options.menuOpen)
			DrawMenu();
	}

	void CL_ReadyToSendPacket(int local) {
		MinHook[2].Stub(local);
		readStructs();
		userCmd_t* curCmd = &UserCmd[ClientActive->cmdnumber & 0x7F];
		userCmd_t* oldCmd = &UserCmd[(ClientActive->cmdnumber - 1) & 0x7F];

		*oldCmd = *curCmd;
		oldCmd->serverTime -= 1;

		if (options.AutoShoot.state)
		{
			if (options.Fire.state) {
				oldCmd->buttonFlag &= ~0x80000000;
				curCmd->buttonFlag |= 0x80000000;
				options.Fire.state = false;
			}

		}

	}

	void CG_BulletHitEvent(int localClientNum, int sourceEntityNum, int targetEntityNum, int weapon, vec3_t* startPos, vec3_t* position, vec3_t* normal, vec3_t* seeThruDecalNormal, int surfType, int event, int eventParam, int hitContents, char boneIndex)
	{
		MinHook[3].Stub(localClientNum, sourceEntityNum, targetEntityNum, weapon, startPos, position, normal, seeThruDecalNormal, surfType, event, eventParam, hitContents, boneIndex);
		readStructs();

		if (sourceEntityNum == cgGame->MyClientNum) {
			cTracer Trace;
			Trace.hit3D = *position;
			Trace.startTime = cgGame->CmdTime;
			Trace.start3D = *startPos;

			GlobalTrace.emplace_back(Trace);
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