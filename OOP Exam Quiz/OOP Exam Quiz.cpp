#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <fstream>
#include <direct.h>
#include <algorithm>
#include <math.h>

using namespace std;

#include "HelpFunctions.h"
#include "Answer.h"
#include "Question.h"
#include "Quiz.h"
#include "Commands.h"
#include "User.h"
#include "Player.h"
#include "Admin.h"
#include "Functions.h"
#include "FileHandling.h"


int main()
{

	



#pragma region LOAD_FILES

	enum FileNames { Quizes, Admins, Players };
	vector<string> fileNames = { "Quizes.txt","Admins.txt","Players.txt" };

	vector<Quiz*> quizes = loadQuizes(fileNames[FileNames::Quizes]);
	vector<Admin*> admins = loadAdmins(fileNames[FileNames::Admins]);
	vector<Player*> players = loadPlayers(fileNames[FileNames::Players]);

	cout << quizes.size() << endl;
	cout << admins.size() << endl;
	cout << players.size() << endl;

#pragma endregion

#pragma region START_SCREEN

	Commands startScreen;

#pragma endregion


	

}