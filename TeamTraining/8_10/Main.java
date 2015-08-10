import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
        public static void main(String[] args) {
                f = new BigInteger[2][1501][1501];
                int n, k;
                Scanner in = new Scanner(System.in);
                n = in.nextInt();
                k = in.nextInt();
                for(int i = 0; i < 2; ++i)
                        for(int j = 0; j < 1501; ++j)
                                for(int t = 0; t < 1501; ++t)
                                        f[i][j][t] = BigInteger.ZERO;
                for(int i = 1; i <= n; ++i) {
                        f[1][i][i] = BigInteger.ONE;
                                for(int j = i - 1; j >= 1; --j)
                                        f[1][i][j] = BigInteger.ONE;
                }
                for(int count = 2; count <= k; ++count) {
                        int cur = (count & 1);
                        int pre = 1 - cur;
                        for(int sum = 1; sum <= n - (k - count); ++sum) {
                                for(int smallest = 1; smallest * count <= sum; ++smallest)
                                        f[cur][sum][smallest] = f[pre][sum - smallest][smallest];
                                if(count != k) {
                                        f[cur][sum][sum / count + 1] = BigInteger.ZERO;
                                        for(int smallest = sum / count; smallest >= 1; --smallest)
                                                f[cur][sum][smallest] = f[cur][sum][smallest].add(f[cur][sum][smallest + 1]);
                                }
                        }
                }
                BigInteger ans;
                ans = BigInteger.ZERO;
                for(int small = 1; small * k <= n; ++small)
                        ans = ans.add(f[k & 1][n][small]);
                System.out.println(ans);
        }
        static BigInteger[][][] f;
}
