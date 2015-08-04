#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

const int N = 12345;
string s;
int D, P, S[N];

void read_data()
{
	int tmp, cnt = 0;
	istringstream read(s);
	read >> D >> P;
	D++;
	while (read >> tmp) {
		S[++cnt] = tmp;
	}
	if(S[cnt] > P)
	{
		for(int i = cnt + 1; i <= D; ++i)
			S[i] = S[cnt];
		return;
	}
	if(cnt < D)
	{
		if(S[1] == 0 && S[2] == 0)
		{
			for(int i = 1; i <= D; ++i)
				S[i] = 0;
			return;
		}
		
		bool succ = false;
		int CoefA, CoefB;
		for(int a = 0; ; ++a)
		{
			bool flag = false;
			for(int j = 1; j + 2 <= cnt; ++j)
			{
				if(S[j] * a > S[j + 2])
					flag = true;
			}
			if(flag) break;
			for(int b = 0; ; ++b)
			{	
				bool flag2 = false;
				for(int j = 1; j + 2 <= cnt; ++j)
				{
					if(S[j] * a + S[j + 1] * b > S[j + 2])
						flag2 = true;
				}
				if(flag2) break;
				bool tmpSucc = true;
				for(int j = 1; j + 2 <= cnt; ++j)
				{
					if(S[j] * a + S[j + 1] * b != S[j + 2])
					{
						tmpSucc = false;
						break;
					}
				}
				if(tmpSucc)
				{
					succ = true;
					CoefA = a, CoefB = b;
					break;
				}
			}
			if(succ) break;
		}
		
		while(cnt < D)
		{
			S[cnt + 1] = CoefB * S[cnt] + CoefA * S[cnt - 1];
			cnt++;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	
	while (getline(cin, s)) {
		read_data();
		if(S[1] > P)
		{
			printf("The spider is going to fall!\n");
			continue;
		}
		int pos = -1;
		for(int i = 1; i <= D && pos == -1; ++i)
		{
			if(S[i] > P)
				pos = i;
		}
		if(pos == -1)
			printf("The spider may fall!\n");
		else
			printf("%d\n", D - pos + 1);
	}	
	return 0;
}
