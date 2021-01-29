import com.fazecast.jSerialComm.*;

public class MyComPortListener implements SerialPortDataListener{

    @Override
    public int getListeningEvents() {
        return SerialPort.LISTENING_EVENT_DATA_AVAILABLE;
    }

    @Override
    public void serialEvent(SerialPortEvent serialPortEvent) {
        byte[] buffer = new byte[serialPortEvent.getSerialPort().bytesAvailable()];
        serialPortEvent.getSerialPort().readBytes(buffer,buffer.length);

        ReformatBuffer.parseByteArray(buffer);
    }
}
