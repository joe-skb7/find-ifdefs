#ifndef STRING_UTILS
#define STRING_UTILS

#include <algorithm>

using namespace std;

// Trim from start (in place)
static inline void ltrim(string &s)
{
	s.erase(s.begin(), find_if(s.begin(), s.end(), not1(
			ptr_fun<int, int>(isspace))));
}

// Trim from end (in place)
static inline void rtrim(string &s)
{
	s.erase(find_if(s.rbegin(), s.rend(), not1(
			ptr_fun<int, int>(isspace))).base(), s.end());
}

// Trim from both ends (in place)
static inline void trim(string &s)
{
	ltrim(s);
	rtrim(s);
}

#endif // STRING_UTILS
