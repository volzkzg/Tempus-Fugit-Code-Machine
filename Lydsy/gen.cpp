#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

int main()
{
	srand(time(0));
	int n = 20000;
	int Q = 25000;
	int Mod = 100000;
	static int a[100000];
	printf("%d\n", n);
	for(int i = 0; i < n; ++i)
		printf("%d%c", rand() % Mod, i == n - 1 ? '\n' : ' '), a[i] = i;
	printf("%d\n", Q);
	for(int i = 0; i < Q; ++i)
	{
		random_shuffle(a, a + n);
		for(int j = 0; j < 4; ++j)
		{
			printf("%d%c", a[j], j == 3 ? '\n' : ' ');	
		}
	}
	return 0;
}