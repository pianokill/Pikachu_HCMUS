#pragma once
#include "game.h"
#include "iomanip"
#define BOARDSIZE 1000
#define NAME 50
#define PASS 50

struct Account
{
    int file_number;
    char name[NAME];
    char pass[PASS];
    filesave saves[3];
};
void printDate(Record date);
void creatingAcc(Account& temp);
void saving_map(Account& acc, const game& Game);
bool printing_account(Account acc[], int acc_number);
bool reading_account(Account acc[], int &acc_number);
int loading_account(Account acc[], int &acc_number, Account guest);