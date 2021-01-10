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

//Black Ops 2

typedef Material* (*Material_RegisterHandle_t)(const char* shaderName, int imgTrack);
typedef Font* (*R_RegisterFont_t)(const char* font, int img);
typedef void(*R_AddCmdDrawText_t)(const char* text, int maxChars, Font* font, float x, float y, float xScale, float yScale, float rotation, float* color, int style);
typedef void(*CG_DrawRotatedPicPhysical_t)(std::uintptr_t scrPlace, float x, float y, float width, float height, float angle, const float* color, Material* material);
typedef int(*R_TextWidth_t)(int local, const char* text, int maxchars, Font* font);
typedef BO2::dvar_s* (*Dvar_FindVar_t)(const char* dvar);
typedef bool(*WorldToScreen_t)(int local, vec3_t& world, vec2_t* screen);
typedef bool(*AimTarget_GetTagPos_0_t)(BO2::centity_tBo2* cen, unsigned int tag, vec3_t& pos);
typedef int(*SL_GetString_t)(const char* string, unsigned int r4);
typedef bool(*CG_IsEntityFriendlyNotEnemy_t)(int local, BO2::centity_tBo2* cent);
typedef bool(*AimTarget_IsTargetVisible_t)(int local, BO2::centity_tBo2* cen);
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
extern vectoAngles_t VecToAngels;

//Black Ops 3

typedef bool(*CG_DobjGetWorldTagPos_t)(BO3::Centity* Entity, int Dobj, short Bone, vec3_t* out);
typedef int32_t(*DB_FindXAssetHeader_t)(int type, const char* name, int imgTrack);
typedef short(*Sl_GetStringOfSize_t)(const char* String, int uzr, int SizeOfString);
typedef void(*CG_LocationTrace_t)(BO3::trace_t* results, vec3_t* start, vec3_t* end, int passEntityNum, int contentMask, bool checkRopes, int* context);
typedef int(*R_TextWidth_fookinreeko)(const char* text, int maxchars, Font* font, int r6);

extern R_TextWidth_fookinreeko Textwidth;
extern CG_LocationTrace_t CG_LocationTrace;
extern Sl_GetStringOfSize_t Sl_GetStringOfSize;
extern DB_FindXAssetHeader_t DB_FindXAssetHeader;
extern CG_DobjGetWorldTagPos_t CG_DobjGetWorldTagPos;


namespace BO2
{
	extern void InitAddress();
	extern void readStructs();
	extern int R_TextHeight(Font* font);
	extern void DrawText(const char* text, float x, float y, const char* font, float fontSize, float* color, alignment align = align_left);
	extern void DrawShader(float x, float y, float width, float height, const float* color, const char* shader = "white");
	extern void BoundingBox(float x, float y, float width, float height, float* color, float thickness);
	extern const char* FontForIndex(int index);
	extern vec3_t AimTarget_GetTagPos(centity_tBo2* client, const char* tag);
	extern void DrawLine(vec2_t start, vec2_t end, float* color, float size);
	extern void drawBones(centity_tBo2* entity, float* color);
	extern bool isTeam(centity_tBo2* cen);
	extern 	bool Dvar_GetBool(const char* dvarName);
	extern void PlayerCmd_SetPrestige(int prestige, int index);
	extern void PlayerCmd_SetRank(int rank, int index);
}

namespace BO3
{
	extern void InitAddress();
	extern void readStructs();
	extern int R_TextHeight(Font* font);

	extern int Com_ClientDObj(int ClientNum, int LocalPlayer);
	extern bool AimTarget_IsVisible(vec3_t BonePos, int i);
	extern short Sl_GetString(const char* String, int usr);
	extern Material* Material_RegisterHandle(const char* name);
	extern Font* R_RegisterFont(const char* name);
}