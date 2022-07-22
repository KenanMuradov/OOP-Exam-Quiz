class Quiz
{
	vector<Question*> _allQuestions;
	vector<Question*> _corrects;
	vector<Question*> _falses;
	vector<Question*> _unanswered;
	string _name = "";
	string _creatorNick = "";

	bool checkQuestion(const vector<Question*>& questions, Question* q);

public:

	short questionIndex = 0;

	Quiz(string name, string creatorNick);



	string name() const;
	string creatorNick() const;
	const vector<Question*>& questions() const;
	vector<Question*>& questions();
	const vector<Question*>& corrects() const;
	vector<Question*>& corrects();
	const vector<Question*>& falses() const;
	vector<Question*>& falses();
	const vector<Question*>& unanswereds() const;
	vector<Question*>& unanswereds();

	void addQuestion(Question* q);
	void questionPlacement(Question* q);
	void showCorrects() const;
	void showFalses() const;
	void showUnanswereds() const;


	~Quiz();
};

#pragma region CONSTRUCTORS

Quiz::Quiz(string name, string creatorNick)
{
	if (name == "" || creatorNick == "")
		throw exception("Quiz name or Creator nick is incorrect");

	_name = name;
	_creatorNick = creatorNick;
}

#pragma endregion

#pragma region ACCESSORS

string Quiz::name() const
{
	return _name;
}

string Quiz::creatorNick() const
{
	return _creatorNick;
}

const vector<Question*>& Quiz::questions() const
{
	return _allQuestions;
}

vector<Question*>& Quiz::questions()
{
	return _allQuestions;
}

const vector<Question*>& Quiz::corrects() const
{
	return _corrects;
}

vector<Question*>& Quiz::corrects()
{
	return _corrects;
}

const vector<Question*>& Quiz::falses() const
{
	return _falses;
}

vector<Question*>& Quiz::falses()
{
	return _falses;
}

const vector<Question*>& Quiz::unanswereds() const
{
	return _unanswered;
}

vector<Question*>& Quiz::unanswereds()
{
	return _unanswered;
}

#pragma endregion


#pragma region METHODS

bool Quiz::checkQuestion(const vector<Question*>& questions, Question* q)
{
	for (auto& question : questions)
	{
		if (question == q)
			return true;
	}

	return false;
}

void Quiz::addQuestion(Question* q)
{
	if (q == nullptr)
		throw exception("Question is not identitfied");

	_allQuestions.push_back(new Question(*q));
}

void Quiz::questionPlacement(Question* q)
{
	if (q == nullptr)
		throw exception("Question is not identitfied");

	bool isCount = false;

	for (auto& question : _allQuestions)
	{
		if (question == q)
			isCount = true;
	}

	if (!isCount)
		throw exception("Question is not identitfied");


	if (q->currentAnswer() == nullptr)
		return;


	if (checkQuestion(_corrects, q))
	{
		for (size_t i = 0; i < _corrects.size(); i++)
		{
			if (_corrects[i] == q)
			{
				_corrects.erase(_corrects.begin() + i);
				break;
			}
		}
	}

	else if (checkQuestion(_falses, q))
	{
		for (size_t i = 0; i < _falses.size(); i++)
		{
			if (_falses[i] == q)
			{
				_falses.erase(_falses.begin() + i);
				break;
			}
		}
	}

	if (q->currentAnswer()->isCorrect())
	{
		_corrects.push_back(q);
		return;
	}

	if (!q->currentAnswer()->isCorrect())
	{
		_falses.push_back(q);
		return;
	}


	if (q->currentAnswer()->isCorrect())
	{
		_corrects.push_back(q);
		return;
	}

	if (!q->currentAnswer()->isCorrect())
	{
		_falses.push_back(q);
		return;
	}
}

void Quiz::showCorrects() const
{
	for (auto& question : _corrects)
	{
		question->answerIndex = -1;

		cout << *question << endl;

		for (auto& answer: question->answers())
		{
			if (answer->isCorrect())
				cout << "Correct One: " << answer->answer() << endl<<endl;;
		}
	}
}

void Quiz::showFalses() const
{
	for (auto& question : _falses)
	{
		question->answerIndex = -1;

		cout << *question << endl;

		for (auto& answer : question->answers())
		{
			if (answer->isCorrect())
				cout << "Correct One: " << answer->answer() << endl << endl;
		}
	}
}

void Quiz::showUnanswereds() const
{
	for (auto& question : _unanswered)
	{
		question->answerIndex = -1;

		cout << *question << endl;

		for (auto& answer : question->answers())
		{
			if (answer->isCorrect())
				cout << "Correct One: " << answer->answer() << endl << endl;
		}
	}
}

#pragma endregion


#pragma region DESTRUCTOR

Quiz::~Quiz()
{
	for (auto& question : _allQuestions)
	{
		delete question;
		question = nullptr;
	}
}

#pragma endregion
