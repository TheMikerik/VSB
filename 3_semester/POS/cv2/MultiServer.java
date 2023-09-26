/* 
 java.net example (1.2): 
    Client-server connection-oriented communication.
    Multithreaded server implementation.

   (written by Petr Grygarek, petr.grygarek@vsb.cz)
*/

import java.net.*;
import java.io.*;

public class MultiServer implements Runnable {

 static ServerSocket s;

 public static void main(String[] args) {

  try {
  s=new ServerSocket(8000);
  Socket cso;

  System.out.println("Server ready to accept connections at " + InetAddress.getLocalHost());
  do {
    cso=s.accept();
    System.out.println("New connection from " + cso.getInetAddress() + " : " + cso.getPort() + ". Starting new instance to handle it.");
    MultiServer ms=new MultiServer(cso);
  }  while (true);
 } catch (IOException e) {
     if (e instanceof SocketException) System.out.println("Shutting the server down"); 
      else System.out.println(e); 
   }
}




MultiServer(Socket cs) { this.cs=cs; (new Thread(this)).start();  }

protected Socket cs;
 
public void run() {
    String msg;
    try {
     BufferedReader is = new BufferedReader(new InputStreamReader(cs.getInputStream()));
     BufferedWriter os = new BufferedWriter(new OutputStreamWriter(cs.getOutputStream()));

     do {
      msg=is.readLine();
      System.out.println("Server "+cs.getInetAddress()+" : "+cs.getPort()+": Data read from connection: " + msg);
      os.write(String.valueOf(msg.length()) ); os.newLine(); os.flush();
     }  while (!msg.equalsIgnoreCase("exit") && !msg.equalsIgnoreCase("down"));
     cs.close();
    System.out.println("Server "+cs.getInetAddress()+" : "+cs.getPort()+": Finishing");
     if (msg.equalsIgnoreCase("down")) s.close();
   } catch (IOException e) { System.out.println(e); }
}

}