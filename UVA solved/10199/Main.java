import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.Scanner;
import java.util.Vector;
import java.util.HashMap;
import java.util.StringTokenizer;

class Graph{
    int n;
    Vector< ArrayList<Integer> > adjacent;
    Vector<Integer>finish, start, parent, low;

    Graph(int n){
        adjacent = new Vector< ArrayList<Integer> >();
        finish=new Vector<Integer>();
        start=new Vector<Integer>();
        parent=new Vector<Integer>();
        low=new Vector<Integer>();

        this.n=n;
        for(int i=0;i<n;i++){
            adjacent.add(new ArrayList<Integer> ());
            finish.add(0);
            start.add(0);
            parent.add(-1);
            low.add(0);
        }
    }

    void addEdge(int u, int v){
        adjacent.elementAt(u).add(v);
        adjacent.elementAt(v).add(u);
    }

    void show(){
        Iterator< ArrayList<Integer> > itrArrList = adjacent.iterator();

        while(itrArrList.hasNext()) System.out.println("%% "+itrArrList.next());

        System.out.println(" &"+parent);
        System.out.println(" &"+start);
        System.out.println(" &"+finish);
        System.out.println(" &"+low);
    }
}

class DFSVisit{
    int time;
    Graph graph;

    DFSVisit(Graph g){
        time=0;

        graph=g;
        for(int i=0;i<graph.n;i++){
            if(graph.start.elementAt(i)==0){
                dfs(i);
            }
        }
    }

    private void dfs(int u) {
        int i, v;

        ++time;
        graph.start.set(u, time);
        graph.low.set(u, time);

        Iterator<Integer> itr = graph.adjacent.elementAt(u).iterator();
        while(itr.hasNext()){
            v=itr.next();

            if(graph.start.elementAt(v)==0){
                graph.parent.set(v, u);
                dfs(v);
                if(graph.low.elementAt(v)<=graph.low.elementAt(u))
                    graph.low.set(u, graph.low.elementAt(v));
            }
            else if(v!=graph.parent.elementAt(u)){
                if(graph.start.elementAt(v)<=graph.low.elementAt(u))
                    graph.low.set(u, graph.start.elementAt(v));
            }
        }

        graph.finish.set(u, ++time);
    }
}

class ArticulationPoint{
    int count;
    ArrayList<String>impCities;

    ArticulationPoint(Graph graph, HashMap<Integer, String>cities){
        new DFSVisit(graph);
        count=0;
        int u, v, childrenOfRoot=0, isRoot, isArticulationPoint;
        impCities = new ArrayList<String>();

        for(u=0;u<graph.n;u++){
            isRoot=0;
            childrenOfRoot=0;
            isArticulationPoint=0;

            if(graph.parent.elementAt(u)==-1){
                isRoot=1;
            }

            Iterator<Integer> itrInt=graph.adjacent.elementAt(u).iterator();
            while(itrInt.hasNext()){
                v=itrInt.next();
                if(isRoot!=0 && graph.parent.elementAt(v)==u && v!=u) childrenOfRoot++;

                if(graph.low.elementAt(v)>=graph.start.elementAt(u) && graph.parent.elementAt(v)==u){
                    if(1!=isRoot || childrenOfRoot>1){
                        isArticulationPoint=1;
                        break;
                    }
                }
            }

            if(isArticulationPoint!=0){
                count++;
                impCities.add(cities.get(u));
            }
        }

        if(cities.isEmpty()==false) Collections.sort(impCities);
    }
}

public class Main {
    public static void main(String[] args) {
        int n=0, test=0;
        Scanner scanner = new Scanner(System.in);

        while(scanner.hasNextInt()){
            n=scanner.nextInt();
            if(n<=0) break;
            Graph graph = new Graph(n);
            HashMap<String, Integer> cities = new HashMap<String, Integer>();
            HashMap<Integer, String> cityIndex = new HashMap<Integer, String>();

            scanner.nextLine();
            for(int i=0;i<n;i++){
                String city=scanner.nextLine();
                cities.put(city, i);
                cityIndex.put(i, city);
            }

            /*for(int i=0;i<n;i++){
                System.out.println(i+" "+cityIndex.get(i));
            }*/

            if(scanner.hasNextInt()){
                n=scanner.nextInt();
                scanner.nextLine();
                for(int i=0;i<n;i++){
                    String road=scanner.nextLine();
                    StringTokenizer strtok = new StringTokenizer(road, " ");
                    String city1=strtok.nextToken(" ");
                    String city2=strtok.nextToken(" ");
                    if(cities.containsKey(city1)==true && cities.containsKey(city2)==true){
                        int u=cities.get(city1);
                        int v=cities.get(city2);
                        graph.addEdge(u, v);
                      //  System.out.println("#"+city1+"#"+city2+" "+u+" "+v);
                    }
                }

                ArticulationPoint artCul = new ArticulationPoint(graph, cityIndex);

               // graph.show();
                if(test!=0)System.out.println();
                System.out.printf("City map #%d: %d camera(s) found\n", ++test, artCul.count);

                Iterator<String> itrStr = artCul.impCities.iterator();
                while(itrStr.hasNext()){
                    System.out.println(itrStr.next());
                }
            }

            cities.clear();
            cityIndex.clear();
        }
    }
}
