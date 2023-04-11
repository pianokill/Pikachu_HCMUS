#pragma once
#include "game.h"
#include "menu.h"
#include "account.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void controlGame(Account list_acc[], int& acc_num, finish F[], int& fin);
void playingGame(Account acc[], int acc_pos, int acc_num, game& b, bool loaded, int file_pos, finish F[], int& fin, menu a);
void onRoundTheme(int diff); //Turn on the music theme for each difficulty board game
void offRoundTheme(int diff); //Turn off the music theme for each difficulty board game
