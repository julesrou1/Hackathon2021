

public class ReformatBuffer {
    public String outputString;

    static int cutoff=66;
    static String cumTempBuf="";

    public static void parseByteArray(byte[] readbuf){
        String readBufferSnippet = new String(readbuf);
        cumTempBuf=cumTempBuf.concat(readBufferSnippet);

        if((cumTempBuf.indexOf(cutoff)+1) >0) {

            String outputString = cumTempBuf.substring(0,cumTempBuf.indexOf(cutoff)+1);
            cumTempBuf=cumTempBuf.substring(cumTempBuf.indexOf(cutoff)+1);

            System.out.print(outputString);
        }
    }
}
