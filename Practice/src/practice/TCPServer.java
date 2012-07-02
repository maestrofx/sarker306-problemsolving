import java.io.*;
import java.net.*;
import java.util.*;

class TCPServer 
{
	public static void main(String argv[]) throws Exception
	{
		int n;
		String user[]=new String[30];
		String pass[]=new String[30];
		String clientSentence;
		String capitalizedSentence;
		ServerSocket welcomeSocket= new ServerSocket(6789);
		Socket connectionSocket=new Socket();
		BufferedReader inFromClient[]=new BufferedReader[100];
		InputStream inFromClient1[]=new InputStream[100];
		DataOutputStream outToClient[]=new DataOutputStream[100];
		SThread ST[]= new SThread[100];
		for(int i=0;i<100;i++) ST[i] = new SThread();
		try{
		
			FileReader FR=new FileReader("User.txt"); // opening txt file to read list of registered users
			BufferedReader BR=new BufferedReader(FR);
			
			String s=BR.readLine();
			n=Integer.parseInt(s);
			
			for(int i=0;i<n;i++)
			{
				user[i]=BR.readLine();  
				pass[i]=BR.readLine();
			}
			
			FR.close();
		}
		catch(IOException e)
		{
			n = 0;
                        System.out.println("Baler aga");
		}
		ST[0] = new SThread(outToClient,ST,user,pass,n,0);
		for(int j=0;j<100;j++)
		{
			if(j!=0&&ST[j].on==true) ST[j].Set(outToClient,ST);
		}
		
		while (true)
		{
			connectionSocket=welcomeSocket.accept();
			System.out.println("now");
			for(int i=0;i<100;i++) {
				if(ST[i].on==false) {
					
					inFromClient1[i] = connectionSocket.getInputStream();;
					inFromClient[i] = new BufferedReader(new InputStreamReader(inFromClient1[i]));
					outToClient[i]=new DataOutputStream(connectionSocket.getOutputStream());
					ST[i] = new SThread(inFromClient1[i],inFromClient[i],outToClient,ST,user,pass,n,i);
					ST[i].on=true;
					for(int j=0;j<100;j++)
					{
						if(j!=i&&ST[j].on==true) ST[j].Set(outToClient,ST);
					}
					break;
					
				}
			}
		
		}
	}
		
}


//===========================================================
class SThread extends Thread{
	BufferedReader inFromClient;
	InputStream inFromClient1;
	DataOutputStream outToClient[]=new DataOutputStream[100];
	SThread ST1[];
	String clientName,User,Pass,serverMessage,option;
	boolean on;
	String user[] = new String[100];
	String pass[] = new String[100];
	int n,pos,val,sr,readMode;
	
	
	
	public SThread()
	{
		on = false; sr = 0; readMode = -1;
		
	}
	
	public SThread(DataOutputStream out[],SThread ST[],String usr[],String pas[],int tot,int ps) {
		on = true;
		inFromClient = new BufferedReader(new InputStreamReader(System.in));
		outToClient=out;
		ST1 = ST;
		user = usr ; pass = pas; n = tot; pos = ps; sr = 1; readMode = -1;
		start();
	}
	
	public SThread(InputStream ISS,BufferedReader in, DataOutputStream out[],SThread ST[],String usr[],String pas[],int tot,int ps){
		
		on = true;
		inFromClient1 = ISS;
		inFromClient=in;
		outToClient=out;
		ST1 = ST;
		user = usr ; pass = pas; n = tot; pos = ps; sr = 0; readMode = -1;
		start();
		
		
	}
	
	public void Set(DataOutputStream out[],SThread ST[])
	{
		outToClient = out ;
		ST1 = ST ;
	}
	
	public void makeClose(String client)    // force connection close
	{
		for(int i=1;i<outToClient.length;i++) {
			if(ST1[i].on&&ST1[i].val!=-1&&ST1[i].User.equals(client)){
				try{
					
					outToClient[i].writeBytes("CLOSE"+"\n");
					
					ST1[i].on=false;
				 	System.out.println("Closing "+i);
				 	sendToALL2(pos,ST1[i].User);
				}
				catch(Exception e)
				{
					
				}
				
			}
		}
	}
	
	
	
	public void sendToALL()
	{
		for(int i=1;i<outToClient.length;i++) {
			if(ST1[i].on&&ST1[i].val!=-1){
				try{
					outToClient[i].writeBytes("Server"+"\n");
				 	outToClient[i].writeBytes(serverMessage+"\n");
				 //	System.out.println("sending to "+i);
				}
				catch(Exception e)
				{
				}
				
			}
		}
	}
	
	public void sendToALL(int ps)
	{
		for(int i=1;i<outToClient.length;i++) {
			if(ST1[i].on&&ST1[i].val!=-1&&i!=ps){
				try{
					outToClient[i].writeBytes("Server"+"\n");
				 	outToClient[i].writeBytes(User+" logged in \n");
				 	//System.out.println("sending to "+i);
				}
				catch(Exception e)
				{
				}
				
			}
		}
	}
	
	public void sendToALL2(int ps,String who)
	{
		for(int i=1;i<outToClient.length;i++) {
			if(ST1[i].on&&ST1[i].val!=-1&&i!=ps){
				try{
					outToClient[i].writeBytes("Server"+"\n");
				 	outToClient[i].writeBytes(who+" logged out\n");
				 //	System.out.println("sending to "+i);
				}
				catch(Exception e)
				{
					
				}
				
			}
		}
	}
	
	
	public void sendToALL(String from)
	{
		for(int i=1;i<outToClient.length;i++) {
			if(ST1[i].on&&ST1[i].val!=-1){
				try{
					outToClient[i].writeBytes(from+"\n");
				 	outToClient[i].writeBytes(serverMessage+"\n");
				 //	System.out.println("sending to "+i);
				}
				catch(Exception e)
				{
				}
				
			}
		}
	}
	
	
	
	public void sendToClient(String from)
	{
		for(int i=1;i<outToClient.length;i++) {
			if(ST1[i].on&&ST1[i].User.equals(option)&&ST1[i].val!=-1) {
			try{
					outToClient[i].writeBytes(from+"\n");
				 	outToClient[i].writeBytes(serverMessage+"\n");
				 //	System.out.println("sending to "+i);
				}
				catch(Exception e)
				{
				}
			} 
		}
	}
	
	
	
	
	public void login()
	{
		while(val==-1)
		{
			try {
			
				User = inFromClient.readLine();
				Pass = inFromClient.readLine();
				
				for(int i=0;i<n;i++) 
				{
					if(user[i].equals(User)&&pass[i].equals(Pass)) val=i;
				
				}
				
				
				
			}
			catch (Exception ee)
			{
				
			}
			if(val==-1) {
				try {
					outToClient[pos].writeBytes("Server"+'\n');
					outToClient[pos].writeBytes("Invalid ID/Password."+'\n');
				}
				catch (Exception ee)
				{
					
				}
			}
			else 
			{
				try {
					outToClient[pos].writeBytes("Server"+'\n');
					outToClient[pos].writeBytes("Connected."+'\n');
					sendToALL(pos);
				}
				catch (Exception ee)
				{
					
				}
			}
		}
	}
	
	
	public void fileTransfer() 
	{
		int to,from,totalLine;
		from = pos;
		to = - 1;
		String valid,msg;
	
		
		for(int i=1;i<outToClient.length;i++) {
			
			if(ST1[i].User.equals(clientName)&&ST1[i].val!=-1&&ST1[i].on) {
				to = i ;
				break;
			}
		}
		if(to!=-1) {
		
			try {
			
				outToClient[to].writeBytes("FILE"+"\n");
				outToClient[to].writeBytes(User+"\n");
				outToClient[to].writeBytes(serverMessage+"\n");
			
				ST1[to].readMode = 0 ;
				while(ST1[to].readMode==0)
				{
					;
				}
				
			
				
				
				
				
				if(ST1[to].readMode==1) {
					ST1[to].readMode = -1;
					outToClient[from].writeBytes("SEND"+'\n');
					outToClient[from].writeBytes(serverMessage+'\n');
					msg = ST1[from].inFromClient.readLine();
					totalLine = Integer.parseInt(msg);
					
					
					
					outToClient[to].writeBytes("RECEIVE"+'\n');
					outToClient[to].writeBytes(serverMessage+'\n');
					outToClient[to].writeBytes(msg+'\n');
					
					byte [] mybytearray= new byte[128];
					
					int bytesRead =0; 
					int current =0;	
					while(bytesRead>=0)
				    {
				    	bytesRead = ST1[from].inFromClient1.read(mybytearray);
				    	if(bytesRead>=0)
				    	{
				    		outToClient[to].write(mybytearray,0,bytesRead);
				    	
				    		current+=bytesRead;
				    	}
				    //	System.out.println(current+" "+bytesRead);
				    	if(current>=totalLine) break;
				    	if(bytesRead<4) break;
				    }
					
					outToClient[to].flush();
					
					 
					
				}
				else ;
			}
			catch(Exception e)
			{
				
			}
			
			
		}
	}
	
		
	public void run(){
		
		
		if(sr==0) {  // code for client threads
		
			val = -1;
			
			login();
			
			while(true) {
				
				if(on==false) break;
				
				try {
				
					option = inFromClient.readLine();
					if(readMode==0)
					{
						if(option.equals("YES")) readMode=1;
						else readMode = -1;
						continue;
					}
					if(option.equals("Logout")) {
						sendToALL2(pos,User);
						val = -1;
						login();
						continue;
					}
					
					serverMessage = inFromClient.readLine();
					if(option.equals("ALL")) {
						sendToALL(User);
					}
					else if(option.startsWith("Client")) {
						sendToClient(User);
					}
					else if(option.equals("FILE")) {
						System.out.println("here o");
						clientName = inFromClient.readLine();
						fileTransfer();
					}
					
				}
				catch (Exception e)
				{
					
				}
			}
		
		}
		else    // code for server
		{
			while(true)
			{
				try {
				
					option = inFromClient.readLine();
					serverMessage = inFromClient.readLine();
				}
				catch (Exception e)
				{
					
				}
				if(option.equals("ALL")) {
					sendToALL();
				}
				else if(option.startsWith("Client")) {
					sendToClient("Server");
				}
				else if(option.equals("CLOSE")) {
					makeClose(serverMessage);
				} 
			
			}
		}
		
		
	}
}
//===========================================================
