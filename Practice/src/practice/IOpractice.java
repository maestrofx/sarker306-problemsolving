package practice;

/**
 *
 * @author avijit_2
 *
 */

import java.io.*;

// implements Character stream classes...

public class IOpractice {
    public static void main(String args[]) throws IOException {
        BufferedReader bufferedreader = new BufferedReader(
                new InputStreamReader (System.in));
        //PrintWriter printwriter = new PrintWriter( System.out, true );
        BufferedWriter bufferedwriter=new BufferedWriter(
                new OutputStreamWriter(System.out));
        String string;
        long number;

        do{
            string=bufferedreader.readLine();
            if(string.equals("ESC")) break;

            try{
                number=Long.parseLong(string);
            } catch(NumberFormatException nfe){
                System.err.println("Invalid Number");
                number=-1;
            }
            bufferedwriter.write(Long.toString(number)+'\n');
            //printwriter.println(number);
        }while( true );

        bufferedwriter.flush();
    }
}
