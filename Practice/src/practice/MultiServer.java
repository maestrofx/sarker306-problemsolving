/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package practice;

/**
 *
 * @author User
 */
import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import java.io.*;
import java.net.*;
import java.util.Scanner;

public class MultiServer {

    private static ServerSocket serverSocket;
    private static final int PORT = 1238;
    static ClientHandler handler[] = new ClientHandler[20];

    public static void main(String[] args)
            throws IOException {
        int ii = 1;
        try {
            serverSocket = new ServerSocket(PORT, 100);
        } catch (IOException ioEx) {
            System.out.println("\nUnable to set up port!");
            System.exit(1);
        }
        do {

            Socket client = serverSocket.accept();
            System.out.println("\nNew client accepted.\n");

            handler[ii] = new ClientHandler(client, ii);
            handler[ii].start();//As usual, method calls run.
            ii++;
        } while (true);
    }

    static class ClientHandler extends Thread {

        Socket client;
        private ObjectOutputStream output; // output stream to client
        private ObjectInputStream input;
        int pos;
        String msg;
        String received;

        public ClientHandler(Socket socket, int k) {
            //Set up reference to associated socket...
            client = socket;
            pos = k;
            try {
                output = new ObjectOutputStream(client.getOutputStream());
                output.flush();


                input = new ObjectInputStream(client.getInputStream());
            } catch (IOException eofException) {
                System.out.println("Error");

            }


        }

        public void run() {


            do {
                try {
                    received = (String) input.readObject();
                    System.out.println(received + "from " + pos);

                } // end try
                catch (ClassNotFoundException classNotFoundException) {
                    System.out.printf("\nUnknown object type received\n");
                } catch (IOException eofException) {
                    System.out.println("Error");

                }

            } while (!received.equals("quit"));
        }
    }
}

