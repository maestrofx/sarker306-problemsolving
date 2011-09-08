/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package practice;
import java.math.BigInteger;
import java.util.*;
import java.util.Map.Entry;
import java.util.Random.*;

/**
 *
 * @author Avijit
 */
public class CollectionDemo {
    public static void main(String args[]){
        // ArrayList

        System.out.println("ArrayList implementation:\n");
        ArrayList arraylist = new ArrayList<String>(100);
        arraylist.add("Everytime");
        arraylist.add(" I kiss,");
        arraylist.add("Deam.");
        arraylist.add(2, " I kiss the");

        System.out.println("Size of arraylist : "+arraylist.size());
        System.out.println("Contents of arraylist : "+arraylist);

        System.out.println("Element at position 3 : "
                +arraylist.get(3));
        arraylist.set(3, "Death.");
        System.out.println("Now, element at position 3 : "
                +arraylist.get(3));

        System.out.println("Contents of arraylist (using array ) : ");
        String []arrStr=new String[arraylist.size()];
        arrStr=(String[]) arraylist.toArray(arrStr);
        for(String str : arrStr) System.out.print(str+" ");
        System.out.println("");

        System.out.println("Contents of arraylist (using iterator ) : ");
        Iterator<String> iteratorStr=arraylist.iterator();
        while(iteratorStr.hasNext()) System.out.print(iteratorStr.next()+" ");
        System.out.println();

        arraylist.clear();

        // LinkedList

        System.out.println();
        System.out.println("LinkedList implementation:\n");
        LinkedList<Integer> linkedlist = new LinkedList<Integer>();
        linkedlist.add(new Integer(88));
        linkedlist.addFirst(306);
        linkedlist.addLast(45);
        linkedlist.add(0, -15);

        System.out.println("Size of linkedlist : "+linkedlist.size());
        System.out.println("Contents of linkedlist : "+linkedlist);

        System.out.println("Element at position 3 : "
                +linkedlist.get(3));
        linkedlist.set(3, 44);
        System.out.println("Now, element at position 3 : "
                +linkedlist.get(3));

        System.out.println("Contents of arraylist (using for-each ) : ");
        for(Integer integer : linkedlist) System.out.print(integer+" ");
        System.out.println();

        linkedlist.clear();

        // HashSet, LinkedHashSet, TreeSet

        System.out.println();
        System.out.println("HashSet, LinkedHashSet, TreeSet implementation:\n");
        HashSet<Double> hashset = new HashSet<Double>(10, (float) 0.5);
        LinkedHashSet<Double> linkedhashset = new LinkedHashSet<Double>(10, (float) 0.5);
        TreeSet<Double> treeset = new TreeSet<Double>();
        Random random = new Random();

        hashset.add(new Double(45.3258));
        linkedhashset.add(new Double(45.3258));

        for(int i=0; i<15;i++){
            Double value = random.nextDouble()*100;
            hashset.add(value);
            linkedhashset.add(value);
        }

        treeset.addAll(hashset);

        System.out.println("Size of the sets : "+hashset.size());
        System.out.println("Contents of hashset (using iterator ) : ");
        Iterator<Double> iteratorDouble=hashset.iterator();
        while(iteratorDouble.hasNext())
            System.out.print(iteratorDouble.next()+" ");
        System.out.println();

        System.out.println("Contents of linkedhashset,"
                +"In order of input (using iterator ) : ");
        iteratorDouble=linkedhashset.iterator();
        while(iteratorDouble.hasNext())
            System.out.print(iteratorDouble.next()+" ");
        System.out.println();

        System.out.println("Contents of treeset, Sorted (using iterator ) : ");
        iteratorDouble=treeset.iterator();
        while(iteratorDouble.hasNext())
            System.out.print(iteratorDouble.next()+" ");
        System.out.println();
        
        System.out.println("hashset contains 45.3258 : "
                +hashset.contains(45.3258));
        System.out.println("hashset contains 325.154 : "
                +hashset.contains(325.154));

        hashset.remove(45.3258);
        System.out.println("45.3258 Removed. hashset contains 45.3258 : "
                +hashset.contains(45.3258));
        
        hashset.clear();
        linkedhashset.clear();
        treeset.clear();

        // ArrayDeque

        System.out.println();
        System.out.println("ArrayDeque implementation:\n");
        ArrayDeque<BigInteger> arraydeque = new ArrayDeque<BigInteger>();
        arraydeque.addFirst(new BigInteger("15"));
        arraydeque.addLast(new BigInteger("45"));
        arraydeque.addLast(BigInteger.ONE);
        arraydeque.addLast(BigInteger.TEN);
        arraydeque.addFirst(BigInteger.ZERO);

        while(arraydeque.isEmpty()==false){
            System.out.print(arraydeque.poll()+" ");
        }
        System.out.println();

        // HashMap, LinkedHashMap, TreeMap

        System.out.println();
        System.out.println("HashMap, LinkedHashMap, TreeMap implementation:\n");
        HashMap<String, String> hashmap = new HashMap<String, String>();
        LinkedHashMap<String, String> linkedhashmap = new LinkedHashMap<String, String>();
        TreeMap<String, String> treemap = new TreeMap<String, String>();

        String in = "Milu:Hasan-Al-Maruf;"+"Jehad:Mohammad Hafiz Uddin;"
                +"Galib:Sharif Mohammad Saad;"+"Irteza:Irteza Nasir;"
                +"Avi:Avijit Sarker;"+"Linkin:Prasanjit Barua;"
                +"Radi:Radi Muhammad Reza;"+"Aula:Tazbinur Shovon";
        StringTokenizer stringtokenizer = new StringTokenizer(in, ":;");

        while(stringtokenizer.hasMoreTokens()){
            String key = stringtokenizer.nextToken();
            String value = stringtokenizer.nextToken();

            hashmap.put(key, value);
            linkedhashmap.put(key, value);
        }

        treemap.putAll(hashmap);

        System.out.println("Size of the maps : "+hashmap.size());
        Set< Map.Entry<String, String> >entryset;
        entryset = hashmap.entrySet();
        System.out.println("\nContents of hashmap (using for-each loop) :");
        for( Entry<String, String> me : entryset)
            System.out.println(me.getKey()+" : "+me.getValue());

        entryset = linkedhashmap.entrySet();
        System.out.println("\nContents of linkedhashmap, Input-order (using for-each loop) :");
        for( Entry<String, String> me : entryset)
            System.out.println(me.getKey()+" : "+me.getValue());

        entryset = treemap.entrySet();
        System.out.println("\nContents of treemap, Sorted (using for-each loop) :");
        for( Entry<String, String> me : entryset)
            System.out.println(me.getKey()+" : "+me.getValue());

        hashmap.clear();
        treemap.clear();
        linkedhashmap.clear();
    }
}
