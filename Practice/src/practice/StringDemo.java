/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package practice;

/**
 *
 * @author avijit_2
 */
import java.util.*;
import java.io.*;

public class StringDemo {
    public static void main(String args[]){
        StringBuffer stringbuffer;
        Scanner scanner=new Scanner(System.in);
        PrintWriter printwriter=new PrintWriter(System.out, true);

        while(scanner.hasNextLine()){
            stringbuffer=new StringBuffer(scanner.nextLine());
            printwriter.print(stringbuffer);
            printwriter.println("  "+stringbuffer.capacity()
                    +' '+stringbuffer.length());
            printwriter.println(stringbuffer.reverse());
        }
    }
}
