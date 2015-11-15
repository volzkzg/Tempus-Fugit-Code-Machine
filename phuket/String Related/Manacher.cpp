char t[1001];       // 要处理的字符串
char s[1001 * 2];   // 中间插入特殊字符以后的
int Z[1001 * 2], L, R;  // Gusfield's Algorithm
// 由a往左，由b往右，对称地做字符匹配
int match(int a, int b){
    int i = 0;
    while (a - i >= 0 && b + i < n && s[a - i] == s[b + i]) i++;
    return i;
}
void longest_palindromic_substring()
{
    int N = strlen(t); 
    /* 在 t 中插入特殊字符，存放到 s*/ memset(s, '.', N*2+1);
    for (int i = 0; i < N; ++i) s[i * 2 + 1] = t[i];
    N = N * 2 + 1;
    Z[0] = 1; L = R = 0;
    for (int i = 1; i < N; ++i) {
        int ii = L - (i - L), n = R + 1 - i;   // i的映射位
        if (i > R) Z[i] = match(i, i), L = i, R = i + Z[i] - 1;
        else if (Z[ii] == n) Z[i] = n + match(i-n, i+n), L = i, R = i + Z[i] - 1;
        else Z[i] = min(Z[ii], n);
    }
    // 尋找最長迴文子字串的長度。
    int n = 0, p = 0;
    for (int i=0; i < N; ++i) if(Z[i] > n) n = Z[p = i];
    // 記得去掉特殊字元。
    cout << "最長迴文子字串的長度是" << (n - 1) / 2;
    // 印出最長迴文子字串，記得別印特殊字元。
    for (int i = p - Z[p] + 1; i <= p + Z[p] - 1; ++i) if (i & 1) cout << s[i];
}