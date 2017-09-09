/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Recording.java
 *
 */
package com.gensym.editor.text;

import java.io.PrintStream;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.ObjectOutputStream;
import java.io.ObjectInputStream;
import java.io.IOException;
import java.io.Serializable;
import java.lang.ClassNotFoundException;
import java.util.Vector;
import java.util.Enumeration;
import com.gensym.message.Trace;
import com.gensym.util.Sequence;


/** A 'recording' in the sense of a record of a sequence of events
 * that can be played back, saved, and restored */

public class Recording extends Sequence implements Serializable {

  private static final boolean traceEvents = true;
  private static final boolean debug = true;

  //int defaultCapacity = 50;
  //   If you use this as the arg to super compiler complains that it can't be
  //   accessed before the super is called.
  //int defaultCapacityIncrement = 25;


  /* If someone uses the same methods during playback as during
   * their original run, we can get a spurious duplication and
   * extensions unless we inhibit add, dump, or the like while
   * the playback operation is ongoing. */
  private boolean isRecording = true;

  public void pause() { isRecording = false; }
  public void resume() { isRecording = true; }



  //---- Constructors ------------------

  public Recording() {
    super(50);
  }

  public Recording(FileInputStream fis) {
    try {
      ObjectInputStream ois = new ObjectInputStream(fis);
      Sequence record = (Sequence)ois.readObject();
      if (debug) {
    	  System.out.println("Retrived record from " + fis);
      }

      /* copy over the elements */
      Object[] contents = record.getContents();
      for (int i = 0; i < contents.length; i++) {
	addElement( contents[i] );
	if (debug) {
		System.out.println(i + " = " + contents[i]);
	}
      }
    } catch (IOException e) {
      Trace.exception(e, "Problem using ObjectInputStream");
    } catch (ClassNotFoundException e) {
      Trace.exception(e);
    }
  }
  


  //---- primary entry point -----------

  /** Adds the object to the end of the record. */
  @Override
  public boolean add(Object o) {
    if ( isRecording ) {
      if ( traceEvents )
	System.out.println("Adding " + o);
      addElement(o);
    }
    /* In jdk1.2 Vector has been revampted to implement List, so now
     * it has an 'add' method, which add's to the end. The javadoc
     * says it (always??) returns true. */
    return true;
  }


  /** Removes all of the stored objects from the record. */
  public void reset() {
    removeAllElements();
  }

  /** */
  public void save (FileOutputStream fos) {
    try {
      ObjectOutputStream oos = new ObjectOutputStream(fos);
      oos.writeObject( this );
      } catch (IOException e) {
	Trace.exception(e, "Problem using ObjectOutputStream");
      }
  }


  //---- Dumping toString's to a stream --------------

  /** Prints a listing of the recorded items to System.out.  
   * This uses the toString method of the items, and is intended
   * for visual inspections of the record rather than offline storage. */
  public void dump() {
    dump(System.out);
  }

  /** Prints a listing of the recorded items to the stream.  
   * This uses the toString method of the items, and is intended
   * for visual inspections of the record rather than offline storage. */
  public void dump(PrintStream stream) {
    for ( int i=0; i < elementCount; i++ ) {
      stream.println("#" + i + "  " + elementAt(i));
    }
  }


  //---- Playing back by issuing the objects as wrapped events ----

  private Vector listeners = new Vector();

  /** Adds a listener to the list of RecordingPlayback listeners. */
  public void addPlaybackListener (RecordingPlaybackEventListener l) {
    listeners.addElement(l);
  }

  /** Removes a listener to the list of RecordingPlayback listeners. */
  public void removePlaybackListener (RecordingPlaybackEventListener l) {
    listeners.removeElement(l);
  }

  public void playback() {
    playback(-1);
  }

  public void playback(long milliesToSleep) {
    boolean oldValueOfRecording = isRecording;
    try { // the Try is here for the benefit of the recording flag.
      isRecording = false;
      Enumeration r = elements();
      Vector list = (Vector)listeners.clone();
      while ( r.hasMoreElements() ) {
	Object next = r.nextElement();
	System.out.println("Playing back " + next);
	RecordingPlaybackEvent e = new RecordingPlaybackEvent(next);
	for (int i = 0; i < list.size(); i++ ) {
	  if ( milliesToSleep != -1 ) {
	    try {
	      Thread.sleep(milliesToSleep);
	    } catch (InterruptedException ex) {
	      Trace.exception(ex, "Unexpected exception while sleeping during Playback");
	    }
	  }
	  ((RecordingPlaybackEventListener)list.elementAt(i))
	    .handleRecordPlaybackEvent(e);
	}
      }
    } finally {
      isRecording = oldValueOfRecording;
    }
  }


}
