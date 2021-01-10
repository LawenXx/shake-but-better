#include "pch.h"

Material_RegisterHandle_t Material_RegisterHandle;
R_RegisterFont_t R_RegisterFont;
R_AddCmdDrawText_t R_AddCmdDrawText;
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

float white[] = { 1,1,1,1 };
float black[] = { 0.07, 0.15, 0.22,1 };
float blue[] = { 0.08, 0.52, 0.84, .8 };
float Red[4] = { 1,0,0,1 };

namespace BO2
{

	UIContext* cgDC;
	cg_s* cgGame;
	centity_tBo2* cg_entitiesArray;
	ClientActive_t* ClientActive;
	gentity_t* g_entitiesArray;

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
	}

	void readStructs()
	{
		cgDC = (UIContext*)MP_UIContext;
		cgGame = *(cg_s**)MP_CG;
		cg_entitiesArray = *(centity_tBo2**)MP_Centitiy;
		ClientActive = *(ClientActive_t**)0x82C70F4C;
		g_entitiesArray = (gentity_t*)0x833D0640;

	}

	void PlayerCmd_SetRank(int rank, int index)
	{
		g_entitiesArray[index].client->rank = rank;
	}

	void PlayerCmd_SetPrestige(int prestige, int index)
	{
		g_entitiesArray[index].client->prestige = prestige;
	}

	void SpoofLevel() {
		if (options.BoolRank.state) {
			PlayerCmd_SetPrestige(15, cgGame->clientNum);
			PlayerCmd_SetRank(1337, cgGame->clientNum);
		}
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

	void DrawLine(vec2_t start, vec2_t end, float* color, float size)
	{
		vec2_t  delta = start - end;
		vec_t angle = atan2(delta.y, delta.x) * (180 / 3.141592654f);
		vec_t length = delta.Length();
		vec2_t  coords(end.x + ((delta.x - length) / 2), end.y + (delta.y / 2));
		CG_DrawRotatedPicPhysical(MP_Scr_Placment, coords.x, coords.y, length, size, angle, color, Material_RegisterHandle("white", 7));
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

		//Cross section
		{
			DrawLine(vec2_t(x + (w / 100 * 10), y + (h / 100 * 18)), vec2_t(x + (w / 100 * 50), y + (h / 100 * 93)), fill, 1);
			DrawLine(vec2_t(x + (w / 100 * 90), y + (h / 100 * 18)), vec2_t(x + (w / 100 * 50), y + (h / 100 * 93)), fill, 1);
			DrawLine(vec2_t(x + (w / 100 * 0), y + (h / 100 * 45)), vec2_t(x + (w / 100 * 100), y + (h / 100 * 45)), fill, 1);
			DrawLine(vec2_t(x + (w / 100 * 0), y + (h / 100 * 45)), vec2_t(x + (w / 100 * 50), y + (h / 100 * 20)), fill, 1);
			DrawLine(vec2_t(x + (w / 100 * 100), y + (h / 100 * 45)), vec2_t(x + (w / 100 * 50), y + (h / 100 * 20)), fill, 1);
			DrawLine(vec2_t(x + (w / 100 * 30), y + (h / 100 * 9)), vec2_t(x + (w / 100 * 50), y + (h / 100 * 93)), fill, 1);
			DrawLine(vec2_t(x + (w / 100 * 70), y + (h / 100 * 9)), vec2_t(x + (w / 100 * 50), y + (h / 100 * 93)), fill, 1);
			DrawLine(vec2_t(x + (w / 100 * 0), y + (h / 100 * 45)), vec2_t(x + (w / 100 * 30), y + (h / 100 * 9)), fill, 1);
			DrawLine(vec2_t(x + (w / 100 * 100), y + (h / 100 * 45)), vec2_t(x + (w / 100 * 70), y + (h / 100 * 9)), fill, 1);
			DrawLine(vec2_t(x + (w / 100 * 30), y + (h / 100 * 9)), vec2_t(x + (w / 100 * 62), y + (h / 100 * 45)), fill, 1);
			DrawLine(vec2_t(x + (w / 100 * 70), y + (h / 100 * 9)), vec2_t(x + (w / 100 * 38), y + (h / 100 * 45)), fill, 1);
		}
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

}


namespace BO3
{
	UIContext* cgDC;
	CgArray* cgGame;
	Centity* cg_entitiesArray;
	ClientActive_t* ClientActive;
	ClientInfo* Cinfo;
	RefDef* Ref;

	void InitAddress()
	{
		DB_FindXAssetHeader = DB_FindXAssetHeader_t(0x82328110);
		R_AddCmdDrawText = R_AddCmdDrawText_t(0x824AE7C0);
		CG_DrawRotatedPicPhysical = CG_DrawRotatedPicPhysical_t(0x82210468);
		WorldToScreen = (WorldToScreen_t)0x82208018;
		CG_DobjGetWorldTagPos = (CG_DobjGetWorldTagPos_t)0x8221ACF0;
		Sl_GetStringOfSize = (Sl_GetStringOfSize_t)0x822D2248;
		VecToAngels = (vectoAngles_t)0x826ACB98;
		CG_LocationTrace = (CG_LocationTrace_t)0x82285838;
		Textwidth = (R_TextWidth_fookinreeko)0x824A1000;
	}

	void readStructs()
	{
		cgDC = (UIContext*)0x841DEFD8;
		cgGame = *(CgArray**)0x82E819D8;
		cg_entitiesArray = *(Centity**)0x82E819EC;
		ClientActive = *(ClientActive_t**)0x84475F74;
		Ref = (RefDef*)(*(int*)0x82E819D8 + 0x32550);
		Cinfo = (ClientInfo*)(*(int*)0x82E819D8 + 0x54E10);
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