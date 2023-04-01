#pragma once

#include "game.h"
#include "menu.h"
#include "account.h"
#include <mmsystem.h>
#include <ctime>
#pragma comment(lib, "winmm.lib")

void controlGame(Account list_acc[], int& acc_num, finish F[], int& fin);
void playingGame(Account acc[], int acc_pos, int acc_num, game& b, bool loaded, finish F[], int &fin);
void onRoundTheme(int diff);
void offRoundTheme(int diff);