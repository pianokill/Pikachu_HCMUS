#include "game.h"
#include "menu.h"
#include "controller.h"

int main()
{
	Account list_acc[5];
	int acc_num = 0;
	cout << acc_num << endl;
	reading_account(list_acc, acc_num);
	cout << acc_num << endl;
	for (int i = 0; i < acc_num; i++)
	{
		cout << i << ": " << list_acc[i].name << " " << list_acc[i].pass << endl;
	}
	controlGame(list_acc, acc_num);
	return 0;
}