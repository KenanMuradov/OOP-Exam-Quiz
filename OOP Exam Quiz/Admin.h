#pragma once
class Admin : public User
{
	string _latestPlayedQuiz = "";
	double _highestScore = 0;

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

#pragma region OPERATORS

ostream& operator<<(ostream& out, const Admin& a)
{
	out << "Nickname: " << a.nickname() << endl
		<< "Latest Played Quiz: " << a.latestPlayedQuiz() << endl
		<< "Highest Score: " << a.highestScore() << endl;

	return out;
}



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
	_latestPlayedQuiz = quizName;
}

void Admin::setHighestScore(float score)
{
	if (score >= _highestScore)
		_highestScore = score;
}

#pragma endregion