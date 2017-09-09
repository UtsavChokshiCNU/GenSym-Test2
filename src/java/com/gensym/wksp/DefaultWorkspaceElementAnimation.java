package com.gensym.wksp;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.classes.ImplAccess;
import com.gensym.ntw.TwAccess;
import com.gensym.message.Trace;
import com.gensym.jgi.G2AccessException;
import java.awt.Rectangle;
import com.gensym.draw.DrawElement;

public class DefaultWorkspaceElementAnimation implements Animation {
  private WorkspaceElementHelper helper;
  private Sequence path;
  private long durationMillis,startTimeMillis;
  private int count,totalLength,currentDistanceTraveled,currentIndex;
  private int[] segmentLengths;
  private Object id;
  private Symbol returnRPCName;
  private int xOffset, yOffset;
  private DrawElement dElement;
  public DefaultWorkspaceElementAnimation(WorkspaceElementHelper helper,
					  DrawElement dElement,
					  Sequence path,
					  int xOffset, int yOffset,
					  long durationMillis,
					  long startTimeMillis,
					  Symbol returnRPCName,
					  Object id) throws NoSuchAttributeException
  {
    this.helper = helper;
    this.dElement = dElement;
    count = path.size()/2;
    this.id = id;
    this.returnRPCName = returnRPCName;      
    this.path = path;
    this.durationMillis = durationMillis;
    this.startTimeMillis = startTimeMillis;
    this.xOffset = xOffset;
    this.yOffset = yOffset;
    segmentLengths=new int[count-1];
    for (int i=0;i<count-1;i++) {
      int[] start = getCoordinates(i, xOffset, yOffset);
      int[] end = getCoordinates(i+1, xOffset, yOffset);
      segmentLengths[i]=(int)Math.sqrt(Math.pow(end[0]-start[0],2)+Math.pow(end[1]-start[1],2));
      totalLength+=segmentLengths[i];
    }
  }
  @Override
  public void dispose() {
    try {
      TwAccess connection = (TwAccess)((ImplAccess)helper.getItem()).getContext();
      if (connection != null && returnRPCName != null) 
	connection.callRPC(returnRPCName, new Object[] {id, connection.getSession()});
    } catch(G2AccessException g2ae) {
      Trace.exception(g2ae);
    }      
  }
  @Override
  public boolean update(long currentTimeMillis) {
    long ellapsedTimeMillis = (currentTimeMillis - startTimeMillis);
    float fractionDone = ((float)ellapsedTimeMillis)/durationMillis;
    Rectangle bnds = dElement.getExactBounds()[0];	      
    try {
      if (fractionDone >= 1) {
	int[] currentCoords=getCoordinates(count-1, xOffset, yOffset);
	helper.shiftTo(currentCoords[0]-bnds.width/2,currentCoords[1]+bnds.height/2);
	return true;
      } else {       
	int updatedDistanceTraveled = (int)(fractionDone*totalLength);
	while(updatedDistanceTraveled > (currentDistanceTraveled+segmentLengths[currentIndex])) 
	  currentDistanceTraveled+=segmentLengths[currentIndex++];
	int[] currentCoords=getCoordinates(currentIndex, xOffset, yOffset),
	  nextCoords=getCoordinates(currentIndex+1, xOffset, yOffset);
	float remainderFraction=(updatedDistanceTraveled-currentDistanceTraveled)/
	  ((float)segmentLengths[currentIndex]);
	int deltaX=nextCoords[0]-currentCoords[0], deltaY=nextCoords[1]-currentCoords[1];
	int centerX=currentCoords[0]+(int)(deltaX*remainderFraction);
	int centerY=currentCoords[1]+(int)(deltaY*remainderFraction);
	helper.shiftTo(centerX-bnds.width/2,centerY+bnds.height/2);
      }
    } catch (NoSuchAttributeException nsae) {
      Trace.exception(nsae);
    }
    return false;
  }
  private final int[] getCoordinates(int index, int xOffset, int yOffset)
       throws NoSuchAttributeException
  {
    return  new int[] {((Integer)path.elementAt(2*index)).intValue()+xOffset,
			 ((Integer)path.elementAt(2*index+1)).intValue()+yOffset};      
  }    
}

