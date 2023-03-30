#pragma once
#include "game.h"
#include "menu.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void controlGame();
void playingGame(game &b);
void onRoundTheme(int diff);
void offRoundTheme(int diff);