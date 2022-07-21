#pragma once

#pragma region QUIZ
void writeAnswerToFile(fstream& stream, Answer* a)
{

	if (!stream)
		throw exception("Cannot create File");

	if (!stream.is_open())
		throw exception("Cannot open File");

	stream << a->answer() << endl << a->isCorrect() << endl;
	return;

}

Answer* readAnswerFromFile(fstream& stream)
{
	string answer;
	bool isCorrect;

	if (!stream)
		throw exception("Cannot create File");

	if (!stream.is_open())
		throw exception("Cannot open File");


	getline(stream, answer);
	stream >> isCorrect;
	stream.ignore();

	return new Answer(answer, isCorrect);
}


void writeQuesetionToFile(fstream& stream, Question* q)
{
	if (!stream)
		throw exception("Cannot create File");

	if (!stream.is_open())
		throw exception("Cannot open File");


	stream << q->question() << endl << q->answers().size() << endl;;

	for (auto& answer : q->answers())
		writeAnswerToFile(stream, answer);


}


Question* readQuestionFromFile(fstream& stream)
{
	if (!stream)
		throw exception("Cannot create File");

	if (!stream.is_open())
		throw exception("Cannot open File");


	string question;
	getline(stream, question);

	size_t answersCount;
	stream >> answersCount;
	stream.ignore();

	Question* q = new Question(question);


	for (size_t i = 0; i < answersCount; i++)
		q->addAnswer(readAnswerFromFile(stream));

	return q;
}


void writeQuizToFile(fstream& stream, Quiz* quiz)
{
	if (!stream)
		throw exception("Cannot create File");

	if (!stream.is_open())
		throw exception("Cannot open File");

	stream << quiz->name() << endl << quiz->creatorNick() << endl;

	stream << quiz->questions().size() << endl;

	for (auto& question : quiz->questions())
		writeQuesetionToFile(stream, question);
}

Quiz* readQuizFromFile(fstream& stream)
{
	if (!stream)
		throw exception("Cannot create File");

	if (!stream.is_open())
		throw exception("Cannot open File");

	string name, creatorNick;
	size_t questionCount;

	getline(stream, name);
	getline(stream, creatorNick);

	Quiz* quiz = new Quiz(name, creatorNick);

	stream >> questionCount;
	stream.ignore();

	for (size_t i = 0; i < questionCount; i++)
		quiz->addQuestion(readQuestionFromFile(stream));

	return quiz;
}

vector<Quiz*> loadQuizes(string fileName)
{
	fstream stream(fileName, ios::in);

	vector<Quiz*> quizes;



	if (!stream || !stream.is_open() || stream.peek() == 10)
		return quizes;

	size_t quizCount;

	stream >> quizCount;
	stream.ignore();

	for (size_t i = 0; i < quizCount; i++)
		quizes.push_back(readQuizFromFile(stream));

	return quizes;
}


void saveQuizes(string fileName, vector<Quiz*>& quizes)
{

	fstream stream(fileName, ios::out);


	if (!stream)
		throw exception("Cannot create File");

	if (!stream.is_open())
		throw exception("Cannot open File");

	stream.seekg(0);

	stream << quizes.size() << endl;

	for (auto& quiz : quizes)
		writeQuizToFile(stream, quiz);
}

#pragma endregion

#pragma region User

void writePlayerToFile(fstream& stream, Player* p)
{
	if (!stream)
		throw exception("Cannot create File");

	if (!stream.is_open())
		throw exception("Cannot open File");

	stream << p->nickname() << endl
		<< p->password() << endl
		<< p->latestPlayedQuiz() << endl
		<< p->highestScore() << endl;
	stream.ignore();

}


Player* readPlayerFromFile(fstream& stream)
{
	if (!stream)
		throw exception("Cannot create File");

	if (!stream.is_open())
		throw exception("Cannot open File");

	string name;
	string pass;
	string latestPlayed;
	float score;

	getline(stream, name);
	getline(stream, pass);
	getline(stream, latestPlayed);

	stream >> score;

	Player* p = new Player(name, pass);

	p->setLatestPlayedQuiz(latestPlayed);
	p->setHighestScore(score);

	return p;
}

vector<Player*> loadPlayers(string fileName)
{
	fstream stream(fileName, ios::in);

	vector<Player*> players;

	if (!stream || !stream.is_open() || stream.peek() == 10)
		return players;

	size_t playersCount;

	stream >> playersCount;
	stream.ignore();

	for (size_t i = 0; i < playersCount; i++)
		players.push_back(readPlayerFromFile(stream));

	return players;
}


void savePlayers(string fileName, vector<Player*> players)
{
	fstream stream(fileName, ios::out);


	if (!stream)
		throw exception("Cannot create File");

	if (!stream.is_open())
		throw exception("Cannot open File");

	stream << players.size() << endl;

	for (auto& player : players)
		writePlayerToFile(stream, player);
}

void writeAdminToFile(fstream& stream, Admin* a)
{
	if (!stream)
		throw exception("Cannot create File");

	if (!stream.is_open())
		throw exception("Cannot open File");

	stream << a->nickname() << endl
		<< a->password() << endl
		<< a->latestPlayedQuiz() << endl
		<< a->highestScore() << endl;
	stream.ignore();

}


Admin* readAdminFromFile(fstream& stream)
{
	if (!stream)
		throw exception("Cannot create File");

	if (!stream.is_open())
		throw exception("Cannot open File");

	string name;
	string pass;
	string latestPlayed;
	float score;

	getline(stream, name);
	getline(stream, pass);
	getline(stream, latestPlayed);

	stream >> score;

	Admin* a = new Admin(name, pass);

	a->setLatestPlayedQuiz(latestPlayed);
	a->setHighestScore(score);

	return a;
}

vector<Admin*> loadAdmins(string fileName)
{
	fstream stream(fileName, ios::in);

	vector<Admin*> admins;

	if (!stream || !stream.is_open() || stream.peek() == 10)
		return admins;

	size_t playersCount;

	stream >> playersCount;
	stream.ignore();

	for (size_t i = 0; i < playersCount; i++)
		admins.push_back(readAdminFromFile(stream));

	return admins;
}


void saveAdmins(string fileName, vector<Admin*> admins)
{
	fstream stream(fileName, ios::out);


	if (!stream)
		throw exception("Cannot create File");

	if (!stream.is_open())
		throw exception("Cannot open File");

	stream << admins.size() << endl;

	for (auto& admin : admins)
		writeAdminToFile(stream, admin);
}


#pragma endregion
