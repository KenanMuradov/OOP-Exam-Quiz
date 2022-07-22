#pragma once

namespace HeaderFiles
{

	namespace QUIZ
	{
		class Answer
		{
			string _answer = "";
			bool _isCorrect = false;

		public:

			Answer() = default;
			Answer(const Answer&) = default;
			Answer(Answer&&) = default;
			Answer(string answer, bool isCorrect);

			string answer() const;
			string& answer();
			bool isCorrect() const;
			void setAnswer(const string& answer);

		};

#pragma region CONSTRUCTORS

		Answer::Answer(string answer, bool isCorrect)
		{
			setAnswer(answer);
			_isCorrect = isCorrect;
		}

#pragma endregion

#pragma region OPERATORS

		ostream& operator<<(ostream& out, const Answer& a)
		{
			return out << a.answer();
		}

#pragma endregion


#pragma region ACCESSORS

		string Answer::answer() const
		{
			return _answer;
		}

		string& Answer::answer()
		{
			return _answer;
		}

		bool Answer::isCorrect() const
		{
			return _isCorrect;
		}

		void Answer::setAnswer(const string& answer)
		{
			if (answer.size() == 0)
				throw exception("Answer cannot be empty");

			_answer = answer;
		}

#pragma endregion

	}

}
