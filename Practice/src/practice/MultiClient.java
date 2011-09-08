/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package practice;
import java.io.*;
import java.net.*;
import java.util.*;


/**
 *
 * @author User
 */
public class MultiClient {

    private static InetAddress host;
    private static final int PORT = 1238;
    private static ObjectOutputStream output; // output stream to server
    private static ObjectInputStream input;
    private static String send;

    public static void main(String[] args) {
        try {
            host = InetAddress.getLocalHost();
        } catch (UnknownHostException uhEx) {
            System.out.println("\nHost ID not found!\n");
            System.exit(1);
        }
        sendMessages();
    }

    private static void sendMessages() {
        Socket socket = null;

        try {
            socket = new Socket(host, PORT);
        } catch (IOException ioEx) {
            System.out.println("\nUnable to set up port!");
            System.exit(1);
        }

        try {
            output = new ObjectOutputStream(socket.getOutputStream());
            output.flush(); // flush output buffer to send header information

            // set up input stream for objects
            input = new ObjectInputStream(socket.getInputStream());
        } catch (IOException eofException) {
            System.out.println("Error");
            // displayMessage( "\nServer terminated connection" );
        }
        // e
        do {

            try {

                Scanner inp = new Scanner(System.in);
                send = inp.nextLine();

                output.writeObject("CLIENT>>> " + send);
                output.flush(); // flush data to output

            }// end try
            catch (IOException ioException) {
                System.out.printf("\nError writing object");
            }
        } while (!send.equals("quit"));
        try {
            output.close(); // close output stream
            input.close(); // close input stream  1
            socket.close(); // close socket
        } // end try
        catch (IOException ioException) {
            ioException.printStackTrace();
        }

    }
}
