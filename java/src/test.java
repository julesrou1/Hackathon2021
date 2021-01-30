import com.fazecast.jSerialComm.SerialPort;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Scanner;

public class test {
    public static void main(String[] args){

        programme prog = new programme();
        audio speaker = new audio();
        mic micro= new mic();
        SerialPort chosenPort;
        chosenPort= SerialPort.getCommPort("COM5");
        chosenPort.setComPortTimeouts(SerialPort.TIMEOUT_SCANNER,0,0);
        chosenPort.openPort();
        Thread thread = new Thread(){
            public void run(){
                Scanner scanner = new Scanner(chosenPort.getInputStream());
                while(scanner.hasNextLine()){

                    String line = scanner.nextLine();
                    String mod =line.substring(0,line.indexOf(";"));
                    String code=line.substring(3,line.indexOf("!"));

                    //Mapping commandes

                    if(mod.equals("01")){//Réglage volume micro
                        System.out.print("MICRO!\n"+code+"\n");
                        micro.volume(Integer.parseInt(code));
                        System.out.print(Integer.parseInt(code));
                    }

                    else if (mod.equals("02")) {//Réglage volume HP
                        System.out.print("SPEAKER!\n" + code + "\n");
                        speaker.volume(Integer.parseInt(code));
                        System.out.print(Integer.parseInt(code));
                    }

                    else if (mod.equals("03")){//Si appui bouton
                        if (code.equals("00")) {//mute micro
                            micro.mutemic();
                            System.out.print("MUTE MICRO\n");
                        }

                        if (code.equals("01")){//unmute mic
                            micro.unmutemic();
                            System.out.print("UNMUTE MICRO\n");
                        }

                        if (code.equals("02")){//mute audio
                            speaker.mute();
                            System.out.print("MUTE AUDIO\n");
                        }

                        if (code.equals("03")){//unmute audio
                            speaker.unmute();
                            System.out.print("UNMUTE AUDIO\n");
                        }

                        if (code.equals("04")){//raccourci application
                            prog.programme1();
                            System.out.print("OUVERTURE OPENOFFICE\n");
                        }

                        if (code.equals("05")){//raccourci web
                            prog.siteweb1();
                            System.out.print("OUVERTURE WEB\n");
                        }

                    }
                }scanner.close();
            }
        };
        thread.start();
    }
}
