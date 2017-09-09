package com.gensym.beaneditor;

import java.awt.*;
import java.util.Vector;
import com.gensym.draw.*;
import java.lang.Math;

public class EventConnection extends ConnectionElement implements java.io.Serializable
{

  /*
   * Allow serialization
   */
  static final long serialVersionUID = -8148564736474650165L;

  Port input;
  protected static int turnLength = 10;
  Component output; // either a LooseEnd or an (input) Port

  public EventConnection(Port input, Component output,
			 Point[] vertices,
			 int[]widths, Object[] stripePattern,
			 Object[] logicalColors, Color[] colors)
  {
    super(vertices,widths,stripePattern,logicalColors,colors, ORTHOGONAL);
    this.input = input;
    this.output = output;
  }

  public Component getOutput()
  {
     return output;
  }

  public void setOutput(Component output)
  {
     this.output = output;
  }

  protected void adjustForPortChange(Object inputOrOutput)
  {
    if ((inputOrOutput == input) && (output instanceof LooseEnd))
      {
	canvas.removeElement(this);
	canvas.removeElement(output);
	input.addOutputConnection(Port.defaultStubLength);
      }
    else
      {
	Port outputPort = (Port) output;
	int outHeading = outputPort.getHeading();
	Point inPoint = input.getPortConnectionPoint();
	Point outPoint = outputPort.getPortConnectionPoint();
	
	Point[] newVertices
	  = generateVertices(input.getHeading(),inPoint.x, inPoint.y,
			     outputPort.getHeading(),outPoint.x,outPoint.y);
	
	canvas.invalidateElement(this);
	setVertices(newVertices);
	canvas.invalidateElement(this);
      }
  }

	
  public Point[] generateVertices(int inHeading, int inX, int inY,
				  int outHeading, int outX, int outY)
  {
    int vertexCount = 0;
    int aveX = (inX + outX) / 2;
    int aveY = (inY + outY) / 2;
    int[] x = new int[5];
    int[] y = new int[5];

    switch (inHeading)
      { 
      case Directions.LEFT:
	switch (outHeading)
	  {
	  case Directions.LEFT:
	    if (inX > outX)
	      {
		vertexCount = 2;
		x[0] = aveX;    y[0] = inY;
		x[1] = aveX;    y[1] = outY;
	      }
	    else
	      {
		vertexCount = 4;
		x[0] = inX - turnLength;   y[0] = inY;
		x[1] = inX - turnLength;   y[1] = aveY;
                x[2] = outX + turnLength;  y[2] = aveY;
                x[3] = outX + turnLength;  y[3] = outY;
	      }
	    break;
	  case Directions.RIGHT:
	    if (outX < inX - turnLength)
	      {
		vertexCount = 2;
		x[0] = outX - turnLength;  y[0] = inY;
		x[1] = outX - turnLength;  y[1] = outY;
	      }
	    else
	      {
		vertexCount = 2;
		x[0] = inX - turnLength;  y[0] = inY;
		x[1] = inX - turnLength;  y[1] = outY;
	      }
	    break;
	  case Directions.TOP:
	    if (outY < inY - turnLength && outX < inX - turnLength)
	      {
		vertexCount = 1;
		x[0] = outX; y[0] = inY;
	      }
	    else if (outY < inY - turnLength)
	      {
		vertexCount = 3;
		x[0] = inX - turnLength; y[0] = inY;
		x[1] = inX - turnLength; y[1] = aveY;
		x[2] = outX;             y[2] = aveY;
	      } 
	    else 
	      {
		int vertX
		  = (outX < inX - turnLength) ?
		  aveX :
		  Math.min(inX - turnLength, outX - turnLength);
	       
		vertexCount = 3;
		x[0] = vertX;   y[0] = inY;
		x[1] = vertX;   y[1] = outY + turnLength;
		x[2] = outX;    y[2] = outY + turnLength;
	      }
	    break;
	  case Directions.BOTTOM:
	    if (outY > inY + turnLength && outX < inX - turnLength)
	      {
		vertexCount = 1;
		x[0] = outX; y[0] = inY;
	      }
	    else if (outY > inY + turnLength)
	      {
		vertexCount = 3;
		x[0] = inX - turnLength; y[0] = inY;
		x[1] = inX - turnLength; y[1] = aveY;
		x[2] = outX;             y[2] = aveY;
	      }
	    else
	      {
		int vertX
		  = (outX < inX - turnLength) ?
		  aveX :
		  Math.min(inX - turnLength, outX - turnLength);

		vertexCount = 3;
		x[0] = vertX;   y[0] = inY;
		x[1] = vertX;   y[1] = outY - turnLength;
		x[2] = outX;    y[2] = outY - turnLength;
	      }
	    break;
	  }
	break;

      case Directions.RIGHT:
	switch (outHeading)
	  {
	  case Directions.LEFT:
	    if (outX < inX - turnLength)
	      {
		vertexCount = 2;
		x[0] = inX + turnLength;  y[0] = inY;
		x[1] = inX + turnLength;  y[1] = outY;
	      }
	    else
	      {
		vertexCount = 2;
		x[0] = outX + turnLength;  y[0] = inY;
		x[1] = outX + turnLength;  y[1] = outY;
	      }
	    break;
	  case Directions.RIGHT:
	    if (inX < outX)
	      {
		vertexCount = 2;
		x[0] = aveX;    y[0] = inY;
		x[1] = aveX;    y[1] = outY;
	      }
	    else
	      {
		vertexCount = 4;
		x[0] = inX + turnLength;   y[0] = inY;
		x[1] = inX + turnLength;   y[1] = aveY;
                x[2] = outX - turnLength;  y[2] = aveY;
                x[3] = outX - turnLength;  y[3] = outY;
	      }
	    break;
	  case Directions.TOP:
	    if (outY < inY - turnLength && outX < inX - turnLength)
	      {
		vertexCount = 1;
		x[0] = outX; y[0] = inY;
	      }
	    else if (outY < inY - turnLength)
	      {
		vertexCount = 3;
		x[0] = inX + turnLength; y[0] = inY;
		x[1] = inX + turnLength; y[1] = aveY;
		x[2] = outX;             y[2] = aveY;
	      } 
	    else 
	      {
		int vertX
		  = (outX > inX + turnLength) ?
		  aveX :
		  Math.max(inX + turnLength, outX + turnLength);
	       
		vertexCount = 3;
		x[0] = vertX;   y[0] = inY;
		x[1] = vertX;   y[1] = outY + turnLength;
		x[2] = outX;    y[2] = outY + turnLength;
	      }
	    break;
	  case Directions.BOTTOM:
	    if (outY > inY + turnLength && outX > inX + turnLength)
	      {
		vertexCount = 1;
		x[0] = outX; y[0] = inY;
	      }
	    else if (outY > inY + turnLength)
	      {
		vertexCount = 3;
		x[0] = inX + turnLength; y[0] = inY;
		x[1] = inX + turnLength; y[1] = aveY;
		x[2] = outX;             y[2] = aveY;
	      }
	    else
	      {
		int vertX
		  = (outX > inX + turnLength) ?
		  aveX :
		  Math.max(inX + turnLength, outX + turnLength);

		vertexCount = 3;
		x[0] = vertX;   y[0] = inY;
		x[1] = vertX;   y[1] = outY - turnLength;
		x[2] = outX;    y[2] = outY - turnLength;
	      }
	    break;
	  }
	break;
      case Directions.TOP:
	switch (outHeading)
	  {
	  case Directions.LEFT:
	    if (outX < inX - turnLength && outY < inY - turnLength)
	      {
		vertexCount = 1;
		x[0] = inX; y[0] = outY;
	      }
	    else if (outX < inX - turnLength)
	      {
		vertexCount = 3;
		x[0] = inX;    y[0] = inY - turnLength;
		x[1] = aveX;  y[1] = inY - turnLength;
		x[2] = aveX;  y[2] = outY;
	      }
	    else
	      {
		int vertY = (outY < inY - turnLength) ? 
		  aveY : Math.min(inY - turnLength, outY - turnLength);
		vertexCount = 3;
		x[0] = inX;               y[0] = vertY;
		x[1] = outX + turnLength; y[1] = vertY;
		x[2] = outX + turnLength; y[2] = outY;
	      }
	    break;
	  case Directions.RIGHT:
	    if (outX > inX + turnLength && outY < inY - turnLength)
	      {
		vertexCount = 1;
		x[0] = inX; y[0] = outY;
	      }
	    else if (outX > inX + turnLength)
	      {
		vertexCount = 3;
		x[0] = inX;   y[0] = inY - turnLength;
		x[1] = aveX;  y[1] = inY - turnLength;
		x[2] = aveX;  y[2] = outY;
	      }
	    else
	      {
		int vertY = (outY < inY - turnLength) ? 
		  aveY : Math.min(inY - turnLength, outY - turnLength);
		vertexCount = 3;
		x[0] = inX;               y[0] = vertY;
		x[1] = outX - turnLength; y[1] = vertY;
		x[2] = outX - turnLength; y[2] = outY;
	      }
	    break;
	  case Directions.TOP:
	    if (outY < inY - turnLength)
	      {
		vertexCount = 2;
		x[0] = inX;  y[0] = aveY;
		x[1] = outX; y[1] = aveY;
	      }
	    else
	      {
		vertexCount = 4;
		x[0] = inX;    y[0] = inY - turnLength;
		x[1] = aveX;   y[1] = inY - turnLength;
		x[2] = aveX;   y[2] = outY + turnLength;
		x[3] = outX;   y[3] = outY + turnLength;
	      }
	    break;
	  case Directions.BOTTOM:
	    int vertY = Math.min(inY - turnLength, outY - turnLength);
	    vertexCount = 2;
	    x[0] = inX;  y[0] = vertY;
	    x[1] = outX; y[1] = vertY;
	    break;
	  }
	break;
      case Directions.BOTTOM:
	switch (outHeading)
	  {
	  case Directions.LEFT:
	    if (outX < inX - turnLength && outY > inY + turnLength)
	      {
		vertexCount = 1;
		x[0] = inX; y[0] = outY;
	      }
	    else if (outX < inX - turnLength)
	      {
		vertexCount = 3;
		x[0] = inX;    y[0] = inY + turnLength;
		x[1] = aveX;  y[1] = inY + turnLength;
		x[2] = aveX;  y[2] = outY;
	      }
	    else
	      {
		int vertY = (outY > inY + turnLength) ? 
		  aveY : Math.max(inY + turnLength, outY + turnLength);
		vertexCount = 3;
		x[0] = inX;               y[0] = vertY;
		x[1] = outX + turnLength; y[1] = vertY;
		x[2] = outX + turnLength; y[2] = outY;
	      }
	    break;
	  case Directions.RIGHT:
	    if (outX > inX + turnLength && outY > inY + turnLength)
	      {
		vertexCount = 1;
		x[0] = inX; y[0] = outY;
	      }
	    else if (outX > inX + turnLength)
	      {
		vertexCount = 3;
		x[0] = inX;   y[0] = inY + turnLength;
		x[1] = aveX;  y[1] = inY + turnLength;
		x[2] = aveX;  y[2] = outY;
	      }
	    else
	      {
		int vertY = (outY > inY + turnLength) ? 
		  aveY : Math.max(inY + turnLength, outY + turnLength);
		vertexCount = 3;
		x[0] = inX;               y[0] = vertY;
		x[1] = outX - turnLength; y[1] = vertY;
		x[2] = outX - turnLength; y[2] = outY;
	      }
	    break;
	  case Directions.TOP:
	    int vertY = Math.max(inY + turnLength, outY + turnLength);
	    vertexCount = 2;
	    x[0] = inX;  y[0] = vertY;
	    x[1] = outX; y[1] = vertY;
	    break;
	  case Directions.BOTTOM:
	    if (outY > inY + turnLength)
	      {
		vertexCount = 2;
		x[0] = inX;  y[0] = aveY;
		x[1] = outX; y[1] = aveY;
	      }
	    else
	      {
		vertexCount = 4;
		x[0] = inX;    y[0] = inY + turnLength;
		x[1] = aveX;   y[1] = inY + turnLength;
		x[2] = aveX;   y[2] = outY - turnLength;
		x[3] = outX;   y[3] = outY - turnLength;
	      }
	    break;
	  }
	break;
      }
    
    if (vertexCount == 0)
      {
	Point[] points = { new Point(inX, inY), new Point(inX, outY),
			   new Point(outX, outY) };
	return points;
      }
    else
      {
	Point[] points = new Point[vertexCount + 2];
	points[0] = new Point(inX,inY);
	points[vertexCount + 1] = new Point(outX, outY);
	
	for (int i = 0 ; i < vertexCount ; i++)
	  points[i+1] = new Point(x[i],y[i]);
	return points;
      }
  }
}


