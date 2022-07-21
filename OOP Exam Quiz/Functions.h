#pragma once

bool quizCursor(Quiz& q)
{

	vector<Question*> temp = q.questions();
	short& answerIndex = temp[q.questionIndex]->answerIndex;

	int button = _getch();
	if (button == 224)
	{
		button = _getch();

		switch (button)
		{
		case 72:
			setCursorPosition(0, 0);
			answerIndex--;
			if (answerIndex < 0) answerIndex = temp[q.questionIndex]->answers().size() - 1;
			break;


		case 80:
			setCursorPosition(0, 0);
			temp[q.questionIndex]->answerIndex++;
			if (answerIndex >= temp[q.questionIndex]->answers().size()) answerIndex = 0;
			break;

		case 75:
			system("cls");
			q.questionIndex--;
			if (q.questionIndex < 0) q.questionIndex = temp.size() - 1;
			break;

		case 77:
			system("cls");
			q.questionIndex++;
			if (q.questionIndex >= temp.size()) q.questionIndex = 0;
			break;
		}

		return false;
	}

	else if (button == 13)
	{
		system("cls");
		return true;
	}

	else
	{
		setCursorPosition(0, 0);
		return false;
	}

}


bool commandCursor(Commands& c)
{
	int button = _getch();

	if (button == 224)
	{
		button = _getch();

		switch (button)
		{
		case 72:
			c.commandIndex--;
			if (c.commandIndex < 0) c.commandIndex = c.commands.size() - 1;
			break;


		case 80:
			c.commandIndex++;
			if (c.commandIndex >= c.commands.size()) c.commandIndex = 0;
			break;

		}

		return false;
	}

	else if (button == 13)
	{
		system("cls");
		return true;
	}

	else
	{
		return false;
	}

}



Quiz* createQuiz(string creatorNick)
{
	string name = "";
	mySetColor(11, 0);


	cout << "Enter the name of the Quiz: ";
	getline(cin, name);
	system("cls");


	Commands questionCommands;
	questionCommands.commands.push_back("Add Question");
	questionCommands.commands.push_back("Accept All Questions");
	questionCommands.commands.push_back("Back");


	Commands answerCommands;
	answerCommands.commands.push_back("Add Answer");
	answerCommands.commands.push_back("Accept All Answers");
	answerCommands.commands.push_back("Back");

	Commands TrueOrFalse;
	TrueOrFalse.commands.push_back("True");
	TrueOrFalse.commands.push_back("False");

	Quiz* tempQuiz;
	try
	{
		tempQuiz = new Quiz(name, creatorNick);
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
		throw exception(ex);
	}

	bool choice = false;
	bool isCorrect = false;
	bool exit = false;

	Question* tempQuestion = nullptr;
	string question;
	string answer;


	while (!exit)
	{
		setCursorPosition(0, 0);

		cout << questionCommands;
		choice = commandCursor(questionCommands);

		if (choice)
		{
			switch (questionCommands.commandIndex)
			{
			case 0:

				cout << "Enter Question Text: ";
				getline(cin, question);

				try
				{
					tempQuestion = new Question(question);

				}
				catch (const std::exception& ex) 
				{
					cout << ex.what() << endl;
					system("pause");
					system("cls");
					continue;
				}
				system("cls");

				while (!exit)
				{
					setCursorPosition(0, 0);
					cout << answerCommands;
					choice = commandCursor(answerCommands);

					if (choice)
					{
						switch (answerCommands.commandIndex)
						{
						case 0:
							cout << "Enter Answer Text: ";
							getline(cin, answer);

							while (true)
							{
								setCursorPosition(0, 0);
								cout << "Is Answer True or False?" << endl;
								cout << TrueOrFalse;
								choice = commandCursor(TrueOrFalse);
								if (choice) break;
							}

							switch (TrueOrFalse.commandIndex)
							{
							case 0:

								tempQuestion->addAnswer(new Answer(answer, 1));
								break;

							case 1:
								tempQuestion->addAnswer(new Answer(answer, 0));
								break;
							}

							break;

						case 1:
							exit = true;
							break;
						case 2:
							delete tempQuestion;
							tempQuestion = nullptr;
							exit = true;

						}
					}

				}


				if (tempQuestion != nullptr)
					tempQuiz->addQuestion(tempQuestion);

				exit = false;
				break;

			case 1:

				exit = true;
				break;

			case 2:
				return nullptr;
				break;
			}
		}
	}

	if (tempQuiz->questions().size() < 5)
		throw exception("At least 5 answers needed");

	return tempQuiz;
}



void quizShuffle(Quiz* quiz)
{
	for (auto& q : quiz->questions())
		random_shuffle(q->answers().begin(), q->answers().end());

	random_shuffle(quiz->questions().begin(), quiz->questions().end());
}

double findScore(Quiz* quiz)
{
	size_t questionCount = quiz->questions().size();
	size_t correctsCount = quiz->corrects().size();
	size_t falsesCount = quiz->falses().size();
	double pointPerQuestion = 100.0f / questionCount;
	double strikePerQuestion = pointPerQuestion / 3.0f;

	double finalPoint = (correctsCount * pointPerQuestion) - (falsesCount * strikePerQuestion);

	finalPoint *= 100;
	finalPoint = round(finalPoint);
	finalPoint /= 100.0f;

	return finalPoint;
}

bool checkNickname(vector<Player*> players, const string& nick)
{
	for (auto& player : players)
	{
		if (player->nickname() == nick)
			return true;
	}

	return false;
}

bool checkNickname(vector<Admin*> admins, const string& nick)
{
	for (auto& admin : admins)
	{
		if (admin->nickname() == nick)
			return true;
	}

	return false;
}


Player* findPlayer(vector<Player*> players, const string& nick, const string& pass)
{
	for (auto& player : players)
	{
		if (player->nickname() == nick && player->password() == pass)
			return player;
	}

	return nullptr;
}

Admin* findAdmin(vector<Admin*> admins, const string& nick, const string& pass)
{
	for (auto& admin : admins)
	{
		if (admin->nickname() == nick && admin->password() == pass)
			return admin;
	}

	return nullptr;
}