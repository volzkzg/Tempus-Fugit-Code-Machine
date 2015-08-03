#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

string s[110];

int main()
{
  int n;
  scanf("%d", &n);
  getchar();
  for(int i = 0; i < n; ++i)
    {
      cin >> s[i];
    }
  sort(s, s + n);
  int ans = 0, cur = 1;
  for(int k = 1; k < n; ++k)
    {
      ans = max(ans, cur);
      if(s[k] != s[k - 1])
	cur = 0;
      cur++;
    }
  ans = max(ans, cur);
  printf("%d\n", ans);
  return 0;
}