#include "board.h"
void board::init(int difficulty)
{
	int m, n;
	m = size[difficulty - 1].first;
	n = size[difficulty - 1].second; // Get the size of the board (m*n) based on the difficulty
	char* used_characters; // The list of the character that will be available on the board
	char* characters_list; // Save the received letter from randomization
	isOktogo = new int* [m];
	letters = new char* [m];
	for (int i = 0; i < m; i++)
	{
		isOktogo[i] = new int[n];
		letters[i] = new char[n];
	}
	used_characters = new char [m * n];
	characters_list = new char[m * n / 2];
	for (int i = 0; i < m * n / 2; i++)
	{
		int id = rand() % 26;
		characters_list[i] = 'a' + id; // Randomize a letter and save to characters_list
		used_characters[i] = characters_list[i]; // Append the received result to the first half of the used_characters
	}
	random_shuffle(characters_list, characters_list + m * n / 2);
	for (int i = 0; i < m * n / 2; i++)
		used_characters[m * n / 2 + i] = characters_list[i]; // Random the characters_list and append the result to the second half of the list
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			isOktogo[i][j] = 1; // Set to true since the cell always have to be available intially
			letters[i][j] = used_characters[n * i + j]; // Put the randomized board onto the map
		}
	//for (int i = 0; i < m; i++)
	//{
	//	for (int j = 0; j < n; j++)
	//		cout << letters[i][j] << ' ';
	//	cout << '\n';
	//}
}
void board::destroy_board()
{
	cout << "burh";
}