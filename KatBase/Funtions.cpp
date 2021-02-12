#include "pch.h"

Material_RegisterHandle_t Material_RegisterHandle;
R_RegisterFont_t R_RegisterFont;
R_AddCmdDrawText_t R_AddCmdDrawText;
R_AddCmdDrawText_bo3 R_AddCmdDrawText_Bo3_Version;
CG_DrawRotatedPicPhysical_t CG_DrawRotatedPicPhysical;
R_TextWidth_t R_TextWidth;
Dvar_FindVar_t Dvar_FindVar;
WorldToScreen_t WorldToScreen;
AimTarget_GetTagPos_0_t AimTarget_GetTagPos_0;
SL_GetString_t SL_GetString;
CG_IsEntityFriendlyNotEnemy_t CG_IsEntityFriendlyNotEnemy;
AimTarget_IsTargetVisible_t AimTarget_IsTargetVisible;
vectoAngles_t VecToAngels;
CG_DobjGetWorldTagPos_t CG_DobjGetWorldTagPos;
DB_FindXAssetHeader_t DB_FindXAssetHeader;
Sl_GetStringOfSize_t Sl_GetStringOfSize;
CG_LocationTrace_t CG_LocationTrace;
R_TextWidth_fookinreeko Textwidth;
BG_GetFactionForTeam_t BG_GetFactionForTeam;
BG_seedRandWithGameTime_t BG_seedRandWithGameTime;
G_GetSpreadForWeapon_t G_GetSpreadForWeapon;
AngleVectors_t AngleVectors;
R_TextWidth_iw R_TextWidthIW;
CG_GetPredictedPlayerState_t CG_GetPredictedPlayerState;
Cbuf_AddText_t Cbuf_AddText;
BG_srand_t BG_srand;
BG_random_t BG_random;
CL_AddReliableCommand_t CL_AddReliableCommand;
cg_simulatebulletfire_t cg_simulatebulletfire;
Hunk_FindDataForFile_t Hunk_FindDataForFile;
R_RegisterModel_t R_RegisterModel;
Hunk_SetDataForFile_t Hunk_SetDataForFile;
CL_ConsolePrint_t CL_ConsolePrint;
CG_DrawRotatedPicPhysical_GFX_t CG_DrawRotatedPicPhysical_GFX;

float white[] = { 1,1,1,1 };
float white2[] = { 1,1,1,0.3 };
float black[] = { 0.07, 0.15, 0.22,1 };
float blue[] = { 0.08, 0.52, 0.84, .8 };
float Red[4] = { 1,0,0,1 };
float Yellow[4] = { 1,1,0,1 };
float Green[4] = { 0,1,0,1 };

namespace BO2
{
	BulletTrace_t* bulletTrace;
	playerstate_s* playerstate;
	UIContext* cgDC;
	cg_s* cgGame;
	Cgs_t* cgServer;
	centity_tBo2* cg_entitiesArray;
	ClientActive_t* ClientActive;
	gentity_t* g_entitiesArray;
	Usercmd_t UserCmd;
	XModel_t* xModel;
	 BulletTraceResults_t BulletTraceResults;
	 BulletFireParams_t BulletFireParams;

	void InitAddress()
	{
		Material_RegisterHandle = Material_RegisterHandle_t(MP_Material_RegisterHandle);
		R_RegisterFont = R_RegisterFont_t(MP_RegisterFont);
		R_RegisterFont = R_RegisterFont_t(MP_RegisterFont);
		R_AddCmdDrawText = R_AddCmdDrawText_t(MP_R_AddCmdDrawText);
		CG_DrawRotatedPicPhysical = CG_DrawRotatedPicPhysical_t(MP_CG_DrawRotatedPicPhysicals);
		R_TextWidth = R_TextWidth_t(MP_R_TextWidth);
		Dvar_FindVar = Dvar_FindVar_t(0x82496430);
		WorldToScreen = WorldToScreen_t(0x821DA808);
		AimTarget_GetTagPos_0 = AimTarget_GetTagPos_0_t(0x821E9C08);
		SL_GetString = SL_GetString_t(0x825334F8);
		CG_IsEntityFriendlyNotEnemy = CG_IsEntityFriendlyNotEnemy_t(0x821CD948);
		AimTarget_IsTargetVisible = AimTarget_IsTargetVisible_t(0x821C47B8);
		VecToAngels = vectoAngles_t(0x8248A470);
		BG_GetFactionForTeam = BG_GetFactionForTeam_t(0x821A6AA8);
	//	BG_seedRandWithGameTime = BG_seedRandWithGameTime_t(0x826961B8);
		G_GetSpreadForWeapon = G_GetSpreadForWeapon_t(0x826BB4E0);
		AngleVectors = AngleVectors_t(0x8248E408);
		CG_GetPredictedPlayerState = CG_GetPredictedPlayerState_t(0x821E64E0);
		Cbuf_AddText = Cbuf_AddText_t(0x824015E0);
		BG_srand = BG_srand_t(0x82697FC0);
//		BG_random = BG_random_t(0x82696250);
		CL_AddReliableCommand = CL_AddReliableCommand_t(0x822786E0);
		cg_simulatebulletfire = cg_simulatebulletfire_t(0x82258840);
		Hunk_FindDataForFile = Hunk_FindDataForFile_t(0x8248ECC8);
		Hunk_SetDataForFile = Hunk_SetDataForFile_t(0x8248ED80);
		CL_ConsolePrint = CL_ConsolePrint_t(0x8226AE80);
	}

	void ReadStructs()
	{
		cgDC = (UIContext*)MP_UIContext;
		cgGame = *(cg_s**)MP_CG;
		cg_entitiesArray = *(centity_tBo2**)MP_Centitiy;
		ClientActive = *(ClientActive_t**)0x82C70F4C;
		g_entitiesArray = (gentity_t*)0x833D0640;
		cgServer = *(Cgs_t**)0x82BBAE44;
	}

	void PlayerCmd_SetRank(int rank, int index)
	{
		g_entitiesArray[index].rank = rank;
	}

	void PlayerCmd_SetPrestige(int prestige, int index)
	{
		g_entitiesArray[index].prestige = prestige;
	}

	void SpoofLevel() {
		if (options.BoolRank.state) {
			PlayerCmd_SetPrestige(15, cgGame->clientNum);
			PlayerCmd_SetRank(55, cgGame->clientNum);
		}
	}
	//Rebuilt from ida dec
	double BG_random(int* pHoldrand)
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

	double BG_seedRandWithGameTime(int *Holdrand)
	{
		unsigned int r11 = 214013 * *Holdrand + 2531011;
		*Holdrand = r11;
		return (double)(r11 >> 17) * 0.000030517578;
	}
	void RandomBulletDir(int seed, float* x, float* y)
	{
		float f26 = (BG_seedRandWithGameTime(&seed) * 360.0f) * (M_PI / 180.0f);
		float f28 = BG_seedRandWithGameTime(&seed);
		*x = f28 * cosf(f26);
		*y = f28 * sinf(f26);
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

	void NetDll_XNetGetTitleXnAddrHook(int xnc, XNADDR* pXna)
	{
		MinHook[2].Stub(xnc, pXna);

		if (options.IpSpoof.state)
		{
			BYTE IP[] = { 0x2, 0x2, 0x33, 0x3 };
			pXna->inaOnline.S_un.S_addr = *(DWORD*)&IP;
		}
	}


	DWORD WINAPI ChangeName(LPVOID)
	{
		char* text = (char*)LocalName;
		wchar_t wtext[31];
		mbstowcs(wtext, text, strlen(text) + 1);
		LPWSTR old = wtext;

		XOVERLAPPED Overlapped;
		WCHAR wValue[0x200];
		char buffer[31];
		ZeroMemory(&Overlapped, sizeof(Overlapped));

		XShowKeyboardUI(0, VKBD_DEFAULT, old, L"Edit A Player Name", L"Enter A New Name", wValue, 31, &Overlapped);

		while (!XHasOverlappedIoCompleted(&Overlapped));
		Sleep(100);
		wcstombs(buffer, wValue, 100);

		if (!strcmp(buffer, ""))
			return 0;

		memcpy((void*)LocalName, buffer, 31);
		CL_AddReliableCommand(0, va("userinfo \"\\name\\%s\"", buffer));
		return 0;
	}
	vec3_t AimTarget_GetTagPos(centity_tBo2* client, const char* tag)
	{
		vec3_t _Pos;
		AimTarget_GetTagPos_0(client, SL_GetString(tag, 0), _Pos);
		return _Pos;
	}

	void drawBones(centity_tBo2* entity, float* color)
	{
		for (int i = 0; i < ARRAYSIZE(Bones) - 1; i++)
		{
			vec2_t Screen, Screen2;
			if (WorldToScreen(0, AimTarget_GetTagPos(entity, Bones[i]), &Screen) && WorldToScreen(0, AimTarget_GetTagPos(entity, Bones[i + 1]), &Screen2))
				DrawLine(Screen, Screen2, color, 1);

		}
	}
	bool Dvar_GetBool(const char* dvarName)
	{
		dvar_s* dvar_t = Dvar_FindVar(dvarName);
		if (!dvar_t)
			return false;
		return dvar_t->current.enabled;
	}
	bool isTeam(centity_tBo2* cen)
	{
		if (CG_IsEntityFriendlyNotEnemy(0, cen))
			return true;
		else
			return false;
	}
	bool isDead(centity_tBo2* cen)
	{
		if (!cen->pose.eType == ET_PLAYER_CORPSE)
			return true;
		else
			return false;
	}
	void GodmodeFix() {
		while (options.XboGodmode.state) {

			if (!Dvar_GetBool("cl_ingame")) continue;

			UINT_PTR ClientStatePtr = (0x83551A10 + (0x57f8 * 0) + 0x1b);
			INT32 CurrentState = *(INT32*)(ClientStatePtr);

			//if (CurrentState == 5)
			*(char*)(ClientStatePtr) = 4;
		}
	}
	void FovSlider(int fov) {
		Cbuf_AddText(cgGame->clientNum, va("cg_fov %i", fov));
	}
}

namespace BO3
{
	UIContext* cgDC;
	CgArray* cgGame;
	Centity* cg_entitiesArray;
	ClientActive_t* ClientActive;
	ClientInfo* Cinfo;
	RefDef* Ref;
	userCmd_t* UserCmd;

	void InitAddress()
	{
		DB_FindXAssetHeader = DB_FindXAssetHeader_t(0x82328110);
		R_AddCmdDrawText_Bo3_Version = R_AddCmdDrawText_bo3(0x824AE7C0);
		CG_DrawRotatedPicPhysical = CG_DrawRotatedPicPhysical_t(0x82210468);
		WorldToScreen = (WorldToScreen_t)0x82208018;
		CG_DobjGetWorldTagPos = (CG_DobjGetWorldTagPos_t)0x8221ACF0;
		Sl_GetStringOfSize = (Sl_GetStringOfSize_t)0x822D2248;
		VecToAngels = (vectoAngles_t)0x826ACB98;
		CG_LocationTrace = (CG_LocationTrace_t)0x82285838;
		Textwidth = (R_TextWidth_fookinreeko)0x824A1000;
		CG_DrawRotatedPicPhysical_GFX = (CG_DrawRotatedPicPhysical_GFX_t)0x82210468;
		Cbuf_AddText = (Cbuf_AddText_t)0x8263A6A0;
	}

	void readStructs()
	{
		cgDC = (UIContext*)0x841DEFD8;
		cgGame = *(CgArray**)0x82E819D8;
		cg_entitiesArray = *(Centity**)0x82E819EC;
		ClientActive = *(ClientActive_t**)0x84475F74;
		Ref = (RefDef*)(*(int*)0x82E819D8 + 0x32550);
		Cinfo = (ClientInfo*)(*(int*)0x82E819D8 + 0x54E10);
		UserCmd = (userCmd_t*)(*(int*)0x84475F74 + 0x231BC);
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
	void drawHeart(float x, float y, float w, float h, float* outline, float* fill)
	{
		//Outline - thick
		{
			DrawLine(vec2_t(x + (w / 100 * 0), y + (h / 100 * 45)), vec2_t(x + (w / 100 * 10), y + (h / 100 * 18)), outline, 2);
			DrawLine(vec2_t(x + (w / 100 * 100), y + (h / 100 * 45)), vec2_t(x + (w / 100 * 90), y + (h / 100 * 18)), outline, 2);
			DrawLine(vec2_t(x + (w / 100 * 10), y + (h / 100 * 18)), vec2_t(x + (w / 100 * 30), y + (h / 100 * 9)), outline, 2);
			DrawLine(vec2_t(x + (w / 100 * 90), y + (h / 100 * 18)), vec2_t(x + (w / 100 * 70), y + (h / 100 * 9)), outline, 2);
			DrawLine(vec2_t(x + (w / 100 * 30), y + (h / 100 * 9)), vec2_t(x + (w / 100 * 50), y + (h / 100 * 20)), outline, 2);
			DrawLine(vec2_t(x + (w / 100 * 70), y + (h / 100 * 9)), vec2_t(x + (w / 100 * 50), y + (h / 100 * 20)), outline, 2);
			DrawLine(vec2_t(x + (w / 100 * 0), y + (h / 100 * 45)), vec2_t(x + (w / 100 * 50), y + (h / 100 * 93)), outline, 2);
			DrawLine(vec2_t(x + (w / 100 * 100), y + (h / 100 * 45)), vec2_t(x + (w / 100 * 50), y + (h / 100 * 93)), outline, 2);
		}
	}

	void ESP_ClientHealth(int cen)
	{
		vec3_t tagOriginHead;
		vec2_t headPosScreen;

		vec2_t screen;

		float* healthColor;
		if (cg_entitiesArray->EType == 1)
			healthColor = (Cinfo[cen].Health < 30) ? Red : (Cinfo[cen].Health < 70) ? Yellow : Green;

		tagOriginHead = AimTarget_GetTagPos(cen, "j_head");

		tagOriginHead.z += 9.0f;

		if (WorldToScreen(0, tagOriginHead, &headPosScreen) && WorldToScreen(0, cg_entitiesArray[cen].Origin, &screen))
		{
			float entWidth = (screen.y - headPosScreen.y) / 5;

			float barWidth = (entWidth / 5);

			if (barWidth > 3)
				barWidth = 3;
			if (cg_entitiesArray->EType == 1)
			{
				std::uint8_t health = Cinfo[cg_entitiesArray[cen].ClientNum].Health;
				std::uint8_t maxHealth = 100;

				DrawShader(screen.x - entWidth - barWidth - 16, headPosScreen.y, barWidth + 2, screen.y - headPosScreen.y, black);
				DrawShader(screen.x - entWidth - barWidth - 15, headPosScreen.y + ((screen.y - headPosScreen.y) - (((screen.y - headPosScreen.y) / maxHealth) * health)) + 1, barWidth, (((screen.y - headPosScreen.y) / maxHealth) * health) - 2, healthColor);
			}
		}
	}
	void FovSlider(int fov) {
		Cbuf_AddText(cgGame->MyClientNum, va("cg_fov %i", fov));
	}
	int Com_ClientDObj(int ClientNum, int LocalPlayer)
	{
		int Dobj = *(short*)(0x83EC1440 + (BO3::cg_entitiesArray[ClientNum].ClientNum << 1));

		if (!Dobj)
			return 0;

		return 0x83E71440 + (Dobj * 0xA0);
	}
	bool AimTarget_IsVisible(vec3_t BonePos, int i) {
		trace_t Trace;
		CG_LocationTrace(&Trace, &Ref->ViewOrigin, &BonePos, cgGame->MyClientNum, 0x280E833, true, 0);
		if (Trace.hitId == i || Trace.fraction >= 0.95)
			return true;
		return false;
	}
	bool inGame()
	{
		return !*(WORD*)0x8447A32C && cg_entitiesArray && cgGame && Ref && ClientActive;
	}
	bool isTeam(int cen)
	{
		if (Cinfo[cen].Team == Cinfo[cgGame->MyClientNum].Team)
			return true;
		return false;
	}
	short Sl_GetString(const char* String, int usr)
	{
		return Sl_GetStringOfSize(String, usr, strlen(String) + 1);
	}
	
	Material* Material_RegisterHandle(const char* name)
	{
		return (Material*)DB_FindXAssetHeader(XASSET_MATERIAL, name, 0);
	}
	Font* R_RegisterFont(const char* name)
	{
		return (Font*)DB_FindXAssetHeader(XASSET_FONT, name, 0);
	}
}

namespace Ghost {	
	CgsArray* CgServer;
	RefDef* Ref;

	void InitAddress() {
		
		DB_FindXAssetHeader = DB_FindXAssetHeader_t(0x82376680); //wrong addr
		R_AddCmdDrawText = R_AddCmdDrawText_t(0x8266CEB8);
		CG_DrawRotatedPicPhysical = CG_DrawRotatedPicPhysical_t(0x82270138);
		R_RegisterFont = R_RegisterFont_t(0x8264DBF0);
		Material_RegisterHandle = Material_RegisterHandle_t(0x8265A470);
		R_TextWidthIW = (R_TextWidth_iw)0x8264DC78;
	}
	void ReadStructs() {
		CgServer = *(CgsArray**)0x82AD56F8;
		Ref = *(RefDef**)0x82ACCCE8;

	}
	
	
}