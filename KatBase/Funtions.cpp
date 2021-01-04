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

float white[] = { 1,1,1,1 };
float black[] = { 0.07, 0.15, 0.22,1 };
float blue[] = { 0.08, 0.52, 0.84, .8 };

namespace BO2
{

	UIContext* cgDC;
	cg_s* cgGame;
	centity_tBo2* cg_entitiesArray;
	ClientActive_t* ClientActive;

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
	}

	void readStructs()
	{
		cgDC = (UIContext*)MP_UIContext;
		cgGame = *(cg_s**)MP_CG;
		cg_entitiesArray = *(centity_tBo2**)MP_Centitiy;
		ClientActive = *(ClientActive_t**)0x82C70F4C;
	}


	const char* FontForIndex(int index)
	{
		if (index == 0)
			return "fonts/720/smallDevFont";
		if (index == 1)
			return "fonts/720/bigDevFont";
		if (index == 2)
			return "fonts/720/consoleFont";
		if (index == 3)
			return "fonts/720/smallFont";
		if (index == 4)
			return "fonts/720/normalFont";
		if (index == 5)
			return "fonts/720/boldFont";
		else
			return "fonts/720/smallFont";
	}

	int R_TextHeight(Font* font)
	{
		return font->pixelHeight;
	}

	void DrawText(const char* text, float x, float y, const char* font, float fontSize, float* color, alignment align)
	{
		int fontA = R_TextWidth(0, text, strlen(text), R_RegisterFont(font, 0)) * fontSize;

		if (align == align_left)
			x = x;
		if (align == align_right)
			x = x - fontA;
		if (align == align_center)
			x = x - (fontA / 2);

		R_AddCmdDrawText(text, strlen(text), R_RegisterFont(font, 0), x, y, fontSize, fontSize, 0, color, 3);
	}

	void DrawShader(float x, float y, float width, float height, const float* color, const char* shader)
	{
		CG_DrawRotatedPicPhysical(BO2::MP_Scr_Placment, x, y, width, height, 0.0f, color, Material_RegisterHandle(shader, 7));
	}

	void BoundingBox(float x, float y, float width, float height, float* color, float thickness)
	{
		DrawShader(x - thickness, y - thickness, width + (thickness * 2), thickness, color); // Top
		DrawShader(x - thickness, y + height, width + (thickness * 2), thickness, color); // Bottom
		DrawShader(x - thickness, y - thickness, thickness, height + thickness, color); // Left
		DrawShader(x + width, y - thickness, thickness, height + (thickness * 2), color); // Right
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


	const char* FontForIndex(int index)
	{
		if (index == 0)
			return "fonts/smallDevFont";
		if (index == 1)
			return "fonts/bigDevFont";
		if (index == 2)
			return "fonts/consoleFont";
		if (index == 3)
			return "fonts/smallFont";
		if (index == 4)
			return "fonts/normalFont";
		if (index == 5)
			return "fonts/boldFont";
		else
			return "fonts/smallFont";
	}

	int R_TextHeight(Font* font)
	{
		return font->pixelHeight;
	}

	void DrawText(const char* text, float x, float y, const char* font, float fontSize, float* color, alignment align)
	{
		int fontA = Textwidth(text, strlen(text), R_RegisterFont(font), 0) * fontSize;

		if (align == align_left)
			x = x;
		if (align == align_right)
		x = x - fontA;
		if (align == align_center)
			x = x - (fontA / 2);

		R_AddCmdDrawText(text, strlen(text), R_RegisterFont(font), x, y, fontSize, fontSize, 0, color, 3);
	}

	void DrawShader(float x, float y, float width, float height, const float* color, const char* shader)
	{
		CG_DrawRotatedPicPhysical(0x83088EC0, x, y, width, height, 0.0f, color, Material_RegisterHandle(shader));
	}

	void BoundingBox(float x, float y, float width, float height, float* color, float thickness)
	{
		DrawShader(x - thickness, y - thickness, width + (thickness * 2), thickness, color); // Top
		DrawShader(x - thickness, y + height, width + (thickness * 2), thickness, color); // Bottom
		DrawShader(x - thickness, y - thickness, thickness, height + thickness, color); // Left
		DrawShader(x + width, y - thickness, thickness, height + (thickness * 2), color); // Right
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