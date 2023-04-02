#pragma once
#include "game.h"
#include "iomanip"
#define BOARDSIZE 1000
#define NAME 50
#define PASS 50

struct Account
{
    int file_number; //Number of saved file
    char name[NAME]; 
    char pass[PASS];
    filesave saves[3]; //Each account has maximum 3 file saves
};
void printDate(Record date); //Help print date and time
void creatingAcc(Account& temp); //Help creating account with only pass and name 
void saving_map(Account& acc, const game& Game); //Saving the playing game to using account
bool printing_account(Account acc[], int acc_number); //Printing the list of accounts to account_log.bin
bool reading_account(Account acc[], int &acc_number); //Loading the list of accounts from account_log.bin
int loading_account(Account acc[], int &acc_number, Account guest); //Loading the account in the list, if not in the list => a new account added to list