import com.fazecast.jSerialComm.*;

import java.io.IOException;
import java.io.InputStream;

public class Receive {
    SerialPort sp;
    protected char[] buf;
    public Receive(String port) throws IOException {
        sp=SerialPort.getCommPort(port);
        sp.setComPortParameters(9600,8,1,0);
        sp.setComPortTimeouts(SerialPort.TIMEOUT_READ_BLOCKING,0,0);
        if (sp.openPort()){
            System.out.println("Port ouvert !");
        } else {
            System.out.println("Port fermé...");
        }
        InputStream input = sp.getInputStream();
        input.skip(sp.bytesAvailable());

        int bit;
        int i=0;
        do{
          bit=input.read();
          System.out.println((char)bit);
          buf[i]=(char)bit;
          i=i+1;
        } while (bit!=66);





    }
}
