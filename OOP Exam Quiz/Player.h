#pragma once
class Player : public User
{
	string _latestPlayedQuiz = "";
	double _highestScore = 0;

public:

	Player() = default;
	Player(string nickname, string password);

	string latestPlayedQuiz() const;
	float highestScore() const;
	void setLatestPlayedQuiz(string quizName);
	void setHighestScore(float score);

};

#pragma region CONSTRUCTOS

Player::Player(string nickname, string password)
	: User(nickname, password) {}

#pragma endregion


#pragma region ACCESSORS

string Player::latestPlayedQuiz() const
{
	return _latestPlayedQuiz;
}

float Player::highestScore() const
{
	return _highestScore;
}

void Player::setLatestPlayedQuiz(string quizName)
{
	if (quizName.size() == 0)
		throw exception("Quiz name cannot be empty");

	_latestPlayedQuiz = quizName;
}

void Player::setHighestScore(float score)
{
	if (score > _highestScore)
		_highestScore = score;
}

#pragma endregion


ostream& operator<<(ostream& out, const Player& p)
{
	out << "Nickname: " << p.nickname() << endl
		<< "Latest Played Quiz: " << p.latestPlayedQuiz() << endl
		<< "Highest Score: " << p.highestScore() << endl;

	return out;
}