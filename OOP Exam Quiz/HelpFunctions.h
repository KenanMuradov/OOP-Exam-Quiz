#pragma once

namespace HeaderFiles
{
	namespace FUNCTIONS
	{
		void setCursorPosition(int x, int y)
		{
			static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			std::cout.flush();
			COORD coord = { (SHORT)x, (SHORT)y };
			SetConsoleCursorPosition(hOut, coord);
		}

		void mySetColor(int fg, int bg)
		{
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, fg | (bg << 4));
		}

		void copyRightMessage()
		{
			cout << "@This Quiz Project is licensed by KepaMax organization in 2022.\nAll rights reserved\n";
		}

		void rulesMessage()
		{
			cout << "You can get a maximum of 100 points and you get 100 divided by the number of questions for each correct answer\nand lose a third of that number for each incorrect one\n";
		}

		void loadScreen()
		{
			mySetColor(11, 0);
			cout << "\n\n\t--------------------------\n"
				<< "\t|******** WELCOME *******|\n"
				<< "\t|********    TO   *******|\n"
				<< "\t|******* KEPA QUIZ ******|\n"
				<< "\t--------------------------\n";
			Sleep(3000);
			size_t timer = 10;
			size_t sleepTime = 2000;
			for (size_t i = 0; i < timer; i++)
			{
				setCursorPosition(9, 10);
				for (size_t j = 0; j < i + 1; j++)
				{
					cout << (char)219 << (char)219;
				}
				cout << ' ' << (i + 1) * 10 << '%';
				Sleep(sleepTime);
				sleepTime -= 175;
			}
		}
	}

	
}
