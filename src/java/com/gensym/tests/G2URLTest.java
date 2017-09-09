
import java.net.*;
import com.gensym.ntw.TwAccess;
import com.gensym.classes.Item;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.net.g2.*;
import com.gensym.jgi.*;


/**
 * Tests the capabilities of the G2 URL mechanism.
 * Specify the protocol of the URL as <code>g2</code>. Plain URLs can
 * be used to fetch data from G2. They do not support setting the place
 * referenced by the URL. In order to set data in G2, use the class
 * G2URL (which does not extend URL, because the latter is a final class).
 * G2URLs can be made out of plain URL paths or by having a root item,
 * with the path being relative to this item.
 */

/*
 * The KB to use with this example is in /bt/vkp/junk/urltest.kb
 */

public class G2URLTest extends com.gensym.core.GensymApplication {

  G2URLTest () { super(new String[0]); }

  public static void main (String[] args) throws MalformedURLException, java.io.IOException, ConnectionTimedOutException, G2AccessException {
    new G2URLTest ();

    System.out.println(System.getProperties());
    
    /* Get Data from plain URL */
    URL myURL = new URL ("g2://bombay:1114/named-item?class=bar&name=noone/value?default-value=32/type=attribute&name=number-of-chips");
    Object y = myURL.getContent ();
    System.out.println ("****** URL Contents = (" + y.getClass() + ") = " + y);

    /* Get and set Data from full G2 URL */
    G2URL myG2URL = new G2URL ("g2://bombay:1114/named-item?class=bar&name=noone/value?default-value=32/type=attribute&name=number-of-chips");
    Object x = myG2URL.getContent ();
    System.out.println ("******* G2URL Contents , a " + x.getClass() + " = " + myG2URL + " -> " + x);
    myG2URL.setContent ("Let's have fun in Paris");

    /* Get and set Data from context G2 URL */
    com.gensym.jgi.G2Connection c = G2Gateway.getOrMakeConnection ("bombay", "1114");
    TwAccess g = (TwAccess)c.getUniqueNamedItem (Symbol.intern ("BAR"), Symbol.intern ("ME"));
    myG2URL = new G2URL ((Item)g, "/value?default-value=43/type=attribute&name=number-of-chips");
    x = myG2URL.getContent ();
    System.out.println ("******* G2URL Contents (from cached item) , a " + x.getClass() + " = " + myG2URL + " -> " + x);
    myG2URL.setContent ("Ho! Ho! Ho! And a bottle of rum...");
  }
}
