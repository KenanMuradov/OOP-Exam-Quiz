#pragma once
class User
{
protected:

	string _nickname = "";
	string _password = "";

public:

	User() = default;
	User(string nickname, string password);
	User(const User& u) = default;
	User(User&& u) = default;


	string nickname() const;
	string password() const;
	void setNickname(const string& nickname);
	void setPassword(const string& password);

	virtual ~User() = 0 {};
};


#pragma region CONSRTUCTOR

User::User(string nickname, string password)
	: _nickname(nickname), _password(password) {}

#pragma endregion


#pragma region ACCESSORS

string User::nickname() const
{
	return _nickname;
}

string User::password() const
{
	return _password;
}

void User::setNickname(const string& nickname)
{
	if (nickname.size() < 3)
		throw exception("Username is too Short");

	_nickname = nickname;
}

void User::setPassword(const string& password)
{
	if (password.size() < 6)
		throw exception("Password is too Short");

	_password = password;
}

#pragma endregion
