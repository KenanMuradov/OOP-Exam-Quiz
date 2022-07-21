#pragma once
struct Commands
{
	vector<string> commands;
	short commandIndex = 0;

};

ostream& operator<<(ostream& out, const Commands& c)
{
	mySetColor(11, 0);
	for (size_t i = 0; i < c.commands.size(); i++)
	{
		if (i == c.commandIndex)
		{
			mySetColor(0, 11);
			out << c.commands[i] << endl;
			mySetColor(11, 0);

			continue;
		}

		out << c.commands[i] << endl;
	}

	return out;
}