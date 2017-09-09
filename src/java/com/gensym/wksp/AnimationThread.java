package com.gensym.wksp;

import java.util.Vector;
import com.gensym.message.Trace;

public class AnimationThread extends Thread {
  private long sleepPeriod = 1000/24;//default of 24 frames per second
  private Vector animations = new Vector();
   
  public void setFramesPerSecond(int framesPerSecond) {
    sleepPeriod = 1000/framesPerSecond;
  }

  public synchronized void addAnimation(Animation animation) {
    animations.addElement(animation);
    notify();
  }
  
  public void removeAnimation(Animation animation) {
    animations.removeElement(animation);
  }
  
  private Animation[] getAnimations() {
    Animation[] anims = null;
    synchronized(animations) {
      int size = animations.size();
      if (size == 0)
	return null;
      anims = new Animation[size];
      animations.copyInto(anims);
    }
    return anims;
  }

  private void updateAnimations(Animation[] anims, long currentTimeMillis) {
    for (int i=0;i<anims.length;i++) {
      Animation animation = anims[i];
      if (animation.update(currentTimeMillis)) {
 	removeAnimation(animation);
 	animation.dispose();
      }
    }
  }

  @Override
  public synchronized void run() {
    while (true) {
      try {
	Animation[] animations = getAnimations();
	
	if (animations == null) {
	  wait();  // until an animation gets added
	} else {
	  // NOTE: we don't know if the optimization of sharing
	  // currentTimeMillis is necessary for performance. It is
	  // possible that it is detrimental in that some animations
	  // (particualarly if there are several) could run
	  // after their allotted time.
	  long currentTimeMillis = System.currentTimeMillis();
	  updateAnimations(animations, currentTimeMillis);
	  wait(sleepPeriod);
	}
      } catch (InterruptedException ie) {
	Trace.exception(ie);
      }
    }
  }
}
