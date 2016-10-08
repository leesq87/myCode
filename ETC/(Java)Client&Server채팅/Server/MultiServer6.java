import java.io.*;
import java.net.*;
import java.util.*;


public class MultiServer6 {
	ServerSocket serverSocket = null;
	Socket socket = null;
	Map<String, PrintWriter> clientMap;
	
	public MultiServer6(){
		clientMap = new HashMap<String, PrintWriter>();
		Collections.synchronizedMap(clientMap);
	}
	
	public void init(){
		try{
			serverSocket = new ServerSocket(9999);
			System.out.println("서버시작됨");
			
			while(true){
				socket = serverSocket.accept();
				System.out.println(socket.getInetAddress() + ":" + socket.getPort());
				
				Thread mst = new MultiServerT(socket);
				mst.start();
			}
		} catch(Exception e){
			e.printStackTrace();
		} finally{
			try{
				serverSocket.close();
			} catch (Exception e){
				e.printStackTrace();
			}
		}
	}
	
	public void sendAllMsg(String msg){
		Iterator it = clientMap.keySet().iterator();
		
		while(it.hasNext()){
			try{
				PrintWriter it_out = (PrintWriter) clientMap.get(it.next());
				it_out.println(msg);
			} catch(Exception e){
				System.out.println("예외 : " +e);
			}
		}
	}
	
	public static void main(String[] args){
		MultiServer6 ms = new MultiServer6();
		ms.init();
	}
	
	class MultiServerT extends Thread{
		Socket socket;
		PrintWriter out = null;
		BufferedReader in = null;
		
		public MultiServerT(Socket socket){
			this.socket = socket;
			try{
				out = new PrintWriter(this.socket.getOutputStream(),true);
				in = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
				
			} catch(Exception e){
				System.out.println("예외 : " +e);
			}
		}
		
		
		@Override
		public void run(){
			String name = "";
			try{
				name = in.readLine();
				
				sendAllMsg(name + "님이 입장함");
				clientMap.put(name, out);
				System.out.println("현재 접속자 수는 : " +clientMap.size()+" 명입ㄴ디ㅏ.");
				
				String s = "";
				while(in != null){
					s = in.readLine();
					System.out.println(s);
					if(s.equals("q") || s.equals("Q"))
						break;
					sendAllMsg(s);
				}
				
			} catch (Exception e){
				System.out.println("예외 : "+e);
			} finally{
				clientMap.remove(name);
				sendAllMsg(name+"님 나감");
				System.out.println("접속자 수 " + clientMap.size() + "명임");
			
				try{
					in.close();
					out.close();
					
					socket.close();
				} catch (Exception e){
					e.printStackTrace();
				}
			}
		}
	}
}
