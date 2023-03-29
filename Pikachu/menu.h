#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

struct menu
{
	bool isRunning = 1; // Is the game running or not
	bool isSound = 1; // Do players want to turn sound on or not
    HANDLE ConsoleOut;
    int command;
    const string logo = R"(
          _________     ___   ___   ___          _____         ________    __     __     ___       ___
         /________/\   /__/  /__/  /__/\        /____/        /_______/\  /__/   /__/|  /__/      /__/|
        |  _____ \  | |  || |  || /  / |       /    \ \      |   _____|/ |  ||  |  | | |  ||     |  | |
        |  |_ __| | / |  || |  \_/  / /       /  /\  \ \     |  ||       |  ||  |  | | |  ||     |  | |
        |________/_/  |  || |      / /       /  / /\  \ \    |  ||       |  ||__|  | | |  ||     |  | |
        |  ||         |  || |  |\  \ \      /  /_/__\  \ \   |  ||       |  |___|  | | |  ||     |  | |
        |  ||         |  || |  ||\  \ \    /  /______\  \ \  |  ||_____  |  ||  |  | | |  ||     |  | |
        |  ||         |  || |  || \  \ \  /  / /      \  \ \ |  |_____|| |  ||  |  | | |   \____/   | |
        |__|/         |__|/ |__|/  \__|/ /__/ /        \__\/ |________|/ |__|/  |__|/   \__________/_/


 				          ___   ___       ___         _______
 		        		 /__/  /__/      /__/|	     /______/\
 				        |  || |  |\     |  | |	    |   ____|/ 
 		        		|  || |  | \    |  | |	    |  ||         _       _
 				        |  || |  |\ \   |  | |	    |  ||       _| |_   _| |_
 				        |  || |  ||\ \  |  | |	    |  ||      |_   _| |_   _|  
 				        |  || |  || \ \ |  | |      |  ||____    |_|     |_|
 				        |  || |  ||  \ \|  | |      |  |____||
  				        |__|/ |__|/   \____|/	    |_______|/
	)";
    void InitalizeConsole();
	void PrintLogo();
    void SetCursor(int, int);
    void CursorColor(int, int);
    void InitializeFont();
};