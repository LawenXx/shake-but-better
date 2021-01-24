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
		IntMenuOption menuBorder;
		IntMenuOption menuFontIndex;
		FloatMenuOption menuFontSize;
		BoolMenuOption AimbotToggle;
		BoolMenuOption NoSpread;
		BoolMenuOption NoRecoil;
		BoolMenuOption ChangeView;

		BoolMenuOption AimRequired;
		BoolMenuOption AutoShoot;
		BoolMenuOption Fire;

		BoolMenuOption EspBoxToggle;
		BoolMenuOption EspDrawLine;
		BoolMenuOption EspDrawBones;
		BoolMenuOption EspFrogChan;
		BoolMenuOption DrawItem;
		BoolMenuOption Wallhack;
		BoolMenuOption Laser;

		BoolMenuOption HostTab;
		BoolMenuOption XboGodmode;

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
		SETTINGS//,
		//HostOnly
	};

	extern void SetupVariables();
	extern void DrawMenuTabs();
	extern void DrawMenuShader();

	extern void ScoreBoard_Draw(std::vector<clientInfo_t> v, int team, float x, float y);

	//Menu DrawOptions 
	extern void DrawButton(const char* text);
	extern void DrawTextInBox(const char* text, int x, int y, int w, int h);
	extern void DrawToggle(const char* text, BoolMenuOption* value);
	extern void DrawIntSlider(const char* text, IntMenuOption* value, const char* fmt);
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
		FloatMenuOption menuFontSize;

		BoolMenuOption OverHeadNames;
		BoolMenuOption Tracers;
		BoolMenuOption NoRecoil;
		BoolMenuOption NoSway;

		BoolMenuOption EspSnap;
		BoolMenuOption EspBox;
		BoolMenuOption EspHeart;
		BoolMenuOption EspBones;
		BoolMenuOption EspNames;
		BoolMenuOption EspHealth;


		BoolMenuOption AutoShoot;
		BoolMenuOption Fire;
		BoolMenuOption Aimbot;
		BoolMenuOption testing;
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

	extern void DrawText(const char* text, float x, float y, const char* font, float fontSize, float* color, alignment align = align_left);
	extern void DrawShader(float x, float y, float width, float height, const float* color, const char* shader = "white");
	extern void BoundingBox(float x, float y, float width, float height, float* color, float thickness);
	extern const char* FontForIndex(int index);

	//Menu DrawOptions 
	extern void DrawButton(const char* text);
	extern void DrawToggle(const char* text, BoolMenuOption* value);
	extern void DrawIntSlider(const char* text, IntMenuOption* value, const char* fmt);
	extern void DrawStringSlider(const char* text, IntMenuOption* value, const char* string);
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

	extern void DrawShader(float x, float y, float width, float height, const float* color, const char* shader);
	extern void DrawText(const char* text, float x, float y, const char* font, float fontSize, float* color, alignment align);
}