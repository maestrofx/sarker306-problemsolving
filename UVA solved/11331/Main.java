import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

/**
 *
 * @author Avijit
 */
enum Color{NONE, WHITE, BLACK};

class JoyOfFarming {
    private ArrayList<ArrayList<Integer> > adj;
    private ArrayList<Integer>Whites, Size;
    private int bulls, cows, total;
    private Color[] color;
    private boolean[] dp;

    JoyOfFarming() {
        adj = new ArrayList<ArrayList<Integer> >();
        color = new Color[2002];
        dp = new boolean[2002];
    }

    public void init(int b, int c){
        bulls = b;
        cows = c;
        total = b + c;
        Size = new ArrayList<Integer>();
        Whites = new ArrayList<Integer>();

        for ( int i = 0 ; i <= total ; i++ ) {
            color[i] = Color.NONE;
            dp[i] = false;
            adj.add(new ArrayList<Integer>());
        }
    }

    public void addEdge(int u, int v) {
        adj.get(u).add(v);
        adj.get(v).add(u);
    }

    public boolean calculate() {
        for ( int i = 1 ; i <= total ; i++ ) {
            if ( color[i] != Color.NONE ) continue;
            if (runBFS(i) == false ) return false;
        }

        dp[0] = true;
        for ( int i = 0 ; i < Whites.size() ; i++ ) {
            for ( int j = 2000 ; j > 0 ; j-- )
                if ( j - Whites.get(i) >= 0 && dp[j - Whites.get(i)]) dp[j] = true;
                else if ( j - Size.get(i) + Whites.get(i) >= 0 && dp[j - Size.get(i) + Whites.get(i)]) dp[j] = true;
                else dp[j] = false;
        }
        return dp[bulls] & dp[cows];
    }

    private boolean runBFS(int start){
        int whiteCnt = 1, totalCnt = 1;
        ArrayList<Integer>queue = new ArrayList<Integer>();
        queue.add(start);
        color[start] = Color.WHITE;

        while ( queue.isEmpty() == false ){
            int u = queue.get(0);
            queue.remove(0);

            Iterator<Integer> itr = adj.get(u).iterator();
            while ( itr.hasNext() ){
                int v = itr.next();
                if ( color[v] == Color.NONE ){
                    color[v] = ( color[u] == Color.BLACK ) ? Color.WHITE : Color.BLACK;
                    queue.add(v);
                    if ( color[v] == Color.WHITE ) whiteCnt++;
                    totalCnt++;
                }
                else if ( color[v] == color[u] ) return false;
            }
        }

        Whites.add(whiteCnt);
        Size.add(totalCnt);
        return true;
    }

    public void clear(){
        for ( int i = 0 ; i <= total ; i++ ) adj.get(i).clear();
        Size.clear();
        Whites.clear();
        adj.clear();
    }
}

public class Main {
     public static void main(String[] args){
         JoyOfFarming cls = new JoyOfFarming();
         int test;
         Scanner scn = new Scanner(System.in);

         while ( scn.hasNextInt() ){
             test = scn.nextInt();
             while ( test-- > 0 ) {
                 int b, c, a;
                 b = scn.nextInt();
                 c = scn.nextInt();
                 a = scn.nextInt();
                 cls.init(b, c);
                 while ( a-- > 0 ) {
                     int u, v;
                     u = scn.nextInt();
                     v = scn.nextInt();
                     cls.addEdge(u, v);
                 }

                 System.out.println(cls.calculate() ? "yes" : "no");
                 cls.clear();
             }
         }
    }
}
