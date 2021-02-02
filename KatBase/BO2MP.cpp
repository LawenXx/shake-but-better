#include "pch.h"

namespace BO2
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
			//	DrawToggle("No Flinch", &options.NoFlinch);
			DrawToggle("No Spread", &options.NoSpread);
			DrawToggle("Laser", &options.Laser);
			DrawToggle("IP Spoof", &options.IpSpoof);
			DrawToggle("End Round", &options.EndGame);
			DrawToggle("Crouch On Lethal", &options.AntiBetty);
			DrawToggle("External Radar", &options.Radar);
			DrawToggle("External Circle Radar", &options.CircleRadar);
			DrawToggle("XbO Godmode Fix", &options.XboGodmode);

			DrawToggle("Test", &options.NoFlinch);

			if (cgGame->clientNum == 0)
				DrawSubMenu("Host Only", &options.HostOnly, HostOnly);
			break;
		case HostOnly:
			DrawToggle("Spoof Rank", &options.BoolRank);
			break;
		case AIMBOT:
			DrawToggle("Aimbot", &options.AimbotToggle);
			DrawToggle("Silent Aim", &options.SilentAim);
			DrawStringSlider("AimTag", &options.MenuAimTargetIndex, AimTag(options.MenuAimTargetIndex.current));
			DrawToggle("AutoShoot", &options.AutoShoot);
			//	DrawToggle("Aim Required", &options.AimRequired);
			break;
		case VISUALS:
			DrawToggle("Healthbar", &options.Healthbar);
			DrawToggle("Wallhack", &options.Wallhack);
			DrawToggle("Esp Box", &options.EspBoxToggle);
			DrawToggle("Esp Bones", &options.EspDrawBones);
			DrawToggle("Esp Heart", &options.EspFrogChan);
			DrawToggle("Esp SnapLines", &options.EspDrawLine);
			DrawToggle("Esp Item", &options.DrawItem);
			DrawSubMenu("Esp Menu", &options.EspMenu, EspMenu);

			break;
		case EspMenu:
			DrawIntSlider("SnapLine Position", &options.SnapPos, "%i");
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
			DrawIntSlider("Menu Y", &options.menuY, "%i");
			DrawStringSlider("Font", &options.menuFontIndex, FontForIndex(options.menuFontIndex.current));
			break;

		}
	}

	void ServerInfo() {
		readStructs();
		DrawTextInBox("Shake Beta v1.0.0", cgDC->screenWidth - cgDC->screenWidth + 5, cgDC->screenHeight - cgDC->screenHeight + 5, R_TextWidth(0, "Shake Beta v1.0", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.65 + 26, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));
		DrawTextInBox(va("Host: %s", cgServer->hostName), cgDC->screenWidth - cgDC->screenWidth + 5, cgDC->screenHeight - cgDC->screenHeight + 37, R_TextWidth(0, va("Host:%s", cgServer->hostName), MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.65 + 26, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));
		DrawTextInBox(va("Map: %s", cgServer->MapName), cgDC->screenWidth - cgDC->screenWidth + 5, cgDC->screenHeight - cgDC->screenHeight + 67, R_TextWidth(0, va("Map: %s .", cgServer->MapName), MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.65 + 40, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));
		DrawTextInBox(va("GameType: %s", cgServer->gametype), cgDC->screenWidth - cgDC->screenWidth + 5, cgDC->screenHeight - cgDC->screenHeight + 98, R_TextWidth(0, va("GameType: %s", cgServer->gametype), MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.65 + 28, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));
		DrawTextInBox(va("Fps: %g", cgDC->FPS), cgDC->screenWidth - cgDC->screenWidth + 5, cgDC->screenHeight - cgDC->screenHeight + 5 + 125, R_TextWidth(0, va("Fps: %g", cgDC->FPS), MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.65 + 14, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));


		if (options.menuOpen)
			DrawTextInBox("Press ^BXENONButtonB^ To ^1Close ^7The Menu.", cgDC->screenWidth - cgDC->screenWidth + 5, cgDC->screenHeight - 35, R_TextWidth(0, "Press ^BXENONButtontrigL^ ^BXENONButtonStickAnimatedR^ To ^2Open ^7The Menu..", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.65 + 14, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));
		else
			DrawTextInBox("Press ^BXENONButtontrigL^ ^BXENONButtonStickAnimatedR^ To ^2Open ^7The Menu.", cgDC->screenWidth - cgDC->screenWidth + 5, cgDC->screenHeight - 35, R_TextWidth(0, "Press ^BXENONButtontrigL^ ^BXENONButtonStickAnimatedR^ To ^2Open ^7The Menu.tedRr", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.65 + 14, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));
	}

	void DrawMenu()
	{
		DrawMenuShader();
		DrawMenuTabs();

		//Options
		DrawMenuText();
	}

	double __cdecl BG_random(int* pHoldrand)
	{
		unsigned int temp;

		temp = 214013 * *pHoldrand + 2531011;
		*pHoldrand = temp;
		return (double)(temp >> 17) * 0.000030517578;
	}

	void TransformSeed(int* seed)
	{
		*seed = 214013 * (214013 * (214013 * (214013 * *seed + 2531011) + 2531011) + 2531011) + 2531011;
	}

	void BG_seedRandWithGameTime(int Holdrand)
	{
		Holdrand ^= *(BYTE*)Holdrand << 8;
		Holdrand = Holdrand ^ ((*(BYTE*)Holdrand << 8) << 8) ^ ((*(BYTE*)Holdrand << 8) << 16);
	}
	void RandomBulletDir(int seed, float* x, float* y)
	{
		BG_seedRandWithGameTime(seed);

		float randX = BG_random(&seed) * XM_2PI;

		TransformSeed(&seed);

		float randY = BG_random(&seed);

		*x = cosf(randX) * randY;
		*y = sinf(randX) * randY;
	}

	void NoSpread(Usercmd_t* cmd, Usercmd_t* oldCmd)
	{
	
		float minSpread = 0.0f, maxSpread = 0.0f, totalSpread = 0.0f;

	G_GetSpreadForWeapon(CG_GetPredictedPlayerState(0), cg_entitiesArray[cgGame->clientNum].WeaponID, &minSpread, &maxSpread);

		totalSpread = (minSpread + ((maxSpread - minSpread) * (cgGame->weaponSpreadScale * 0.00399956862f)));

		vec2_t Spread = vec2_t();

		RandomBulletDir(cmd->serverTime, &Spread.x, &Spread.y);

		oldCmd->viewAngles[0] += ANGLE2SHORT(Spread.x * totalSpread);
		oldCmd->viewAngles[1] += ANGLE2SHORT(Spread.y * totalSpread);
	}


	int nearestClient;
	bool playerReady;
	vec3_t anglesOut;
	const char* Tag;

	bool isClientWallbangable(int client, const char* tag)
	{
		vec3_t End;
		End = AimTarget_GetTagPos(&cg_entitiesArray[client], tag);

		BulletTraceResults_t bulletTraceResults;
		BulletFireParams_t bulletFireParams;
		memset(&bulletFireParams, 0x00, sizeof(bulletFireParams));

		bulletFireParams.weaponEntIndex = 1022;
		bulletFireParams.ignoreEntIndex = cgGame->clientNum;
		bulletFireParams.damageMultiplier = 2.0f;
		bulletFireParams.methodOfDeath = 1;

		memcpy(&bulletFireParams.origStart, &cgGame->refdef.viewOrigin, 0xC);
		memcpy(&bulletFireParams.start, &cgGame->refdef.viewOrigin, 0xC);
		memcpy(&bulletFireParams.end, &End, 0xC);

		vec3_t EndDir;
		End - cgGame->refdef.viewOrigin;
		VecToAngels(End, EndDir);
		AngleVectors(&EndDir, &bulletFireParams.dir, NULL, NULL);

		cg_simulatebulletfire(0, &bulletFireParams, cgGame->ps.primaryWeapon, &cg_entitiesArray[cgGame->clientNum], &cgGame->refdef.viewOrigin, false, false, &bulletTraceResults, false);

		if (bulletTraceResults.trace.hitType != 1) {
			return true;
		}
		return false;
	}

	bool EntityWallbangable(int i, const char* tag) {
		return AimTarget_IsTargetVisible(0, &cg_entitiesArray[i]) || isClientWallbangable(i, tag);
	}

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
			if (!cg_entitiesArray[i].nextState.State & 0x40000000 && cg_entitiesArray[i].nextState.Alive)
				continue;
			if (isTeam(&cg_entitiesArray[i]))
				continue;

			float Distance = cg_entitiesArray[client].pose.Origin.GetDistance(cg_entitiesArray[i].pose.Origin);
			if (EntityWallbangable(i, AimTag(options.MenuAimTargetIndex.current)) && cg_entitiesArray[i].nextState.Alive) {
				if (Distance < nearestDistance)
				{
					nearestDistance = Distance;
					nearestClient = i;
					playerReady = true;
					options.Fire.state = true;
				}
			}

		}
		return nearestClient;
	}

	vec3_t newAngles;

	void doAimbot()
	{
		if (options.AimbotToggle.state) {

			if (!Dvar_GetBool("cl_ingame"))
				return;
			if (cgGame->ps.health < 1)
				return;

			int nearestClient = GetNearestPlayer(cgGame->clientNum);
			if (nearestClient == -1)
				newAngles = ClientActive->baseAngle;

			if (playerReady && nearestClient != -1)
			{

				if (cg_entitiesArray[nearestClient].WeaponID == 89)
					Tag = "j_ankle_ri";
				else
					Tag = AimTag(options.MenuAimTargetIndex.current);

				vec3_t Difference = AimTarget_GetTagPos(&cg_entitiesArray[nearestClient], Tag);
				vec3_t Angles = Difference - cgGame->refdef.viewOrigin;

				VecToAngels(Angles, anglesOut);

				if (nearestClient != cgGame->clientNum) {
					if (options.SilentAim.state)
						newAngles = anglesOut - ClientActive->baseAngle;
					else
						ClientActive->viewAngle = anglesOut - ClientActive->baseAngle;
				}
			}
			playerReady = false;

		}


	}
	void Esp() {
		for (int i = 0; i < 18; i++)
		{

			if (!(cg_entitiesArray[i].pose.eType == ET_PLAYER && (cg_entitiesArray[i].pose.eType != ET_PLAYER_CORPSE)))
				continue;
			if (!(cg_entitiesArray[i].nextState.ClientNumber != cgGame->clientNum))
				continue;
			if (!(cg_entitiesArray[i].nextState.Alive))
				continue;
			if (!cg_entitiesArray[i].nextState.State & (1 << 6) != 0)
				continue;
			if (cgGame->ps.health < 1)
				return;

			vec2_t Pos = vec2_t();
			vec2_t head = vec2_t();
			vec3_t origin = cg_entitiesArray[i].pose.Origin;

			vec3_t headPos = AimTarget_GetTagPos(&cg_entitiesArray[i], "j_head");
			headPos.z += 10;
			origin.z -= 5;

			if (!WorldToScreen(0, origin, &Pos))
				continue;
			if (!WorldToScreen(0, headPos, &head))
				continue;

			float playerHeight = fabsf(head.y - Pos.y);
			float playerWidth = (fabsf(head.y - Pos.y) * 0.65f);

			if (options.EspBoxToggle.state)
				BoundingBox(Pos.x - (playerWidth / 2.f) - 6.f, head.y - 4.f, playerWidth, playerHeight, isTeam(&cg_entitiesArray[i]) ? Green : Red, 1.f);
			if (options.EspDrawBones.state)
				drawBones(&cg_entitiesArray[i], blue);
			if (options.EspDrawLine.state)
				DrawLine(vec2_t(cgDC->screenWidth / 2, options.SnapPos.current), Pos, isTeam(&cg_entitiesArray[i]) ? Green : Red, 1);
			if (options.EspFrogChan.state)
				drawHeart(Pos.x - (playerWidth / 2.f) - 6.f, head.y - 4.f, playerWidth, playerHeight, isTeam(&cg_entitiesArray[i]) ? Green : Red, isTeam(&cg_entitiesArray[i]) ? Green : Red);
		}
		for (int j = 0; j < 2048; j++) {
			if (!(cg_entitiesArray[j].pose.eType == ET_MISSILE))
				continue;

			if ((cg_entitiesArray[j].nextState.pickupId < 0))
				continue;

			vec3_t origin = cg_entitiesArray[j].pose.Origin;
			vec2_t Pos = vec2_t();

			if (!WorldToScreen(0, origin, &Pos))
				continue;

			if (options.DrawItem.state)
				DrawLine(vec2_t(cgDC->screenWidth / 2, cgDC->screenHeight - 5), Pos, Red, 1);

		}
	}


	bool round = false;
	void EndRound() {
		round = true;
		if (round) {
			Cbuf_AddText(0, va("cmd mr %i 3 endround", *(int*)0x82c15758));
			round = false;
			options.EndGame.state = false;
		}
	}
	//TODO: move over to dof hook
	void Menu_PaintAll(int a, int b)
	{
		MinHook[0].Stub(a, b);

		options.menuHeight = options.menuTabHeight + (options.menuMaxScroll * (R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current)) + (options.menuBorder.current * 2) + 2;
		if (options.menuOpen)
			DrawMenu();

		ServerInfo();
	}
	XOVERLAPPED Overlapped_LSC;
	XOVERLAPPED Overlapped2_LSC;
	WCHAR Username_LSC[512];
	WCHAR Username2_LSC[15];
	WCHAR Username3_LSC[15];
	WCHAR Username4_LSC[14];


	void CMDSender()
	{
		XOVERLAPPED Overlapped;
		WCHAR CMDText[512];
		char CMDBuffer[512];
		char CMD[512];
		ZeroMemory(&Overlapped, sizeof(Overlapped));
		XShowKeyboardUI(0, VKBD_DEFAULT, L"", L"Dvar Sender", L"Please Enter Your Custom Dvar.", CMDText, 512, &Overlapped);

		while (!XHasOverlappedIoCompleted(&Overlapped))
			Sleep(100);

		wcstombs(CMDBuffer, CMDText, 512);
		sprintf(CMD, "s \"%s\"", CMDBuffer);
	}

	HRESULT RenderScene(DWORD a1) {
		MinHook[4].Stub(a1);

		if (options.NoFlinch.state)
			CMDSender();

		readStructs();
		if (Dvar_GetBool("cl_ingame"))
		{
			Esp();

			*(uint32_t*)0x82259BC8 = options.NoRecoil.state ? 0x60000000 : 0x48461341;
			*(uint32_t*)0x82255E1C = options.Laser.state ? 0x2B000B01 : 0x2B0B0000;
			*(uint32_t*)0x826C6E6C = options.NoSway.state ? 0x60000000 : 0x4BFFE975;
			*(uint32_t*)0x826C7A7C = options.NoSway.state ? 0x60000000 : 0x4BFFFA857F;
			*(uint32_t*)0x821fc04c = options.Wallhack.state ? 0x38C0FFFF : 0x7FA6EB78;
			*(uint32_t*)0x83c56038 = options.Wallhack.state ? 0xF51F0000DF : 0x3F800000;

			if (options.Healthbar.state)
				HealthBar(cgDC->screenWidth - cgDC->screenWidth + 15, cgDC->CenterY(), 10);
			if (options.CircleRadar.state)
				renderRadar(cgDC->screenWidth - 200, cgDC->screenHeight - cgDC->screenHeight + 5, 190, 20, 0.08, true);
			if (options.Radar.state)
				renderRadar(cgDC->screenWidth - 200, cgDC->screenHeight - cgDC->screenHeight + 5, 190, 20, 0.08, false);

			if (options.EndGame.state)
				EndRound();

			SpoofLevel();
		}

		return S_OK;
	}

	void Cl_WritePacket(int a) {
		MinHook[3].Stub(a);
		readStructs();

		if (Dvar_GetBool("cl_ingame")) {
			doAimbot();
			GodmodeFix();

			Usercmd_t* Cmd = ClientActive->GetCmd(ClientActive->CurrentCmdNumber);
			Usercmd_t* newCmd = ClientActive->GetCmd(ClientActive->CurrentCmdNumber);
			Usercmd_t* oldCmd = ClientActive->GetCmd(ClientActive->CurrentCmdNumber - 1);

			memcpy(oldCmd, Cmd, sizeof(Usercmd_t));
			memcpy(newCmd, Cmd, sizeof(Usercmd_t));

			oldCmd->serverTime -= 1;
			newCmd->serverTime += 2;


			if (options.AutoShoot.state) {
				if (options.Fire.state) {
					oldCmd->buttons &= ~0x80000000;
					newCmd->buttons |= 0x80000000;
					options.Fire.state = false;
				}

			}

			if (options.NoSpread.state)
				NoSpread(Cmd, oldCmd);

			bool betty = false;
			for (int i = 0; i < 2048; i++) {
				float Distance = cg_entitiesArray[cgGame->clientNum].pose.Origin.GetDistance(cg_entitiesArray[i].pose.Origin);
				if (!(cg_entitiesArray[i].pose.eType == ET_MISSILE))
					continue;

				if (options.AntiBetty.state) {
					if (Distance < 5) {
						betty = true;
						if (betty) {
							oldCmd->buttons |= 0x400000;
							//newCmd->buttons |= 0x800000;
							betty = false;

						}

					}

				}
			}
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
				options.menuScroll = 0;
				if (options.menuPageIndex < 4)
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

			if (KeyIsDown(Buttons, XINPUT_GAMEPAD_A))
			{
				SwitchToSubMenu(&options.EspMenu, options.menuPageIndex);
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
