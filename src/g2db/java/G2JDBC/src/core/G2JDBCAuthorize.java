package core;

public class G2JDBCAuthorize {
    static
    {
	System.loadLibrary("G2JDBCAuthorize");
    }

    public static native boolean authorize();
}
