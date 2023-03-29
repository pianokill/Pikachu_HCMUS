#pragma once
#include "game.h"
#include "menu.h"
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void controlGame();
void playingGame(menu& a, int diff, int& pairs, int& fin_score);