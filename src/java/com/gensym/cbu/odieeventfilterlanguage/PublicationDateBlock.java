package com.gensym.cbu.odieeventfilterlanguage;

import java.util.Date;

public class PublicationDateBlock extends EventFilterBlock
{
  long earliestTimeDelta = -1;
  long latestTimeDelta = -1;

  public long getEarliestTimeDelta()
  {
    return earliestTimeDelta;
  }

  public void setEarliestTimeDelta(long earliestTimeDelta)
  {
    this.earliestTimeDelta = earliestTimeDelta;
    if (earliestTimeDelta == -1 
	&& latestTimeDelta == -1)
      properlyConfigured = false;
    else 
      properlyConfigured = true;
  }

  public long getLatestTimeDelta()
  {
    return latestTimeDelta;
  }

  public void setLatestTimeDelta(long latestTimeDelta)
  {
    this.latestTimeDelta = latestTimeDelta;
    if (earliestTimeDelta == -1 
	&& latestTimeDelta == -1)
      properlyConfigured = false;
    else 
      properlyConfigured = true;
  }

  @Override
  public String booleanExpression()
  {
    StringBuffer booleanExpression = new StringBuffer("(");
     if (earliestTimeDelta > 0)
       booleanExpression.append("(odieEvent.getPublicationDate()).after((new Date(new Date()).getTime() " +
				"- earliestTimeDelta))");
     if (earliestTimeDelta > 0 && latestTimeDelta > 0)
       booleanExpression.append(" && ");
     if (latestTimeDelta > 0)
       booleanExpression.append("(odieEvent.getPublicationDate()).before((new Date(new Date()).getTime() " + 
				"- earliestTimeDelta))");
     booleanExpression.append(")");
    return booleanExpression.toString();
  }
}



















