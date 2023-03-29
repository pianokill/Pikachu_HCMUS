#include "game.h"

void ClearScreen() //Function to clear screen as suggested by chatGPT
{
	system("cls");
}
void game::select1(int x, int y)
{
	selection.first = { x,y };
	select_state = 1;
}
void game::deselect()
{
	selection.first = { 0,0 };
	select_state = 0;
}
void game::select2(int x, int y)
{
	selection.second = { x,y };
	select_state = 0;
}
void game::resetState()
{
	selection = { {0,0},{0,0} };
}
