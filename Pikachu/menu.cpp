#include "menu.h"
void menu::InitalizeConsole()
{
	InitializeFont();
}
void menu::PrintLogo()
{
	cout << logo;
}
void menu::SetCursor(int x, int y)
{
	short sx, sy;
	sx = short(x);
	sy = short(y);
	SetConsoleCursorPosition(ConsoleOut, COORD{ sx,sy });
}
void menu::CursorColor(int bground, int txt)
{
	SetConsoleTextAttribute(ConsoleOut, bground * 16 + txt);
}
void menu::InitializeFont()
{
	CONSOLE_FONT_INFOEX info;
	info.cbSize = sizeof(info);
	GetCurrentConsoleFontEx(ConsoleOut, FALSE, &info);
	info.dwFontSize.X = 12;
	info.dwFontSize.Y = 24;
	wcscpy_s(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(ConsoleOut, FALSE, &info);
}
