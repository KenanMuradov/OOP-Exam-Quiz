#pragma once

namespace HeaderFiles
{
	namespace USERS
	{

		class Admin : public User
		{
		public:
			Admin() = default;
			Admin(string nickname, string password);

		};

#pragma region CONSTRUCTOS

		Admin::Admin(string nickname, string password)
			: User(nickname, password) {}

#pragma endregion
	}

}
