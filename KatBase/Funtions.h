#pragma once
#define ANGLE2SHORT(x) ((int)((x)*65536/360) & 65535)

enum alignment
{
	align_left,
	align_right,
	align_center,
};

extern float white[];
extern float black[];
extern float blue[];
extern float Red[];
extern float Yellow[4];
extern float Green[4];
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
typedef const char* (*BG_GetFactionForTeam_t)(int team, const char* mapName);
typedef void(*BG_seedRandWithGameTime_t)(unsigned int* pHoldrand);
typedef void(*G_GetSpreadForWeapon_t)(BO2::playerstate_s *ps, int weapon, float* minSpread, float* maxSpread);
typedef void(*AngleVectors_t)(vec3_t* angles, vec3_t* forward, vec3_t* right, vec3_t* up);
typedef BO2::playerstate_s* (*CG_GetPredictedPlayerState_t)(int localClientNum);
typedef void(*RandomBulletDir_t)(int randSeed, float* x, float* y);

extern RandomBulletDir_t RandomBulletDir;
extern CG_GetPredictedPlayerState_t CG_GetPredictedPlayerState;
extern AngleVectors_t AngleVectors;
extern G_GetSpreadForWeapon_t G_GetSpreadForWeapon;
extern BG_seedRandWithGameTime_t BG_seedRandWithGameTime;
extern BG_GetFactionForTeam_t BG_GetFactionForTeam;
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
typedef void(*R_AddCmdDrawText_bo3)(const char* text, int maxChars, Font* font, float x, float y, float xScale, float yScale,  float* color, int style);

//infinity ward
typedef __int64(*R_TextWidth_iw)(const char* text, int maxChars, Font* font);
extern R_TextWidth_iw R_TextWidthIW;


extern R_AddCmdDrawText_bo3 R_AddCmdDrawText_test;
extern R_TextWidth_fookinreeko Textwidth;
extern CG_LocationTrace_t CG_LocationTrace;
extern Sl_GetStringOfSize_t Sl_GetStringOfSize;
extern DB_FindXAssetHeader_t DB_FindXAssetHeader;
extern CG_DobjGetWorldTagPos_t CG_DobjGetWorldTagPos;


namespace BO2
{
	extern void GodmodeFix();
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
	extern 	bool isDead(centity_tBo2* cen);
	extern 	bool Dvar_GetBool(const char* dvarName);
	extern void PlayerCmd_SetPrestige(int prestige, int index);
	extern void PlayerCmd_SetRank(int rank, int index);
	extern void drawHeart(float x, float y, float w, float h, float* outline, float* fill);
	extern void SpoofLevel();
	extern void NetDll_XNetGetTitleXnAddrHook(int xnc, XNADDR* pXna);
}

namespace BO3
{
	extern void InitAddress();
	extern void readStructs();
	extern int R_TextHeight(Font* font);

	extern void CG_BulletHitEvent(int localClientNum, int sourceEntityNum, int targetEntityNum, int weapon, vec3_t* startPos, vec3_t* position, vec3_t* normal, vec3_t* seeThruDecalNormal, int surfType, int event, int eventParam, int hitContents, char boneIndex);
	extern void ESP_ClientHealth(int cen);
	extern vec3_t AimTarget_GetTagPos(int client, const char* tag);
	extern void drawHeart(float x, float y, float w, float h, float* outline, float* fill);
	extern void DrawLine(vec2_t start, vec2_t end, float* color, float size);
	extern bool inGame();
	extern bool isTeam(int cen);
	extern int Com_ClientDObj(int ClientNum, int LocalPlayer);
	extern bool AimTarget_IsVisible(vec3_t BonePos, int i);
	extern short Sl_GetString(const char* String, int usr);
	extern Material* Material_RegisterHandle(const char* name);
	extern Font* R_RegisterFont(const char* name);
}

namespace Ghost 
{
	extern void InitAddress();
	extern void ReadStructs();
	extern int R_TextHeight(Font* font);
}