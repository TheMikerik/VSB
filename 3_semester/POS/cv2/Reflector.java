/* 
 java.net example (2.1): 
    Datagram service communication.
    Receiver's side.

   (written by Petr Grygarek, petr.grygarek@vsb.cz)
*/

import java.net.*;
import java.io.IOException;

public class Reflector {
 public static void main(String[] args) {

  try {
  DatagramSocket s=new DatagramSocket(8000);
  System.out.println("Reflector ready to reflect packets at " + InetAddress.getLocalHost());
  DatagramPacket p;
  String msg;

  do {
    p=new DatagramPacket(new byte[512],512);
    // musi se vytvaret vzdy znova, neumi prepsat jednou nastavenou delku
    s.receive(p);
    msg = new String(p.getData(),0,p.getLength());
    //-------> 0-4 xx
    //-------> 4-9 time
    //-------> 10-15 msg

    System.out.println("Datagram arrived from " + p.getAddress() + " : " + p.getPort() + " > " + msg);
    p.setData(msg.toUpperCase().getBytes());
    p.setLength(msg.length());
    s.send(p);
  } while (!msg.equalsIgnoreCase("down"));

  s.close();
  System.out.println("Shutting the server down");
 } catch (IOException e) { System.out.println(e); }
 }
}
