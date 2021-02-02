#include "pch.h"


void SetupSubMenu(SubMenuMenuOption* option, int newMenu, int previousPageIndex, int previousScroll, bool enabled)
{
	option->newMenu = newMenu;
	option->previousPageIndex = previousPageIndex;
	option->previousScroll = previousScroll;

	option->enabled = enabled;
}
void SetupSubSubMenu(SubMenuMenuOption* option, int newMenu, int homePage, int previousPageIndex, int previousScroll, bool enabled)
{
	option->newMenu = newMenu;
	option->previousPageIndex = previousPageIndex;
	option->previousScroll = previousScroll;
	option->homePageIndex = homePage;

	option->enabled = enabled;
}

void SwitchToSubMenu(SubMenuMenuOption* option, int& menuPageIndex)
{
	if (!option->enabled)
		return;

	menuPageIndex = option->newMenu;
}

void SetupBool(BoolMenuOption* option, bool state, bool enabled)
{
	option->state = state;

	option->enabled = enabled;
}

void ToggleBool(BoolMenuOption* option)
{
	if (!option->enabled)
		return;

	option->state = !option->state;
}

void SetupInt(IntMenuOption* option, int current, int init, int max, int min, int step, bool enabled)
{
	option->current = current;
	option->init = init;
	option->max = max;
	option->min = min;
	option->step = step;

	option->enabled = enabled;
}

void AddInt(IntMenuOption* option)
{
	if (!option->enabled)
		return;

	if (option->max > option->current)
		option->current += option->step;
}

void SubInt(IntMenuOption* option)
{
	if (!option->enabled)
		return;

	if (option->min < option->current)
		option->current -= option->step;
}

void ResetInt(IntMenuOption* option)
{
	if (!option->enabled)
		return;

	option->current = option->init;
}

void SetupFloat(FloatMenuOption* option, float current, float init, float max, float min, float step, bool enabled)
{
	option->current = current;
	option->init = init;
	option->max = max;
	option->min = min;
	option->step = step;

	option->enabled = enabled;
}

void AddFloat(FloatMenuOption* option)
{
	if (!option->enabled)
		return;

	if (option->max > option->current)
		option->current += option->step;
}

void SubFloat(FloatMenuOption* option)
{
	if (!option->enabled)
		return;

	if (option->min < option->current)
		option->current -= option->step;
}


void ResetFloat(FloatMenuOption* option)
{
	if (!option->enabled)
		return;

	option->current = option->init;
}

// lists

std::vector<SubMenuMenuOption*> SubMenuMenuOption_List;
std::vector<BoolMenuOption*> BoolMenuOption_List;
std::vector<IntMenuOption*> IntMenuOption_List;
std::vector<FloatMenuOption*> FloatMenuOption_List;

void StartMenuPage()
{
	SubMenuMenuOption_List.clear();
	BoolMenuOption_List.clear();
	IntMenuOption_List.clear();
	FloatMenuOption_List.clear();
}

// Sub Menu


void AddSubMenuMenuOptionToList(SubMenuMenuOption* option)
{
	SubMenuMenuOption_List.push_back(option);
}

void SwitchToSubMenu_List(int menuScroll, int& menuPageIndex, bool& isInSubMenu, int& scroll, int& previousPageIndex, int& previousScroll)
{
	for each (SubMenuMenuOption * option in SubMenuMenuOption_List)
	{
		if (option->scrollIndex == menuScroll)
		{
			if (!option->enabled)
				continue;

			previousPageIndex = menuPageIndex;
			previousScroll = menuScroll;

			SwitchToSubMenu(option, menuPageIndex);

			isInSubMenu = true;
			scroll = 0;
		}
	}
}

// bool

void AddBoolMenuOptionToList(BoolMenuOption* option)
{
	BoolMenuOption_List.push_back(option);
}

void ToggleBool_List(int menuScroll)
{
	for each (BoolMenuOption * option in BoolMenuOption_List)
	{
		if (option->scrollIndex == menuScroll)
			ToggleBool(option);
	}
}

void OpenSubMenu(SubMenuMenuOption* option) {
	SubMenuMenuOption_List.push_back(option);
}
// int

void AddIntMenuOptionToList(IntMenuOption* option)
{
	IntMenuOption_List.push_back(option);
}

void AddInt_List(int menuScroll)
{
	for each (IntMenuOption * option in IntMenuOption_List)
	{
		if (option->scrollIndex == menuScroll)
			AddInt(option);
	}
}

void SubInt_List(int menuScroll)
{
	for each (IntMenuOption * option in IntMenuOption_List)
	{
		if (option->scrollIndex == menuScroll)
			SubInt(option);
	}
}

void ResetInt_List(int menuScroll)
{
	for each (IntMenuOption * option in IntMenuOption_List)
	{
		if (option->scrollIndex == menuScroll)
			ResetInt(option);
	}
}

void AddFloatMenuOptionToList(FloatMenuOption* option)
{
	FloatMenuOption_List.push_back(option);
}

void AddFloat_List(float menuScroll)
{
	for each (FloatMenuOption * option in FloatMenuOption_List)
	{
		if (option->scrollIndex == menuScroll)
			AddFloat(option);
	}
}

void SubFloat_List(float menuScroll) 
{
	for each (FloatMenuOption * option in FloatMenuOption_List)
	{
		if (option->scrollIndex == menuScroll)
			SubFloat(option);
	}
}

void ResetFloat_List(int menuScroll)
{
	for each (FloatMenuOption * option in FloatMenuOption_List)
	{
		if (option->scrollIndex == menuScroll)
			ResetFloat(option);
	}
}
