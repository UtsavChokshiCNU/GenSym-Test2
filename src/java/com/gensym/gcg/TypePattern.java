package com.gensym.gcg;

import com.gensym.types.*;
import com.gensym.util.Cons;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import java.util.Vector;
import java.io.*;
import java.awt.Component;
import java.lang.reflect.Constructor;
import java.nio.charset.Charset;

public class TypePattern
{
  private static final int MAX_STACK = 100;
  
  private Object patternSpec;
  private Cons builderSpec;
  private Symbol[] bindingNames = new Symbol[MAX_STACK];
  private G2Type[] bindingTypes = new G2Type[MAX_STACK];
  private int stackPointer = 0;
  private boolean matchExactly = false;

  private static final Symbol structure_ = Symbol.intern("STRUCTURE");
  private static final Symbol slots_ = Symbol.intern("SLOTS");
  private static final Symbol requiredSlots_ 
    = Symbol.intern("REQUIRED-SLOTS");
  private static final Symbol type_ 
    = Symbol.intern("TYPE");
  private static final Symbol attributeName_ 
    = Symbol.intern("ATTRIBUTE-NAME");
  private static final Symbol sequence_ = Symbol.intern("SEQUENCE");
  private static final Symbol elementType_ 
    = Symbol.intern("ELEMENT-TYPE");
  private static final Symbol minimumElements_ 
    = Symbol.intern("MINIMUM-ELEMENTS");
  private static final Symbol maximumElements_ 
    = Symbol.intern("MAXIMUM-ELEMENTS");

  private static final Symbol member_ = Symbol.intern("MEMBER");
  private static final Symbol possibleValues_ 
    = Symbol.intern("POSSIBLE-VALUES");

  private static final Symbol class_ = Symbol.intern("CLASS");
  private static final Symbol className_ 
    = Symbol.intern("CLASS-NAME");


  private static final Symbol one_ = Symbol.intern("ONE");
  private static final Symbol any_ = Symbol.intern("ANY");
  private static final Symbol alt_ = Symbol.intern("ALT");
  private static final Symbol bind_ = Symbol.intern("BIND");
  private static final Symbol exactly_ = Symbol.intern("EXACTLY");
  private static final Symbol generally_ = Symbol.intern("GENERALLY");

  private static final Symbol and_ = Symbol.intern("AND");
  private static final Symbol or_ = Symbol.intern("OR");
  private static final Symbol not_ = Symbol.intern("NOT");

  private static final Symbol none_ = Symbol.intern("NONE");
  private static final Symbol value_ = Symbol.intern("VALUE");
  private static final Symbol itemOrValue_ = Symbol.intern("ITEM-OR-VALUE");

  private static final Symbol float_ = Symbol.intern("FLOAT");
  private static final Symbol integer_ = Symbol.intern("INTEGER");
  private static final Symbol quantity_ = Symbol.intern("QUANTITY");
  private static final Symbol symbol_ = Symbol.intern("SYMBOL");
  private static final Symbol text_ = Symbol.intern("TEXT");
  private static final Symbol truthValue_ = Symbol.intern("TRUTH-VALUE");
  private static final Symbol noItem_ = Symbol.intern("NO-ITEM");

  private static IntegerType scratchIntegerType = new IntegerType();
  private static FloatType scratchFloatType = new FloatType();
  private static SymbolType scratchSymbolType = new SymbolType();
  private static TextType scratchTextType = new TextType();

  private static final int MAX_OR_ELEMENTS = 4;
  private static int[][][] permutationTable 
  = { 
    { {} },
    { {0} },
    { {0, 1 } , {1 , 0 } },
    { {0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}}, 
    { {0, 1, 2, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}, {0, 2, 3, 1}, {0, 3, 1, 2}, {0, 3, 2, 1},
      {1, 0, 2, 3}, {1, 0, 3, 2}, {1, 2, 0, 3}, {1, 2, 3, 0}, {1, 3, 0, 2}, {1, 3, 2, 0},
      {2, 0, 1, 3}, {2, 0, 3, 1}, {2, 1, 0, 3}, {2, 1, 3, 0}, {2, 3, 0, 1}, {2, 3, 1, 0},
      {3, 0, 1, 2}, {3, 0, 1, 2}, {3, 1, 0, 2}, {3, 1, 2, 0}, {3, 2, 0, 1}, {3, 2, 1, 0} }
    
  };
  private static int[] permutationCounts = {1, 1, 2, 6, 24};

  public TypePattern(Object pattern, Object builderSpec)
  {
    patternSpec = pattern;
    if (checkBuilderSpec(builderSpec))
      this.builderSpec = (Cons) builderSpec;
    else
      throw new RuntimeException("Bad Builder Spec: "+builderSpec);
  }

  private boolean checkBuilderSpec(Object builderSpec)
  {
    if (builderSpec instanceof Cons)
      {
	Cons specList = (Cons) builderSpec;
	if (specList.isProperList())
	  {
	    if (specList.car instanceof String)
	      {
		Cons tail = specList.tail();
		while (tail != null)
		  if ((tail.car instanceof Symbol) ||
		      (tail.car instanceof Boolean))
		    tail = tail.tail();
		  else
		    return false;
		return true;
	      }
	    else
	      return false;
	  }
	else
	  return false;
      }
    return false;
  }

  public static Vector readPatternFile(InputStream stream)
       throws IOException
  {
    BufferedReader reader = new BufferedReader(new InputStreamReader(stream, Charset.defaultCharset()));
    Vector patterns = new Vector();
    
    try 
      {
	while (true)
	  {
	    Object pattern = Cons.read(reader);
	    Object builderSpec = Cons.read(reader);
	    if (false)
	      System.out.println("Cons.read -> "+pattern);
	    patterns.addElement(new TypePattern(pattern,builderSpec));
	  }
      } catch (EOFException e) {
	reader.close();
      }

    return patterns;
  }

  public synchronized Structure match(G2Type type)
  {
    stackPointer = 0;
    boolean trace = false;
    Structure bindings = null;
    PrintWriter writer;

    if (trace)
      {
	writer = new PrintWriter(new OutputStreamWriter(System.out, Charset.defaultCharset()),true);
	System.out.println("matching pattern "+patternSpec+" against ");
	type.pprint(writer,0);
	writer.flush(); // hack around bug.
      }

    if (matchDispatch(type,patternSpec))
      {
	bindings = new Structure();
	for (int i = 0; i<stackPointer; i++)
	  bindings.setAttributeValue(bindingNames[i],bindingTypes[i]);
      }

    if (trace)
      {
	System.out.println("    result = "+bindings);
	System.out.println("");
      }

    return bindings;
  }

  private boolean matchDispatch(G2Type type, Object pattern)
  {
    // System.out.println("hoping that "+pattern+" includes");
    // type.pprint(new PrintWriter(System.out),2);
    // System.out.println("");
    if (pattern instanceof Cons)
      {
	Cons patternList = (Cons)pattern;
	Symbol key = (Symbol) patternList.car;
	// Control Directives
	if (key.equals(alt_))
	  return matchAlt(type,patternList);
	else if (key.equals(bind_))
	  return matchBind(type,patternList);
	else if (key.equals(exactly_))
	  return matchWithExactness(type,patternList,true);
	else if (key.equals(generally_))
	  return matchWithExactness(type,patternList,false);
	  
	// CompoundTypes
	else if (key.equals(or_))
	  return matchOr(type,patternList);
	else if (key.equals(and_))
	  return matchAnd(type,patternList);
	
	// parameterized types
	else if (key.equals(class_))
	  return matchClass(type,patternList);
	else if (key.equals(sequence_))
	  return matchSequence(type,patternList);
	else if (key.equals(structure_))
	  return matchStructure(type,patternList);
	else if (key.equals(member_))
	  return matchMember(type,patternList);
	else
	  throw new RuntimeException("unknown pattern "+pattern);
      }
    // Simple Types

    // here implement exactness and itemOrValue handling
    else if (pattern.equals(noItem_))
      return type instanceof NoItemType;
    else if (pattern.equals(value_))
      return  matchExactly ? 
	      type.getClass() == ValueType.class :
	      type instanceof ValueType;
    else if (pattern.equals(itemOrValue_))
      return matchExactly ? 
	      type.getClass() == ItemOrValueType.class :
	      type instanceof ItemOrValueType;
    else if (pattern.equals(integer_))
      return type instanceof IntegerType;
    else if (pattern.equals(float_))
      return type instanceof FloatType;
    else if (pattern.equals(quantity_))
      return matchExactly ? 
	      type.getClass() == QuantityType.class : 
              type instanceof QuantityType;
    else if (pattern.equals(text_))
      return type instanceof TextType;
    else if (pattern.equals(truthValue_))
      return type instanceof TruthValueType;
    else if (pattern.equals(symbol_))
      return type instanceof SymbolType;
    else
      throw new RuntimeException("unknown pattern: "+pattern);
  }

  private boolean matchAlt(G2Type type, Cons pattern)
  {
    if (pattern.isProperList())
      {
	Cons tail = pattern.tail();
	int savedStack = stackPointer;
	while (tail != null)
	  {
	    stackPointer = savedStack;
	    if (matchDispatch(type,tail.car))
	      return true;
	    tail = tail.tail();
	  }
	return false;
      }
    else 
      throw new RuntimeException("unknown pattern: "+pattern);
  }

  private boolean matchWithExactness(G2Type type, Cons pattern, boolean exactness)
  {
    if (pattern.isProperList() &&
	pattern.properListLength() > 1)
      {
	boolean previousValue = matchExactly;
	matchExactly = exactness;
	boolean result = matchDispatch(type,pattern.second());
	matchExactly = previousValue;
	return result;
      }
    else 
      throw new RuntimeException("unknown pattern: "+pattern);
  }

  private boolean matchBind(G2Type type, Cons pattern)
  {
    if (pattern.isProperList() &&
	pattern.properListLength() == 3)
      {
	Symbol bindingName = (Symbol)pattern.second();
	Object realPattern = pattern.third();
	
	if (matchDispatch(type,realPattern))
	  {
	    // must only accumulate bindings in true match
	    bindingNames[stackPointer] = bindingName;
	    bindingTypes[stackPointer] = type;
	    stackPointer++;
	    if (stackPointer == MAX_STACK)
	      throw new RuntimeException("TypePattern Binding Stack Overflow near "+
					 pattern);
	    return true;
	  }
	else
	  return false;
      }
    else 
      throw new RuntimeException("unknown pattern "+pattern);
  }

  private boolean matchAnd(G2Type type, Cons pattern)
  {
    if (type instanceof IntersectionType)
      {
	return false;
      }
    else return false;
  }

  private boolean matchOr(G2Type type, Cons pattern)
  {
    if (type instanceof UnionType)
      {
	UnionType unionType = (UnionType)type;
	Object cdr = pattern.cdr;
	if (cdr == null)
	  return false;
	else if (cdr instanceof Cons)
	  {
	    Cons disjunctPatterns = (Cons) cdr;
	    G2Type[] disjunctTypes = unionType.getDisjuncts();
	    if (!(disjunctPatterns.isProperList() &&
		  disjunctPatterns.properListLength() <= MAX_OR_ELEMENTS))
	      throw new RuntimeException("unknown pattern "+pattern);
	    else if (disjunctTypes.length > MAX_OR_ELEMENTS || disjunctTypes.length != disjunctPatterns.properListLength())
	      return false;
	    
	    int i,j, length = disjunctTypes.length,
	        count = permutationCounts[length],
	        savedStack = stackPointer;
	    int[][] permutations = permutationTable[length];
	    for (i=0; i<count ; i++)
	      {
		// System.out.println("matching Or perm = "+i);
		int[] permutation = permutations[i];
		boolean ok = true;
		stackPointer = savedStack;
		Cons tail = disjunctPatterns;
		for (j=0 ; j<length ; j++)
		  if (!matchDispatch(disjunctTypes[permutation[j]],
				     tail.car))
		    { 
		      ok = false;
		      break;
		    }
		  else 
		    tail = tail.tail();
		if (ok)
		  return true;
	      }
	    return false;
	  }
	else
	  throw new RuntimeException("unknown pattern "+pattern);
      }
    else return false;
  }

  private boolean matchClass(G2Type type, Cons pattern)
  {
    // this should do something about specific classes at some point.
    return type instanceof ClassType;
  }

  private boolean matchSequence(G2Type type, Cons pattern)
  {
    if (type instanceof SequenceType)
      {
	Object cdr = pattern.cdr;
	// eliminate irregular/easy case;
	if (cdr == null)
	  return true;
	else if (cdr instanceof Cons)
	  {
	    Cons tail = (Cons) cdr;
	    SequenceType sequenceType = (SequenceType)type;
	    return matchDispatch(sequenceType.getElementType(),tail.car);
	  }
	else
	  throw new RuntimeException("unknown pattern: "+pattern);
      }
    else
      return false;
  }

  private boolean matchStructure(G2Type type, Cons pattern)
  {
    if (type instanceof StructureType)
      {
	Object cdr = pattern.cdr;
	StructureType structureType = (StructureType) type;
	if (cdr == null)
	  return true;
	else if (pattern.isProperList())
	  {
	    return true; // give up for now
	  }
	else
	  throw new RuntimeException("unknownPattern: "+pattern);
      }
    else
      return false;
  }

  private boolean matchMember(G2Type type, Cons pattern)
  {
    if (type instanceof MemberType)
      {
	Object cdr = pattern.cdr;
	MemberType memberType = (MemberType)type;
	// eliminate irregular/easy case;
	if (cdr == null)
	  return true;
	else if (pattern.isProperList())
	  {
	    Object second = pattern.second();
	    Object anyPattern = null;
	    Object singletonPattern = null;
	    Cons tail;
	    
	    if (second instanceof Cons &&
		(((Cons)second).car.equals(any_) ||
		 ((Cons)second).car.equals(one_)))
	      {
		Cons oneOrAnySpec = (Cons)second;
		Object key = oneOrAnySpec.car;
		if (oneOrAnySpec.isProperList() && 
		    oneOrAnySpec.properListLength() == 2)
		  {
		    tail = pattern.tail().tail();
		    if (key.equals(any_))
		      anyPattern = oneOrAnySpec.second();
		    else
		      singletonPattern = oneOrAnySpec.second();
		  }
		else
		  throw new RuntimeException("unknown pattern: "+pattern);
	      }
	    else
	      tail = pattern.tail();
	    
	    // match the members allowing anyType if not explicitly mentioned
	    Object[] members = memberType.getMembers();
	    int i;
	    if (singletonPattern != null)
	      return (members.length == 1) && 
		      matchDispatch(inventTypeForMember(members[0]),
				    singletonPattern);
	    else if (anyPattern != null)
	      {
		for (i = 0; i<members.length ; i++)
		  if (!matchDispatch(inventTypeForMember(members[i]),anyPattern) &&
		      !findMemberInList(members[i],tail))
		    return false;
		return true;
	      }
	    else 
	      {
		for (i = 0; i<members.length ; i++)
		  if (!findMemberInList(members[i],tail))
		    return false;
		return true;
	      }
	  }
	else
	  throw new RuntimeException("unknown pattern: "+pattern);
      }
    else
      return false;
  }
  
  private static G2Type inventTypeForMember(Object member)
  {
    if (member instanceof Double)
      return scratchFloatType;
    else if (member instanceof Integer)
      return scratchIntegerType;
    else if (member instanceof Symbol)
      return scratchSymbolType;
    else if (member instanceof String)
      return scratchTextType;
    else
      throw new RuntimeException("unexpected type for member "+member);
  }
  
  private static boolean findMemberInList(Object member, Cons list)
  {
    Cons tail = list;
    while (tail != null)
      if (tail.car.equals(member))
	return true;
      else if (tail.cdr instanceof Cons)
	tail = (Cons) tail.cdr;
      else
	throw new RuntimeException("not a proper list "+list);
    return false;
  } 

  protected Component invokeEditorBuilder(Structure bindings)
   {
     try
       {
	 String builderName = (String) builderSpec.car;
	 Class builderClass = Class.forName(builderName);
	 
	 int i, length = builderSpec.properListLength() - 1;
	 Class[] argTypes = new Class[length];
	 Object[] args = new Object[length];
	 Cons tail = builderSpec.tail();
	 for (i=0; i<length ; i++)
	   {	     
	     Object argSpec = tail.car;
	     // System.out.println("argSpec = "+argSpec);
	     if (argSpec instanceof Symbol)
	       {
		 argTypes[i] = G2Type.class;
		 args[i] = (G2Type) bindings.getAttributeValue((Symbol)argSpec,null);
	       }
	     else 
	       {
		 argTypes[i] = Boolean.class;
		 args[i] = argSpec;
	       }
	     // System.out.println("argType = "+argTypes[i]);
	     tail = tail.tail();
	   }
	 Constructor constructor = builderClass.getConstructor(argTypes);
	 EditorBuilder builder = (EditorBuilder) constructor.newInstance(args);
	 return builder.buildEditor();
       } catch (Exception e)
	 {
	   System.out.println("Editor Builder Invocation Failure:");
	   e.printStackTrace();
	   return null;
	 }
  }

  public static void main(String[] args)
       throws IOException
  {
    Vector patterns = readPatternFile(new FileInputStream(args[0]));
    
    G2Type[] testTypes = new G2Type[8];
    testTypes[0] = new FloatType();
    testTypes[1] = new IntegerType();
    testTypes[2] = new UnionType(new G2Type[] { new FloatType(), new IntegerType() });
    testTypes[3] = new UnionType(new G2Type[] { new IntegerType(), new FloatType() });
    testTypes[4] = new UnionType(new G2Type[] { new FloatType(), new TextType() });
    testTypes[5] = new SequenceType();
    testTypes[6] = new SequenceType(new IntegerType());
    testTypes[7] = new StructureType();
    
    int i,j,size = patterns.size();
    PrintWriter writer = new PrintWriter(new OutputStreamWriter(System.out, Charset.defaultCharset()), true);
    for (i=0 ; i<size ; i++)
      for (j=0; j<testTypes.length ; j++)
	{
	  TypePattern pattern = (TypePattern)patterns.elementAt(i);
	  G2Type type = testTypes[j];
	  
	  System.out.println("matching pattern "+pattern.patternSpec+" against ");
	  type.pprint(writer,0);
	  writer.flush(); // hack around bug.
	  
	  Structure result = pattern.match(type);
	  System.out.println("    result = "+result);
	  System.out.println("");
	}
    
  }
}
