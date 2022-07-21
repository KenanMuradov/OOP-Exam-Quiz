#pragma once
class Admin : public User
{
	string _latestPlayedQuiz = "";
	float _highestScore = 0;

public:
	Admin() = default;
	Admin(string nickname, string password);

	string latestPlayedQuiz() const;
	float highestScore() const;
	void setLatestPlayedQuiz(string quizName);
	void setHighestScore(float score);

};

#pragma region CONSTRUCTOS

Admin::Admin(string nickname, string password)
	: User(nickname, password) {}

#pragma endregion


#pragma region ACCESSORS

string Admin::latestPlayedQuiz() const
{
	return _latestPlayedQuiz;
}

float Admin::highestScore() const
{
	return _highestScore;
}

void Admin::setLatestPlayedQuiz(string quizName)
{
	if (quizName.size() == 0)
		throw exception("Quiz name cannot be empty");

	_latestPlayedQuiz = quizName;
}

void Admin::setHighestScore(float score)
{
	if (score > _highestScore)
		_highestScore = score;
}

#pragma endregion