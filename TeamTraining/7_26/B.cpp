#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAXN = 100;

char map[MAXN][MAXN];
char ans[MAXN][MAXN];

int tst;
int w[MAXN];

int main() {
	scanf("%d", &tst);
	for (char ch = 'A'; ch <= 'Z'; ++ch) {
		int now = (int)ch;
		int cnt0 = 0, cnt1 = 0;
		while (now) {
			if (now & 1)
				++cnt1;
			else
				++cnt0;
			now >>= 1;
		}
		w[(int)(ch - 'A' + 1)] = cnt1 * 2 + cnt0;
	}
	for (int tt = 1; tt <= tst; ++tt) {
		for (int i = 1; i <= 8; ++i)
			scanf("%s", map[i] + 1);
		printf("Case %d:\n", tt);
		int left = 0, right = 0;
		for (int i = 1; i <= 8; ++i)
			for (int j = 1; j <= 8; ++j)
				if (map[i][j] >= 'A' && map[i][j] <= 'Z')
					left += w[map[i][j] - 'A' + 1];
		for (int i = 1; i <= 8; ++i)
			for (int j = 11; j <= 18; ++j)
				if (map[i][j] >= 'A' && map[i][j] <= 'Z')
					right += w[map[i][j] - 'A' + 1];
		int org, cur;
		if (map[6][1] == '/')
			org = 1;
		else if (map[5][1] == '/')
			org = 0;
		else
			org = - 1;
		if (left > right)
			cur = 1;
		else if (left == right)
			cur = 0;
		else
			cur = -1;
		if (org == cur) {
			puts("The figure is correct.");
		}
		else {
			int curl, curr;
			if (org == 1) {
				curl = 3;
				curr = 1;
			}
			else if (org == 0) {
				curl = 2;
				curr = 2;
			}
			else {
				curl = 1;
				curr = 3;
			}
			memset(ans, 0, sizeof(ans));
			memcpy(ans, map, sizeof(ans));
			if (cur == 1) {
				for (int i = 1; i <= 2; ++i)
					for (int j = 1; j <= 8; ++j)
						ans[i][j] = '.';
				for (int i = 3; i <= 7; ++i)
					for (int j = 1; j <= 8; ++j)
						ans[i][j] = map[curl + (i - 3)][j];
				for (int i = 1; i <= 5; ++i)
					for (int j = 11; j <= 18; ++j)
						ans[i][j] = map[curr + (i - 1)][j];
				for (int i = 6; i <= 7; ++i)
					for (int j = 11; j <= 18; ++j)
						ans[i][j] = '.';
			}
			else if (cur == 0) {
				for (int i = 1; i <= 8; ++i)
					ans[1][i] = ans[7][i] = '.';
				for (int i = 2; i <= 6; ++i)
					for (int j = 1; j <= 8; ++j)
						ans[i][j] = map[curl + (i - 2)][j];
				for (int i = 11; i <= 18; ++i)
					ans[1][i] = ans[7][i] = '.';
				for (int i = 2; i <= 6; ++i)
					for (int j = 11; j <= 18; ++j)
						ans[i][j] = map[curr + (i - 2)][j];
			}
			else {
			       for (int i = 6; i <= 7; ++i)
					for (int j = 1; j <= 8; ++j)
						ans[i][j] = '.';
				for (int i = 1; i <= 5; ++i)
					for (int j = 1; j <= 8; ++j)
						ans[i][j] = map[curl + (i - 1)][j];
				for (int i = 3; i <= 7; ++i)
					for (int j = 11; j <= 18; ++j)
						ans[i][j] = map[curr + (i - 3)][j];
				for (int i = 1; i <= 2; ++i)
					for (int j = 11; j <= 18; ++j)
						ans[i][j] = '.';
			}
			for (int i = 1; i <= 7; ++i) {
				for (int j = 1; j <= 18; ++j)
					putchar(ans[i][j]);
				puts("");
			}
		}
	}
	return 0;
}
