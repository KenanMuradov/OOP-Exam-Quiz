#pragma once
class Question
{
	vector<Answer*> _answers;
	string _question = "";
	Answer* _currentAnswer = nullptr;

public:

	short answerIndex = 0;


	Question() = default;
	Question(const Question& q);
	Question(Question&& q) noexcept;
	Question(string question);

	Question& operator=(const Question& q);
	Question& operator=(Question&& q) noexcept;

	const vector<Answer*> answers() const;
	vector<Answer*>& answers();
	string question() const;
	Answer* currentAnswer() const;
	Answer*& currentAnswer();
	void setQuestion(const string& question);

	void addAnswer(Answer* answer);


	~Question();
};

#pragma region CONSTRUCTORS

Question::Question(string question)
{
	setQuestion(question);
}

Question::Question(const Question& q)
{
	for (auto& answer : q._answers)
		_answers.push_back(new Answer(*answer));

	_question = q._question;

	if (q._currentAnswer != nullptr)
		_currentAnswer = new Answer(*q._currentAnswer);

}

Question::Question(Question&& q) noexcept
{
	_answers.swap(q._answers);

	for (auto& answer : q._answers)
		answer = nullptr;

	_question = q._question;

	_currentAnswer = q._currentAnswer;
	q._currentAnswer = nullptr;
}


#pragma endregion

#pragma region OPERATORS

Question& Question::operator=(const Question& q)
{
	for (auto& answer : q._answers)
		_answers.push_back(new Answer(*answer));

	_question = q._question;

	if (q._currentAnswer != nullptr)
		_currentAnswer = new Answer(*q._currentAnswer);

	return *this;
}

Question& Question::operator=(Question&& q) noexcept
{
	q._answers.swap(_answers);

	for (auto& answer : _answers)
		answer = nullptr;

	q._question.assign(_question);

	q._currentAnswer = _currentAnswer;
	_currentAnswer = nullptr;

	return *this;
}

ostream& operator<<(ostream& out, const Question& q)
{
	mySetColor(11, 0);

	out << q.question() << endl;
	for (size_t i = 0; i < q.answers().size(); i++)
	{
		if (i == q.answerIndex)
		{
			mySetColor(0, 11);
			out << *q.answers()[i] << endl;
			mySetColor(11, 0);

			continue;
		}
		out << *q.answers()[i] << endl;

	}
	mySetColor(11, 0);

	if (q.currentAnswer() != nullptr)
		out << "\nCurrent Answer: " << *q.currentAnswer() << endl;

	return out;
}

#pragma endregion

#pragma region ACCESSORS

const vector<Answer*> Question::answers() const
{
	return _answers;
}

vector<Answer*>& Question::answers()
{
	return _answers;
}

string Question::question() const
{
	return _question;
}

Answer* Question::currentAnswer() const
{
	return _currentAnswer;
}

Answer*& Question::currentAnswer()
{
	return _currentAnswer;
}

void Question::setQuestion(const string& question)
{
	if (question.size() < 5)
		throw exception("Question cannot be that short");

	_question = question;
}

#pragma endregion

#pragma region METHODS

void Question::addAnswer(Answer* answer)
{
	if (answer == nullptr)
		throw exception("Answer is not identitfied");

	_answers.push_back(new Answer(*answer));
}

#pragma endregion


#pragma region DESTRUCTOR

Question::~Question()
{
	for (auto& answer : _answers)
	{
		delete answer;
		answer = nullptr;
	}

	delete _currentAnswer;
}


#pragma endregion