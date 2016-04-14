#ifndef PARAMS_H
#define PARAMS_H

#include <string>

using namespace std;

class Params
{
public:
	bool parseParams(int argc, char *argv[]);

	string file() const;
	string def() const;

private:
	string m_file;
	string m_def;
};

#endif // PARAMS_H
