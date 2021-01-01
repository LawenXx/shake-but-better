#pragma once


struct SubMenuMenuOption
{
	int newMenu;
	int homePageIndex;
	int previousPageIndex;
	int previousScroll;

	int scrollIndex;
	bool enabled;
};

struct BoolMenuOption
{
	bool state;

	int scrollIndex;
	bool enabled;
};

struct IntMenuOption
{
	int current;
	int init;
	int max;
	int min;
	int step;

	int scrollIndex;
	bool enabled;
};

struct FloatMenuOption
{
	float current;
	float init;
	float max;
	float min;
	float step;

	int scrollIndex;
	bool enabled;
};

void SetupSubMenu(SubMenuMenuOption* option, int newMenu, int previousPageIndex, int previousScroll, bool enabled = true);
void SetupSubSubMenu(SubMenuMenuOption* option, int newMenu, int homePage = -1, int previousPageIndex = -1, int previousScroll = -1, bool enabled = true);

void SwitchToSubMenu(SubMenuMenuOption* option, int& menuPageIndex);

void SetupBool(BoolMenuOption* option, bool state, bool enabled = true);
void ToggleBool(BoolMenuOption* option);

void SetupInt(IntMenuOption* option, int current, int init, int max, int min, int step = 1, bool enabled = true);
void AddInt(IntMenuOption* option);
void SubInt(IntMenuOption* option);
void ResetInt(IntMenuOption* option);

void SetupFloat(FloatMenuOption* option, float current, float init, float max, float min, float step, bool enabled = true);
void AddFloat(FloatMenuOption* option);
void SubFloat(FloatMenuOption* option);
void ResetFloat(FloatMenuOption* option);

extern std::vector<SubMenuMenuOption*> SubMenuMenuOption_List;
extern std::vector<BoolMenuOption*> BoolMenuOption_List;
extern std::vector<IntMenuOption*> IntMenuOption_List;
extern std::vector<FloatMenuOption*> FloatMenuOption_List;

void StartMenuPage();

void AddSubMenuMenuOptionToList(SubMenuMenuOption* option);
void SwitchToSubMenu_List(int menuScroll, int& menuPageIndex, bool& isInSubMenu, int& scroll, int& previousPageIndex, int& previousScroll);

void AddBoolMenuOptionToList(BoolMenuOption* option);
void ToggleBool_List(int menuScroll);

void AddIntMenuOptionToList(IntMenuOption* option);
void AddInt_List(int menuScroll);
void SubInt_List(int menuScroll);
void ResetInt_List(int menuScroll);

void AddFloatMenuOptionToList(FloatMenuOption* option);
void AddFloat_List(int menuScroll);
void SubFloat_List(int menuScroll);
void ResetFloat_List(int menuScroll);
