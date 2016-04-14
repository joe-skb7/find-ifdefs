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

		trim(line);
		if (line.at(0) != '#')
			continue;

		// Remove '#' and spaces
		line.erase(0, 1);
		ltrim(line);

		size_t pos;

		pos = line.find("if");
		if (pos == 0) {
			m_ifdefs.push(lineNum);
			continue;
		}

		pos = line.find("endif");
		if (pos == 0) {
			m_ifdefs.pop();
			continue;
		}

		pos = line.find("define");
		if (pos != 0)
			continue;
		line.erase(0, 6);
		ltrim(line);
		pos = line.find(def);
		if (pos != 0)
			continue;
		line.erase(pos, def.length());
		if (line.length() == 0 || isspace(line.at(0))) {
			m_defLineNum = lineNum;
			return true;
		}
	}

	cerr << "Error: " << def << " not found in file" << endl;
	return false;
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
