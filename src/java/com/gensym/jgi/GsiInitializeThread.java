/****************************************************************************
 * 	 Class G2LoopThread
 *
 * Description:  The purpose of this thread is to help set up a
 *     network "pipe".  The GSI loop thread will set up the first part
 *     of the connection, and then kick off this thread.  We will wait
 *     for a short time, while the GSI loop thread enters C code to
 *     accept the connection, and we connect.  In fact, the meat of
 *     this is done in C, so this thread just waits and then calls a C
 *     function.  Then its life is complete, so it dies.
 * 
 *     This is necessary because of the inability of GSI to watch a
 *     fd of a pipe, but only able to deal with network connections.
 *     If you look at the C code for UNIX, this is a noop, but I
 *     didn't want to do any platform specificity anywhere except C.
 *
 *****************************************************************************/

package com.gensym.jgi;

class GsiInitializeThread extends Thread
{
  @Override
  public void run() {
    //System.out.println ("starting GSI thread for connect.");
    int return_value;
    try {
      sleep (500);
    }
    catch (java.lang.InterruptedException e) { System.out.println ("got interrupted in GSI thread for connect.");}
    //System.out.println ("done sleeping in GSI thread for connect.");
    if ((return_value = GsiLoopThread.connect_tickle ()) != 0)
	JGInterface.getJGInterface(new String[0]).communicationError(-1, -1, "failed to initialize JNI code (connect): "+return_value, null);
  }
}
