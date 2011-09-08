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

public class ConsoleIO {
    public static void main(String args[]){
        Console console=System.console();
        String string, password, temp;

        if(console==null){
            System.err.println("No console available.");
            return;
        }
        
        string=console.readLine("Enter a string : ");
        console.printf("%s\n", string);
        password=new String(console.readPassword("Enter a password : "));
        temp=new String(console.readPassword("Verify the password : "));
        while(!temp.equals(password)){
            System.err.println("\bPassword not set! Try again please!");
            password=new String(console.readPassword("Enter a password : "));
            temp=new String(console.readPassword("Verify the password : "));
        }

        console.printf("Your password is set!!! Thank you!!!");
    }
}
