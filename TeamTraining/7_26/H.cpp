#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

class point
{
public:
	long double x, y;
	__inline point(){}
	__inline point(long double x, long double y):x(x), y(y){}
	__inline point operator - (const point &b)
	{
		return point(x - b.x, y - b.y);
	}
	__inline point operator + (const point &b)
	{
		return point(x + b.x, y + b.y);
	}
	__inline point operator * (const long double p)
	{
		return point(x * p, y * p);
	}
};

point loc[3];

__inline long double dist(const point &a, const point &b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

__inline long double calc0(point p)
{
	return (dist(loc[2], p) + dist(loc[1], p)) * 2 + dist(loc[0], p);
}
__inline long double calc1(point p)
{
	return (dist(loc[0], p) + dist(loc[2], p)) * 2 + dist(loc[1], p);
}
__inline long double calc2(point p)
{
	return (dist(loc[0], p) + dist(loc[1], p)) * 2 + dist(loc[2], p);
}

point dir[4] = {point(1, 0), point(-1, 0), point(0, 1), point(0, -1)};

long double ans;

void randomWalk0(point c)
{
//	double T = calc(point(cx, cy));
	for(long double step = 4000; step > 1e-10; step *= 0.5)
	{
		double delta = 0;
		bool flag = true;
		while(flag)
		{
			flag = false;
			for(int j = 0; j < 4; ++j)
			{
				point nxt = c + dir[j] * step;
				delta = calc0(c) - calc0(nxt);
				if(delta > 0)
				{
					flag = true;
					c = nxt;
					break;
				}
			}
			if(delta < 1e-15)
				break;
		}
	}
	if(calc0(c) < ans)
	{
		ans = calc0(c);
	}
}
void randomWalk1(point c)
{
//	double T = calc(point(cx, cy));
	for(long double step = 4000; step > 1e-10; step *= 0.5)
	{
		double delta = 0;
		bool flag = true;
		while(flag)
		{
			flag = false;
			for(int j = 0; j < 4; ++j)
			{
				point nxt = c + dir[j] * step;
				delta = calc1(c) - calc1(nxt);
				if(delta > 0)
				{
					flag = true;
					c = nxt;
					break;
				}
			}
			if(delta < 1e-15)
				break;
		}
	}
	if(calc1(c) < ans)
	{
		ans = calc1(c);
	}
}
void randomWalk2(point c)
{
//	double T = calc(point(cx, cy));
	for(long double step = 4000; step > 1e-10; step *= 0.5)
	{
		double delta = 0;
		bool flag = true;
		while(flag)
		{
			flag = false;
			for(int j = 0; j < 4; ++j)
			{
				point nxt = c + dir[j] * step;
				delta = calc2(c) - calc2(nxt);
				if(delta > 0)
				{
					flag = true;
					c = nxt;
					break;
				}
			}
			if(delta < 1e-15)
				break;
		}
	}
	if(calc2(c) < ans)
	{
		ans = calc2(c);
	}
}

int main()
{
	srand(time(0));
	int iCase = 1;
	while(true)
	{
		ans = 1e100;
		for(int i = 0; i < 3; ++i)
		{
			cin >> loc[i].x >> loc[i].y;
		}
		if(loc[0].x < 0) break;
		randomWalk0((loc[0] + loc[1] + loc[2]) * 0.3333333333);
		randomWalk1((loc[0] + loc[1] + loc[2]) * 0.3333333333);
		randomWalk2((loc[0] + loc[1] + loc[2]) * 0.3333333333);
		printf("Case %d: %.8f\n", iCase++, (double)ans);
	}
	return 0;
}
