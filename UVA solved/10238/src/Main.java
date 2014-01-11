/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Avijit
 */
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
    private static boolean[][][] visited;
    private static BigInteger[][][] ways;

    private static BigInteger getWays( int faces, int nThrows, int sum ){
        BigInteger res = BigInteger.ZERO;
        int i;

        if ( nThrows == 0 && sum == 0 ) return BigInteger.ONE;
        if ( sum == 0 || nThrows == 0 ) return BigInteger.ZERO;
        if ( visited[faces][nThrows][sum] ) return ways[faces][nThrows][sum];

        visited[faces][nThrows][sum] = true;
        for ( i = 1 ; i <= faces ; i++ ) {
            if ( sum < i ) break;
            res = res.add(getWays(faces, nThrows - 1, sum - i));
        }

        return ways[faces][nThrows][sum] = res;
    }

    private static void initArray(){
        ways = new BigInteger[51][][];
        visited = new boolean[51][][];
        for ( int i = 0 ; i <= 50 ; i++ ){
            visited[i] = new boolean[51][];
            ways[i] = new BigInteger[51][];
            for ( int j = 0 ; j <= 50 ; j++ ){
                visited[i][j] = new boolean[4001];
                ways[i][j] = new BigInteger[4001];
                for ( int k = 0 ; k <= 4000 ; k++ ){
                    visited[i][j][k] = false;
                    ways[i][j][k] = BigInteger.ZERO;
                }
            }
        }
    }

    public static void main(String[] args) {
        int faces, nThrows, sum;
        Scanner scn = new Scanner ( System.in );
        initArray();

        while ( scn.hasNextInt() ){
            faces = scn.nextInt();
            nThrows = scn.nextInt();
            sum = scn.nextInt();
            System.out.println(getWays(faces, nThrows, sum) + "/"
                    + BigInteger.valueOf(faces).pow(nThrows));
        }
    }
}
