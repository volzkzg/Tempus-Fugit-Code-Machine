#include <cstdio>
#include <string>
#include <iostream>
#include <map>

using namespace std;

map<string, bool> ex;

string p;

int main()
{
	cin >> p;
	for(int i = 0; i < p.length(); ++i)
	{
		char str[2];
		str[1] = 0;
		for(char j = 'a'; j <= 'z'; ++j)
		{
			str[0] = j;
			string s;
			if(i)
				s = p.substr(0, i) + string(str) + p.substr(i, p.length());
			else
				s = string(str) + p;
	//		cout << s << endl;
			ex[s] = true;
		}
	}
	for(char j = 'a'; j <= 'z'; ++j)
	{
		char str[2];
		str[1] = 0;
		str[0] = j;
		string s = p + string(str);
		ex[s] = true;
	}
	printf("%d\n", (int)ex.size());
	return 0;
}