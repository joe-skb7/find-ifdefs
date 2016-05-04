#include <parser.h>

#include <string_utils.h>

#include <fstream>
#include <iostream>

Parser::Parser()
	: m_defLineNum(0)
{
}

bool Parser::readFile(const string &filePath)
{
	m_filePath = filePath;

	ifstream file(filePath.c_str());
	if (!file.is_open()) {
		cerr << "Error: Unable to open file: " << filePath << endl;
		return false;
	}

	string line;
	while (file.good()) {
		getline(file, line);
		m_fileContent.push_back(line);
	}

	file.close();

	return true;
}

// false -- def not found
bool Parser::parse(const string &def)
{
	int lineNum = -1;

	for (auto line : m_fileContent) {
		++lineNum;

		if (line.empty())
			continue;

		// Look only for preprocessor directives
		trim(line);
		if (line.at(0) != '#')
			continue;

		// Remove '#' and spaces
		line.erase(0, 1);
		ltrim(line);

		size_t pos;

		// Look for "#if"; if found -- push to stack
		pos = line.find("if");
		if (pos == 0) {
			m_ifdefs.push(lineNum);
			continue;
		}

		// Look for "#endif"; if found -- pop previous #if from stack
		pos = line.find("endif");
		if (pos == 0) {
			m_ifdefs.pop();
			continue;
		}

		// Look for "#define"
		pos = line.find("define");
		if (pos != 0)
			continue;
		line.erase(0, 6); // remove "define" word
		ltrim(line);

		// Look for specified definition
		pos = line.find(def);
		if (pos != 0)
			continue;

		// Check right boundary of definition
		line.erase(pos, def.length());
		if (line.length() == 0 || isspace(line.at(0))) {
			m_defLineNum = lineNum;
			return true;
		}
	}

	cerr << "Error: " << m_filePath << ": " << def << " not found" << endl;
	return false;
}

void Parser::printDef() const
{
	cout << m_filePath << ":" << m_defLineNum+1 << ":"
			<< m_fileContent.at(m_defLineNum) << endl;
}

void Parser::printIfdefs()
{
	while (!m_ifdefs.empty()) {
		int lineNum = m_ifdefs.top();
		cout << m_filePath << ":" << lineNum+1 << ":"
				<< m_fileContent.at(lineNum) << endl;
		m_ifdefs.pop();
	}
}
