#pragma once
#include "game.h"
#define NAME 50
#define PASS 50
struct Account {
	char name[NAME];
	char pass[PASS];
	game filesave[5];
};