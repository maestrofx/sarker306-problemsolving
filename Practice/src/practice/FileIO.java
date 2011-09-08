/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package practice;

/**
 *
 * @author avijit_2
 */

import java.io.*;

//implements Byte Stream Clases ...

public class FileIO {
    public static void main( String args[] ) throws IOException{
        File f1, f2;
        FileInputStream filein;
        FileOutputStream fileout;
        int n, i=0;

        f1=new File("C:\\Users\\avijit_2\\Desktop\\wannasolve.txt");
        System.out.printf("%s %tc %d\n",
                f1.getAbsolutePath(), f1.lastModified(), f1.length());
        f1.setReadOnly();
        try{
            filein=new FileInputStream(f1);
            fileout=new FileOutputStream(
                    "C:\\Users\\avijit_2\\Desktop\\wannasolve2.txt");
        } catch (FileNotFoundException fnf) {
            System.err.println("File Not Found!!");
            return;
        }

        while( true ){
            try{
                n=(int)filein.read();
                if(n==-1){
                    System.out.println("\nEOF reached!");
                    break;
                }
                //filein.skip(i+1);
            } catch (IOException ioe){
                System.err.println("IOException occurred!!");
                return;
            }

            fileout.write( (char)n );
        }

        filein.close();
        fileout.close();
        f1.delete();
        f2=new File("C:\\Users\\avijit_2\\Desktop\\wannasolve2.txt");
        f2.renameTo(new File( "C:\\Users\\avijit_2\\Desktop\\wannasolve.txt"));
    }
}
