#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;
char w[2][110];
char s[110000];
int wlen[2], slen;
int k;

multimap<long long, int> mp;

long long hashVal[110];
const int p = 101;

long long myPow[110];

void initHash(char *s, int len)
{
	long long po = 1;
	hashVal[0] = s[0];
	for(int i = 1; i < len; ++i)
	{
		po = po * p;
		hashVal[i] = hashVal[i - 1] + po * s[i];
	}
}

int main()
{
	myPow[0] = 1;
	for(int i = 1; i < 110; ++i)
		myPow[i] = myPow[i - 1] * p;
	while(scanf("%d", &k) == 1)
	{
		mp.clear();
		if(k == 0) break;
		scanf("%s%s%s", w[0], w[1], s);
		wlen[0] = strlen(w[0]);
		wlen[1] = strlen(w[1]);
		slen = strlen(s);

		for(int i = 0; i < slen - wlen[0] + 1; ++i)
		{
			static char curKey[110];
			static bool vis[110];
			for(int j = 0; j < wlen[0]; ++j)
				curKey[j] = (((int)s[i + j] - 1 - w[0][j]) % 26 + 26) % 26 + 'A', vis[j + 1] = false;
			curKey[wlen[0]] = 0;
			initHash(curKey, wlen[0]);
			for(int l = 1; l <= k; ++l)
			{
				if(vis[l]) continue;
				int startPos = i % l;
				long long h = hashVal[l - 1];
				bool flag = true;
				for(int i = 0; i * l + l - 1 < wlen[0]; ++i)
				{
					if(h * (myPow[i * l]) != (hashVal[i * l + l - 1] - (i * l == 0 ? 0 : hashVal[i * l - 1])))
					{
						flag = false;
						break;
					}
				}
				if(!flag) continue;
				for(int i = wlen[0] / l * l, j = 0; i < wlen[0]; ++i, ++j)
				{
					if(curKey[i] != curKey[j])
					{
						flag = false;
						break;
					}
				}
				if(flag)
				{
					for(int i = 0; i * l <= wlen[0]; ++i)
						vis[i * l] = true;
					static char finalKey[110];
					h = 0;
					for(int i = startPos, j = 0; j < l; ++j, i = (i + 1) % l)
						finalKey[i] = curKey[j % wlen[0]];
					finalKey[l] = 0;
					for(int i = 0; i < l; ++i)
						h += myPow[i] * finalKey[i];
					mp.insert(make_pair(h, i));
				}
			}
		}
		int cnt = 0, keyLen;
		char key[110];
		long long resKey;
	//	printf("%d %d\n", wlen[0], wlen[1]);
		
		for(int i = 0; i < slen - wlen[1] + 1; ++i)
		{
			static char curKey2[110];
			static bool vis2[110];
			for(int j = 0; j < wlen[1]; ++j)
				curKey2[j] = (((int)s[i + j] - 1 - w[1][j]) % 26 + 26) % 26 + 'A', vis2[j + 1] = false;
			curKey2[wlen[1]] = 0;
			initHash(curKey2, wlen[1]);
			for(int l = 1; l <= k; ++l)
			{
				if(vis2[l]) continue;
				int startPos = i % l;
				long long h = hashVal[l - 1];
				bool flag = true;
				for(int i = 0; (i + 1) * l - 1 < wlen[1]; ++i)
				{
					if(h * (myPow[i * l]) != (hashVal[i * l + l - 1] - (i * l == 0 ? 0 : hashVal[i * l - 1])))
					{
						flag = false;
						break;
					}
				}
				if(!flag) continue;
				for(int i = wlen[1] / l * l, j = 0; i < wlen[1]; ++i, ++j)
				{
					if(curKey2[i] != curKey2[j])
					{
						flag = false;
						break;
					}
				}
				if(flag)
				{
					for(int i = 0; i * l <= wlen[1]; ++i)
						vis2[i * l] = true;
					static char finalKey2[110];
					h = 0;
					for(int i = startPos, j = 0; j < l; ++j, i = (i + 1) % l)
						finalKey2[i] = curKey2[j % wlen[1]];
					for(int i = 0; i < l; ++i)
						h += myPow[i] * finalKey2[i];
					finalKey2[l] = 0;
					pair<multimap<long long, int>::iterator, multimap<long long, int>::iterator> range;
					range = mp.equal_range(h);
					if(range.first == range.second) continue;
					range.second--;
			//		printf("%d %d\n", range.first -> second, range.second -> second);
					if(range.first -> second + wlen[0] - 1 < i || (range.second) -> second > i + wlen[1] - 1)
					{
						if(cnt != 0)
						{
							if(resKey == h) continue;
						}
						cnt++;
						if(cnt == 1)
						{
							for(int j = 0; j < l; ++j)
								key[j] = finalKey2[j];
							keyLen = l;
							resKey = h;
						}
					}
				}
			}
		}
		if(cnt == 1)
		{
			for(int i = 0, j = 0; i < slen; ++i, j = (j + 1) % keyLen)
			{
				putchar((((int)s[i] - 'A' - key[j] + 'A' - 1) % 26 + 26) % 26 + 'A');
			}
			puts("");
		}
		else
		{
			if(cnt > 1)
				puts("ambiguous");
			else
				puts("impossible");
		}
	}
	return 0;
}