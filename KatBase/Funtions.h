#pragma once

enum alignment
{
	align_left,
	align_right,
	align_center,
};



extern float white[];
extern float black[];
extern float blue[];

typedef BO2::Material* (*Material_RegisterHandle_t)(const char* shaderName, int imgTrack);
typedef BO2::Font* (*R_RegisterFont_t)(const char* font, int img);
typedef void(*R_AddCmdDrawText_t)(const char* text, int maxChars, BO2::Font* font, float x, float y, float xScale, float yScale, float rotation, float* color, int style);
typedef void(*CG_DrawRotatedPicPhysical_t)(std::uintptr_t scrPlace, float x, float y, float width, float height, float angle, const float* color, BO2::Material* material);
typedef int(*R_TextWidth_t)(int local, const char* text, int maxchars, BO2::Font* font);
typedef BO2::dvar_s* (*Dvar_FindVar_t)(const char* dvar);
typedef bool(*WorldToScreen_t)(int local, vec3_t& world, vec2_t* screen);
typedef bool(*AimTarget_GetTagPos_0_t)(BO2::centity_t* cen, unsigned int tag, vec3_t& pos);
typedef int(*SL_GetString_t)(const char* string, unsigned int r4);
typedef bool(*CG_IsEntityFriendlyNotEnemy_t)(int local, BO2::centity_t* cent);
typedef bool(*AimTarget_IsTargetVisible_t)(int local, BO2::centity_t* cen);
typedef void(*vectoAngles_t)(vec3_t& vec, vec3_t& angles);



extern Material_RegisterHandle_t Material_RegisterHandle;
extern R_RegisterFont_t R_RegisterFont;
extern R_AddCmdDrawText_t R_AddCmdDrawText;
extern CG_DrawRotatedPicPhysical_t CG_DrawRotatedPicPhysical;
extern R_TextWidth_t R_TextWidth;
extern Dvar_FindVar_t Dvar_FindVar;
extern WorldToScreen_t WorldToScreen;
extern AimTarget_GetTagPos_0_t AimTarget_GetTagPos_0;
extern SL_GetString_t SL_GetString;
extern CG_IsEntityFriendlyNotEnemy_t CG_IsEntityFriendlyNotEnemy;
extern AimTarget_IsTargetVisible_t AimTarget_IsTargetVisible;
extern vectoAngles_t vectoAngles;

namespace BO2
{
	extern void InitAddress();
	extern void readStructs();
	extern int R_TextHeight(Font* font);
	extern void DrawText(const char* text, float x, float y, const char* font, float fontSize, float* color, alignment align = align_left);
	extern void DrawShader(float x, float y, float width, float height, const float* color, const char* shader = "white");
	extern void BoundingBox(float x, float y, float width, float height, float* color, float thickness);

	extern const char* FontForIndex(int index);


}