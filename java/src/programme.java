import java.io.IOException;

public class programme {
    public void programme1(){
        try{
            Runtime.getRuntime().exec("powershell Start-Process -FilePath  raccourci/raccourci1.lnk ");
        }catch(IOException e){
            System.out.println(e);
        }
    }
    public void programme2(){
        try{
            Runtime.getRuntime().exec("powershell Start-Process -FilePath  raccourci/raccourci2.lnk ");
        }catch(IOException e){
            System.out.println(e);
        }
    }
    public void programme3(){
        try{
            Runtime.getRuntime().exec("powershell Start-Process -FilePath  raccourci/raccourci3.lnk ");
        }catch(IOException e){
            System.out.println(e);
        }
    }
    public void siteweb1(){
        try{
            Runtime.getRuntime().exec("powershell Start-Process -FilePath  raccourci/raccourciweb1.url ");
        }catch(IOException e){
            System.out.println(e);
        }
    }
    public void siteweb2(){
        try{
            Runtime.getRuntime().exec("powershell Start-Process -FilePath  raccourci/raccourciweb2.url ");
        }catch(IOException e){
            System.out.println(e);
        }
    }
    public void siteweb3(){
        try{
            Runtime.getRuntime().exec("powershell Start-Process -FilePath  raccourci/raccourciweb3.url ");
        }catch(IOException e){
            System.out.println(e);
        }
    }
}