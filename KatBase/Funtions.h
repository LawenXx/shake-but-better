#pragma once
#define ANGLE2SHORT(x) ((int)((x)*65536/360) & 65535)
#define LocalName 0x8486EFF0

enum alignment
{
	align_left,
	align_right,
	align_center,
};

extern float white[];
extern float white2[];
extern float black[];
extern float blue[];
extern float Red[];
extern float Yellow[4];
extern float TraceCol[4];
extern float Green[4];

extern int SnapPos;
//Black Ops 2

typedef Material* (*Material_RegisterHandle_t)(const char* shaderName, int imgTrack);
typedef Font* (*R_RegisterFont_t)(const char* font, int img);
typedef void(*R_AddCmdDrawText_t)(const char* text, int maxChars, Font* font, float x, float y, float xScale, float yScale, float rotation, float* color, int style);
typedef void(*CG_DrawRotatedPicPhysical_t)(std::uintptr_t scrPlace, float x, float y, float width, float height, float angle, const float* color, Material* material);
typedef void(*CG_DrawRotatedPicPhysical_GFX_t)(std::uintptr_t scrPlace, float x, float y, float width, float height, float angle, GfxColor* color, Material* material);
typedef int(*R_TextWidth_t)(int local, const char* text, int maxchars, Font* font);
typedef BO2::dvar_s* (*Dvar_FindVar_t)(const char* dvar);
typedef bool(*WorldToScreen_t)(int local, vec3_t& world, vec2_t* screen);
typedef bool(*AimTarget_GetTagPos_0_t)(BO2::Centity* cen, unsigned int tag, vec3_t& pos);
typedef bool(*AimTarget_GetTagPos_Ghost_t)(Ghost::Centity* cen, unsigned int tag, vec3_t& pos);
typedef int(*SL_GetString_t)(const char* string, unsigned int r4);
typedef bool(*CG_IsEntityFriendlyNotEnemy_t)(int local, BO2::Centity* cent);
typedef bool(*AimTarget_IsTargetVisible_t)(int local, BO2::Centity* cen);
typedef void(*vectoAngles_t)(vec3_t& vec, vec3_t& angles);
typedef const char* (*BG_GetFactionForTeam_t)(int team, const char* mapName);
typedef void(*BG_seedRandWithGameTime_t)(int pHoldrand);
typedef void(*BG_GetSpreadForWeapon_t)(BO2::playerstate_s* ps, int weapon, float* minSpread, float* maxSpread);
typedef void(*AngleVectors_t)(vec3_t* angles, vec3_t* forward, vec3_t* right, vec3_t* up);
typedef BO2::playerstate_s* (*CG_GetPredictedPlayerState_t)(int localClientNum);
typedef void(*Cbuf_AddText_t)(int localClientNum, const char* text);
typedef float(*BG_srand_t)(unsigned int* rand);
typedef float(*BG_random_t)(unsigned int* rand);
typedef void(*CL_AddReliableCommand_t)(int localClientNum, const char* cmd);
typedef void(*AngleVectors_t)(vec3_t* angles, vec3_t* forward, vec3_t* right, vec3_t* up);
typedef void (*cg_simulatebulletfire_t)(int localclient, BO2::BulletFireParams_t* bulletFireParams, int weapon, BO2::Centity* attacker, vec3_t* start, bool drawTracer, bool isPlayer, BO2::BulletTraceResults_t* br, bool traceHit);
typedef void*(*Hunk_FindDataForFile_t)(int type, const char* name);
typedef BO2::XModel_t(*R_RegisterModel_t)(const char* name);
typedef const char*(*Hunk_SetDataForFile_t)(int type, const char* name, void* data, void* (__cdecl* alloc)(int));
typedef void*(* CL_ConsolePrint_t)(int localClientNum, int channel, const char* txt, int duration, int pixelWidth, char color, int flags);

extern CG_DrawRotatedPicPhysical_GFX_t CG_DrawRotatedPicPhysical_GFX;
extern CL_ConsolePrint_t CL_ConsolePrint;
extern Hunk_SetDataForFile_t Hunk_SetDataForFile;
extern R_RegisterModel_t R_RegisterModel;
extern Hunk_FindDataForFile_t Hunk_FindDataForFile;
extern cg_simulatebulletfire_t cg_simulatebulletfire;
extern CL_AddReliableCommand_t CL_AddReliableCommand;
extern BG_srand_t BG_srand;
extern BG_random_t BG_random;
extern Cbuf_AddText_t Cbuf_AddText;
extern CG_GetPredictedPlayerState_t CG_GetPredictedPlayerState;
extern AngleVectors_t AngleVectors;
extern BG_GetSpreadForWeapon_t BG_GetSpreadForWeapon;
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
typedef void(*R_AddCmdDrawText_bo3)(const char* text, int maxChars, Font* font, float x, float y, float xScale, float yScale, float* color, int style);

//infinity ward
typedef __int64(*R_TextWidth_iw)(const char* text, int maxChars, Font* font);
extern R_TextWidth_iw R_TextWidthIW;
extern AimTarget_GetTagPos_Ghost_t AimTarget_GetTagPos_Ghost;

extern R_AddCmdDrawText_bo3 R_AddCmdDrawText_Bo3_Version;
extern R_TextWidth_fookinreeko Textwidth;
extern CG_LocationTrace_t CG_LocationTrace;
extern Sl_GetStringOfSize_t Sl_GetStringOfSize;
extern DB_FindXAssetHeader_t DB_FindXAssetHeader;
extern CG_DobjGetWorldTagPos_t CG_DobjGetWorldTagPos;


namespace BO2
{
	extern void HealthBar(float x, float y, float w);
	extern void GodmodeFix();
	extern void InitAddress();
	extern void ReadStructs();
	extern int R_TextHeight(Font* font);
	extern void DrawText(const char* text, float x, float y, const char* font, float fontSize, float* color, alignment align = align_left);
	extern void DrawShader(float x, float y, float width, float height, const float* color, const char* shader = "white");
	extern void BoundingBox(float x, float y, float width, float height, float* color, float thickness);
	extern const char* FontForIndex(int index);
	extern vec3_t AimTarget_GetTagPos(Centity* client, const char* tag);
	extern void DrawLine(vec2_t start, vec2_t end, float* color, float size);
	extern void drawBones(Centity* entity, float* color);
	extern bool isTeam(Centity* cen);
	extern 	bool isDead(Centity* cen);
	extern 	bool Dvar_GetBool(const char* dvarName);
	extern void PlayerCmd_SetPrestige(int prestige, int index);
	extern void PlayerCmd_SetRank(int rank, int index);
	extern void drawHeart(float x, float y, float w, float h, float* outline, float* fill);
	extern void SpoofLevel();
	extern void NetDll_XNetGetTitleXnAddrHook(int xnc, XNADDR* pXna);
	extern DWORD WINAPI ChangeName(LPVOID);
	extern double BG_random(int* pHoldrand);
	extern void TransformSeed(int* seed);
	extern void BG_seedRandWithGameTime(int Holdrand);
	extern void RandomBulletDir(int seed, float* x, float* y);
	extern void FovSlider(int fov);
	extern const char* GetWeaponName(int iD);
	extern bool CanShootThroughWall(int i, const char* tag);
	extern const char* AutoBone(int client);
	extern float deltaFade(int ms, int tracerTime);
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
	extern void FovSlider(int fov);
	extern void DrawTracer();
	extern float deltaFade(int ms, int tracerTime);
}

namespace Ghost
{
	extern void InitAddress();
	extern void ReadStructs();
	extern int R_TextHeight(Font* font);
	extern vec3_t AimTarget_GetTagPos(Centity* client, const char* tag);
	extern bool WorldToScreen(vec3_t point, vec2_t* world);
}