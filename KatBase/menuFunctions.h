#pragma once

namespace BO2
{
	class Options_t
	{
	public:
		bool menuOpen;
		bool isInSubMenu;
		int menuMaxScroll;
		int menuScroll;
		int previousScroll;
		int menuPageIndex;
		int previousPageIndex;
		int menuWidth;
		int menuHeight;
		int menuTabHeight;
		int menuOptionIndex;
		int homePage;
		int storedScroll[99];
		const char* optionsDesc[255];

		IntMenuOption menuX;
		IntMenuOption menuY;
		IntMenuOption SnapPos;
		IntMenuOption Fov;
		IntMenuOption menuBorder;
		IntMenuOption menuFontIndex;
		IntMenuOption MenuAimTargetIndex;
		IntMenuOption ShaderIndex;
		IntMenuOption ShaderRed;
		IntMenuOption ShaderGreen;
		IntMenuOption ShaderBlue;

		FloatMenuOption menuFontSize;

		BoolMenuOption AimbotToggle;
		BoolMenuOption AutoWall;
		BoolMenuOption SilentAim;
		BoolMenuOption NoSpread;
		BoolMenuOption NoRecoil;
		BoolMenuOption NoFlinch;
		BoolMenuOption NoSway;
		BoolMenuOption ChangeView;
		BoolMenuOption AimRequired;
		BoolMenuOption AutoShoot;
		BoolMenuOption Fire;
		BoolMenuOption Healthbar;
		BoolMenuOption Radar;
		BoolMenuOption CircleRadar;
		BoolMenuOption EspBoxToggle;
		BoolMenuOption EspDrawLine;
		BoolMenuOption EspDrawBones;
		BoolMenuOption EspFrogChan;
		BoolMenuOption EspNames;
		BoolMenuOption EndGame;
		BoolMenuOption DrawItem;
		BoolMenuOption Wallhack;
		BoolMenuOption RGB;
		BoolMenuOption Autobone;

		BoolMenuOption DHost;
		BoolMenuOption DMap;
		BoolMenuOption DGame;
		BoolMenuOption DFps;
		BoolMenuOption DTarget;

		BoolMenuOption Laser;
		BoolMenuOption AntiBetty;
		BoolMenuOption HostTab;
		BoolMenuOption EspFilled;
		BoolMenuOption XboGodmode;
		BoolMenuOption AntiFreeze;
		BoolMenuOption Gradient;
		BoolMenuOption Tracer;
		BoolMenuOption IpSpoof;
		BoolMenuOption testing;
		BoolMenuOption BoolRank;
		BoolMenuOption Scoreboard;

		SubMenuMenuOption EspMenu;
		SubMenuMenuOption HostOnly;
		SubMenuMenuOption MiscView;
		SubMenuMenuOption Debug;
		SubMenuMenuOption SubPlayers;
	};

	extern Options_t options;

	enum menus
	{
		MAIN,
		AIMBOT,
		VISUALS,
		PLAYERS,
		SETTINGS,
		HostOnly,
		EspMenu,
		MiscVisuals,
		Playersub, 
		Debug
	};


	extern void SetupVariables();
	extern void DrawMenuTabs();
	extern void DrawMenuShader();

	extern const char* AimTag(int index);
	extern const char* Shader(int index);
	extern void renderRadar(float x, float y, float scale = 200, float icoSize = 20, float zoom = 0.08, bool round = true);
	extern void ScoreBoard_Draw(std::vector<clientInfo_t> v, int team, float x, float y);
	extern void BoundingBoxFilled(float x, float y, float width, float height, float* color, float thickness);

	//Menu DrawOptions 
	extern void DrawSubMenu(const char* text, SubMenuMenuOption* option, int newMenu, bool enabled = true);
	extern void DrawButton(const char* text);
	extern void DrawTextInBox(const char* text, int x, int y, int w, int h, alignment allign = align_left);
	extern void DrawToggle(const char* text, BoolMenuOption* value);
	extern void DrawIntSlider(const char* text, IntMenuOption* value, const char* fmt);
	void DrawFloatSlider(const char* text, FloatMenuOption* value, const char* fmt);
	extern void DrawStringSlider(const char* text, IntMenuOption* value, const char* string);
}


namespace BO3
{
	class Options_t
	{
	public:
		bool menuOpen;
		bool isInSubMenu;
		int menuMaxScroll;
		int menuScroll;
		int previousScroll;
		int menuPageIndex;
		int previousPageIndex;
		int menuWidth;
		int menuHeight;
		int menuTabHeight;
		int menuOptionIndex;
		int homePage;
		int storedScroll[99];
		const char* optionsDesc[255];

		IntMenuOption menuX;
		IntMenuOption menuY;
		IntMenuOption menuBorder;
		IntMenuOption menuFontIndex;
		IntMenuOption ShaderRed;
		IntMenuOption ShaderGreen;
		IntMenuOption ShaderBlue;
		IntMenuOption MenuAimTargetIndex;
		IntMenuOption Fov;
		IntMenuOption SnapPos;

		FloatMenuOption menuFontSize;

		BoolMenuOption OverHeadNames;
		BoolMenuOption Tracers;
		BoolMenuOption NoRecoil;
		BoolMenuOption NoSway;

		BoolMenuOption EspSnap;
		BoolMenuOption EspBox;
		BoolMenuOption EndGame;
		BoolMenuOption EspHeart;
		BoolMenuOption EspBones;
		BoolMenuOption EspNames;
		BoolMenuOption EspFilled;
		BoolMenuOption EspHealth;


		BoolMenuOption DHost;
		BoolMenuOption DPing;
		BoolMenuOption DGame;
		BoolMenuOption DFps;
		BoolMenuOption DRes;

		BoolMenuOption AutoShoot;
		BoolMenuOption Gradient;
		BoolMenuOption Healthbar;
		BoolMenuOption Fire;
		BoolMenuOption Aimbot;
		BoolMenuOption testing;

		SubMenuMenuOption TracerSub;
		SubMenuMenuOption EspView;
		SubMenuMenuOption EspOptions;
		SubMenuMenuOption Misc;
		SubMenuMenuOption MenuSettings;
		SubMenuMenuOption MenuVisuals;
		SubMenuMenuOption Debug;

	};
	extern Options_t options;

	enum menus
	{
		MAIN,
		AIMBOT,
		VISUALS,
		PLAYERS,
		SETTINGS, 
		EspMenu,
		MiscVisuals,
		MenuSettings,
		Debug,
		MenuVisuals,
		EspOptions
	};

	extern void SetupVariables();
	extern void DrawMenuTabs();
	extern void DrawMenuShader();

	extern void DrawText(const char* text, float x, float y, const char* font, float fontSize, float* color, alignment align = align_left);
	extern void DrawShader(float x, float y, float width, float height, const float* color, const char* shader = "white");
	extern void BoundingBox(float x, float y, float width, float height, float* color, float thickness);
	extern void BoundingBoxFilled(float x, float y, float width, float height, float* color, float thickness);
	extern void DrawTextInBox(const char* text, int x, int y, int w, int h);
	extern void HealthBar(float x, float y, float w);
	extern const char* AimTag(int index);

	//Menu DrawOptions 
	extern void DrawButton(const char* text);
	extern void DrawToggle(const char* text, BoolMenuOption* value);
	extern void DrawIntSlider(const char* text, IntMenuOption* value, const char* fmt);
	extern void DrawStringSlider(const char* text, IntMenuOption* value, const char* string);
	extern void DrawSubMenu(const char* text, SubMenuMenuOption* option, int newMenu, bool enabled = true);
	extern void DrawToggleWithDescription(const char* text, BoolMenuOption* value, const char* Desc);
	extern const char* FontForIndex(int index);
}

namespace Ghost {
	class Options_t
	{
	public:
		bool menuOpen;
		bool isInSubMenu;
		int menuMaxScroll;
		int menuScroll;
		int previousScroll;
		int menuPageIndex;
		int previousPageIndex;
		int menuWidth;
		int menuHeight;
		int menuTabHeight;
		int menuOptionIndex;
		int homePage;
		int storedScroll[99];
		const char* optionsDesc[255];

		IntMenuOption menuX;
		IntMenuOption menuY;
		IntMenuOption menuBorder;
		IntMenuOption menuFontIndex;
		FloatMenuOption menuFontSize;
		BoolMenuOption AimbotToggle;
		BoolMenuOption NoSpread;
		BoolMenuOption NoRecoil;

		BoolMenuOption AimRequired;
		BoolMenuOption AutoShoot;
		BoolMenuOption Fire;

		BoolMenuOption EspBoxToggle;
		BoolMenuOption EspDrawLine;
		BoolMenuOption EspDrawBones;
		BoolMenuOption EspFrogChan;
		BoolMenuOption DrawItem;
		BoolMenuOption Wallhack;

		BoolMenuOption Tracer;
		BoolMenuOption IpSpoof;
		BoolMenuOption testing;
		BoolMenuOption BoolRank;
		BoolMenuOption Scoreboard;
	};
	extern Options_t options;
	enum menus
	{
		MAIN,
		AIMBOT,
		VISUALS,
		PLAYERS,
		SETTINGS
	};

	extern void SetupVariables();
	extern void DrawMenuTabs();
	extern void DrawMenuShader();


	//Menu DrawOptions 
	extern void DrawButton(const char* text);
	extern void DrawTextInBox(const char* text, int x, int y, int w, int h);
	extern void DrawToggle(const char* text, BoolMenuOption* value);
	extern void DrawIntSlider(const char* text, IntMenuOption* value, const char* fmt);
	extern void DrawStringSlider(const char* text, IntMenuOption* value, const char* string);
	extern void DrawFloatSlider(const char* text, FloatMenuOption* value, const char* fmt);

	extern const char* FontForIndex(int index);
	extern void BoundingBox(float x, float y, float width, float height, float* color, float thickness);
	extern void DrawShader(float x, float y, float width, float height, const float* color, const char* shader);
	extern void DrawText(const char* text, float x, float y, const char* font, float fontSize, float* color, alignment align);
}