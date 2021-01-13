#include "pch.h"


namespace BO2
{
	Options_t options;


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

	void ScoreBoard_Draw(int team, float x, float y) {
	
		if (options.Scoreboard.state) {
			const char* faction = BG_GetFactionForTeam(team, cgServer->MapName);

			DrawShader(x, y, 500, 500, black);
			for (int i = 0; i < 18; i++) {
				DrawText(va("Score: %i", cgGame->clientInfo[i].score), x, y/2, "fonts/720/normalfont", 1, white);
				DrawText(faction, x, y, "fonts/720/normalfont", 1, white);
				
			}
		}
	}

	void SetupVariables()
	{
		int numFonts = 5;

		options.menuOpen = false;
		options.isInSubMenu = false;
		options.menuMaxScroll = 0;
		options.menuScroll = 0;
		options.menuPageIndex = 0;
		options.menuWidth = 290.f;
		options.menuHeight = 500;
		options.menuTabHeight = 30;
		options.menuOptionIndex = 0;

		SetupInt(&options.menuX, 500, 5, 1280, 0, 1);
		SetupInt(&options.menuY, 205, 205, 500, 0);
		SetupInt(&options.menuBorder, 4, 4, 20, 1);
		SetupInt(&options.menuFontIndex, 4, 4, numFonts, 0);
		SetupFloat(&options.menuFontSize, 0.58, 0.58, 5.0f, 0.1f, 0.001f);

		SetupBool(&options.testing, false);
		SetupBool(&options.BoolRank, false);
		SetupBool(&options.IpSpoof, false);

		SetupBool(&options.NoRecoil, false);
		SetupBool(&options.AimbotToggle, false);
		SetupBool(&options.AimRequired, false);

		SetupBool(&options.EspBoxToggle, false);
		SetupBool(&options.EspDrawBones, false);
		SetupBool(&options.EspDrawLine, false);
		SetupBool(&options.EspFrogChan, false);
		SetupBool(&options.Scoreboard, false);
		SetupBool(&options.DrawItem, false);

	}

	void DrawMenuTabs()
	{
		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;
		int textWidth = R_TextWidth(0, "Main", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6 + 20;
		int textShaderW = R_TextWidth(0, "Main", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6 + 20;
		DrawText("Shake BO2", options.menuX.current + 155, options.menuY.current - 20, FontForIndex(options.menuFontIndex.current), .8, white, align_center);


		DrawText("Main", options.menuX.current + options.menuBorder.current + 10, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.6, white, align_left);
		if (options.menuPageIndex == MAIN)
			DrawShader(options.menuX.current + options.menuBorder.current + 10, options.menuY.current + options.menuBorder.current + textHeight, 5 + R_TextWidth(0, "Main", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6, 3, blue);

		DrawText("Aimbot", options.menuX.current + options.menuBorder.current + 10 + textWidth + 6, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.6, white, align_left);
		if (options.menuPageIndex == AIMBOT)
			DrawShader(options.menuX.current + options.menuBorder.current + 10 + textShaderW + 6, options.menuY.current + options.menuBorder.current + textHeight, 5 + R_TextWidth(0, "Aimbot", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6, 3, blue);
		textWidth += R_TextWidth(0, "Aimbot", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6 + 34;
		textShaderW += R_TextWidth(0, "Aimbot", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6 + 34;

		DrawText("Visuals", options.menuX.current + options.menuBorder.current + 10 + textWidth, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.6, white, align_left);
		if (options.menuPageIndex == VISUALS)
			DrawShader(options.menuX.current + options.menuBorder.current + 10 + textShaderW, options.menuY.current + options.menuBorder.current + textHeight, 5 + R_TextWidth(0, "Visuals", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6, 3, blue);
		textWidth += R_TextWidth(0, "Visuals", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6 + 34;
		textShaderW += R_TextWidth(0, "Visuals", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6 + 34;

		DrawText("Players", options.menuX.current + options.menuBorder.current + 10 + textWidth, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.6, white, align_left);
		if (options.menuPageIndex == PLAYERS)
			DrawShader(options.menuX.current + options.menuBorder.current + 10 + textShaderW, options.menuY.current + options.menuBorder.current + textHeight, 5 + R_TextWidth(0, "Players", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6, 3, blue);
		textWidth += R_TextWidth(0, "Players", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6 + 34;
		textShaderW += R_TextWidth(0, "Players", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6 + 34;
		/*
		DrawText("Host Only", options.menuX.current + options.menuBorder.current + 10 + textWidth, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.6, white, align_left);
		if (options.menuPageIndex == HostOnly)
			DrawShader(options.menuX.current + options.menuBorder.current + 10 + textShaderW, options.menuY.current + options.menuBorder.current + textHeight, 5 + R_TextWidth(0, "Host Only", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6, 3, blue);
		textWidth += R_TextWidth(0, "Host Only", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6 + 34;
		textShaderW += R_TextWidth(0, "Host Only", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6 + 34;
		*/

		DrawText("Settings", options.menuX.current + options.menuBorder.current + 10 + textWidth, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.6, white, align_left);
		if (options.menuPageIndex == SETTINGS)
			DrawShader(options.menuX.current + options.menuBorder.current + 10 + textShaderW, options.menuY.current + options.menuBorder.current + textHeight, 5 + R_TextWidth(0, "Settings", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6, 3, blue);

	}

	void DrawMenuShader()
	{
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current - 55, 310, 95 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current), blue);
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current - 12, 310, 48, black);
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current - 12 + 78 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current), 310, 5, blue);

		//ScrollBar
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current + 38 + (options.menuScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current), 310, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current, black);

		//Footer
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current - 12 + 50 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current), 310, 30, black);
		DrawText(va("%i/%i", options.menuScroll + 1, options.menuMaxScroll - 1), 5 + options.menuX.current + 5, 1 + options.menuY.current + 60 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);

	}

	void DrawButton(const char* text)
	{
		options.menuMaxScroll++;

		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;

		DrawText(text, 5 + options.menuX.current + 5, options.menuY.current + 38 + textHeight + (options.menuOptionIndex * textHeight), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);
		options.menuOptionIndex++;
	}

	void DrawToggle(const char* text, BoolMenuOption* value)
	{
		options.menuMaxScroll++;

		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;

		DrawText(text, 5 + options.menuX.current + 5, options.menuY.current + 38 + textHeight + (options.menuOptionIndex * textHeight), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);

		DrawShader(options.menuX.current + options.menuWidth - options.menuBorder.current - 12 - 2 + 25, options.menuY.current + 31 + (options.menuOptionIndex * textHeight) + ((textHeight - 12) / 2) + (options.menuBorder.current * 2), 12, 12, black);
		DrawShader(options.menuX.current + options.menuWidth - options.menuBorder.current - 10 - 3 + 25, options.menuY.current + 31 + (options.menuOptionIndex * textHeight) + ((textHeight - 10) / 2) + (options.menuBorder.current * 2), 10, 10, value->state ? white : black);
		BoundingBox(options.menuX.current + options.menuWidth - options.menuBorder.current - 12 - 2 + 25, options.menuY.current + 31 + (options.menuOptionIndex * textHeight) + ((textHeight - 12) / 2) + (options.menuBorder.current * 2), 12, 12, white, 1);

		if (!value->state)
		{
			value->scrollIndex = options.menuOptionIndex;
			AddBoolMenuOptionToList(value);
			options.menuOptionIndex++;
			return;
		}

		value->scrollIndex = options.menuOptionIndex;
		AddBoolMenuOptionToList(value);
		options.menuOptionIndex++;
	}

	void DrawIntSlider(const char* text, IntMenuOption* value, const char* fmt)
	{
		options.menuMaxScroll++;

		int textWidth = R_TextWidth(0, text, 0x7FFFFFFF, R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;
		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;

		DrawText(text, 5 + options.menuX.current + 5, options.menuY.current + 38 + textHeight + (options.menuOptionIndex * textHeight), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);

		DrawShader(options.menuX.current + options.menuWidth - options.menuBorder.current - 75 - 5 + 2 + 25, options.menuY.current + 70 + (options.menuOptionIndex * textHeight) + ((textHeight - 75) / 2) + 2, 75 - 4, 5 - 4 + 8, black);
		DrawShader(options.menuX.current + options.menuWidth - options.menuBorder.current - 75 - 5 + 1 + 25, options.menuY.current + 70 + (options.menuOptionIndex * textHeight) + ((textHeight - 75) / 2) + 1, ((75 - 2) / (float)value->max) * value->current, 5 - 2 + 8, blue);
		BoundingBox(options.menuX.current + options.menuWidth - options.menuBorder.current - 75 - 5 + 2 + 25, options.menuY.current + 70 + (options.menuOptionIndex * textHeight) + ((textHeight - 75) / 2) + 2, 75 - 4, 5 - 4 + 8, white, 1);

		DrawText(va(fmt, value->current), 5 + options.menuX.current + 222, options.menuY.current + 38 + textHeight + (options.menuOptionIndex * textHeight), FontForIndex(options.menuFontIndex.current), 0.5, white, align_right);

		value->scrollIndex = options.menuOptionIndex;
		AddIntMenuOptionToList(value);
		options.menuOptionIndex++;
	}

	void DrawStringSlider(const char* text, IntMenuOption* value, const char* string)
	{
		options.menuMaxScroll++;

		int textWidth = R_TextWidth(0, text, 0x7FFFFFFF, R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;
		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;

		DrawText(text, 5 + options.menuX.current + 5, options.menuY.current + 38 + textHeight + (options.menuOptionIndex * textHeight), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);
		DrawText(string, options.menuX.current + options.menuWidth - 8 + 25, options.menuY.current + 39 + textHeight + (options.menuOptionIndex * textHeight) - 2, FontForIndex(options.menuFontIndex.current), 0.5, white, align_right);

		value->scrollIndex = options.menuOptionIndex;
		AddIntMenuOptionToList(value);
		options.menuOptionIndex++;
	}
}


namespace BO3
{
	Options_t options;

	const char* FontForIndex(int index)
	{
		if (index == 0)
			return "fonts/smallDevFont";
		if (index == 1)
			return "fonts/bigDevFont";
		if (index == 2)
			return "fonts/consoleFont";
		if (index == 3)
			return "fonts/smallFont";
		if (index == 4)
			return "fonts/normalFont";
		if (index == 5)
			return "fonts/boldFont";
		else
			return "fonts/smallFont";
	}

	int R_TextHeight(Font* font)
	{
		return font->pixelHeight;
	}

void DrawText(const char* text, float x, float y, const char* font, float fontSize, float* color, alignment align)
{
	
	int fontA = Textwidth(text, strlen(text), R_RegisterFont(font), 0) * fontSize;

	if (align == align_left)
		x = x;
	if (align == align_right)
		x = x - fontA;
	if (align == align_center)
		x = x - (fontA / 2);
		
	R_AddCmdDrawText_test(text, strlen(text), R_RegisterFont(font), x, y, fontSize, fontSize, color, 0);
}


	void DrawShader(float x, float y, float width, float height, const float* color, const char* shader)
	{
		CG_DrawRotatedPicPhysical(0x83088EC0, x, y, width, height, 0.0f, color, Material_RegisterHandle(shader));
	}

	void BoundingBox(float x, float y, float width, float height, float* color, float thickness)
	{
		DrawShader(x - thickness, y - thickness, width + (thickness * 2), thickness, color); // Top
		DrawShader(x - thickness, y + height, width + (thickness * 2), thickness, color); // Bottom
		DrawShader(x - thickness, y - thickness, thickness, height + thickness, color); // Left
		DrawShader(x + width, y - thickness, thickness, height + (thickness * 2), color); // Right
	}


	void SetupVariables()
	{
		int numFonts = 5;

		options.menuOpen = false;
		options.isInSubMenu = false;
		options.menuMaxScroll = 0;
		options.menuScroll = 0;
		options.menuPageIndex = 0;
		options.menuWidth = 290.f;
		options.menuHeight = 500;
		options.menuTabHeight = 30;
		options.menuOptionIndex = 0;

		SetupInt(&options.menuX, 500, 5, 1280, 0, 1);
		SetupInt(&options.menuY, 205, 205, 500, 0);
		SetupInt(&options.menuBorder, 4, 4, 20, 1);
		SetupInt(&options.menuFontIndex, 4, 4, numFonts, 0);
		SetupFloat(&options.menuFontSize, 0.58, 0.58, 5.0f, 0.1f, 0.001f);

		SetupBool(&options.testing, false);
		SetupBool(&options.Aimbot, false);
	}

	void DrawMenuTabs()
	{
		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current;
		int textWidth = Textwidth("Main", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current)), 0) * 0.6 + 20;
		int textShaderW = Textwidth("Main", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current)), 0) * 0.6 + 20;
		DrawText("Shake BO3", options.menuX.current + 155, options.menuY.current - 20, FontForIndex(options.menuFontIndex.current), .8, white, align_center);

		DrawText("Main", options.menuX.current + options.menuBorder.current + 10, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.6, white, align_left);
		if (options.menuPageIndex == MAIN)
			DrawShader(options.menuX.current + options.menuBorder.current + 10, options.menuY.current + options.menuBorder.current + textHeight, Textwidth("Main", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current)), 0) * 0.6, 3, blue);

		DrawText("Aimbot", options.menuX.current + options.menuBorder.current + 10 + textWidth, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.6, white, align_left);
		if (options.menuPageIndex == AIMBOT)
			DrawShader(options.menuX.current + options.menuBorder.current + 10 + textShaderW, options.menuY.current + options.menuBorder.current + textHeight, Textwidth("Aimbot", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current)), 0) * 0.6, 3, blue);
		textWidth += Textwidth("Aimbot", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current)), 0) * 0.6 + 20;
		textShaderW += Textwidth("Aimbot", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current)), 0) * 0.6 + 20;

		DrawText("Visuals", options.menuX.current + options.menuBorder.current + 10 + textWidth, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.6, white, align_left);
		if (options.menuPageIndex == VISUALS)
			DrawShader(options.menuX.current + options.menuBorder.current + 10 + textShaderW, options.menuY.current + options.menuBorder.current + textHeight, Textwidth("Visuals", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current)), 0) * 0.6, 3, blue);
		textWidth += Textwidth("Visuals", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current)), 0) * 0.6 + 15;
		textShaderW += Textwidth("Visuals", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current)), 0) * 0.6 + 15;


		DrawText("Players", options.menuX.current + options.menuBorder.current + 10 + textWidth, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.6, white, align_left);
		if (options.menuPageIndex == PLAYERS)
			DrawShader(options.menuX.current + options.menuBorder.current + 10 + textShaderW, options.menuY.current + options.menuBorder.current + textHeight, Textwidth("Players", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current)), 0) * 0.6, 3, blue);
		textWidth += Textwidth("Players", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current)), 0) * 0.6 + 15;
		textShaderW += Textwidth("Players", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current)), 0) * 0.6 + 15;


		DrawText("Settings", options.menuX.current + options.menuBorder.current + 10 + textWidth, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.6, white, align_left);
		if (options.menuPageIndex == SETTINGS)
			DrawShader(options.menuX.current + options.menuBorder.current + 10 + textShaderW, options.menuY.current + options.menuBorder.current + textHeight, Textwidth("Settings", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current)), 0) * 0.6, 3, blue);

	}

	void DrawMenuShader()
	{
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current - 55, 310, 95 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current), blue);
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current - 12, 310, 48, black);
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current - 12 + 78 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current), 310, 5, blue);

		//ScrollBar
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current + 36 + (options.menuScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current), 310, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current, black);

		//Footer
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current - 12 + 50 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current), 310, 30, black);
		DrawText(va("%i/%i", options.menuScroll + 1, options.menuMaxScroll + 1), 5 + options.menuX.current + 5, 1 + options.menuY.current + 60 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);

	}

	void DrawButton(const char* text)
	{
		options.menuMaxScroll++;

		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current;

		DrawText(text, 5 + options.menuX.current + 5, options.menuY.current + 38 + textHeight + (options.menuOptionIndex * textHeight), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);
		options.menuOptionIndex++;
	}

	void DrawToggle(const char* text, BoolMenuOption* value)
	{
		options.menuMaxScroll++;

		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current;

		DrawText(text, 5 + options.menuX.current + 5, options.menuY.current + 38 + textHeight + (options.menuOptionIndex * textHeight), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);

		DrawShader(options.menuX.current + options.menuWidth - options.menuBorder.current - 12 - 2 + 25, options.menuY.current + 31 + (options.menuOptionIndex * textHeight) + ((textHeight - 12) / 2) + (options.menuBorder.current * 2), 12, 12, black);
		DrawShader(options.menuX.current + options.menuWidth - options.menuBorder.current - 10 - 3 + 25, options.menuY.current + 31 + (options.menuOptionIndex * textHeight) + ((textHeight - 10) / 2) + (options.menuBorder.current * 2), 10, 10, value->state ? white : black);
		BoundingBox(options.menuX.current + options.menuWidth - options.menuBorder.current - 12 - 2 + 25, options.menuY.current + 31 + (options.menuOptionIndex * textHeight) + ((textHeight - 12) / 2) + (options.menuBorder.current * 2), 12, 12, white, 1);

		if (!value->state)
		{
			value->scrollIndex = options.menuOptionIndex;
			AddBoolMenuOptionToList(value);
			options.menuOptionIndex++;
			return;
		}

		value->scrollIndex = options.menuOptionIndex;
		AddBoolMenuOptionToList(value);
		options.menuOptionIndex++;
	}

	void DrawIntSlider(const char* text, IntMenuOption* value, const char* fmt)
	{
		options.menuMaxScroll++;

		int textWidth = Textwidth(text, 0x7FFFFFFF, R_RegisterFont(FontForIndex(options.menuFontIndex.current)), 0) * options.menuFontSize.current;
		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current;

		DrawText(text, 5 + options.menuX.current + 5, options.menuY.current + 38 + textHeight + (options.menuOptionIndex * textHeight), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);

		DrawShader(options.menuX.current + options.menuWidth - options.menuBorder.current - 75 - 5 + 2 + 25, options.menuY.current + 70 + (options.menuOptionIndex * textHeight) + ((textHeight - 75) / 2) + 2, 75 - 4, 5 - 4 + 8, black);
		DrawShader(options.menuX.current + options.menuWidth - options.menuBorder.current - 75 - 5 + 1 + 25, options.menuY.current + 70 + (options.menuOptionIndex * textHeight) + ((textHeight - 75) / 2) + 1, ((75 - 2) / (float)value->max) * value->current, 5 - 2 + 8, blue);
		BoundingBox(options.menuX.current + options.menuWidth - options.menuBorder.current - 75 - 5 + 2 + 25, options.menuY.current + 70 + (options.menuOptionIndex * textHeight) + ((textHeight - 75) / 2) + 2, 75 - 4, 5 - 4 + 8, white, 1);

		DrawText(va(fmt, value->current), 5 + options.menuX.current + 222, options.menuY.current + 38 + textHeight + (options.menuOptionIndex * textHeight), FontForIndex(options.menuFontIndex.current), 0.5, white, align_right);

		value->scrollIndex = options.menuOptionIndex;
		AddIntMenuOptionToList(value);
		options.menuOptionIndex++;
	}

	void DrawStringSlider(const char* text, IntMenuOption* value, const char* string)
	{
		options.menuMaxScroll++;

		int textWidth = Textwidth(text, 0x7FFFFFFF, R_RegisterFont(FontForIndex(options.menuFontIndex.current)), 0) * options.menuFontSize.current;
		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current;

		DrawText(text, 5 + options.menuX.current + 5, options.menuY.current + 38 + textHeight + (options.menuOptionIndex * textHeight), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);
		DrawText(string, options.menuX.current + options.menuWidth - 8 + 25, options.menuY.current + 39 + textHeight + (options.menuOptionIndex * textHeight) - 2, FontForIndex(options.menuFontIndex.current), 0.5, white, align_right);

		value->scrollIndex = options.menuOptionIndex;
		AddIntMenuOptionToList(value);
		options.menuOptionIndex++;
	}
}