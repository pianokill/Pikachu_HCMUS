#pragma once
#include "game.h"
#include "menu.h"
#include "account.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void controlGame(Account list_acc[], int &acc_num);
void playingGame(Account acc[], int acc_pos, int acc_num, game& b);
void onRoundTheme(int diff);
void offRoundTheme(int diff);