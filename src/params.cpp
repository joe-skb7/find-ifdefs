#include <params.h>

#include <iostream>

bool Params::parseParams(int argc, char *argv[])
{
	if (argc != 3) {
		cerr << "Error: Invalid arguments count" << endl;
		return false;
	}

	m_def = argv[1];
	m_file = argv[2];

	return true;
}

string Params::file() const
{
	return m_file;
}

string Params::def() const
{
	return m_def;
}
