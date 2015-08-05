#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

const int Maxn = 51000;
const int Population = 200;
const int MaxGen = 200;
const double mutation = 0.8;
const double crossProb = 0.5;

int BagCap, n, p;
class share
{
public:
	long long cost, income;
};
share stock[510], geneInput[Maxn];
vector<share> gene;

class individual
{
public:
	long long fitness;
	long long weight;
	vector<bool> chromosome;
	void init()
	{
		fitness = weight = 0;
		chromosome.clear();
	}
	individual(){init();}
	bool operator < (const individual &b) const
	{
		return fitness > b.fitness;
	}
	bool calcFit()
	{
		fitness = weight = 0;
		for(int i = 0; i < gene.size(); ++i)
		{
			if(chromosome[i])
			{
				fitness += gene[i].income - gene[i].cost;
				weight += gene[i].cost;
			}
		}
		return weight <= BagCap;
	}
	bool randomGen()
	{
		chromosome.resize(gene.size());
		for(int i = 0; i < gene.size(); ++i)
			chromosome[i] = rand() % 2;
		return calcFit();
	}
};

inline bool probTest(double x)
{
	double res = (double)(rand() % 10000) / 10000;
	return res <= x;
}

vector<individual> oldGen, newGen;

void init()
{
	cin >> n >> p;
	for(int i = 0; i < n; ++i)
		cin >> stock[i].cost >> stock[i].income;
	for(int i = 0; i < p; ++i)
	{
		geneInput[i].cost = geneInput[i].income = 0;
		int s;
		cin >> s;
		for(int j = 0; j < s; ++j)
		{
			int x, y;
			cin >> x >> y;
			x--;
			geneInput[i].cost += stock[x].cost * y;
			geneInput[i].income += stock[x].income * y;
		}
	}
	gene.clear();
	for(int i = 0; i < p; ++i)
		if(geneInput[i].income - geneInput[i].cost > 0)
			gene.push_back(geneInput[i]);
	oldGen.clear(), newGen.clear();
}

void firstGen()
{
	oldGen.resize(Population);
	newGen.resize(Population);
	for(int i = 0; i < n; ++i)
	{
		while(!oldGen[i].randomGen());
	}
}

int selection()
{
	long long sum = 0;
	for(int i = 0; i < Population; ++i)
		sum += oldGen[i].fitness;
	long long rnd = 1LL * rand() * rand() % sum;
	long long tmpSum = 0;
	for(int i = 0; i < p; ++i)
	{
		if(rnd >= tmpSum && rnd < tmpSum + oldGen[i].fitness)
			return i;
		tmpSum += oldGen[i].fitness;
	}
	assert(false);
	return -1;
}

void cross(const individual &parent1, const individual &parent2, int target)
{
	int pos = -1;
	if(probTest(crossProb))
	{
		pos = rand() % gene.size();
	}
	if(pos == -1)
		newGen[target] = parent1;
	else
	{
		newGen[target].chromosome.resize(gene.size());
		for(int i = 0; i < pos; ++i)
			newGen[target].chromosome[i] = parent1.chromosome[i];
		for(int i = pos; i < gene.size(); ++i)
			newGen[target].chromosome[i] = parent2.chromosome[i];
	}
}
void performMutation(individual &target)
{
	for(int i = 0; i < gene.size(); ++i)
	{
		if(probTest(mutation))
			target.chromosome[i] = rand() % 2;
	}
}

void generation()
{
	int curPopulation = 0;
	while(curPopulation < Population)
	{
		bool succ = false;
		while(!succ)
		{
			int parent1 = selection();
			int parent2 = selection();
			cross(oldGen[parent1], oldGen[parent2], curPopulation);
			performMutation(newGen[curPopulation]);
			if(newGen[curPopulation].calcFit())
				break;
		}
		curPopulation++;
	}
}

bool better(const vector<individual> &oldGen, const vector<individual> &newGen)
{
	long long mxOld = -1, mxNew = -1;
	for(int i = 0; i < Population; ++i)
	{
		mxOld = max(mxOld, oldGen[i].fitness);
		mxNew = max(mxNew, newGen[i].fitness);
	}
	return mxNew > mxOld;
}

int main()
{
	srand(time(0));
	ios::sync_with_stdio(false);
	while(cin >> BagCap)
	{
		init();
		firstGen();
		for(int gen = 1; gen < MaxGen; ++gen)
		{
			generation();
			if(better(newGen, oldGen))
				oldGen = newGen;
		}

		long long ans = -1;
		for(int i = 0; i < Population; ++i)
			ans = max(ans, oldGen[i].fitness);
		cout << ans << endl << endl;
	}
	return 0;
}