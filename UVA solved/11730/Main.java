import java.util.ArrayDeque;
import java.util.Iterator;
import java.util.Vector;
import java.util.Scanner;

public class Main {
    static final int infinity = 1<<14, limit=1002;
    static Vector< Vector<Integer> > divisors = new Vector< Vector<Integer> >(1002);
    static int visit[] = new int[limit];
    static char sieve[]= new char[limit];
    static int i, j, cases=1;

    static void init(int n){
        for(i=0;i<n;i++){
            Vector<Integer> temp = new Vector<Integer>();
            divisors.add(temp);
            sieve[i]=1;
        }

        for(i=2;i<n;i++){
            if(sieve[i]==1) for(j=2*i;j<n;j+=i){
                divisors.elementAt(j).add(i);
                sieve[j]=0;
            }
        }
    }

    static void bfsInit(int S, int T){
        for(i=0;i<=T;i++) visit[i]=infinity;
        visit[S]=0;
    }

    static int bfs(int S, int T){
        ArrayDeque<Integer> deque = new ArrayDeque();
        int u, v;

        bfsInit(S, T);
        deque.add(S);

        while(deque.isEmpty()==false){
            u=deque.getFirst();
            Iterator<Integer> itrInt = divisors.elementAt(u).iterator();

            if(u==T) return visit[T];
            while(itrInt.hasNext()){
                i=itrInt.next();
                v=u+i;
                if(v>=0 && v<=T && visit[v]>visit[u]+1){
                    visit[v]=visit[u]+1;
                    deque.addLast(v);
                }
            }

            deque.removeFirst();
        }
        
        return -1;
    }

    public static void main(String[] args) {
        Main.init(limit);
        Scanner scanner = new Scanner(System.in);
        int S, T;

        while(scanner.hasNextInt()){
            S=scanner.nextInt();
            if(scanner.hasNextInt()==false) break;
            T=scanner.nextInt();
            if(S==0 && T==0) break;

            System.out.print("Case "+ cases++);
            if(S>T) System.out.println(": -1");
            else System.out.println(": "+bfs(S, T));
        }
    }
}
