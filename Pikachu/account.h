#pragma once
#include "game.h"
#include "menu.h"
#include <iomanip>
#include <limits>

const int BOARDSIZE = 1000;
const int PASS = 50;

struct Account
{
    int file_number; //Number of saved file
    char name[NAME];
    char pass[PASS];
    filesave saves[3]; //Each account has maximum 3 file saves
};
void printDate(Record date); //Help print date and time
void creatingAcc(Account& temp); //Help creating account with only pass and name 
void saving_map(Account& acc, const game& Game, int file_pos); //Saving the playing game to using account
void xor_filesave(filesave& save, int mask);
void xor_account(Account& acc, int mask);
bool printing_account(Account acc[], int acc_number, int mask); //Printing the list of accounts to account_log.bin
bool reading_account(Account acc[], int& acc_number, int mask); //Loading the list of accounts from account_log.bin
int loading_account(Account acc[], int& acc_number, Account guest); //Loading the account in the list, if not in the list => a new account added to list
void Changeaccount_name(Account list_acc[], int acc_num, int pos);
void Changeaccount_password(Account list_acc[], int acc_num, int pos);
void Changeaccount_filesave(Account list_acc[], int acc_num, int pos, menu mn);
