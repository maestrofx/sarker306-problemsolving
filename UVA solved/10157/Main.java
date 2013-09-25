import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    private static BigInteger[][] dp = new BigInteger[301][];
    private static int n, k;
    private static Integer tmp;

    private static void Init(){
        for ( int i = 0 ; i < dp.length ; i++ ){
            dp[i] = new BigInteger[151];
            for ( int j = 0 ; j < dp[i].length ; j++ ) dp[i][j] = BigInteger.ZERO;
        }

		for ( int j = 0 ; j < dp[0].length ; j++ ) dp[0][j] = BigInteger.ONE;
		
        for ( int n = 2 ; n < dp.length ; n += 2 ){
            for ( int d = 1 ; d < dp[n].length ; d++ ){
                for ( int k = 2 ; k <= n  ; k += 2 ) 
                    dp[n][d] = dp[n][d].add(dp[k-2][d-1].multiply(dp[n-k][d]));
            }
        }
    }

    public static void main(String[] args){
        Init();

        Scanner scn = new Scanner(System.in);
        while ( scn.hasNextInt() ){
            n = scn.nextInt();
            k = scn.nextInt();
            System.out.println(dp[n][k].subtract(dp[n][k-1]));
        }
    }
}
