import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try {
            Socket socket = new Socket("localhost", 9460);

            BufferedReader in = new BufferedReader(
                    new InputStreamReader(
                            socket.getInputStream()
                    )
            );

            BufferedWriter out = new BufferedWriter(
                    new OutputStreamWriter(
                            socket.getOutputStream()
                    )
            );

            Scanner scanner = new Scanner(System.in);

            while(true) {
                String outTxt = scanner.nextLine();
                out.write(outTxt);
                out.newLine();
                out.flush();


                String txt = in.readLine();
                System.out.println(txt);

                if (outTxt.equals("quit")) {
                    break;
                }
            }
            in.close();
            out.close();
            socket.close();

        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}