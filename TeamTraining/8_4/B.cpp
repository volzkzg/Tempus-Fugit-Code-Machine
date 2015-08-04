#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int Maxn = 110;
const int inf = 0x3f3f3f3f;

int f[Maxn][Maxn][Maxn];
char s[Maxn], t[Maxn];

int main()
{
	int T;
	scanf("%d", &T);
	for(int cas = 1; cas <= T; ++cas)
	{
		printf("Case %d: ", cas);
		scanf("%s%s", s + 1, t + 1);
		int n = strlen(s + 1);
		for(int i = 0; i <= n; ++i)
			for(int j = 0; j <= n; ++j)
				for(int k = 0; k <= n; ++k)
					f[i][j][k] = inf;
		f[0][0][0] = 0;
		for(int i = 0; i < n; ++i)
		{
			for(int j = 0; j <= i; ++j)
			{
				for(int k = 0; k + j <= i; ++k)
				{
					int &curf = f[i][j][k];
					if(curf == inf) continue;
					//1
					{
						int delta = 0, da, db;
						if(s[i + 1] == '1') delta = inf;
						if(s[i + 1] == '0') delta = 0;
						if(s[i + 1] == '?') delta = 1;
						if(t[i + 1] == '1') da = 1, db = 0;
						else da = 0, db = 0;
						f[i + 1][j + da][k + db] = min(f[i + 1][j + da][k + db], curf + delta);
					}
					//2
					{
						int delta, da, db;
						if(s[i + 1] == '1') delta = 0;
						else delta = 1;
						if(t[i + 1] == '1') da = 0, db = 0;
						else da = 0, db = 1;
						f[i + 1][j + da][k + db] = min(f[i + 1][j + da][k + db], curf + delta);
					}
					//3
					{
						int delta, da, db;
						if(s[i + 1] == '0') delta = 1;
						if(s[i + 1] == '1') delta = inf;
						if(s[i + 1] == '?') delta = 2;
						if(k == 0) delta = inf; //No '1'
						if(t[i + 1] == '0') da = 0, db = 0;
						else da = 0, db = -1;
						if(delta != inf)
							f[i + 1][j + da][k + db] = min(f[i + 1][j + da][k + db], curf + delta);
					}
					//4
					{
						int delta, da, db;
						if(s[i + 1] == '0' || s[i + 1] == '?') delta = 2;
						if(s[i + 1] == '1') delta = 1;
						if(j == 0) delta = inf;
						if(t[i + 1] == '0') da = -1, db = 0;
						else da = 0, db = 0;
						if(delta != inf)
							f[i + 1][j + da][k + db] = min(f[i + 1][j + da][k + db], curf + delta);
					}
				}
			}
		}
		if(f[n][0][0] == inf)
			printf("-1\n");
		else
			printf("%d\n", f[n][0][0]);
	}
	return 0;
}
