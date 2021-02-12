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
		if (index == 6)
			return "fonts/720/gamefonts_xenon";
		else
			return "fonts/720/smallFont";
	}
	const char* AimTag(int index)
	{
		return Bones[index];
	}
	const char* Shader(int index)
	{
		return ShaderList[index];
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
	void BoundingBoxFilled(float x, float y, float width, float height, float* color, float thickness)
	{
		DrawShader(x - thickness, y - thickness, width + (thickness * 2), thickness, color); // Top
		DrawShader(x - thickness, y + height, width + (thickness * 2), thickness, color); // Bottom
		DrawShader(x - thickness, y - thickness, thickness, height + thickness, color); // Left
		DrawShader(x + width, y - thickness, thickness, height + (thickness * 2), color); // Right
		DrawShader(x - thickness, y - thickness, width, height + (thickness * 2), white2); // Filled
	}
	void DrawTextInBox(const char* text, int x, int y, int w, int h, alignment allign) {
		DrawShader(x + allign, y, w + R_TextWidth(0, text, MAXCHAR, R_RegisterFont("fonts/720/normalfont",0))/8, h, black);
		BoundingBox(x + allign, y, w + R_TextWidth(0, text, MAXCHAR, R_RegisterFont("fonts/720/normalfont", 0))/8, h, blue, 1);
		DrawText(text, x + 5, y + h - 5, "fonts/720/normalfont", 0.63, white, allign);
	}
	void DrawLine(vec2_t start, vec2_t end, float* color, float size)
	{
		vec2_t  delta = start - end;
		vec_t angle = atan2(delta.y, delta.x) * (180 / 3.141592654f);
		vec_t length = delta.Length();
		vec2_t  coords(end.x + ((delta.x - length) / 2), end.y + (delta.y / 2));
		CG_DrawRotatedPicPhysical(MP_Scr_Placment, coords.x, coords.y, length, size, angle, color, Material_RegisterHandle("white", 7));
	}
	void drawHeart(float x, float y, float w, float h, float* outline, float* fill)
	{
		//Outline - thick
		{
			DrawLine(vec2_t(x + (w / 100 * 0), y + (h / 100 * 45)), vec2_t(x + (w / 100 * 10), y + (h / 100 * 18)), outline, 2);
			DrawLine(vec2_t(x + (w / 100 * 100), y + (h / 100 * 45)), vec2_t(x + (w / 100 * 90), y + (h / 100 * 18)), outline, 2);
			DrawLine(vec2_t(x + (w / 100 * 10), y + (h / 100 * 18)), vec2_t(x + (w / 100 * 30), y + (h / 100 * 9)), outline, 2);
			DrawLine(vec2_t(x + (w / 100 * 90), y + (h / 100 * 18)), vec2_t(x + (w / 100 * 70), y + (h / 100 * 9)), outline, 2);
			DrawLine(vec2_t(x + (w / 100 * 30), y + (h / 100 * 9)), vec2_t(x + (w / 100 * 50), y + (h / 100 * 20)), outline, 2);
			DrawLine(vec2_t(x + (w / 100 * 70), y + (h / 100 * 9)), vec2_t(x + (w / 100 * 50), y + (h / 100 * 20)), outline, 2);
			DrawLine(vec2_t(x + (w / 100 * 0), y + (h / 100 * 45)), vec2_t(x + (w / 100 * 50), y + (h / 100 * 93)), outline, 2);
			DrawLine(vec2_t(x + (w / 100 * 100), y + (h / 100 * 45)), vec2_t(x + (w / 100 * 50), y + (h / 100 * 93)), outline, 2);
		}
	}

	void HealthBar(float x, float y, float w) {
		std::uint8_t health = cgGame->ps.health;
		std::uint8_t maxHealth = cgGame->ps.maxHealth;
		float* healthColor = (health < 30) ? Red : (health < 70) ? Yellow : Green;

		R_AddCmdDrawText(va("Health: %i/%i", cgGame->ps.health, cgGame->ps.maxHealth), strlen(va("Health: %i/%i", cgGame->ps.health, cgGame->ps.maxHealth)), R_RegisterFont("fonts/720/normalfont", 0), x, y - 40, 0.6, 0.6, 90, black, 0);
		DrawShader(x - w, y - health * 1.75 / 2, w, health * 1.75, healthColor);
	}

	void drawCircle(float x, float y, float w, float h, float thickness, float* color)
	{
		float angle1, angle2;
		for (int i = 0; i < 32; i++)
		{
			angle1 = i * 2 * M_PI / 32;
			angle2 = (i + 1) * 2 * M_PI / 32;
			DrawLine(vec2_t((x + (w / 2) * cos(angle1)) + (w / 2), (y + (h / 2) * sin(angle1)) + (h / 2)), vec2_t(((x + (w / 2) * cos(angle2)) + (w / 2)), (y + (h / 2) * sin(angle2)) + (h / 2)), color, thickness);
		}
	}
	void renderArrow(float x, float y, float scale, float angle, float* color)
	{
		scale /= 2;
		x += scale;
		y += scale;
		angle = (3.14f / 180) * (angle - 27);

		drawCircle(x, y - (sin(angle) * scale), 5, 5, scale, color);
	}
	void renderRadar(float x, float y, float scale, float icoSize, float zoom, bool round)
	{
		scale = scale - icoSize;
		vec2_t RadarCenter = vec2_t(scale, scale);
		vec2_t dif = vec2_t(((RadarCenter.x - (scale / 2)) - x), ((RadarCenter.y - (scale / 2)) - y));
		float angle, FinalA, CircleX, CircleY;
		BoundingBox(x, y, scale + icoSize, scale + icoSize, black, 1);
		DrawShader(x, y + (scale / 2) + (icoSize / 2), scale + icoSize, 1, black);
		DrawShader(x + (scale / 2) + (icoSize / 2), y, 1, scale + icoSize, black);
		if (round)
			drawCircle(x, y, scale + icoSize, scale + icoSize, 1, black);
		for (int i = 0; i < 1024; i++)
			if (cg_entitiesArray[i].nextState.Alive > 0)
			{
				int RadarX, RadarY;
				RadarX = cg_entitiesArray[cgGame->clientNum].pose.Origin.x - cg_entitiesArray[i].pose.Origin.x;
				RadarY = cg_entitiesArray[cgGame->clientNum].pose.Origin.y - cg_entitiesArray[i].pose.Origin.y;
				float
					Angle = cg_entitiesArray[cgGame->clientNum].pose.viewAngles.y / 180 * 3.141,
					RotateX = RadarY * cos(Angle) - RadarX * sin(Angle),
					RotateY = RadarX * cos(Angle) + RadarY * sin(Angle),
					FinalX = RadarCenter.x + (RotateX / (scale * zoom)),
					FinalY = RadarCenter.y + (RotateY / (scale * zoom));

				if (!round) {
					if (FinalX < RadarCenter.x - scale / 2) FinalX = (RadarCenter.x - scale / 2);
					if (FinalY < RadarCenter.y - scale / 2) FinalY = (RadarCenter.y - scale / 2);
					if (FinalX > RadarCenter.x + scale / 2) FinalX = (RadarCenter.x + scale / 2);
					if (FinalY > RadarCenter.y + scale / 2) FinalY = (RadarCenter.y + scale / 2);
				}
				else
				{
					angle = atan(RotateX / RotateY) * (180 / XM_PI);
					FinalA = (FinalY > RadarCenter.y ? -angle - 180.0f : -angle);
					if (FinalA < 0)
						FinalA += 360.0f;
					double radians = (XM_PI / 180) * (FinalA - 90.0f);
					CircleX = RadarCenter.x + (cosf(radians) * (scale / 2));
					CircleY = RadarCenter.y + (sinf(radians) * (scale / 2));
				}
				if ((((FinalX - RadarCenter.x) * (FinalX - RadarCenter.x) + (FinalY - RadarCenter.y) * (FinalY - RadarCenter.y)) < ((scale / 2) * (scale / 2))) || !round)
				{
					if (i != cgGame->clientNum && (cg_entitiesArray[i].pose.eType == ET_ACTOR && cg_entitiesArray[i].pose.eType != ET_ACTOR_CORPSE))
						renderArrow(FinalX - dif.x, FinalY - dif.y, icoSize, (cg_entitiesArray[cgGame->clientNum].pose.viewAngles.y - cg_entitiesArray[i].pose.viewAngles.y), Red);
					else if (cg_entitiesArray[i].pose.eType == ET_PLAYER) {
						if (!isTeam(&cg_entitiesArray[i]))
							renderArrow(FinalX - dif.x, FinalY - dif.y, icoSize, (cg_entitiesArray[cgGame->clientNum].pose.viewAngles.y - cg_entitiesArray[i].pose.viewAngles.y), Red);
						else
							renderArrow(FinalX - dif.x, FinalY - dif.y, icoSize, (cg_entitiesArray[cgGame->clientNum].pose.viewAngles.y - cg_entitiesArray[i].pose.viewAngles.y), Green);
					}
				}
				else
					if (cg_entitiesArray[i].pose.eType == 16 && cg_entitiesArray[i].nextState.Alive > 0)
						renderArrow(CircleX - dif.x, CircleY - dif.y, icoSize, (cg_entitiesArray[cgGame->clientNum].pose.viewAngles.y - cg_entitiesArray[i].pose.viewAngles.y), Red);
			}
	}
	void ScoreBoard_Draw(std::vector<clientInfo_t> v, int team, float x, float y) {

		if (options.Scoreboard.state) {
			const char* faction = BG_GetFactionForTeam(team, cgServer->MapName);

			DrawShader(x, y, 500, 500, black);
			for (int i = 0; i < 18; i++) {
				DrawText(va("Score: %i", v[i].score), x, y / 2, "fonts/720/normalfont", 1, white);
				DrawText(faction, x, y, "fonts/720/normalfont", 1, white);

			}
		}
	}

	void SetupVariables()
	{
		int numFonts = 5;
		int NumBones = sizeof(Bones);
		int NumShader = sizeof(ShaderList);
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
		SetupInt(&options.Fov, 65, 65, 150, 0);
		SetupInt(&options.SnapPos, 720, 215, 720, 0);
		SetupInt(&options.ShaderBlue, 255, 215, 255, 0);
		SetupInt(&options.ShaderGreen, 0, 215, 255, 0);
		SetupInt(&options.ShaderRed, 255, 215, 255, 0);
		SetupInt(&options.menuBorder, 4, 4, 20, 1);
		SetupInt(&options.menuFontIndex, 4, 4, numFonts, 0);
		SetupInt(&options.MenuAimTargetIndex, 0, 4, NumBones, 0);
		SetupInt(&options.ShaderIndex, 0, 4, NumShader, 0);
		SetupFloat(&options.menuFontSize, 0.58, 0.58, 5.0f, 0.1f, 0.001f);
		SetupSubMenu(&options.EspMenu, EspMenu, 8, 8);
		SetupSubMenu(&options.HostOnly, HostOnly, 8, 8);
		SetupSubMenu(&options.MiscView, MiscVisuals, 8, 8);
		SetupSubMenu(&options.SubPlayers, Playersub, 8, 8);

		SetupBool(&options.testing, false);
		SetupBool(&options.BoolRank, false);
		SetupBool(&options.IpSpoof, false);
		SetupBool(&options.AntiFreeze, false);
		SetupBool(&options.Gradient, false);
		SetupBool(&options.Tracer, false);
		SetupBool(&options.HostTab, false);
		SetupBool(&options.EspFilled, false);
		SetupBool(&options.XboGodmode, false);
		SetupBool(&options.Healthbar, false);

		SetupBool(&options.NoRecoil, false);
		SetupBool(&options.NoSway, false);
		SetupBool(&options.NoFlinch, false);
		SetupBool(&options.ChangeView, false);
		SetupBool(&options.AimbotToggle, false);
		SetupBool(&options.AutoWall, false);
		SetupBool(&options.SilentAim, false);
		SetupBool(&options.NoSpread, false);
		SetupBool(&options.AimRequired, false);

		SetupBool(&options.EspBoxToggle, false);
		SetupBool(&options.EspDrawBones, false);
		SetupBool(&options.EspDrawLine, false);
		SetupBool(&options.Radar, false);
		SetupBool(&options.CircleRadar, false);
		SetupBool(&options.ChangeView, false);
		SetupBool(&options.EspNames, false);
		SetupBool(&options.EspFrogChan, false);
		SetupBool(&options.EndGame, false);
		SetupBool(&options.Scoreboard, false);
		SetupBool(&options.DrawItem, false);
		SetupBool(&options.Laser, false);
		SetupBool(&options.AntiBetty, false);
		SetupBool(&options.Wallhack, false);
		SetupBool(&options.RGB, false);
		SetupBool(&options.AutoShoot, false);

	}

	void DrawMenuTabs()
	{
		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;
		int textWidth = R_TextWidth(0, "Main", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6 + 20;
		int textShaderW = R_TextWidth(0, "Main", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6 + 20;
		DrawText("Shake", options.menuX.current + 155, options.menuY.current - 20, FontForIndex(options.menuFontIndex.current), .8, white, align_center);

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


		DrawText("Settings", options.menuX.current + options.menuBorder.current + 10 + textWidth, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.6, white, align_left);
		if (options.menuPageIndex == SETTINGS)
			DrawShader(options.menuX.current + options.menuBorder.current + 10 + textShaderW, options.menuY.current + options.menuBorder.current + textHeight, 5 + R_TextWidth(0, "Settings", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.6, 3, blue);

	}

	void DrawMenuShader()
	{
		
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current - 55, 310, 95 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current), blue, options.Gradient.state ? "gradient_fadein" : "white");
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current - 12, 310, 48, black);
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current - 12 + 78 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current), 310, 5, blue, options.Gradient.state ? "gradient_fadein" : "white");

		//ScrollBar
		if (options.menuScroll <= 7)
			DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current + 38 + (options.menuScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current), 310, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current + 1, black);
		else
			DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current + 38 + (options.menuScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current) - 2.2, 310, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current + 1, black);

		//Footer
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current - 12 + 50 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current), 310, 30, black);
		DrawText(va("%i/%i", options.menuScroll + 1, options.menuMaxScroll), 5 + options.menuX.current + 5, 1 + options.menuY.current + 60 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);

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
	void DrawFloatSlider(const char* text, FloatMenuOption* value, const char* fmt)
	{
		options.menuMaxScroll++;

		int textWidth = R_TextWidthIW(text, 0x7FFFFFFF, R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;
		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;

		DrawText(text, 5 + options.menuX.current + 5, options.menuY.current + 38 + textHeight + (options.menuOptionIndex * textHeight), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);

		DrawShader(options.menuX.current + options.menuWidth - options.menuBorder.current - 75 - 5 + 2 + 25, options.menuY.current + 70 + (options.menuOptionIndex * textHeight) + ((textHeight - 75) / 2) + 2, 75 - 4, 5 - 4 + 8, black);
		DrawShader(options.menuX.current + options.menuWidth - options.menuBorder.current - 75 - 5 + 1 + 25, options.menuY.current + 70 + (options.menuOptionIndex * textHeight) + ((textHeight - 75) / 2) + 1, ((75 - 2) / (float)value->max) * value->current, 5 - 2 + 8, blue);
		BoundingBox(options.menuX.current + options.menuWidth - options.menuBorder.current - 75 - 5 + 2 + 25, options.menuY.current + 70 + (options.menuOptionIndex * textHeight) + ((textHeight - 75) / 2) + 2, 75 - 4, 5 - 4 + 8, white, 1);

		DrawText(va(fmt, value->current), 5 + options.menuX.current + 222, options.menuY.current + 38 + textHeight + (options.menuOptionIndex * textHeight), FontForIndex(options.menuFontIndex.current), 0.5, white, align_right);

		value->scrollIndex = options.menuOptionIndex;
		AddFloat_List(*(int*)value);
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

	void DrawSubMenu(const char* text, SubMenuMenuOption* option, int newMenu, bool enabled) {

		options.menuMaxScroll++;

		int textWidth = R_TextWidth(0, text, 0x7FFFFFFF, R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;
		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;

		DrawText(text, options.menuX.current + options.menuBorder.current + 5, options.menuY.current + textHeight + options.menuTabHeight + (options.menuOptionIndex * textHeight) + (options.menuBorder.current * 2), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, option->enabled ? white : black);
		DrawText("->>", options.menuX.current + options.menuWidth - options.menuBorder.current - R_TextWidth(0, "->>", 0x7FFFFFFF, R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current - 6, options.menuY.current + textHeight + options.menuTabHeight + (options.menuOptionIndex * textHeight) + (options.menuBorder.current * 2), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, option->enabled ? white : black);

		SetupSubMenu(option, newMenu, options.menuPageIndex, options.menuOptionIndex, enabled);
		option->scrollIndex = options.menuOptionIndex;
		AddSubMenuMenuOptionToList(option);
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

	const char* AimTag(int index)
	{
		return Bones[index];
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

		R_AddCmdDrawText_Bo3_Version(text, strlen(text), R_RegisterFont(font), x, y, fontSize, fontSize, color, 0);
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
	void BoundingBoxFilled(float x, float y, float width, float height, float* color, float thickness)
	{
		DrawShader(x - thickness, y - thickness, width + (thickness * 2), thickness, color); // Top
		DrawShader(x - thickness, y + height, width + (thickness * 2), thickness, color); // Bottom
		DrawShader(x - thickness, y - thickness, thickness, height + thickness, color); // Left
		DrawShader(x + width, y - thickness, thickness, height + (thickness * 2), color); // Right
		DrawShader(x - thickness, y - thickness, width, height + (thickness * 2), white2); // Filled
	}
	void DrawTextInBox(const char* text, int x, int y, int w, int h) {
		DrawShader(x, y, w, h, black);
		BoundingBox(x, y, w, h, blue, 1);
		DrawText(text, x + 5, y + h - 5, "fonts/normalfont", 0.65, white);
	}

	void HealthBar(float x, float y, float w) {
		std::uint8_t health = Cinfo[cgGame->MyClientNum].Health;
		std::uint8_t maxHealth = 100;
		float* healthColor = (health < 30) ? Red : (health < 70) ? Yellow : Green;

		//R_AddCmdDrawText_Bo3_Version(va("Health: %i/%i", Cinfo->Health, Cinfo->Health), strlen(va("Health: %i/%i", Cinfo->Health, Cinfo->Health)), R_RegisterFont("fonts/normalfont"), x, y - 40, 0.6, 0.6, black, 0);
		DrawShader(x - w, y - health * 1.75 / 2, w, health * 1.75, healthColor);
	}

	void SetupVariables()
	{
		int numFonts = 5;
		int NumBones = sizeof(Bones);

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
		SetupInt(&options.ShaderBlue, 255, 215, 255, 0);
		SetupInt(&options.ShaderGreen, 0, 215, 255, 0);
		SetupInt(&options.ShaderRed, 255, 215, 255, 0);
		SetupInt(&options.menuFontIndex, 4, 4, numFonts, 0);
		SetupInt(&options.MenuAimTargetIndex, 0, 4, NumBones, 0);
		SetupInt(&options.Fov, 65, 65, 150, 0);

		SetupFloat(&options.menuFontSize, 0.58, 0.58, 5.0f, 0.1f, 0.001f);

		SetupBool(&options.EspBones, false);
		SetupBool(&options.Healthbar, false);
		SetupBool(&options.EndGame, false);
		SetupBool(&options.EspHeart, false);
		SetupBool(&options.EspBox, false);
		SetupBool(&options.EspHealth, false);
		SetupBool(&options.EspNames, false);
		SetupBool(&options.EspFilled, false);
		SetupBool(&options.EspSnap, false);
		SetupBool(&options.NoRecoil, false);
		SetupBool(&options.NoSway, false);
		SetupBool(&options.OverHeadNames, false);
		SetupBool(&options.Tracers, false);
		SetupBool(&options.Fire, false);
		SetupBool(&options.AutoShoot, false);
		SetupBool(&options.testing, false);
		SetupBool(&options.Aimbot, false);
	}

	void DrawMenuTabs()
	{
		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current;
		int textWidth = Textwidth("Main", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current)), 0) * 0.6 + 20;
		int textShaderW = Textwidth("Main", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current)), 0) * 0.6 + 20;
		DrawText("Shake", options.menuX.current + 155, options.menuY.current - 20, FontForIndex(options.menuFontIndex.current), .8, white, align_center);

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
		DrawText(va("%i/%i", options.menuScroll + 1, options.menuMaxScroll), 5 + options.menuX.current + 5, 1 + options.menuY.current + 60 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);

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
	void DrawToggleWithDescription(const char* text, BoolMenuOption* value, const char* Desc)
	{
		options.menuMaxScroll++;

		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current;

		DrawText(text, 5 + options.menuX.current + 5, options.menuY.current + 38 + textHeight + (options.menuOptionIndex * textHeight), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);
		DrawText(Desc, 5 + options.menuX.current + 5, options.menuY.current - 12 + 50 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);

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
	void DrawSubMenu(const char* text, SubMenuMenuOption* option, int newMenu, bool enabled) {

		options.menuMaxScroll++;

		int textWidth = Textwidth(text, 0x7FFFFFFF, R_RegisterFont(FontForIndex(options.menuFontIndex.current)),0) * options.menuFontSize.current;
		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current))) * options.menuFontSize.current;

		DrawText(text, options.menuX.current + options.menuBorder.current + 5, options.menuY.current + textHeight + options.menuTabHeight + (options.menuOptionIndex * textHeight) + (options.menuBorder.current * 2), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, option->enabled ? white : black);
		DrawText("->>", options.menuX.current + options.menuWidth - options.menuBorder.current - Textwidth("->>", 0x7FFFFFFF, R_RegisterFont(FontForIndex(options.menuFontIndex.current)),0) * options.menuFontSize.current - 6, options.menuY.current + textHeight + options.menuTabHeight + (options.menuOptionIndex * textHeight) + (options.menuBorder.current * 2), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, option->enabled ? white : black);

		SetupSubMenu(option, newMenu, options.menuPageIndex, options.menuOptionIndex, enabled);
		option->scrollIndex = options.menuOptionIndex;
		AddSubMenuMenuOptionToList(option);
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

namespace Ghost {
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
			return "fonts/normalFont";
		if (index == 4)
			return "fonts/smallFont";
		if (index == 5)
			return "fonts/boldFont";
		else
			return "fonts/smallFont";
	}

	int R_TextHeight(Font* font)
	{
		return font->pixelHeight;
	}

	void DrawText(const char* text, float x, float y, const char* font, float fontSize, float* color, alignment align = align_left)
	{
		int fontA = R_TextWidthIW(text, strlen(text), R_RegisterFont(font, 0)) * fontSize;

		if (align == align_left)
			x = x;
		if (align == align_right)
			x = x - fontA;
		if (align == align_center)
			x = x - (fontA / 2);

		R_AddCmdDrawText(text, strlen(text), R_RegisterFont(font, 0), x, y, fontSize, fontSize, 0, color, 3);
	}

	void DrawShader(float x, float y, float width, float height, const float* color, const char* shader = "white")
	{
		CG_DrawRotatedPicPhysical(Ghost::ScrPlace, x, y, width, height, 0.0f, color, Material_RegisterHandle(shader, 7));
	}

	void BoundingBox(float x, float y, float width, float height, float* color, float thickness)
	{
		DrawShader(x - thickness, y - thickness, width + (thickness * 2), thickness, color); // Top
		DrawShader(x - thickness, y + height, width + (thickness * 2), thickness, color); // Bottom
		DrawShader(x - thickness, y - thickness, thickness, height + thickness, color); // Left
		DrawShader(x + width, y - thickness, thickness, height + (thickness * 2), color); // Right
	}
	void DrawTextInBox(const char* text, int x, int y, int w, int h) {
		DrawShader(x, y, w, h, black, "white");
		BoundingBox(x, y, w, h, blue, 1);
		DrawText(text, x + 5, y + h - 5, "fonts/smallfont", 0.65, white);
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
		SetupFloat(&options.menuFontSize, 0.48, 0.48, 4.0f, 0.1f, 0.001f);

		SetupBool(&options.testing, false);
		SetupBool(&options.BoolRank, false);
		SetupBool(&options.IpSpoof, false);
		SetupBool(&options.Tracer, false);

		SetupBool(&options.NoRecoil, false);
		SetupBool(&options.AimbotToggle, false);
		SetupBool(&options.NoSpread, false);
		SetupBool(&options.AimRequired, false);

		SetupBool(&options.EspBoxToggle, false);
		SetupBool(&options.EspDrawBones, false);
		SetupBool(&options.EspDrawLine, false);
		SetupBool(&options.EspFrogChan, false);
		SetupBool(&options.Scoreboard, false);
		SetupBool(&options.DrawItem, false);
		SetupBool(&options.Wallhack, false);
		SetupBool(&options.AutoShoot, false);

	}
	void DrawMenuTabs()
	{
		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;
		int textWidth = R_TextWidthIW("Main", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.5 + 20;
		int textShaderW = R_TextWidthIW("Main", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.5 + 20;
		DrawText("Shake Ghost", options.menuX.current + 155, options.menuY.current - 20, FontForIndex(options.menuFontIndex.current), .7, white, align_center);


		DrawText("Main", options.menuX.current + options.menuBorder.current + 10, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.5, white, align_left);
		if (options.menuPageIndex == MAIN)
			DrawShader(options.menuX.current + options.menuBorder.current + 10, options.menuY.current + options.menuBorder.current + textHeight, 5 + R_TextWidthIW("Main.", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.5, 3, blue);

		DrawText("Aimbot", options.menuX.current + options.menuBorder.current + 10 + textWidth + 6, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.5, white, align_left);
		if (options.menuPageIndex == AIMBOT)
			DrawShader(options.menuX.current + options.menuBorder.current + 10 + textShaderW + 6, options.menuY.current + options.menuBorder.current + textHeight, 5 + R_TextWidthIW("Aimbot.", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.5, 3, blue);
		textWidth += R_TextWidthIW("Aimbot", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.5 + 34;
		textShaderW += R_TextWidthIW("Aimbot", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.5 + 34;

		DrawText("Visuals", options.menuX.current + options.menuBorder.current + 10 + textWidth, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.5, white, align_left);
		if (options.menuPageIndex == VISUALS)
			DrawShader(options.menuX.current + options.menuBorder.current + 10 + textShaderW, options.menuY.current + options.menuBorder.current + textHeight, 5 + R_TextWidthIW("Visuals.", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.5, 3, blue);
		textWidth += R_TextWidthIW("Visuals", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.5 + 34;
		textShaderW += R_TextWidthIW("Visuals", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.5 + 34;

		DrawText("Players", options.menuX.current + options.menuBorder.current + 10 + textWidth, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.5, white, align_left);
		if (options.menuPageIndex == PLAYERS)
			DrawShader(options.menuX.current + options.menuBorder.current + 10 + textShaderW, options.menuY.current + options.menuBorder.current + textHeight, 5 + R_TextWidthIW("Players.", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.5, 3, blue);
		textWidth += R_TextWidthIW("Players", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.5 + 34;
		textShaderW += R_TextWidthIW("Players", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.5 + 34;
		/*
		DrawText("Host Only", options.menuX.current + options.menuBorder.current + 10 + textWidth, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.5, white, align_left);
		if (options.menuPageIndex == HostOnly)
			DrawShader(options.menuX.current + options.menuBorder.current + 10 + textShaderW, options.menuY.current + options.menuBorder.current + textHeight, 5 + R_TextWidthIW(0, "Host Only", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.5, 3, blue);
		textWidth += R_TextWidthIW(0, "Host Only", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.5 + 34;
		textShaderW += R_TextWidthIW(0, "Host Only", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.5 + 34;
		*/

		DrawText("Settings", options.menuX.current + options.menuBorder.current + 10 + textWidth, options.menuY.current + options.menuBorder.current + textHeight, FontForIndex(options.menuFontIndex.current), 0.5, white, align_left);
		if (options.menuPageIndex == SETTINGS)
			DrawShader(options.menuX.current + options.menuBorder.current + 10 + textShaderW, options.menuY.current + options.menuBorder.current + textHeight, 5 + R_TextWidthIW("Settings.", MAXLONG, R_RegisterFont(FontForIndex(options.menuFontSize.current), 0)) * 0.5, 3, blue);

	}

	void DrawMenuShader()
	{
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current - 55, 310, 95 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current), blue);
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current - 12, 310, 48, black);
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current - 12 + 78 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current), 310, 5, blue);

		//ScrollBar
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current + 36 + (options.menuScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current), 310, R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current, black);

		//Footer
		DrawShader(options.menuX.current + options.menuBorder.current, options.menuY.current - 12 + 50 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current), 310, 30, black);
		DrawText(va("%i/%i", options.menuScroll + 1, options.menuMaxScroll), 5 + options.menuX.current + 5, 1 + options.menuY.current + 60 + (options.menuMaxScroll * R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);

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

		int textWidth = R_TextWidthIW(text, 0x7FFFFFFF, R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;
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
	void DrawFloatSlider(const char* text, FloatMenuOption* value, const char* fmt)
	{
		options.menuMaxScroll++;

		int textWidth = R_TextWidthIW(text, 0x7FFFFFFF, R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;
		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;

		DrawText(text, 5 + options.menuX.current + 5, options.menuY.current + 38 + textHeight + (options.menuOptionIndex * textHeight), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);

		DrawShader(options.menuX.current + options.menuWidth - options.menuBorder.current - 75 - 5 + 2 + 25, options.menuY.current + 70 + (options.menuOptionIndex * textHeight) + ((textHeight - 75) / 2) + 2, 75 - 4, 5 - 4 + 8, black);
		DrawShader(options.menuX.current + options.menuWidth - options.menuBorder.current - 75 - 5 + 1 + 25, options.menuY.current + 70 + (options.menuOptionIndex * textHeight) + ((textHeight - 75) / 2) + 1, ((75 - 2) / (float)value->max) * value->current, 5 - 2 + 8, blue);
		BoundingBox(options.menuX.current + options.menuWidth - options.menuBorder.current - 75 - 5 + 2 + 25, options.menuY.current + 70 + (options.menuOptionIndex * textHeight) + ((textHeight - 75) / 2) + 2, 75 - 4, 5 - 4 + 8, white, 1);

		DrawText(va(fmt, value->current), 5 + options.menuX.current + 222, options.menuY.current + 38 + textHeight + (options.menuOptionIndex * textHeight), FontForIndex(options.menuFontIndex.current), 0.5, white, align_right);

		value->scrollIndex = options.menuOptionIndex;
		AddFloat_List(*(int*)value);
		options.menuOptionIndex++;
	}

	void DrawStringSlider(const char* text, IntMenuOption* value, const char* string)
	{
		options.menuMaxScroll++;

		int textWidth = R_TextWidthIW(text, 0x7FFFFFFF, R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;
		int textHeight = R_TextHeight(R_RegisterFont(FontForIndex(options.menuFontIndex.current), 0)) * options.menuFontSize.current;

		DrawText(text, 5 + options.menuX.current + 5, options.menuY.current + 38 + textHeight + (options.menuOptionIndex * textHeight), FontForIndex(options.menuFontIndex.current), options.menuFontSize.current, white);
		DrawText(string, options.menuX.current + options.menuWidth - 8 + 25, options.menuY.current + 39 + textHeight + (options.menuOptionIndex * textHeight) - 2, FontForIndex(options.menuFontIndex.current), 0.5, white, align_right);

		value->scrollIndex = options.menuOptionIndex;
		AddIntMenuOptionToList(value);
		options.menuOptionIndex++;
	}

}
