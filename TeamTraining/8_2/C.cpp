#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>

using namespace std;

bool have[10000];
map<string, char> down, up;
vector<char> ans;
string s;
int pos;

void insert(string s, char d)
{
	down[s] = d;
}

void insert(string s, char d, char u)
{
	down[s] = d;
	up[s] = u;
}

bool get_next(string &ret)
{
	ret = "";
	if (pos + 2 <= (int)s.size()) {
		ret += s[pos];
		ret += s[pos + 1];
		pos += 2;
		return true;
	} else
		return false;
}

void remove()
{
	if (ans.empty()) {
		return;
	} else {
		ans.pop_back();
	}
}

int main()
{
	ios::sync_with_stdio(false);
	insert("0E", '`', '~');
	insert("16", '1', '!');
	insert("1E", '2', '@');
	insert("26", '3', '#');
	insert("23", '4', '$');
	insert("2E", '5', '%');
	insert("36", '6', '^');
	insert("3D", '7', '&');
	insert("3E", '8', '*');
	insert("46", '9', '(');
	insert("22", '0', ')');
	insert("4E", '-', '_');
	insert("55", '=', '+');
	insert("0D", '\t', '\t');
	insert("15", 'q', 'Q');
	insert("1D", 'w', 'W');
	insert("24", 'e', 'E');
	insert("2C", 'r', 'R');
	insert("2D", 't', 'T');
	insert("35", 'y', 'Y');
	insert("3C", 'u', 'U');
	insert("43", 'i', 'I');
	insert("44", 'o', 'O');
	insert("4D", 'p', 'P');
	insert("54", '[', '{');
	insert("5B", ']', '}');
	insert("5D", '\\', '|');
	insert("1C", 'a', 'A');
	insert("1B", 's', 'S');
	insert("25", 'd', 'D');
	insert("2B", 'f', 'F');
	insert("33", 'g', 'G');
	insert("34", 'h', 'H');
	insert("3B", 'j', 'J');
	insert("42", 'k', 'K');
	insert("4B", 'l', 'L');
	insert("4C", ';', ':');
	insert("52", '\'', '"');
	insert("5A", '\n', '\n');
	insert("1A", 'z', 'Z');
	insert("45", 'x', 'X');
	insert("29", 'c', 'C');
	insert("2A", 'v', 'V');
	insert("32", 'b', 'B');
	insert("31", 'n', 'N');
	insert("3A", 'm', 'M');
	insert("41", ',', '<');
	insert("49", '.', '>');
	insert("4A", '/', '?');
	insert("21", ' ', ' ');

	while (cin >> s) {
		memset(have, false, sizeof(have));
		ans.clear();
		pos = 0;
		bool L_shift, R_shift, caps_down;
		int caps_lock;
		L_shift = R_shift = caps_down = false;
		caps_lock = 0;
		string now;
		while (true) {
			if (!get_next(now)) break;
			if (now == "F0") {
				get_next(now);
				if (now == "58") {
					if (!caps_down) continue;
					caps_down = false;
					continue;
				}
				if (now == "12") {
					L_shift = false;
					continue;
				}
				if (now == "59") {
					R_shift = false;
					continue;
				}
			} else {
				if (now == "66") { // backspace
					remove();
					continue;
				} 
				if (now == "58") {
					if (caps_down) continue;
					if (caps_lock == 0) {
						caps_lock = 1;
						caps_down = true;
					} else if (caps_lock == 1) {
						caps_lock = 0;
						caps_down = true;
					}
					continue;
				}
				if (now == "12") {
					L_shift = true;
					continue;
				}
				if (now == "59") {
					R_shift = true;
					continue;
				}
				char c = down[now];
				if (c >= 'a' && c <= 'z') {
					if (caps_lock) {
						if (L_shift || R_shift) 
							ans.push_back(down[now]);
						else 
							ans.push_back(up[now]);
					} else {
						if (L_shift || R_shift) 
							ans.push_back(up[now]);
						else
							ans.push_back(down[now]);
					}
				} else {
					if (L_shift || R_shift)
						ans.push_back(up[now]);
					else
						ans.push_back(down[now]);
				}
			}
		}
		for (int i = 0; i < (int)ans.size(); ++i)
			cout << ans[i];
		cout << endl;
	}
	return 0;
}




