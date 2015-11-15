#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	srand(time(0));
	int n = 50000, T = 20;
	while(T--)
	{
		printf("%d\n", n);
		for(int i = 0; i < n; ++i)
			printf("%d ", n - i);
		puts("");
		for(int i = 0; i < n; ++i)
			printf("%d ", i + 1);
		puts("");
	}
	return 0;
}