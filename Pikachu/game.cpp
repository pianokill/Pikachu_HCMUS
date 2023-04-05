#include "game.h"

void ClearScreen() //Function to clear screen as suggested by chatGPT
{
	system("cls");
}
void game::select1(int x, int y)
{
	selection.first = { x,y };
	select_state = 1;
}
void game::deselect()
{
	selection.first = { 0,0 };
	select_state = 0;
}
void game::select2(int x, int y)
{
	selection.second = { x,y };
	select_state = 0;
}
void game::resetState()
{
	selection = { {0,0},{0,0} };
}
Record getTime()
{
	Record curr_time;
	struct tm ltm; //Using ctime library 
	time_t now = time(0);
	localtime_s(&ltm, &now);
	curr_time.day = ltm.tm_mday;
	curr_time.month = 1 + ltm.tm_mon;
	curr_time.year = 1900 + ltm.tm_year;
	curr_time.second = ltm.tm_sec;
	curr_time.minute = ltm.tm_min;
	curr_time.hour = ltm.tm_hour;
	return curr_time;
}
float final_score(int score, int time)
{
	float score2 = (float)score;
	float time2 = (float)time;
	float bonus_factor = 1; //Bonus_factor helps determine the importance of total playing time
	float bonus_score = (1 - time2 / 300) * 100 * bonus_factor; 
	float score_weight_factor = 0.7; //Playing score percentages in the final score
	float time_weight_factor = 0.3; //Bonus time percentages in the final score
	return (score2 * score_weight_factor) + (bonus_score * time_weight_factor);
}
int total_playingtime(Record a, Record b) {
	// Calculate the total number of seconds for each time
	int secondsA = a.second + a.minute * 60 + a.hour * 3600 + a.day * 86400 + (a.month - 1) * 2678400 + (a.year - 1970) * 31536000; //As suggested by Chat-GPT
	int secondsB = b.second + b.minute * 60 + b.hour * 3600 + b.day * 86400 + (b.month - 1) * 2678400 + (b.year - 1970) * 31536000; 
	// Calculate the difference between the two times in seconds
	if (secondsA > secondsB)
	{
		return secondsA - secondsB;
	}
	else {
		return secondsB - secondsA;
	}
}
void xor_finish(finish& f, int mask) { //Xor the finish struct with the mask
	f.difficulty ^= mask;  //Int with int
 	f.time ^= mask; //Int with int
	f.date.day ^= mask;
	f.date.month ^= mask;
	f.date.year ^= mask;
	f.date.hour ^= mask;
	f.date.minute ^= mask;
	f.date.second ^= mask;
	int* p_score = reinterpret_cast<int*>(&f.score); //Float with int 
	*p_score ^= mask;
	for (size_t i = 0; i < NAME; i++) { //Char with int
		f.name[i] ^= static_cast<char>(mask);
	}
}
bool printingLeaderboard(finish F[], int n, int mask)
{
	ofstream fout;
	fout.open("leaderboard.bin", ios::binary | ios::trunc);
	if (fout.fail())
	{
		cout << "Can not read leaderboard.bin file!" << endl;
		return 0;
	}
	fout.write((char*)&n, sizeof(n)); //Print the number of finished games first
	for (int i = 0; i < n; i++)
	{
		xor_finish(F[i], mask); //Xor the finished game first
		fout.write((char*)&F[i], sizeof(finish)); //Print it into the leaderboard.bin with exact size
	}
	fout.close();
	return 1;
}
bool readingLeaderboard(finish F[], int &n, int mask)
{
	ifstream fin;
	fin.open("leaderboard.bin", ios::binary | ios::in);
	if (fin.fail())
	{
		cout << "Can not read leaderboard.bin file!" << endl;
		return 0;
	}
	fin.read((char*)&n, sizeof(n)); //Get the number of finished games
	for (int i = 0; i < n; i++)
	{
		fin.read((char*)&F[i], sizeof(finish)); //Read the finished game first
		xor_finish(F[i], mask); //Xor it with the mask int
	}
	fin.close();
	return 1;
}
void getTop5(finish F[], int n, int difficulty, finish top5[5], int &num)
{
	int filtered_size = 0;
	finish filtered[50];
	for (int i = 0; i < n; i++) {
		if (F[i].difficulty == difficulty) {
			filtered[filtered_size] = F[i]; //Get the difficulty size only in this finish array
			filtered_size++;
		}
	}
	for (int i = 0; i < filtered_size; i++) //Using bubble sort to sort the finish array descending
	{
		for (int j = i + 1; j < filtered_size; j++) 
		{
			if (filtered[j].score > filtered[i].score)
			{ 
				finish temp = filtered[i];
				filtered[i] = filtered[j];
				filtered[j] = temp;
			}
		}
	}
	if(filtered_size < 5)
	{
		num = filtered_size; //To make sure segmentation fault doesn't happen
	}
	else {
		num = 5;
	}
	for (int i = 0; i < num; i++) {
		top5[i] = filtered[i];
	}

}
