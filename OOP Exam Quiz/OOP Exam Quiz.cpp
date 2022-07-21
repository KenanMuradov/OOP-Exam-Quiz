#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <fstream>
#include <algorithm>

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

	string adminSecretPass = "Dattebayo";

#pragma region LOAD_FILES

	enum FileNames { Quizes, Admins, Players };
	vector<string> fileNames = { "Quizes.txt","Admins.txt","Players.txt" };

	vector<Quiz*> quizes = loadQuizes(fileNames[FileNames::Quizes]);
	vector<Admin*> admins = loadAdmins(fileNames[FileNames::Admins]);
	vector<Player*> players = loadPlayers(fileNames[FileNames::Players]);


#pragma endregion

#pragma region START_SCREEN

	Commands startScreen;
	startScreen.commands.push_back("Get Started");
	startScreen.commands.push_back("See The rules");
	startScreen.commands.push_back("See CopyRight@");
	startScreen.commands.push_back("Exit");

	bool exit = false;
	bool choice;

	//loadScreen();
	system("cls");

	while (!exit)
	{
	start:
		setCursorPosition(0, 0);
		cout << startScreen;
		choice = commandCursor(startScreen);

		if (choice)
		{
			switch (startScreen.commandIndex)
			{
			case 0:

				exit = true;
				break;

			case 1:
				system("cls");
				rulesMessage();
				system("pause");
				system("cls");
				break;

			case 2:
				system("cls");
				copyRightMessage();
				system("pause");
				system("cls");
				break;

			case 3:
				system("cls");
				cout << "======GOOD BYE======\n";
				Sleep(2500);
				return 0;
				break;

			}
		}
	}


	exit = false;

#pragma endregion

#pragma region LOG_IN

	Commands start;
	start.commands.push_back("Sign up");
	start.commands.push_back("Log in");
	start.commands.push_back("Continue as a Guest");
	start.commands.push_back("Back");

	Commands signUp;
	signUp.commands.push_back("Sign up as Player");
	signUp.commands.push_back("Sign up as Admin");
	signUp.commands.push_back("Back");

	Commands logIn;
	logIn.commands.push_back("Log in as Player");
	logIn.commands.push_back("Log in as Admin");
	logIn.commands.push_back("Back");

	string nickname;
	string password;
	string superSecretKeyword;

	User* currentUser;

	bool isAdmin = true;
	bool back = false;

	while (!exit)
	{
		setCursorPosition(0, 0);
		cout << start;
		choice = commandCursor(start);
		if (choice)
		{
			switch (start.commandIndex)
			{
			case 0:
				system("cls");
				while (!back)
				{
					setCursorPosition(0, 0);
					cout << signUp;
					choice = commandCursor(signUp);

					if (choice)
					{
						switch (signUp.commandIndex)
						{
						case 0:
							system("cls");
							cout << "Enter your nick: ";
							getline(cin, nickname);
							cout << "\nEnter your password: ";
							getline(cin, password);

							if (checkNickname(players, nickname))
							{
								cout << "\nThis nickname is already used\n";
								system("pause");
								system("cls");
								continue;
							}

							try
							{
								currentUser = new Player(nickname, password);
								players.push_back(dynamic_cast<Player*>(currentUser));
							}
							catch (const std::exception& ex)
							{
								cout << ex.what() << endl;
								system("pause");
								system("cls");
								continue;
							}

							exit = true;
							back = true;
							break;

						case 1:


							cout << "If you want to be an admin you need write Secret Keyword: ";
							getline(cin, superSecretKeyword);

							if (superSecretKeyword != adminSecretPass)
							{
								cout << "You are not ready to be an admin\n";
								Sleep(2000);
								cout << "SHINRA TENSEI!!!!\n";
								system("pause");
								system("cls");
								return 0;
							}
							Sleep(1000);
							system("cls");
							cout << "Enter your nick: ";
							getline(cin, nickname);
							cout << "\nEnter your password: ";
							getline(cin, password);

							if (checkNickname(admins, nickname))
							{
								cout << "\nThis nickname is already used\n";
								system("pause");
								system("cls");
								continue;
							}
							try
							{
								currentUser = new Admin(nickname, password);
								isAdmin = true;
								admins.push_back(dynamic_cast<Admin*> (currentUser));
							}
							catch (const std::exception& ex)
							{
								cout << ex.what() << endl;
								system("pause");
								system("cls");
								continue;
							}

							exit = true;
							back = true;
							break;

						case 2:
							back = true;
						}
					}
				}

				back = false;
				break;

			case 1:
				system("cls");
				while (!back)
				{
					setCursorPosition(0, 0);
					cout << logIn;
					choice = commandCursor(logIn);
					if (choice)
					{
						switch (logIn.commandIndex)
						{
						case 0:

							system("cls");
							cout << "Enter your nick: ";
							getline(cin, nickname);
							cout << "\nEnter your password: ";
							getline(cin, password);

							currentUser = findPlayer(players, nickname, password);
							if (currentUser == nullptr)
							{
								cout << "Such player Does't exists. Please Sign up\n";
								system("pause");
								system("cls");
								continue;
							}
							break;

						case 1:
							system("cls");
							cout << "Enter your nick: ";
							getline(cin, nickname);
							cout << "\nEnter your password: ";
							getline(cin, password);

							currentUser = findAdmin(admins, nickname, password);
							if (currentUser == nullptr)
							{
								cout << "Such Admin Does't exists. Please Sign up\n";
								system("pause");
								system("cls");
								continue;
							}

							back = true;
							exit = true;
							break;

						case 2:
							back = true;

						}

					}
				}

				back = false;
				break;

			case 2:
				exit = true;
				break;

			case 3:
				goto start;
			}
		}


	}
#pragma endregion
}