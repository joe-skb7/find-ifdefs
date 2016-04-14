#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <stack>
#include <string>

using namespace std;

class Parser
{
public:
	explicit Parser();

	bool readFile(const string &filePath);
	bool parse(const string &def);
	void printIfdefs();
private:
	string m_filePath;
	vector<string> m_fileContent;
	stack<int> m_ifdefs;		/* line numbers for #ifdefs */
	int m_defLineNum;
};

#endif // PARSER_H
