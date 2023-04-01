#include "game.h"
#include "menu.h"
#include "controller.h"

int main()
{
	Account list_acc[10];
	int acc_num = 0;
	reading_account(list_acc, acc_num);
	for (int i = 0; i < acc_num; i++)
	{
		cout << i << ": " << list_acc[i].name << " " << list_acc[i].pass << endl;
	}
	finish Leaderboard[20];
	int fin = 0;
	readingLeaderboard(Leaderboard, fin, 0x12345678);
	controlGame(list_acc, acc_num, Leaderboard, fin);
	return 0;
}