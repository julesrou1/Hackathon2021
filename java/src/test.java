import com.fazecast.jSerialComm.SerialPort;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Scanner;

public class test {
    public static void main(String args[]){
/*
        JFrame window = new JFrame();
        window.setTitle("nique");
        window.setSize(300,200);
        window.setLayout(new BorderLayout());
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JButton connectButton=new JButton("connecc");
        JPanel top=new JPanel();
        top.add(connectButton);
        window.add(top,BorderLayout.NORTH);
        connectButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(connectButton.getText().equals("connecc")){

                }
            }
        });
*/

        SerialPort chosenPort;
        chosenPort= SerialPort.getCommPort("COM5");
        chosenPort.setComPortTimeouts(SerialPort.TIMEOUT_SCANNER,0,0);
        chosenPort.openPort();
        Thread thread = new Thread(){
            public void run(){
                Scanner scanner = new Scanner(chosenPort.getInputStream());
                while(scanner.hasNextLine()){
                    String line = scanner.nextLine();
                    //int number = Integer.parseInt(line);
                    //System.out.println(number);
                    if(line.equals("1")){
                        System.out.print("MUTE!\n");
                    }
                    else if (line.equals("2")){
                        System.out.print("mabite\n");
                    }
                    else if (line.equals("3")){
                        System.out.print("oui\n");
                    }
                    else if (line.equals("4")){
                        System.out.print("non\n");
                    }
                    else if (line.equals("5")){
                        System.out.print("bah si\n");
                    }
                    else if (line.equals("A")){
                        System.out.print("meh\n");
                    }
                    else if (line.equals("*")){
                        System.out.print("*\n");
                    }
                    //System.out.print(line+"\n");
                }
                scanner.close();
            }
        };
        thread.start();
    }
}
