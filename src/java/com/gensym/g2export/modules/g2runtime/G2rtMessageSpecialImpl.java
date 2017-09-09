package com.gensym.g2export.modules.g2runtime;

import java.lang.reflect.*;
import java.util.Hashtable;
import com.gensym.g2export.G2__BaseImpl;
import com.gensym.fida.message.Message;
import com.gensym.util.Sequence;

public class G2rtMessageSpecialImpl extends G2__BaseImpl implements Message
{

  public String replyExceptionName;
  public String replyExceptionText = "";
  public Object reply = null;
  public Sequence relpySeq = null;
  public String category = "";
  public double timestamp;
  public Exception exception;
  private Object content;
  private Hashtable attributes;
  private String contentType;
  
  public String getCategory()
  {
    return category;
  }

  public void setCategory(String category)
  {
    this.category = category;
  }


  public void setTimeStamp(long UTC)
  {
    timestamp = (double)UTC;
  }


  public long getTimeStamp()
  {
    return (long)timestamp;
  }


  public void set_replySeq(Sequence seq)
  {
    if (seq.size() > 0)
      reply= seq.elementAt(0);
    else
      reply= null;
  }
  
  public void setReply(Object value)
  {
    reply = value;
    Sequence seq = new Sequence(1);
    seq.addElement(value);
  }

  public void setException(Exception ex)
  {
    try {
      Class exceptionClass = Class.forName(replyExceptionName);
      Constructor cons = exceptionClass.getConstructor(new Class[] {String.class});
      exception = (Exception)cons.newInstance(new Object[] {replyExceptionText});
    } catch (Exception e) {
      exception = e;
    }
  }

  public Object getReply()
  {
    return reply;
  }

  public Exception getRepliedException()
  {
    return exception;
  }

  /**
   * Set an attribute of this message.
   * @param attributeName The non-null name of the attribute to set.
   * @param attributeValue The possibly null new attribute value.
   */
  public void setAttributeValue(String attributeName, Object attributeValue)
  {
    if (attributeName == null)
      return;
    if (attributes == null)
      attributes = new Hashtable();
    attributes.put(attributeName, attributeValue);
  }
  
  /**
   * Get the value of an attribute of this message.
   * @param attributeName The non-null name of the attribute to get.
   * @return the possibliy null value of the attribute.
   */
  public Object getAttributeValue(String attributeName)
  {
    if (attributes == null || attributeName == null)
      return null;
    return attributes.get(attributeName);
  }

  /**
   * Set the content of this message.
   * @param content The content if this message.
   */
  public void setContent(Object content)
  {
    this.content = content;
  }


  /**
   * Get the value of the contents of the message.
   * @return The possibliy null content of this message.
   */
  public Object getContent()
  {
    return content;
  }

  /**
   * Get the message contents Type.
   * @return the possibly null content type of this message.
   */
  public String getContentType()
  {
    return contentType;
  }

}
