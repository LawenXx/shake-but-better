#include "pch.h"

namespace BO2
{
	HANDLE Thread;
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
			DrawToggle("No Spread", &options.NoSpread);
			DrawToggle("Laser", &options.Laser);
			//DrawToggle("End Round", &options.EndGame);
			DrawToggle("Crouch On Lethal", &options.AntiBetty);
			DrawToggle("Change Name", &options.NoFlinch);
			DrawToggle("IP Spoof", &options.IpSpoof);
			DrawToggle("AntiFreeze", &options.AntiFreeze);
			DrawToggle("XbO Godmode Fix", &options.XboGodmode);
			DrawToggle("External Radar", &options.Radar);
			DrawToggle("External Circle Radar", &options.CircleRadar);
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
			DrawToggle("AutoWall", &options.AutoWall);
			//	DrawToggle("AutoBone", &options.Autobone);
				//	DrawToggle("Aim Required", &options.AimRequired);
			break;
		case VISUALS:
			DrawToggle("Healthbar", &options.Healthbar);
			DrawSubMenu("Esp Menu", &options.EspMenu, EspMenu);
			DrawSubMenu("Misc Visuals", &options.MiscView, MiscVisuals);
			break;
		case EspMenu:
			DrawToggle("Esp Box", &options.EspBoxToggle);
			DrawToggle("Esp Box Filled", &options.EspFilled);
			DrawToggle("Esp Bones", &options.EspDrawBones);
			DrawToggle("Esp Heart", &options.EspFrogChan);
			DrawToggle("Esp Names", &options.EspNames);
			DrawToggle("Esp SnapLines", &options.EspDrawLine);
			DrawIntSlider("SnapLine Position", &options.SnapPos, "%i");
			DrawToggle("Esp Item", &options.DrawItem);
			break;
		case MiscVisuals:
			DrawToggle("Wallhack", &options.Wallhack);
			DrawToggle("Tracers", &options.Tracer);
			DrawIntSlider("Fov", &options.Fov, "%i");
			DrawStringSlider("Shader", &options.ShaderIndex, Shader(options.ShaderIndex.current));
			DrawIntSlider("Shader Red", &options.ShaderRed, "%i");
			DrawIntSlider("Shader Green", &options.ShaderGreen, "%i");
			DrawIntSlider("Shader Blue", &options.ShaderBlue, "%i");
			DrawToggle("RGB", &options.RGB);
			break;
		case PLAYERS:
			for (int i = 0; i < 18; i++) {
				if (!strcmp(cgGame->clientInfo[i].name, "")) {}
				//DrawButton("N/A");
				else
					DrawSubMenu(va("%s [%s]", cgGame->clientInfo[i].name, isTeam(&cg_entitiesArray[i]) ? "^2Friendly^7" : "^1Enemy^7"), &options.SubPlayers, Playersub);
			}
			break;
		case Playersub:
			DrawButton("WIP");
			DrawButton("WIP");
			DrawButton("WIP");
			break;
		case SETTINGS:
			DrawIntSlider("Menu X", &options.menuX, "%i");
			DrawIntSlider("Menu Y", &options.menuY, "%i");
			DrawStringSlider("Font", &options.menuFontIndex, FontForIndex(options.menuFontIndex.current));
			DrawToggle("Gradient Menu", &options.Gradient);
			DrawSubMenu("Debug Info", &options.Debug, Debug);
			break;
		case Debug:
			DrawToggle("Host", &options.DHost);
			DrawToggle("Map", &options.DMap);
			DrawToggle("Gametype", &options.DGame);
			DrawToggle("Fps", &options.DFps);
			DrawToggle("Target Details", &options.DTarget);
			break;

		}
	}

	void ServerInfo() {
		std::string strMap = cgServer->MapName;
		strMap.erase(0, 3);
		const char* map = strMap.c_str();
		DrawTextInBox("Shake Beta v1.1.0", cgDC->screenWidth - cgDC->screenWidth + 5, cgDC->screenHeight - cgDC->screenHeight + 5, R_TextWidth(0, "ShakeBeta v1.1.0", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.65, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));
		if (options.DHost.state)
			DrawTextInBox(va("Host: %s", cgServer->hostName), cgDC->screenWidth - cgDC->screenWidth + 5, cgDC->screenHeight - cgDC->screenHeight + 37, R_TextWidth(0, va("Host: %s.", cgServer->hostName), MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.65, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));
		if (options.DMap.state)
			DrawTextInBox(va("Map: %s", map), cgDC->screenWidth - cgDC->screenWidth + 5, cgDC->screenHeight - cgDC->screenHeight + 67, R_TextWidth(0, va("Map: %s .", map), MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.65, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));
		if (options.DGame.state)
			DrawTextInBox(va("Gametype: %s", cgServer->gametype), cgDC->screenWidth - cgDC->screenWidth + 5, cgDC->screenHeight - cgDC->screenHeight + 98, R_TextWidth(0, va("GameType: %s..", cgServer->gametype), MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.65, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));
		if (options.DFps.state)
			DrawTextInBox(va("Fps: %g", cgDC->FPS), cgDC->screenWidth - cgDC->screenWidth + 5, cgDC->screenHeight - cgDC->screenHeight + 5 + 125, R_TextWidth(0, va("Fps: %g.", cgDC->FPS), MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.65, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));

		if (options.menuOpen)
			DrawTextInBox("Press ^BXENONButtonB^ To ^1Close ^7The Menu.", cgDC->screenWidth - cgDC->screenWidth + 5, cgDC->screenHeight - 35, R_TextWidth(0, "Press ^BXENONButtonB^ To ^1Close ^7The Menu.", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.65, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));
		else
			DrawTextInBox("Press ^BXENONButtontrigL^ ^BXENONButtonStickAnimatedR^ To ^2Open ^7The Menu", cgDC->screenWidth - cgDC->screenWidth + 5, cgDC->screenHeight - 35, R_TextWidth(0, "Press ^BXENONButtontrigL^ ^BXENONButtonStickAnimatedR To ^2Open ^7The Menu..", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.65 + 14, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));
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
	const char* Tag;

	bool isClientWallbangable(int client, const char* tag)
	{
		*(DWORD*)(0x82258D60) = 0x60000000;
		*(DWORD*)(0x82258D68) = 0x60000000;
		*(DWORD*)(0x82258D64) = 0x60000000;
		*(DWORD*)(0x82258D6C) = 0x60000000;

		vec3_t End;
		End = AimTarget_GetTagPos(&cg_entitiesArray[client], tag);

		BulletTraceResults_t bulletTraceResults;
		BulletFireParams_t bulletFireParams;
		memset(&bulletFireParams, 0x00, sizeof(bulletFireParams));

		bulletFireParams.weaponEntIndex = 1022;
		bulletFireParams.ignoreEntIndex = cgGame->clientNum;
		bulletFireParams.damageMultiplier = 2.0f;
		bulletFireParams.methodOfDeath = 1;
		bulletFireParams.origStart = cgGame->refdef.viewOrigin;
		bulletFireParams.start = cgGame->refdef.viewOrigin;
		bulletFireParams.end = End;

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
	bool CanShootThroughWall(int i, const char* tag) {
		return options.AutoWall.state ? AimTarget_IsTargetVisible(0, &cg_entitiesArray[i]) || isClientWallbangable(i, tag) : AimTarget_IsTargetVisible(0, &cg_entitiesArray[i]);
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
			if (!cg_entitiesArray[i].nextState.Alive)
				continue;
			if (isTeam(&cg_entitiesArray[i]))
				continue;

			float Distance = cg_entitiesArray[client].pose.Origin.GetDistance(cg_entitiesArray[i].pose.Origin);

			if (CanShootThroughWall(i, "j_neck") && Distance < nearestDistance)
			{
				nearestDistance = Distance;
				nearestClient = i;
				playerReady = true;
				options.Fire.state = true;
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
				//if (options.Autobone.state)
					//Tag = AutoBone(nearestClient);

				if (cg_entitiesArray[nearestClient].WeaponID == 89)
					Tag = "j_ankle_ri";
				else
					Tag = AimTag(options.MenuAimTargetIndex.current);


				vec3_t Difference = AimTarget_GetTagPos(&cg_entitiesArray[nearestClient], Tag);
				//Difference.z -= 5;
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
			if (options.EspNames.state) {
				DrawText(va("%s", cgGame->clientInfo[i].name), Pos.x, head.y, "fonts/720/normalfont", 0.4, Red, align_center);
			
			}
			if (options.EspFilled.state)
				BoundingBoxFilled(Pos.x - (playerWidth / 2.f) - 6.f, head.y - 4.f, playerWidth, playerHeight, isTeam(&cg_entitiesArray[i]) ? Green : Red, 1.f);
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

	void TargetDetails() {
		int nearest = GetNearestPlayer(cgGame->clientNum);
		float Distance = cg_entitiesArray[cgGame->clientNum].pose.Origin.GetDistance(cg_entitiesArray[nearest].pose.Origin);
		if (options.DTarget.state) {
			DrawTextInBox("Target Details:", cgDC->screenWidth - R_TextWidth(0, "Target Details", MAXCHAR, R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) + 30, cgDC->CenterY(), R_TextWidth(0, "Target Details", MAXCHAR, R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) / 1.6, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));
			DrawTextInBox(va("Name: %s", cgGame->clientInfo[nearest].name), cgDC->screenWidth - 5 - R_TextWidth(0, va("Name: %s", cgGame->clientInfo[nearest].name), MAXCHAR, R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) + 2, cgDC->CenterY() + 32, R_TextWidth(0, va("Name: %s", cgGame->clientInfo[nearest].name), MAXCHAR, R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) / 1.6, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));
			DrawTextInBox(va("Distance: %.fm", Distance), cgDC->screenWidth + 15 - R_TextWidth(0, va("Distance: %.fm", Distance), MAXCHAR, R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) + 2, cgDC->CenterY() + 64, R_TextWidth(0, va("Distance: %.fm", Distance), MAXCHAR, R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) / 1.6, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));
			DrawTextInBox(va("Weapon: %s", GetWeaponName(cgGame->clientInfo[nearest].primaryWeapon)), cgDC->screenWidth + 15 - R_TextWidth(0, va("Weapon: %s", GetWeaponName(cgGame->clientInfo[nearest].primaryWeapon)), MAXCHAR, R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) + 2, cgDC->CenterY() + 96, R_TextWidth(0, va("Weapon: %s", GetWeaponName(cgGame->clientInfo[nearest].primaryWeapon)), MAXCHAR, R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) / 1.6, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)));
		}
	}

	void CL_ConsolePrintHook(int localClientNum, int channel, const char* txt, int duration, int pixelWidth, char color, int flags) {
		MinHook[6].Stub(localClientNum, channel, txt, duration, pixelWidth, color, flags);

		if (options.AntiFreeze.state) {
			if (strstr(txt, "[{+}]") || strstr(txt, "KEY_UNBOUND")
				|| strstr(txt, "^H") || strstr(txt, "KEYUNBOUND") || strstr(txt, "^B{}")) {

				//^H crash location
				*(uint32_t*)0x82717D48 = 0x60000000;
				//CG_GameMessage
				*(uint32_t*)0x8222E27C = 0x60000000;
				*(uint32_t*)0x8222A754 = 0x60000000;

				txt = "Shake Crash Blocked";
				return;
			}
		}
	}

	void CL_Disconnect_Hook(int r3, bool r4)
	{
		*(int*)0x82717D48 = 0x91370000;
		*(uint32_t*)0x8222E27C = 0x4BFB829D;
		*(uint32_t*)0x8222A754 = 0x4BFBBDC5;
		MinHook[7].Stub(r3, r4);
	}

	const char* Keyboard(LPCWSTR DefaultText, LPCWSTR TitleText, LPCWSTR DescriptionText, DWORD Length) {
		XOVERLAPPED Overlapped;
		WCHAR KeyboardText[0x200];
		char Return[0x100];
		ZeroMemory(&Overlapped, sizeof(Overlapped));
		XShowKeyboardUI(0, 0, DefaultText, TitleText, DescriptionText, KeyboardText, Length, &Overlapped);

		while (!XHasOverlappedIoCompleted(&Overlapped))
			Sleep(50);
		wcstombs(Return, KeyboardText, Length);
		return Return;
	}
	void keyboard_hook() {
		int error = 0;
		const char* cmd = Keyboard(L"", L"Custom Name", L"Enter A Name", 0x20);

		if (error == 0) {
			printf("%s\n", cmd);
			strcpy((char*)0x841E1B30, cmd);
			strcpy((char*)0x82C55D60, cmd);
			Cbuf_AddText(0, va(";cmd userinfo \"\\clanAbbrev\\%s\\name\\%s\"", "^1", cmd));
		}
	}
	void keyboard_thread(HANDLE) {
		ExCreateThread(&Thread, 0, 0, 0, (LPTHREAD_START_ROUTINE)keyboard_hook, 0, 0);
		XSetThreadProcessor(Thread, 4);
		ResumeThread(Thread);
	}
	std::vector<cTracer> GlobalTrace;
	float testcol[] = { options.ShaderRed.current * 255, options.ShaderGreen.current * 255 ,options.ShaderBlue.current * 255, 1 };
	void DrawTracer() {
		if (options.Tracer.state) {
			auto it = GlobalTrace.begin();
			while (it != GlobalTrace.end())
			{
				vec2_t Hit2D = vec2_t();
				vec2_t Start2D = vec2_t();
				WorldToScreen(0, it->hit3D, &Hit2D);
				WorldToScreen(0, it->start3D, &Start2D);
				//DrawLineGFX(Hit2D, Start2D, Col, 2);
				DrawLine(Hit2D, Start2D, testcol, 1.7);
				//SoulStar(Hit2D.x, Hit2D.y, 40, 40, 2, Black2);
				if (deltaFade(2000, it->startTime) <= 0)
					it = GlobalTrace.erase(it);
				else
					++it;
			}
		}
	}
	void Menu_PaintAll(int a, int b)
	{
		MinHook[0].Stub(a, b);
		ReadStructs();

		if (Dvar_GetBool("cl_ingame"))
		{
			DrawTracer();
			Esp();
			*(uint32_t*)0x82259BC8 = options.NoRecoil.state ? 0x60000000 : 0x48461341;
			*(uint32_t*)0x82255E1C = options.Laser.state ? 0x2B000B01 : 0x2B0B0000;
			*(uint32_t*)0x826C6E6C = options.NoSway.state ? 0x60000000 : 0x4BFFE975;
			*(uint32_t*)0x826C7A7C = options.NoSway.state ? 0x60000000 : 0x4BFFFA857F;
			*(uint32_t*)0x821fc04c = options.Wallhack.state ? 0x38C0FFFF : 0x7FA6EB78;
			*(uint32_t*)0x83c56038 = options.Wallhack.state ? 0xF51F0000DF : 0x3F800000;
			*(uint32_t*)0x826BB50C = options.NoSpread.state ? 0x39600002 : 0x817B01EC;

			if (options.Healthbar.state)
				HealthBar(cgDC->screenWidth - cgDC->screenWidth + 15, cgDC->CenterY(), 10);
			if (options.CircleRadar.state)
				renderRadar(cgDC->screenWidth - 200, cgDC->screenHeight - cgDC->screenHeight + 5, 190, 20, 0.08, true);
			if (options.Radar.state)
				renderRadar(cgDC->screenWidth - 200, cgDC->screenHeight - cgDC->screenHeight + 5, 190, 20, 0.08, false);

			FovSlider(options.Fov.current);
			SpoofLevel();
			TargetDetails();
		}
		if (options.NoFlinch.state) {
			keyboard_thread(Thread);
			CloseHandle(Thread);
			options.NoFlinch.state = false;
		}
		options.menuHeight = options.menuTabHeight + (options.menuMaxScroll * (R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current)) + (options.menuBorder.current * 2) + 2;
		if (options.menuOpen)
			DrawMenu();
		ServerInfo();
	}

	void CG_BulletHitEvent(int localClientNum, int sourceEntityNum, int targetEntityNum, int weapon, vec3_t* startPos, vec3_t* position, vec3_t* normal, vec3_t* seeThruDecalNormal, int surfType, int event, int eventParam, int hitContents, char boneIndex)
	{
		MinHook[4].Stub(localClientNum, sourceEntityNum, targetEntityNum, weapon, startPos, position, normal, seeThruDecalNormal, surfType, event, eventParam, hitContents, boneIndex);

		if (sourceEntityNum == cgGame->clientNum) {
			cTracer Trace;
			Trace.hit3D = *position;
			Trace.startTime = cgGame->ServerTime;
			Trace.start3D = *startPos;

			GlobalTrace.emplace_back(Trace);
		}
	}
	void Rgb() {
		if (options.RGB.state) {


		}
	}
	void Quad_Hook(Material* r3, short t, vec3_t* x, vec2_t* xx, GfxColor* Col, int c) {
		const char* Material = r3->name;

		/*	if (strstr(Material, "menu_mp") || strstr(Material, "globe")
				|| strstr(Material, "fonts/") || strstr(Material, "compass_map"))*/
		if (strstr(Material, Shader(options.ShaderIndex.current)))
		{
			Rgb();
			byte r = options.ShaderRed.current;
			byte g = options.ShaderGreen.current;
			byte b = options.ShaderBlue.current;
			Col->r = r;
			Col->g = g;
			Col->b = b;
			Col->a = 255;
		}
		MinHook[5].Stub(r3, t, x, xx, Col, c);
	}

	void LiveStats_Probation_GiveProbation(int controllerIndex, int gamemode, float time)
	{
		time = 0;
		XNotify("Probation Bypassed!");
		MinHook[8].Stub(controllerIndex, gamemode, time);
	}

	void Cl_WritePacket(int a) {
		MinHook[3].Stub(a);
		ReadStructs();

		if (Dvar_GetBool("cl_ingame")) {
			doAimbot();
			GodmodeFix();

			Usercmd_t* Cmd = ClientActive->GetCmd(ClientActive->CurrentCmdNumber);
			Usercmd_t* newCmd = ClientActive->GetCmd(ClientActive->CurrentCmdNumber);
			Usercmd_t* oldCmd = ClientActive->GetCmd(ClientActive->CurrentCmdNumber - 1);

			memcpy(oldCmd, Cmd, sizeof(Usercmd_t));
			memcpy(newCmd, Cmd, sizeof(Usercmd_t));

			oldCmd->serverTime -= 1;
			newCmd->serverTime += 1;


			if (options.AutoShoot.state) {
				if (options.Fire.state) {
					if (cg_entitiesArray[cgGame->clientNum].WeaponID != 89) {
						oldCmd->buttons &= ~0x80000000;
						newCmd->buttons |= 0x80000000;
						options.Fire.state = false;
					}
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
