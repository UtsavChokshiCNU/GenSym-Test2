
import com.gensym.util.Sequence;

public class SequenceTest {

  public static void main (String args[]) {

    Sequence s = new Sequence (10);

    s.addElement (new Integer (5));
    s.addElement (new Float (10.1));
    s.addElement (new Double (3.141592));
    s.addElement ("Hello World");

    System.out.println (s.toString());

    Object[] contents = s.getContents ();
    for (int i=0; i<contents.length; i++)
      System.out.println (" #" + i + " = " + contents[i].toString ());

    Sequence s0 = new Sequence (3), s1 = new Sequence (3), s2 = new Sequence (3);
    s0.addElement (new Integer (0));
    s0.addElement (new Integer (1));
    s0.addElement (new Integer (2));

    s1.addElement (new Integer (0));
    s1.addElement (new Integer (1));
    s1.addElement (new Integer (2));

    s2.addElement (new Integer (0));
    s2.addElement (new Integer (2));
    s2.addElement (new Integer (1));

    System.out.println ("s0.hashCode () = " + s0.hashCode ());
    System.out.println ("s1.hashCode () = " + s1.hashCode ());
    System.out.println ("s2.hashCode () = " + s2.hashCode ());

    System.out.println ("S0 =? S0 : " + s0.equals (s0));
    System.out.println ("S0 =? S1 : " + s0.equals (s1));
    System.out.println ("S0 =? S2 : " + s0.equals (s2));

    Sequence s3 = (Sequence) s1.clone ();
    System.out.println ("Clone of " + s1.print() + "\n ==> " + s3.print());
    s3.concatenate (s2);
    System.out.println ("Concatenated Sequence Copy --> " + s3.print ());
    System.out.println ("Original Sequence (unaffected) --> " + s1.print ());
  }
}
