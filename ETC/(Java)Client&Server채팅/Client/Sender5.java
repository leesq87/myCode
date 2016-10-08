import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Sender5 extends Thread {
	
	Socket socket;
	PrintWriter out = null;
	String name;
	
	public Sender5(Socket socket, String name){
		this.socket = socket;
		try {
			out =new PrintWriter(this.socket.getOutputStream(),true);
			this.name = name;
		}
		catch (Exception e){
			System.out.println("예외S3:"+e);
		}
	
	}

	
	@Override
	public void run(){
		Scanner s = new Scanner(System.in);
		
		try{
			out.println(name);
			
			while (out !=null){
				try{
					String s2 = s.nextLine();
					if(s2.equals("q") || s2.equals("Q")){
						out.println(s2);
						break;
					}
					else{
						out.println(name + "=>" + s2);
					}
					
				}
				catch(Exception e){
					System.out.println("예외S1:" +e);
				}
			}
			out.close();
			socket.close();
		}
		
		catch(Exception e){
			System.out.println("예외S2:" +e);
		}
	}
}
