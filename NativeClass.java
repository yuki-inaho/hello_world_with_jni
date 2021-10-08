public class NativeClass {
    static {
        System.loadLibrary("native");
    }

    private native void sayHello(String name);

    public static void main(String[] args) {
        new NativeClass().sayHello("World");
    }
}