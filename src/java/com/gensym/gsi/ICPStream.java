
package com.gensym.gsi;

import java.util.*;
import com.gensym.gsi.*;

public abstract class ICPStream extends Thread {
    public ICPSocket sck;

    public IndexSpace standardIndexSpace = new IndexSpace();
    public IndexSpace itemIndexSpace = new IndexSpace();
    public IndexSpace temporaryIndexSpace = new IndexSpace();

}
