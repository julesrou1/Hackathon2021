import java.io.FileWriter;   
import java.io.IOException;


public class mic {
    String micro = "Add-Type -TypeDefinition @'\n        using System.Runtime.InteropServices;\n        [Guid(\"5CDF2C82-841E-4546-9722-0CF74078229A\"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]\n        interface IAudioEndpointVolume {\n          // f(), g(), ... are unused COM method slots. Define these if you care\n          int f(); int g(); int h(); int i();\n          int SetMasterVolumeLevelScalar(float fLevel, System.Guid pguidEventContext);\n          int j();\n          int GetMasterVolumeLevelScalar(out float pfLevel);\n          int k(); int l(); int m(); int n();\n          int SetMute([MarshalAs(UnmanagedType.Bool)] bool bMute, System.Guid pguidEventContext);\n          int GetMute(out bool pbMute);\n        }\n        [Guid(\"D666063F-1587-4E43-81F1-B948E807363F\"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]\n        interface IMMDevice {\n          int Activate(ref System.Guid id, int clsCtx, int activationParams, out IAudioEndpointVolume aev);\n        }\n        [Guid(\"A95664D2-9614-4F35-A746-DE8DB63617E6\"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]\n        interface IMMDeviceEnumerator {\n          int f(); // Unused\n          int GetDefaultAudioEndpoint(int dataFlow, int role, out IMMDevice endpoint);\n        }\n        [ComImport, Guid(\"BCDE0395-E52F-467C-8E3D-C4579291692E\")] class MMDeviceEnumeratorComObject { }\n                public class Audio {\n          static IAudioEndpointVolume Vol() {\n            var enumerator = new MMDeviceEnumeratorComObject() as IMMDeviceEnumerator;\n            IMMDevice dev = null;\n            Marshal.ThrowExceptionForHR(enumerator.GetDefaultAudioEndpoint(/*eCapture*/ 1, /*eMultimedia*/ 1, out dev));\n            IAudioEndpointVolume epv = null;\n            var epvid = typeof(IAudioEndpointVolume).GUID;\n            Marshal.ThrowExceptionForHR(dev.Activate(ref epvid, /*CLSCTX_ALL*/ 23, 0, out epv));\n            return epv;\n          }\n          public static float Volume {            get {float v = -1; Marshal.ThrowExceptionForHR(Vol().GetMasterVolumeLevelScalar(out v)); return v;}\n            set {Marshal.ThrowExceptionForHR(Vol().SetMasterVolumeLevelScalar(value, System.Guid.Empty));}\n          }\n          public static bool Mute {\n            get { bool mute; Marshal.ThrowExceptionForHR(Vol().GetMute(out mute)); return mute; }\n            set { Marshal.ThrowExceptionForHR(Vol().SetMute(value, System.Guid.Empty)); }\n          }\n        }\n'@\n\n";
    public void mutemic() {
        try {
            String filename= "script/micro.ps1";
            FileWriter fw = new FileWriter(filename,false); 
            fw.write(micro);
            fw.write("[Audio]::Mute = $true");
            fw.close();
        }catch (IOException e) {
            System.out.println("marche pas :(");
        }
        try {
            Runtime.getRuntime().exec("powershell \"script/micro.ps1\"");
        }catch (IOException e) {
            System.out.println("marche pas :("+e);
        }
    }
    public void unmutemic() {
        try {
            String filename= "script/micro.ps1";
            FileWriter fw = new FileWriter(filename,false); 
            fw.write(micro);
            fw.write("[Audio]::Mute = $false");
            fw.close();
        }catch (IOException e) {
            System.out.println("marche pas :(");
        }
        try {
            Runtime.getRuntime().exec("powershell \"script/micro.ps1\"");
        }catch (IOException e) {
            System.out.println("marche pas :(");
        }
    }
    public void volume(int vol) {
        try {
            String filename= "script/micro.ps1";
            FileWriter fw = new FileWriter(filename,false); 
            fw.write(micro);
            float vol2 = vol;
            vol2 = vol2/100;
            System.out.println(vol2);
            fw.write("[Audio]::Volume  = "+vol2);
            fw.close();
        }catch (IOException e) {
            System.out.println("marche pas :(");
        }
        try {
            Runtime.getRuntime().exec("powershell \"script/micro.ps1\"");
        }catch (IOException e) {
            System.out.println("marche pas :(");
        }
    }
}

