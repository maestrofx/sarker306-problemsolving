import java.io.*;
import java.net.*;
import java.util.*;
//============================================================
class TCPClient
{
	public static void main(String argv[]) throws Exception
	{
		String modifiedSentence;
		
		InetAddress inetAddress=InetAddress.getLocalHost();
		//.getByName(String hostname); "CL11"
		System.out.println(inetAddress);

		Socket clientSocket = new Socket(inetAddress,6789);
		DataOutputStream outToServer=
			new  DataOutputStream(clientSocket.getOutputStream());
		
		InputStream inFromServer1 = clientSocket.getInputStream();
		BufferedReader inFromServer=
			new  BufferedReader(new InputStreamReader
							(inFromServer1));
		

		CThread write=new CThread(inFromServer1,inFromServer, outToServer, 0);
        CThread read=new CThread(inFromServer1,inFromServer, outToServer, 1);
      
        
        write.join();
        read.join();
        clientSocket.close();
	}
}
//===================================================================
class CThread extends Thread{
	BufferedReader inFromServer;
	InputStream inFromServer1;
	DataOutputStream outToServer;
	int RW_Flag,on;
	

	
	
	public CThread(InputStream ISS,BufferedReader in, DataOutputStream out, int rwFlag){
		inFromServer=in;
		inFromServer1=ISS;
		outToServer=out;
		RW_Flag=rwFlag;on=1;//clientSocket = soc;
		start();
	}
	
	
	
	public void run(){
		String sentence,from,fileName;
		int total;
		try{
			while (true){
				if(on==0) {
					
					System.exit(0);
					
				}
				if(RW_Flag==0){
					BufferedReader inFromUser=
					new BufferedReader(new InputStreamReader(System.in));
					sentence=inFromUser.readLine();
					if(sentence.equals("FILE")) {
					
					
						outToServer.writeBytes(sentence+'\n');
						sentence = inFromUser.readLine();
						outToServer.writeBytes(sentence+'\n');
						sentence = inFromUser.readLine();
						outToServer.writeBytes(sentence+'\n');
						
					}
					else 
					{
						outToServer.writeBytes(sentence+'\n');
					}
				}
				else if(RW_Flag==1){					
					sentence=inFromServer.readLine();
					System.out.println(sentence);
					if(sentence.startsWith("CLOSE")||sentence.equals("CLOSE")) {
						on = 0;
						System.exit(0);
						
						
					}
					if(sentence.equals("FILE")) {
						from = inFromServer.readLine();
						fileName = inFromServer.readLine();
						System.out.println(from+" want to send "+fileName);
						
					}
					else if(sentence.equals("RECEIVE"))
					{
						fileName = inFromServer.readLine();
						sentence = inFromServer.readLine();
						total = Integer.parseInt(sentence);
						byte [] mybytearray  = new byte [128];
						FileOutputStream fos = new FileOutputStream("re"+fileName);
						BufferedOutputStream bos = new BufferedOutputStream(fos);
						
						int bytesRead =0;
					    int current = 0;
					    
						while(bytesRead>=0)
					    {
					    	bytesRead = inFromServer1.read(mybytearray);
					    	if(bytesRead>=0)
					    	{
					    		bos.write(mybytearray, 0 , bytesRead);
					    		current+=bytesRead;
					    	}
					    
					    	if(bytesRead<128||current>=total) break;
					    }
					  	
					
					    
					    bos.flush();
					    bos.close();
						System.out.println("FILE Received");
						
					}
					else if(sentence.equals("SEND")) 
					{
						System.out.println("send shuru ");
						fileName = inFromServer.readLine();
						File myFile = new File (fileName);
      					byte [] mybytearray  = new byte [(int)myFile.length()];
      					FileInputStream fis = new FileInputStream(myFile);
      					BufferedInputStream bis = new BufferedInputStream(fis);
      					bis.read(mybytearray,0,mybytearray.length);
      					outToServer.writeBytes(Integer.toString(mybytearray.length)+'\n');
						outToServer.write(mybytearray);
						
						
						System.out.println("FILE SEND");
						
					}
					
					else {
						System.out.printf("From "+sentence+": ");
						sentence=inFromServer.readLine();
						System.out.println(sentence);
					}	
				}
			}		
		}catch(Exception e){}		
	}
}
//===================================================================