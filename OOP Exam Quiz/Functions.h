#pragma once

bool quizCursor(Quiz& q)
{

	//  Up key - 224 72
	//
	//	Down key - 224 80
	//
	//	Left key - 224 75
	//
	//	Right key - 224 77
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
			setCursorPosition(0, 0);
			c.commandIndex--;
			if (c.commandIndex < 0) c.commandIndex = c.commands.size() - 1;
			break;


		case 80:
			setCursorPosition(0, 0);
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
		setCursorPosition(0, 0);
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

	if (name == "")
		throw exception("Quiz name Cannot be empty");


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

	Quiz* tempQuiz = new Quiz(name, creatorNick);

	bool choice = false;
	bool isCorrect = false;
	bool exit = false;

	Question* tempQuestion = nullptr;
	string question;
	string answer;


	while (!exit)
	{
		cout << questionCommands;
		choice = commandCursor(questionCommands);

		if (choice)
		{
			switch (questionCommands.commandIndex)
			{
			case 0:

				cout << "Enter Question Text: ";
				getline(cin, question);

				tempQuestion = new Question(question);

				while (!exit)
				{
					system("cls");
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
								system("cls");
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