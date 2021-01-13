struct Material
{
	const char* name;
};

struct Font
{
	const char* name;
	int pixelHeight;
};


namespace BO2
{
	enum XASSET
	{
		XASSET_PHYSPRESET,
		XASSET_PHYSCONSTRAINTS,
		XASSET_DESTRUCTIBLEDEF,
		XASSET_XANIM,
		XASSET_XMODEL,
		XASSET_XMODELMESH,
		XASSET_MATERIAL,
		XASSET_PIXELSHADER,
		XASSET_TECHSET,
		XASSET_IMAGE,
		XASSET_SOUND,
		XASSET_SOUND_PATCH,
		XASSET_COL_MAP,
		XASSET_COM_MAP,
		XASSET_GAME_MAP,
		XASSET_MAP_ENTS,
		XASSET_GFX_MAP,
		XASSET_LIGHTDEF,
		XASSET_LENSFLAREDEF,
		XASSET_UI_MAP,
		XASSET_FONT,
		XASSET_FONTICON,
		XASSET_LOCALIZE,
		XASSET_WEAPON,
		XASSET_WEAPONDEF,
		XASSET_WEAPONVARIANT,
		XASSET_WEAPONFULL,
		XASSET_CGMEDIATABLE,
		XASSET_PLAYERSOUNDSTABLE,
		XASSET_PLAYERFXTABLE,
		XASSET_SHAREDWEAPONSOUNDS,
		XASSET_ATTACHMENT,
		XASSET_ATTACHMENTUNIQUE,
		XASSET_WEAPONCAMO,
		XASSET_CUSTOMIZATIONTABLE,
		XASSET_CUSTOMIZATIONTABLE_FEIMAGES,
		XASSET_CUSTOMIZATIONTABLECOLOR,
		XASSET_SNDDRIVERGLOBALS,
		XASSET_FX,
		XASSET_FX_ALIAS,
		XASSET_TAGFX,
	};

	enum entityType_t
	{
		ET_GENERAL,
		ET_PLAYER,
		ET_PLAYER_CORPSE,
		ET_ITEM,
		ET_MISSILE,
		ET_INVISIBLE,
		ET_SCRIPTMOVER,
		ET_SOUND_BLEND,
		ET_FX,
		ET_LOOP_FX,
		ET_PRIMARY_LIGHT,
		ET_TURRET,
		ET_HELICOPTER,
		ET_PLANE,
		ET_VEHICLE,
		ET_VEHICLE_CORPSE,
		ET_ACTOR,
		ET_ACTOR_SPAWNER,
		ET_ACTOR_CORPSE,
		ET_STREAMER_HINT,
		ET_ZBARRIER,
		ET_EVENTS,
	};

	struct UIContext
	{
		int contextIndex; //0x0000
		float bias; //0x0004
		std::int32_t realTime; //0x0008
		std::int32_t frameTime; //0x000C
		char pad_0010[12]; //0x0010
		std::int32_t screenWidth; //0x001C
		std::int32_t screenHeight; //0x0020
		float screenAspect; //0x0024
		float FPS; //0x0028
		char pad_002C[20]; //0x002C

		float CenterX()
		{
			return this->screenWidth / 2;
		}
		float CenterY()
		{
			return this->screenHeight / 2;
		}
	};


	union DvarValue
	{
		bool enabled;                               //0x01
		int integer;                                //0x04
		unsigned int unsignedInt;                   //0x04
		__int64 integer64;                          //0x08
		unsigned __int64 unsignedInt64;             //0x08
		float value;                                //0x04
		float vector[4];                            //0x10
		const char* string;                         //0x04
		char color[4];                              //0x04
	}; //Size = 0x10

	union DvarLimits
	{
		struct
		{
			int stringCount;
			const char** strings;
		} enumeration;                              //0x08

		struct
		{
			int min;
			int max;
		} integer;                                  //0x08

		struct
		{
			__int64 min;
			__int64 max;
		} integer64;                                //0x10

		struct
		{
			float min;
			float max;
		} value, vector;                            //0x08
	}; //Size = 0x10

	struct dvar_s
	{
		const char* name;                           //0x00
		const char* description;                    //0x04
		int hash;                                   //0x08
		unsigned int flags;                         //0x0C
		int type;                                   //0x10
		int modified;                               //0x14
		DvarValue current;                          //0x18
		DvarValue latched;                          //0x28
		DvarValue reset;                            //0x38
		DvarValue saved;                            //0x48
		DvarLimits domain;                          //0x58
		dvar_s* next;                               //0x68
	}; //Size = 0x6C


	struct cpose_t
	{
		__int16 lightingHandle; //0x0000 
		unsigned char eType; //0x0002 
		unsigned char localClientNum; //0x0003 
		char _0x0004[40];
		vec3_t Origin; //0x002C 
		vec3_t viewAngles; //0x0038
		char _0x0044[272];
	};

	struct trajectory_t
	{
		unsigned char trType; //0x015C 
		char _0x015D[3];
		__int32 trTime; //0x0160 
		__int32 trDuration; //0x0164 
		vec3_t NewOrigin; //0x0168 
		vec3_t trDelta; //0x0174 
	};

	struct LerpEntityState
	{
		__int32 Flags; //0x0154 
		__int32 eFlags2; //0x0158 
		trajectory_t pos;

	};

	struct entityState_t
	{
		__int32 ClientNumber; //0x01D0 
		LerpEntityState lerp;
		char _0x0200[88];
		char _0x0258[1]; //0x0258 
		BYTE Check; //0x0259 
		BYTE Alive; //0x025A 
		BYTE Alive2; //0x025B 
		char _0x025C[4];
		BYTE Blank; //0x0260 
		BYTE Witch; //0x0261 
		char _0x0262[38];
		__int8 compassType; //0x0288 
		char _0x0289[31];
		__int16 Type; //0x02A8
		char _0x02Adc[0xA];
		int pickupId;                // 0x2B4
		char _0x02AA[0xB4];
		char State;                    //0x36C    
		char padding05[0x7];        //0x36D
	};

	struct centity_tBo2
	{
		cpose_t pose;
		LerpEntityState curState;
		char _0x0180[36];
		float leanf; //0x01A4 
		__int32 movementDir; //0x01A8 
		__int32 movementType; //0x01AC 
		__int32 WeaponID; //0x01B0 
		__int32 OldWeapon; //0x01B4 
		__int32 offHandWeaponModel; //0x01B8 
		__int32 meleeWeapon; //0x01BC 
		unsigned char offhandeWeaponModel; //0x01C0 
		unsigned char meleeWeaponModel; //0x01C1 
		unsigned char vehicleType; //0x01C2 
		unsigned char vehicleAnimBoneIndex; //0x01C3 
		unsigned char vehicleSeat; //0x01C4 
		unsigned char stowedweaponCamo; //0x01C5 
		char _0x01C6[10];
		entityState_t nextState;
		//size 0x374
	};

	struct playerstate_s
	{
		__int32 commandTime; //0x0090 
		__int32 pm_type; //0x0094 
		__int32 bobCycle; //0x0098 
		__int32 pm_flags; //0x009C 
		__int64 weapFlags; //0x00A0 
		__int32 otherFlags; //0x00A8 
		__int32 pm_time; //0x00AC 
		__int32 loopSoundId; //0x00B0 
		__int32 loopSoundFade; //0x00B4 
		vec3_t origin; //0x00B8 
		vec3_t velocity; //0x00C4 
		__int32 remoteEyesEnt; //0x00D0 
		__int32 remoteEyesTagname; //0x00D4 
		__int32 remoteControlEnt; //0x00D8 
		__int32 weaponTime; //0x00DC 
		__int32 weaponDelay; //0x00E0 
		__int32 weaponTimeLeft; //0x00E4 
		__int32 weaponDelayTime; //0x00E8 
		__int32 weaponIdleTime; //0x00EC 
		__int32 grenadeTimeLeft; //0x00F0 
		__int32 throwBackGrenadeOwner; //0x00F4 
		__int32 throwBackGrenadeTimeLeft; //0x00F8 
		__int32 weaponRestrictKickTime; //0x00FC 
		char _0x0100[28];
		__int32 gravity; //0x011C 
		float leanf; //0x0120 
		__int32 speed; //0x0124 
		vec3_t delta_angles; //0x0128 
		__int32 groundEntityNum; //0x0134 
		__int32 moverEntityNum; //0x0138 
		__int32 moverTimestamp; //0x013C 
		__int32 groundType; //0x0140 
		vec3_t vLadderVec; //0x0144 
		__int32 jumpTime; //0x0150 
		float jumpOriginZ; //0x0154 
		__int32 slideTime; //0x0158 
		__int32 moveType; //0x015C 
		__int32 legsTimer; //0x0160 
		__int32 torsoTimer; //0x0164 
		char _0x0168[36];
		__int32 eFlags; //0x018C 
		__int32 eFlags2; //0x0190 
		char _0x0194[180];
		__int32 primaryWeapon; //0x0248 
		char _0x024C[8];
		__int32 offhand; //0x0254 
		char _0x0258[112];
		__int32 health; //0x02C8 
		char _0x02CC[4];
		__int32 maxHealth; //0x02D0 
	};

	struct Snapshot_s
	{
		__int32 snapFlags; //0x0000 
		__int32 ping; //0x0004 
		__int32 serverTime; //0x0008 
		__int32 physicsTime; //0x000C 
		playerstate_s N246FD0C6; //0x0010 
	};

	struct refdef_t
	{
		__int32 x; //0x0000 
		__int32 y; //0x0004 
		__int32 scrWidth; //0x0008 
		__int32 scrHeight; //0x000C 
		char _0x0010[20];
		float tanfFovX; //0x0024 
		float tanfFovY; //0x0028 
		float tanfFovZ; //0x002C 
		char _0x0030[4];
		float fov; //0x0034 
		vec3_t viewOrigin; //0x0038 
		char _0x0044[4];
		vec3_t viewAxis[3]; //0x0048 
	};

	struct score_s
	{
		__int32 place; //0x0090 
		__int32 score; //0x0094 
		__int32 kills; //0x0098 
		__int32 assist; //0x009C 
		__int32 deaths; //0x00A0 
		__int32 wagerWinnings; //0x00A4 
		__int32 scoreboardPoints; //0x00A8 
		__int32 scoreboardKills; //0x00AC 
		__int32 scoreboardDeath; //0x00B0 
		__int32 headshots; //0x00B4 
		char _0x00B8[20];
		__int32 curStreak; //0x00CC 
	};

	struct clientInfo_t
	{
		__int32 infoValid; //0x0000 
		__int32 nextValid; //0x0004 
		__int32 clientNum; //0x0008 
		char name[32]; //0x000C 
		__int32 team; //0x002C 
		__int32 oldTeam; //0x0030 
		__int32 ffaTeam; //0x0034 
		char _0x0038[87];
		__int8 dead; //0x008F 
		score_s score; //0x0090 
		__int32 hStatusIcon; //0x00D0 
		__int32 hRankIcon; //0x00D4 
		char _0x00D8[8];
		char bodyModel[64]; //0x00E0 
		char attachModelNames[64][6]; //0x0120 
		char attachTagNames[64][6]; //0x02A0 
		char _0x0420[164];
		vec3_t viewAngles; //0x04C4 
		char _0x04D0[244];
		__int32 primaryWeapon; //0x05C4 
		char _0x05C8[576];
	}; //0x808

	struct cg_s
	{
		__int32 clientNum; //0x0000 
		__int32 localClientNum; //0x0004 
		char _0x0008[16];
		__int32 renderScreen; //0x0018 
		__int32 latestSnapshotNum; //0x001C 
		__int32 latestSnapshotTime; //0x0020 
		Snapshot_s* snap; //0x0024 
		Snapshot_s* nextSnap; //0x0028 
		char _0x002C[100];
		playerstate_s ps;
		char _0x02D4[0x27C0];
		int entity_count; //0x2A98
		int player_count; //0x2A9C
		int actor_count; //0x2AA0
		char _0x2AA0[0x455E4];
		int ServerTimeSubtractCount; //0x48088
		int ServerTime; //0x4808C
		int SubtractedCountServerTime; // 0x48090
		char _0x48094[0x57EC];
		refdef_t refdef; //0x4D880
		char _0x482B4[0x22C];
		float AdsScale; //0x4DB18
		char _0x4DB1C[0x1BCF4];
		vec3_t ViewAngles; //0x69810
		char _0x6981C[0x4C];
		float compassNorthYaw; //0x69868
		vec2_t compassNorth; //0x6986C
		Material* compassMapMaterial; //0x69874
		int* compassMapScrambledMaterial; //0x69878
		vec2_t compassMapUpperLeft; //0x6987C
		vec2_t compassMapWorldSize; //0x69884 - 0x6988C
		char _0x6988C[0x204];
		clientInfo_t clientInfo[18]; //0x69A90
		char _0x72B20[0xE060];
		float weaponSpreadScale; //0x80B80
	};
	struct Cgs_t
	{
		char pad_0000[8]; //0x0000
		int32_t screenX; //0x0008
		int32_t screenY; //0x000C
		char pad_0010[32]; //0x0010
		char gametype[4]; //0x0030
		char pad_0034[28]; //0x0034
		char hostName[12]; //0x0050
		char pad_005C[244]; //0x005C
		int32_t MaxClients; //0x0150
		char pad_0154[4]; //0x0154
		char MapFileName[32]; //0x0158
		char pad_0178[32]; //0x0178
		char MapName[16]; //0x0198
		char pad_01A8[456]; //0x01A8
	};
	struct Usercmd_t// size 0x3C
	{
		int serverTime;		// 0x00
		int buttons;		// 0x04
		char _0x08[4];		// 0x08
		int viewAngles[3];	// 0x0C
		int primaryWeapon;	// 0x18
		int secondayWeapon;	// 0x1C
		char _0x20[4];		// 0x20
		char forwardDir;	// 0x24
		char reverseDir;	// 0x25
		char _0x26[0x16];	// 0x26
	};

	struct ClientActive_t
	{
		char padding00[0x44];		 //0x00
		bool ADS;					 //0x44
		char padding01[0xC3];		 //0x45
		vec3_t baseAngle;			 //0x108
		char padding02[0x2B75];		 //0x110
		vec3_t viewAngle;			 //0x2C8C
		char padding03[0x40010];	 //0x2C94
		Usercmd_t Usercmd[128];		 //0x42CA8
		int CurrentCmdNumber;		 //0x44AA8
	};

	struct gentity_t
	{
		char pad_0000[340]; //0x0000
		struct
		{
			char _0x00[0x5558];
			int rank;
			int prestige;
		}*pClient;
		char pad_0158[452]; //0x0158
	}; //Size: 0x031C

	static char* Bones[] = {
		"j_helmet", "j_head", "j_neck",
		"j_shoulder_le", "j_elbow_le", "j_wrist_le", "j_elbow_le", "j_shoulder_le", "j_neck",
		"j_shoulder_ri", "j_elbow_ri", "j_wrist_ri", "j_elbow_ri", "j_shoulder_ri", "j_neck",
		"j_spineupper", "j_spinelower", "j_hip_le", "j_knee_le", "j_ankle_le", "j_knee_le",
		"j_hip_le", "j_spinelower", "j_hip_ri", "j_knee_ri", "j_ankle_ri"
	};


	extern UIContext* cgDC;
	extern cg_s* cgGame;
	extern Cgs_t* cgServer;
	extern centity_tBo2* cg_entitiesArray;
	extern ClientActive_t* ClientActive;
	extern gentity_t* g_entitiesArray;
}

namespace BO3
{
	enum XASSET
	{
		XASSET_PHYSPRESET,
		XASSET_PHYSCONSTRAINTS,
		XASSET_DESTRUCTIBLEDEF,
		XASSET_XANIM,
		XASSET_XMODEL,
		XASSET_XMODELMESH,
		XASSET_MATERIAL,
		XASSET_PIXELSHADER,
		XASSET_TECHSET,
		XASSET_IMAGE,
		XASSET_SOUND,
		XASSET_SOUND_PATCH,
		XASSET_COL_MAP,
		XASSET_COM_MAP,
		XASSET_GAME_MAP,
		XASSET_MAP_ENTS,
		XASSET_GFX_MAP,
		XASSET_LIGHTDEF,
		XASSET_LENSFLAREDEF,
		XASSET_UI_MAP,
		XASSET_FONT,
		XASSET_FONTICON,
		XASSET_LOCALIZE,
		XASSET_WEAPON,
		XASSET_WEAPONDEF,
		XASSET_WEAPONVARIANT,
		XASSET_WEAPONFULL,
		XASSET_CGMEDIATABLE,
		XASSET_PLAYERSOUNDSTABLE,
		XASSET_PLAYERFXTABLE,
		XASSET_SHAREDWEAPONSOUNDS,
		XASSET_ATTACHMENT,
		XASSET_ATTACHMENTUNIQUE,
		XASSET_WEAPONCAMO,
		XASSET_CUSTOMIZATIONTABLE,
		XASSET_CUSTOMIZATIONTABLE_FEIMAGES,
		XASSET_CUSTOMIZATIONTABLECOLOR,
		XASSET_SNDDRIVERGLOBALS,
		XASSET_FX,
		XASSET_FX_ALIAS,
		XASSET_TAGFX,
	};

	enum entityType_t
	{
		ET_GENERAL,
		ET_PLAYER,
		ET_PLAYER_CORPSE,
		ET_ITEM,
		ET_MISSILE,
		ET_INVISIBLE,
		ET_SCRIPTMOVER,
		ET_SOUND_BLEND,
		ET_FX,
		ET_LOOP_FX,
		ET_PRIMARY_LIGHT,
		ET_TURRET,
		ET_HELICOPTER,
		ET_PLANE,
		ET_VEHICLE,
		ET_VEHICLE_CORPSE,
		ET_ACTOR,
		ET_ACTOR_SPAWNER,
		ET_ACTOR_CORPSE,
		ET_STREAMER_HINT,
		ET_ZBARRIER,
		ET_EVENTS,
	};

	struct UIContext
	{
		int contextIndex; //0x0000
		float bias; //0x0004
		std::int32_t realTime; //0x0008
		std::int32_t frameTime; //0x000C
		char pad_0010[12]; //0x0010
		std::int32_t screenWidth; //0x001C
		std::int32_t screenHeight; //0x0020
		float screenAspect; //0x0024
		float FPS; //0x0028
		char pad_002C[20]; //0x002C

		float CenterX()
		{
			return this->screenWidth / 2;
		}
		float CenterY()
		{
			return this->screenHeight / 2;
		}
	};

	struct Centity
	{
		char pad_0000[2]; //0x0000
		int8_t EType; //0x0002
		char pad_0003[37]; //0x0003
		vec3_t Origin; //0x0028
		vec3_t ViewAngle; //0x0034
		char pad_0040[536]; //0x0040
		int32_t ClientNum; //0x0258
		char pad_025C[988]; //0x025C
		char StateFlag; //0x0638
		char pad_0639[7];
	};
	struct ClientInfo
	{
		char pad_0000[12]; //0x0000
		char Name[32]; //0x000C
		int32_t Team; //0x002C
		char pad_0030[155]; //0x0030
		int8_t Health; //0x00CB
		char pad_00CC[2228]; //0x00CC
	};
	struct CgArray
	{
		int32_t MyClientNum; //0x0000
		char pad_0004[128]; //0x0004
		int32_t Ping; //0x0084
		int32_t ServerTime; //0x0088
		int32_t PhysicalTime; //0x008C
		int64_t CmdTime; //0x0090
		char pad_0098[40]; //0x0098
		vec3_t Origin; //0x00C0
		vec3_t Velocity; //0x00CC
		char pad_00D8[884]; //0x00D8
	};
	struct ClientActive_t
	{
		char pad_0000[348]; //0x0000
		vec3_t SpawnAngles; //0x015C
		char pad_0168[12344]; //0x0168
		vec3_t ViewAngles; //0x31A0
		char _0xd[0x22010];
		int cmdnumber;
	};
	struct RefDef
	{
		char pad_0000[132]; //0x0000
		vec3_t ViewOrigin; //0x0084
		char pad_0090[16]; //0x0090
		vec3_t ViewAxis[3]; //0x00A0
		char pad_00C4[1952]; //0x00C4
	};
	struct trace_t
	{
		vec3_t normal; // 0x0
		char padding[0x04]; // 0xC
		float fraction; // 0x10
		int surfaceType; // 0x14
		int surfaceFlags; // 0x18
		int hitType; // 0x1C
		short hitId; // 0x20
		short modelIndex; // 0x22
		short partName;//0x24
		short boneIndex;//0x26
		short partGroup;//0x28
		bool allsolid; // 0x2A
		bool startsolid; // 0x2B
		bool walkable; // 0x2C
		char padding2[0x13];//0x2D   //og size 0x0B
	};
	static char* Bones[] = {
		"j_helmet", "j_head", "j_neck",
		"j_shoulder_le", "j_elbow_le", "j_wrist_le", "j_elbow_le", "j_shoulder_le", "j_neck",
		"j_shoulder_ri", "j_elbow_ri", "j_wrist_ri", "j_elbow_ri", "j_shoulder_ri", "j_neck",
		"j_spineupper", "j_spinelower", "j_hip_le", "j_knee_le", "j_ankle_le", "j_knee_le",
		"j_hip_le", "j_spinelower", "j_hip_ri", "j_knee_ri", "j_ankle_ri"
	};


	extern UIContext* cgDC;
	extern CgArray* cgGame;
	extern Centity* cg_entitiesArray;
	extern ClientActive_t* ClientActive;
	extern ClientInfo* Cinfo;
	extern RefDef* Ref;
}