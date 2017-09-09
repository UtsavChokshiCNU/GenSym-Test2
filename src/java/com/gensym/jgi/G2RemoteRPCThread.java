package com.gensym.jgi;

class G2RemoteRPCThread extends Thread {

  private G2Connection G2Connection;
  private int g2_function_handle;
  private Object[] items;
  Object retnvalue;
  
  G2RemoteRPCThread (G2Connection G2Connection, int g2_function_handle, Object[] items) {

    super ();
    this.G2Connection = G2Connection;
    this.g2_function_handle = g2_function_handle;
    this.items = new Object [items.length];
    System.arraycopy (items, 0, this.items, 0, items.length);
  }

  public synchronized native void callRPCSynchronous (G2Connection G2Connection,
						      int function_handle, 
						      Object arguments[],
						      boolean start_proc);

  @Override
  public void run () {
    callRPCSynchronous (G2Connection, g2_function_handle, items, false );
    //System.out.println ("Call " + g2_function_handle + "(" + items + ")  complete");
    //System.out.println ("<<<<<<<<<<<<<  " + retnvalue + "  >>>>>>>>>>>>>>>");
  }
}
