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
void menu::drawInfo()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;
	// Build a short animation to draw the outline of the info board
	cursorPos = { 106,6 };
	SetConsoleCursorPosition(console, cursorPos);
	for (int i = 0; i < 30; i++)
	{
		cout << '-';
		Sleep(6.9);
	}
	for (int i = 0; i < 14; i++)
	{
		cursorPos = { 136,short(7 + i) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << '|';
		Sleep(6.9);
	}
	for (int i = 0; i < 30; i++)
	{
		cursorPos = {short(135 - i), 21};
		SetConsoleCursorPosition(console, cursorPos);
		cout << '-';
		Sleep(6.9);
	}
	for (int i = 0; i < 14; i++)
	{
		cursorPos = { 105,short(20 - i) };
		SetConsoleCursorPosition(console, cursorPos);
		cout << '|';
		Sleep(6.9);
	}
}
