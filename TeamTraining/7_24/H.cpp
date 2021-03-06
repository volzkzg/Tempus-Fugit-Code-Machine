#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

inline void read(int &x)
{
	x = 0;
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
}

class person
{
public:
	int x, y, id;
	bool operator < (const person &b) const
	{
		if(y == b.y) return id < b.id;
		return y < b.y;
	}
	person(){}
	person(int x, int y, int id): x(x), y(y), id(id){}
};

person changeP[100000];
int _totP;

const int bloSize = 8;

class Block
{
public:
	set<person> t[1 << bloSize];
	set<person> total;
	int xl, xr;
	void insert(const person p)
	{
		total.insert(p);
		t[p.x & ((1 << bloSize) - 1)].insert(p);
	}
	void query(int ylow, int yhigh)
	{
		set<person>::iterator c = total.lower_bound(person(0, ylow, 0));
		int start = _totP;
		for(; c != total.end() && (*c).y <= yhigh; c++)
		{
			changeP[_totP++] = *c;
			//ret.push_back(*c);
		//	printf("Aquired %d\n", (*c).id + 1);
		}
		for(int i = start; i < _totP; ++i)
			total.erase(changeP[i]), t[changeP[i].x & ((1 << bloSize) - 1)].erase(changeP[i]);
	}
	void partquery(int xlow, int xhigh, int ylow, int yhigh)
	{
		xlow = max(xlow, xl);
		xhigh = min(xhigh, xr);
		xlow = xlow & ((1 << bloSize) - 1);
		xhigh = xhigh & ((1 << bloSize) - 1);
		int start = _totP;
		for(int x = xlow; x <= xhigh; ++x)
		{
			set<person>::iterator c = t[x].lower_bound(person(0, ylow, 0));
			for(; c != t[x].end() && (*c).y <= yhigh; c++)
			{
				changeP[_totP++] = *c;
			//	ret.push_back(*c);
			//	printf("Aquired %d\n", (*c).id + 1);
			}
		}
		for(int i = start; i < _totP; ++i)
			total.erase(changeP[i]), t[changeP[i].x & ((1 << bloSize) - 1)].erase(changeP[i]);
	}
	void clear()
	{
		total.clear();
		for(int i = 0; i < (1 << bloSize); ++i)
			t[i].clear();
	}
	void getAll()
	{
		for(set<person>::iterator c = total.begin(); c != total.end(); c++)
			changeP[_totP++] = *c;//.push_back((*c));
	}
};

Block blo[1 << bloSize];

int n, q, w, h;

bool cmp(const person &a, const person &b)
{
	return a.id < b.id;
}

int main()
{
	int T;
	read(T);
	for(int i = 0; i < (1 << bloSize); ++i)
	{
		blo[i].xl = i * (1 << bloSize);
		blo[i].xr = blo[i].xl + (1 << bloSize) - 1;
	}
	for(int cas = 1; cas <= T; ++cas)
	{
		for(int i = 0; i < (1 << bloSize); ++i)
			blo[i].clear();
		read(n);
		read(q);
		read(w);
		read(h);
		for(int i = 0; i < n; ++i)
		{
			int x, y;
			read(x);
			read(y);
			person p = person(x + y, x - y, i);
			blo[(p.x >> bloSize)].insert(p);
		}
		for(int i = 0; i < q; ++i)
		{
			_totP = 0;
		//	printf("Query %d\n", i);
			int x, y, E, a, b, c, d, e, f;
			read(x); read(y); read(E);
			read(a); read(b); read(c); read(d); read(e); read(f);
			//scanf("%d%d%d", &x, &y, &E);
			//scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f);
			int nx, ny;
			nx = x + y, ny = x - y;
			x = nx, y = ny;
			int l = x - E, r = x + E;
			for(int j = (max(l, 0) >> bloSize); j < (1 << bloSize) && blo[j].xl <= r; ++j)
			{
				int curL = blo[j].xl;
				if(curL >= l && curL + (1 << bloSize) - 1 <= r)
				{
					blo[j].query(y - E, y + E);
				}
				else
				{
					if(l >= curL && l <= curL + (1 << bloSize) - 1)
					{
						blo[j].partquery(l, r, y - E, y + E);
					}
					else if(r >= curL && r <= curL + (1 << bloSize) - 1)
					{
						blo[j].partquery(l, r, y - E, y + E);
					}
				}
			}
			for(int j = 0; j < _totP; ++j)
			{
				int nx, ny, id;
				nx = changeP[j].x + changeP[j].y;
				ny = changeP[j].x - changeP[j].y;
				nx /= 2, ny /= 2;
				id = changeP[j].id;
				int x, y;
				x = (1LL * nx * a + 1LL * ny * b + 1LL * (id + 1) * c) % w;
				y = (1LL * nx * d + 1LL * ny * e + 1LL * (id + 1) * f) % h;
				x %= w;
				y %= h;
			//	printf("TransForm %d (%d, %d) -> (%d, %d)\n", 1 + id, nx, ny, x, y);
				blo[(x + y) >> bloSize].insert(person(x + y, x - y, id));
			}
		}
		printf("Case #%d:\n", cas);
		_totP = 0;
		for(int i = 0; i < (1 << bloSize); ++i)
			blo[i].getAll();
		sort(changeP, changeP + _totP, cmp);
		for(int i = 0; i < _totP; ++i)
		{
			int nx = changeP[i].x + changeP[i].y;
			int ny = changeP[i].x - changeP[i].y;
			nx /= 2;
			ny /= 2;
			printf("%d %d\n", nx, ny);
		}
	}
	return 0;
}
