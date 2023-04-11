#include "game.h"
#include "menu.h"
#include "controller.h"
//Mask of the leaderboard is 0x12345678(int)
int main()
{
	Account list_acc[20]; //Number of account to manage 
	int acc_num = 0;
	reading_account(list_acc, acc_num, 777);
	finish Leaderboard[20]; //Number of finished game to be in the leaderboard.bin => get top 5 of each size only
	int fin = 0;
	readingLeaderboard(Leaderboard, fin, 0x12345678);
	controlGame(list_acc, acc_num, Leaderboard, fin);
	return 0;
}
