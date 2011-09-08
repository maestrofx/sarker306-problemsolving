/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package practice;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import javax.print.Doc;
import javax.print.DocFlavor;
import javax.print.DocPrintJob;
import javax.print.PrintException;
import javax.print.PrintService;
import javax.print.PrintServiceLookup;
import javax.print.SimpleDoc;
import javax.print.attribute.HashPrintRequestAttributeSet;
import javax.print.attribute.PrintRequestAttributeSet;
import javax.print.attribute.standard.Copies;
import javax.print.attribute.standard.MediaSize;
import javax.print.attribute.standard.MediaSizeName;
import javax.print.attribute.standard.Sides;

/**
 *
 * @author Avijit
 */
public class PrintJobDemo {
    public static void main(String args[]){
        FileInputStream fin;

        try{
            fin=new FileInputStream("C:\\Users\\Avijit\\Desktop\\wannasolve.txt");
        } catch (FileNotFoundException fe){
            System.err.println("File pailo na go! Sorry!");
            return;
        }

        DocFlavor docFlavor = DocFlavor.INPUT_STREAM.TEXT_PLAIN_US_ASCII;
        Doc myDoc = new SimpleDoc(fin, docFlavor, null);
        PrintRequestAttributeSet attrSet = new HashPrintRequestAttributeSet();
        attrSet.add(new Copies(2));
        attrSet.add(MediaSizeName.ISO_A4);
        attrSet.add( Sides.DUPLEX );
        PrintService[] services =
                    PrintServiceLookup.lookupPrintServices( docFlavor, attrSet );

        if(services.length>0){
            DocPrintJob job = services[0].createPrintJob();
            try{
                job.print(myDoc, attrSet);
            } catch (PrintException pe){
                System.err.println("Print korar chance pailo na go! Sorry!");
                return;
            }
        }

        System.out.println("Done!");
    }
}
