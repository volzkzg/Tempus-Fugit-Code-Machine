#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 1000010;
struct Node {
    int c1, c2;
}data[N];
int T, n, a[N];
int *b[N];
//vector<int> L[N], R[N];
int L_merge[N], R_merge[N];
bool L_vis[N], R_vis[N];
int L_size, R_size;

class list
{
public:
	int head[N], end[N];
	int nxt[N];
	int data[N], tot, size[N];
	void init(int n)
	{
		tot = 0;
		for(int i = 0; i <= n; ++i)
			head[i] = nxt[i] = end[i] = -1, size[i] = 0;
	}
	void add(int x, int dat)
	{
		if(head[x] == -1)
		{
			head[x] = end[x] = tot++;
		}
		else
			nxt[end[x]] = tot, end[x] = tot++;
		data[end[x]] = dat;
		size[x]++;
	}
};

list L, R;

bool cmp(const int *u, const int *v) {
    return (*u < *v);
}

int process()
{
    sort(b, b + n, cmp);
    
    int pre = *b[0]; *b[0] = 1;
    for(int i = 1; i < n; ++i) {
        if(pre != *b[i]) {
            pre = *b[i];
            *b[i] = *b[i - 1] + 1;
        }
        else
            *b[i] = *b[i - 1];
    }
    return (*b[n - 1]);
}

void L_disposal(int );
void R_disposal(int );

void L_disposal(int u)
{
    L_vis[u] = true;
    //for (int i = 0; i < (int)L[u].size(); ++i) {
    for (int i = L.head[u]; i != -1; i = L.nxt[i]) {
        //int v = data[L[u][i]].c2;
        int v = data[L.data[i]].c2;
        if (!R_vis[v])
            R_disposal(v);
    }
}

void R_disposal(int u)
{
    R_vis[u] = true;
    //for (int i = 0; i < (int)R[u].size(); ++i) {
    for (int i = R.head[u]; i != -1; i = R.nxt[i]) {
    //    int v = data[R[u][i]].c1;
    	int v = data[R.data[i]].c1;
        if (!L_vis[v])
            L_disposal(v);
    }
}

int main()
{
    scanf("%d", &T);
    for (int tst = 1; tst <= T; ++tst) {
        printf("Case #%d: ", tst);
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d%d", &data[i].c1, &data[i].c2);
        
        for (int i = 1; i <= n; ++i)
            b[i - 1] = &(data[i].c1);
        L_size = process();
        for (int i = 1; i <= n; ++i)
            b[i - 1] = &(data[i].c2);
        R_size = process();
		
		L.init(n);
		R.init(n);
        for (int i = 1; i <= L_size; ++i)
        {
            L_merge[i] = 0, L_vis[i] = false;
        }
        for (int i = 1; i <= R_size; ++i)
        {
            R_merge[i] = 0, R_vis[i] = false;
        }
        int left_set, right_set;
        for (int i = 1; i <= n; ++i) {
            left_set = data[i].c1;
            right_set = data[i].c2;
            //L[left_set].push_back(i);
            //R[right_set].push_back(i);
            L.add(left_set, i);
            R.add(right_set, i);
            if (L_merge[left_set] == 0)
                L_merge[left_set] = right_set;
            else if (L_merge[left_set] != right_set)
                L_merge[left_set] = -1;
            if (R_merge[right_set] == 0)
                R_merge[right_set] = left_set;
            else if (R_merge[right_set] != left_set)
                R_merge[right_set] = -1;
        }

        int merge, split, one;
        merge = split = one = 0;

        for (int i = 1; i <= L_size; ++i) {
            if (L_vis[i]) continue;
            if (L_merge[i] > 0) {
                bool flag = true;
                int pivot = L_merge[i];

                if (R_merge[pivot] == i && /*R[pivot].size()*/ R.size[pivot] == /*L[i].size()*/ L.size[i]) {
                    one++;
                } else {
                    //for (int j = 0; j < (int)R[pivot].size(); ++j) {
                    for (int j = R.head[pivot]; j != -1; j = R.nxt[j]) {
                        //int pos = data[R[pivot][j]].c1;
                        int pos = data[R.data[j]].c1;
                        if (L_merge[pos] == -1 || L_merge[pos] != pivot) {
                            flag = false;
                            break;
                        }
                    }
                    if (flag) {
                        merge++;
                    }
                }
                L_disposal(i);
            }
        }

        for (int i = 1; i <= R_size; ++i) {
            if (R_vis[i]) continue;
            if (R_merge[i] > 0) {
                bool flag = true;
                int pivot = R_merge[i];

                //if (L_merge[pivot] == i && L[pivot].size() == R[i].size()) {
                if (L_merge[pivot] == i && L.size[pivot] == R.size[i]) {
                    one++;
                } else {
                    //for (int j = 0; j < (int)L[pivot].size(); ++j) {
                    for (int j = L.head[pivot]; j != -1; j = L.nxt[j]) {
                        //int pos = data[L[pivot][j]].c2;
                        int pos = data[L.data[j]].c2;
                        if (R_merge[pos] == -1 || R_merge[pos] != pivot) {
                            flag = false;
                            break;
                        }
                    }
                    if (flag) {
                        split++;
                    }
                }
                R_disposal(i);
            }
        }

        printf("%d %d %d\n", split, merge, one);
    }
    
    return 0;
}
