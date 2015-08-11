import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
        public static void init() {
                val = new int[N];
                num = new int[N];
                times = new BigInteger[N];
                C = new BigInteger[N][N];

                val[1] = 0;
                for (int i = 2; i < N; ++i)
                        val[i] = val[i / 2] + val[i - i / 2] + i - 1;

                C[0][0] = BigInteger.ONE;
                for (int i = 1; i < N; ++i) {
                        C[i][0] = BigInteger.ONE;
                        C[i][i] = BigInteger.ONE;
                        for (int j = 1; j < i; ++j)
                                C[i][j] = C[i - 1][j].add(C[i - 1][j - 1]);
                }
                times[1] = BigInteger.ONE;
                for (int i = 2; i < N; ++i) {
                        int x = (1 + i) / 2;
                        int y = i - x;
                        times[i] = BigInteger.valueOf(2);
                        times[i] = times[i].multiply(C[i - 2][x - 1]);
                        times[i] = times[i].multiply(times[x].multiply(times[y]));
                }
                for (int i = 1; i <= n; ++i)
                        num[i] = i;
        }

        public static void ConstructAns(int L, int R) {
                if (L == R) return;
                int mid = (L + R) / 2;
                int tmp = num[R - 1];
                for (int i = R - 1; i >= mid + 1; --i)
                        num[i] = num[i - 1];
                num[mid] = tmp;
                ConstructAns(L, mid);
                ConstructAns(mid + 1, R);
        }

        public static void main(String[] args) throws IOException {
                PrintStream console = System.out;
                BufferedInputStream in = new BufferedInputStream(new FileInputStream("merge.in"));
                PrintStream out = new PrintStream(new BufferedOutputStream(new FileOutputStream("merge.out")));
                System.setIn(in);
                System.setOut(out);

                Scanner stdin = new Scanner(System.in);
                n = stdin.nextInt();
                init();
                System.out.println(val[n]);
                ConstructAns(1, n);
                for (int i = 1; i <= n; ++i) {
                        System.out.print(num[i]);
                        if (i == n)
                                System.out.println();
                        else
                                System.out.print(" ");
                }
                System.out.println(times[n]);
                out.close();
                System.out.close();
        }

        static int n;
        static int N = 210;
        static int val[], num[];
        static BigInteger times[];
        static BigInteger C[][];
}
