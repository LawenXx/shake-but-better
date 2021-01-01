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
vectoAngles_t vectoAngles;
float white[] = { 1,1,1,1 };
float black[] = { 0.07, 0.15, 0.22,1 };
float blue[] = { 0.08, 0.52, 0.84, .8 };

namespace BO2
{

	UIContext* cgDC;
	cg_s* cgGame;
	centity_t* cg_entitiesArray;
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
		vectoAngles = vectoAngles_t(0x8248A470);
	}

	void readStructs()
	{
		cgDC = (UIContext*)MP_UIContext;
		cgGame = *(cg_s**)MP_CG;
		cg_entitiesArray = *(centity_t**)MP_Centitiy;
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