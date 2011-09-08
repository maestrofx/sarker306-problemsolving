package practice;

import java.io.*;
import java.net.*;
import java.util.Scanner;

public class MultiEchoServer {

    private static ServerSocket serverSocket;
    private static final int PORT = 1456;
    static ClientHandler handler[] = new ClientHandler[20];

    public static void main(String[] args)
            throws IOException {
        int ii = 0;
        try {
            serverSocket = new ServerSocket(PORT);
        } catch (IOException ioEx) {
            System.out.println("\nUnable to set up port!");
            System.exit(1);
        }
        do {
            //Wait for client...
            Socket client = serverSocket.accept();
            System.out.println("\nNew client accepted.\n");
            //Create a thread to handle communication with
            //this client and pass the constructor for this
            //thread a reference to the relevant socket...
            handler[ii] = new ClientHandler(client, ii);
            handler[ii].start();//As usual, method calls run.
            ii++;
        } while (true);
    }

    static class ClientHandler extends Thread {

        Socket client;
        Scanner input;
        PrintWriter output;
        int pos;
        String msg;

        public ClientHandler(Socket socket, int k) {
            //Set up reference to associated socket...
            client = socket;
            pos = k;
            try {
                input = new Scanner(client.getInputStream());
                output = new PrintWriter(
                        client.getOutputStream(), true);
            } catch (IOException ioEx) {
                ioEx.printStackTrace();
            }
        }

        public void run() {
            String received;
            do {
                //Accept message from client on
                //the socket's input stream...
                if(input.hasNext()==false) break;
                received = input.nextLine();

                if(received.equals("QUIT")==true) break;
                System.out.println("Client "+(pos+1)+" : "+received);
                output.println("Client "+(pos+1)+" : "+received);
                output.flush();

                //Echo message back to client on
                //the socket's output stream...QUIT

                //Repeat above until 'QUIT' sent by client...
            } while (true);
            try {
                if (client != null) {
                    System.out.println(
                            "Closing down connection...");
                    client.close();
                }
            } catch (IOException ioEx) {
                System.out.println("Unable to disconnect!");
            }
        }
    }
}
