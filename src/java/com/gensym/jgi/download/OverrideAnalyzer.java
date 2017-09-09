
package com.gensym.jgi.download;

import java.io.*;
import java.nio.charset.Charset;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.StringTokenizer;
import java.util.Vector;
import com.gensym.core.DebugUtil;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

/** 
 * This class can be used to generate overrides for classes in G2.
 * In order to use it, first write the implementation for the overrides
 * in a Java class that inherits directly from com.gensym.classes.G2__BaseImpl.
 * Then use this class to generate the overrides structure as follows:
 * <code> OverrideAnalyzer oa = new OverrideAnalyzer (fileName);
 * Structure overrides = oa.parse (); </code>
 * <p>
 * The generator parses the file into the component blocks and
 * inserts them into the overrides structure appropriately. It
 * currently places the following restrictions on the code
 * that implements the overrides :
 * <ul>
 * <li> No inner classes
 * <li> No comments in field or method declarations
 * <li> Unique import statements
 * </ul>
 *
 */
public class OverrideAnalyzer implements com.gensym.util.symbol.OverrideSymbols {

  private static final Symbol IMPORTS_ = Symbol.intern ("IMPORTS");
  private static final Symbol INSTANCE_INITIALIZER_ = Symbol.intern ("INSTANCE-INITIALIZER");
  private static final String NO_COMMENTS="  /**\n   * No comment for this member\n   */\n";
  private static final String PUBLIC = "public";
  private String commentedClassCode, classCode, className;
  private String CR = "\n", semiColon = ";", openParen = "{", closeParen = "}", equalSign = "=";
  private Vector members = new Vector (10), comments = new Vector (10);
  private int classStartIndex;
  Structure classStruct, classInfo;
  Sequence methods, fields, events, properties, imports;
  private Hashtable methodTable   = new Hashtable (29),
                    fieldTable    = new Hashtable (17),
                    eventTable    = new Hashtable (7),
                    propertyTable = new Hashtable (11),
                    importTable   = new Hashtable (11);
  private static final Integer CURRENT_VERSION = 1;
  private Vector undocumentedPublicMembers;

  /**
   * Constructs a new OverrideAnalyzer to parse the specfied file.
   *
   * @param fileName the name of the file to generate overrides from.
   */
  public OverrideAnalyzer (String fileName) throws IOException {
    File f = new File (fileName);
    if (!f.exists ())
      throw new IOException ("File " + fileName + " does not exist");
    int fileLength = (int)f.length ();
    FileInputStream fis = new FileInputStream (f);
    byte[] fileContents = new byte[fileLength];
    fis.read (fileContents);
    commentedClassCode = new String (fileContents, Charset.defaultCharset());
  }

  /**
   * Constructs a new OverrideAnalyzer 
   *
   */
  public OverrideAnalyzer ()
  {
       commentedClassCode = "";
  }

  /**
   * Returns a structure conforming to the specification of the
   * overrides. It has 5 attributes: PROPERTIES, METHODS, EVENTS,
   * FIELDS, and IMPORTS, each of which is a sequence of
   * appropriate structures.
   *
   * @return an overrides structure
   */
  public Structure parse () {
    classCode = discardComments (commentedClassCode);

    classStruct = new Structure ();
    classStruct.setAttributeValue (VERSION_, CURRENT_VERSION);
    classStruct.setAttributeValue (CLASS_INFO_, classInfo = new Structure ());
    classStruct.setAttributeValue (EVENTS_, events = new Sequence ());
    classStruct.setAttributeValue (METHODS_, methods = new Sequence ());
    classStruct.setAttributeValue (FIELDS_, fields = new Sequence ());
    classStruct.setAttributeValue (IMPORTS_, imports = new Sequence ());
    classStruct.setAttributeValue (PROPERTIES_, properties = new Sequence ());

    readPackage ();
    readImports ();
    readClassDeclaration ();
    readMembers ();

    Enumeration e = methodTable.elements ();
    while (e.hasMoreElements ())
      methods.addElement (e.nextElement ());
    return classStruct;
  }

  /**
   * Returns a structure conforming to the specification of the
   * overrides. It has 5 attributes: PROPERTIES, METHODS, EVENTS,
   * FIELDS, and IMPORTS, each of which is a sequence of
   * appropriate structures.
   *
   * @param  commentedClassCode code to parse
   * @return an overrides structure
   */
  public Structure parse(String commentedClassCode)
  {
    this.commentedClassCode = commentedClassCode;
    return parse();
  }

  /**
   * Allows this class to be executed from the comamnd line.
   * The command-line must specify two arguments : the name
   * of the file to parse and the name of the file in which
   * to store the overrides.
   *
   * @param args the command-line arguments
   */
  public static void main (String[] args) throws IOException {
    OverrideAnalyzer o = new OverrideAnalyzer (args[0]);
    Structure s = o.parse ();
    DebugUtil.writeToFile (s, args[1]);
    if (o.undocumentedPublicMembers != null)
      new com.gensym.dlg.MessageDialog (null, "Naughty, Naughty!", true,
					"Undocumented Public Members exist in this override.\n" + o.undocumentedPublicMembers,
					null).setVisible (true);
    com.gensym.core.ExitThread.exit ();
  }

  private String discardComments (final String str) {
	  String strComment = str;
    StringBuffer strBuffer = new StringBuffer (strComment);
    int endOfLastRemovedComment = 0;
    while (true) {
      int regCommentIndex = strComment.indexOf ("/*");
      int docCommentIndex = strComment.indexOf ("/**");
      int lineCommentIndex = strComment.indexOf ("//");
      /*System.out.println (">> " + regCommentIndex + "(" + 
			  docCommentIndex + ") : " +
			  lineCommentIndex);*/
      if (regCommentIndex < 0 && lineCommentIndex < 0)
	break;
      int startIndex, endIndex;
      if ((lineCommentIndex < 0) ||
	  (regCommentIndex >= 0 && regCommentIndex < lineCommentIndex)) {
	//System.out.println ("SlashStar Comment");
	startIndex = regCommentIndex;
	endIndex = strComment.indexOf ("*/", startIndex) + 2;
	if (regCommentIndex == docCommentIndex) {
	  // make sure that we don't remove a comment that has already
	  // been removed
	  int origStartIndex = commentedClassCode.indexOf (strComment.substring (startIndex, endIndex),
							   endOfLastRemovedComment);
	  endOfLastRemovedComment = origStartIndex + endIndex - startIndex;
	  comments.addElement
	    (new CommentInfo (origStartIndex, origStartIndex - startIndex + endIndex, strComment.substring (startIndex, endIndex)));
	  blank (strBuffer, origStartIndex, origStartIndex - startIndex + endIndex);
 	  /*System.out.println ("DOC COMMENT: (" + origStartIndex + 
 			      ", " + (origStartIndex - startIndex + endIndex) +
 			      ") " + str.substring (startIndex, endIndex));*/
	}
      } else {
	//System.out.println ("SlashSlash Comment");
	startIndex = lineCommentIndex;
	endIndex = strComment.indexOf (CR, startIndex);
	int origStartIndex = commentedClassCode.indexOf (strComment.substring (startIndex, endIndex));
	blank (strBuffer, origStartIndex, origStartIndex - startIndex + endIndex);
      }
      //System.out.println ("Discarding (" + startIndex + ", " + endIndex + ")");
      strComment = strComment.substring (0, startIndex) + strComment.substring (endIndex);
    }
    //System.out.println ("After removing comments : \n" + str);
    //System.out.println ("--------------------------------------------------------------------------------");
    //System.out.println ("Blanking comments : \n" + strBuffer.toString ());
    //System.out.println ("--------------------------------------------------------------------------------");
    return strBuffer.toString ();
  }

  private void blank (StringBuffer strB, int startIndex, int endIndex) {
    for (int i=startIndex; i<endIndex; i++)
      if (strB.charAt (i) != '\n')
	strB.setCharAt (i, ' ');
  }

  int curPosn = 0;
  private void readPackage () {
    int curPPosn = classCode.indexOf ("package");
    int endPosn = classCode.indexOf (semiColon);
    //System.out.println ("PACKAGE: " + classCode.substring (curPosn + 7, endPosn).trim ());
    if (curPPosn != -1)  // not found;
      curPosn = endPosn + 1;

  }

  private void readImports () {
    int classPosn = classCode.indexOf ("public class", curPosn);
    //System.out.println ("CursorPosn : public class = " + curPosn + " : " + classPosn);
    String importsHdr = classCode.substring (curPosn, classPosn);
    parseImports (importsHdr);
    curPosn = classPosn;
  }

  private void parseImports (String importsHdr) {
    int posn = 0;
    while (true) {
      int scIndex = importsHdr.indexOf (semiColon, posn);
      if (scIndex < 0)
	break;
      int keywdIndex = importsHdr.indexOf ("import ", posn);
      String typeOrPackage = importsHdr.substring (keywdIndex + 7, scIndex).trim ();
      //System.out.println ("IMPORT: " + typeOrPackage);
      posn = scIndex + 1;
      Structure importStruct = createImportStruct (typeOrPackage);
      imports.addElement (importStruct);
    }
  }

  private Structure createImportStruct (String typeOrPackage) {
    boolean onDemand = typeOrPackage.endsWith ("*");
    int sp1Index = typeOrPackage.lastIndexOf ('.');
    Symbol importName = null;
    if (onDemand) {
      do {
	int searchBackIndex = sp1Index;
	int sp2Index = typeOrPackage.lastIndexOf ('.', searchBackIndex - 1);
	importName = backOutG2NameFromJavaName ("Package-" + typeOrPackage.substring (sp2Index + 1, sp1Index));
      } while (importTable.get (importName) != null);
    } else {
      importName = backOutG2NameFromJavaName (typeOrPackage.substring (sp1Index + 1)); // Simple names should not collide
    }
    importTable.put (importName, importName);
    Structure importStruct = new Structure ();
    importStruct.setAttributeValue (IMPORT_NAME_, importName);
    importStruct.setAttributeValue (TYPE_OR_PACKAGE_, typeOrPackage);
    return importStruct;
  }

  private void readClassDeclaration () {
    classStartIndex = classCode.indexOf (openParen);
    System.out.println ("CLASS: " + classCode.substring (curPosn, classStartIndex));
    String classDeclaration = classCode.substring (curPosn, classStartIndex);
    Sequence interfaces = new Sequence ();
    int intfIndex = classDeclaration.indexOf ("implements");
    if (intfIndex > 0) {
      String intfCode = classDeclaration.substring (intfIndex + 11);
      for (StringTokenizer tknzr = new StringTokenizer (intfCode, " ,\t\n\r");
	   tknzr.hasMoreTokens ();) {
	interfaces.addElement (tknzr.nextToken ());
      }
    }
    classInfo.setAttributeValue (INTERFACES_, interfaces);
    int classNameIndex = classCode.indexOf ("class ") + 6;
    int classNameEndIndex = classCode.indexOf (" ", classNameIndex);
    className = classCode.substring (classNameIndex, classNameEndIndex);
    curPosn = classStartIndex + 1;
  }

  private static final int NONE = 0, FIELD = 1, METHOD = 2;
  private void readMembers () {
    int nextMemberType;
    while ((nextMemberType = nextMember ()) != NONE) {
      if (nextMemberType == FIELD)
	readField ();
      else
	readMethod ();
    }
  }

  private int nextMember () {
    int scIndex = classCode.indexOf (semiColon, curPosn);
    int opIndex = classCode.indexOf (openParen, curPosn);
    int eqIndex = classCode.indexOf (equalSign, curPosn);
    boolean isEqualBeforeOp = eqIndex < 0 || opIndex < eqIndex;
    if (scIndex < 0 && opIndex < 0)
      return NONE;
    else if (opIndex >= 0 && (scIndex < 0 || (opIndex < scIndex && isEqualBeforeOp)))
      return METHOD;
    else
      return FIELD;
  }

  private void readField () {
    int scIndex = classCode.indexOf (semiColon, curPosn);
    String field = classCode.substring (curPosn, scIndex).trim ();
    //System.out.println ("FIELD: " + field);
    Symbol fieldKey = createMemberStruct (field, FIELD);
    Structure fieldStruct = (Structure) fieldTable.get (fieldKey);
    fields.addElement (fieldStruct);
    //String comment = readCommentForMember (classCode.substring (curPosn, scIndex).trim (), FIELD);
    curPosn = scIndex + 1;
  }

  private void readMethod () {
    int parenDepth = 1;
    int posn = classCode.indexOf (openParen, curPosn) + 1;
    while (parenDepth > 0) {
      int opIndex = classCode.indexOf (openParen, posn);
      int clIndex = classCode.indexOf (closeParen, posn);
      if (opIndex < 0 || clIndex < opIndex) {
	parenDepth--;
	posn = clIndex + 1;
      } else {
	parenDepth++;
	posn = opIndex + 1;
      }
    }
    String method = classCode.substring (curPosn, posn).trim ();
    //System.out.println ("METHOD: " + method);
    Symbol methodKey = createMemberStruct (method, METHOD);
    //methods.addElement (methodTable.get (methodKey));
    //System.out.println ("methodTable.get (" + methodKey + ") = " + methodTable.get (methodKey));
    checkIfPropertyMethod (methodKey);
    checkIfEventMethod (methodKey);
    checkIfConstructor (methodKey);
    //System.out.println ("COMMENT: " + readCommentForMember (classCode.substring (curPosn, posn).trim (), METHOD));
    curPosn = posn;
  }

  private void checkIfPropertyMethod (Symbol methodKey) {
    Structure methodStruct = (Structure) methodTable.get (methodKey);
    String methodDeclaration = (String) methodStruct.getAttributeValue (INTERFACE_, null);
    String methodName = getMethodNameFromDeclaration (methodDeclaration);
    if (methodName == null)
      return;
    boolean isGetter = methodName.startsWith ("get");
    boolean isSetter = methodName.startsWith ("set");
    if (!isGetter && !isSetter)
      return;
    Symbol propertyName = backOutG2NameFromJavaName (methodName.substring (3));
    Structure propStruct = (Structure) propertyTable.get (propertyName);
    if (propStruct == null) {
      propStruct = createPropertyStruct (propertyName);
      propertyTable.put (propertyName, propStruct);
      properties.addElement (propStruct);
    }
    copyPropertyAccessor (propStruct, methodStruct, isGetter);
    propertyTable.put (propertyName, propStruct);
    methodTable.remove (methodKey);
  }

  private Structure createPropertyStruct (Symbol propertyName) {
    Structure propertyStruct = new Structure ();
    propertyStruct.setAttributeValue (PROPERTY_NAME_, propertyName);
    return propertyStruct;
  }

  private void copyPropertyAccessor (Structure propertyStruct,
				     Structure methodStruct,
				     boolean isGetter) {
    Symbol intfAttrName, implAttrName, commAttrName;
    if (isGetter) {
      intfAttrName = GETTER_INTERFACE_;
      implAttrName = GETTER_IMPLEMENTATION_;
      commAttrName = GETTER_COMMENTS_;
    } else {
      intfAttrName = SETTER_INTERFACE_;
      implAttrName = SETTER_IMPLEMENTATION_;
      commAttrName = SETTER_COMMENTS_;
    }
    propertyStruct.setAttributeValue (intfAttrName, methodStruct.getAttributeValue (INTERFACE_, null));
    propertyStruct.setAttributeValue (implAttrName, methodStruct.getAttributeValue (IMPLEMENTATION_, null));
    propertyStruct.setAttributeValue (commAttrName, methodStruct.getAttributeValue (COMMENTS_, null));
  }
  
  private void checkIfEventMethod (Symbol methodKey) {
    Structure methodStruct = (Structure) methodTable.get (methodKey);
    if (methodStruct == null) // was a Property Accessor
      return;
    String methodDeclaration = (String) methodStruct.getAttributeValue (INTERFACE_, null);
    String methodName = getMethodNameFromDeclaration (methodDeclaration);
    if (methodName == null)
      return;
    boolean isAdder = (methodName.startsWith ("add") && methodName.endsWith ("Listener"));
    boolean isRemover = (methodName.startsWith ("remove") && methodName.endsWith ("Listener"));
    System.out.println ("Check If Event Method: " + methodName + "(" + isAdder + ", " + isRemover + ") arg count=" + getArgumentCountFromDeclaration(methodDeclaration));
    if ((!isAdder && !isRemover) ||
	getArgumentCountFromDeclaration(methodDeclaration) > 1)
      return;

    Symbol eventName = getEventName (methodName, isAdder);
    Structure eventStruct = (Structure) eventTable.get (eventName);
    if (eventStruct == null) {
      eventStruct = createEventStruct (eventName);
      eventTable.put (eventName, eventStruct);
      events.addElement (eventStruct);
    }
    copyEventMethod (eventStruct, methodStruct, isAdder);
    System.out.println (eventName + " is an Event. Putting in eventTable and removing from methodTable");
    eventTable.put (eventName, eventStruct);
    methodTable.remove (methodKey);
  }
  
  private Structure createEventStruct (Symbol eventName) {
    Structure eventStruct = new Structure ();
    eventStruct.setAttributeValue (EVENT_NAME_, eventName);
    return eventStruct;
  }

  private void copyEventMethod (Structure eventStruct, Structure methodStruct, boolean isAdder) {
    Symbol intfAttrName, implAttrName, commAttrName;
    if (isAdder) {
      intfAttrName = ADD_LISTENER_INTERFACE_;
      implAttrName = ADD_LISTENER_IMPLEMENTATION_;
      commAttrName = ADD_LISTENER_COMMENTS_;
    } else {
      intfAttrName = REMOVE_LISTENER_INTERFACE_;
      implAttrName = REMOVE_LISTENER_IMPLEMENTATION_;
      commAttrName = REMOVE_LISTENER_COMMENTS_;
    }
    eventStruct.setAttributeValue (intfAttrName, methodStruct.getAttributeValue (INTERFACE_, null));
    eventStruct.setAttributeValue (implAttrName, methodStruct.getAttributeValue (IMPLEMENTATION_, null));
    eventStruct.setAttributeValue (commAttrName, methodStruct.getAttributeValue (COMMENTS_, null));
  }

  private Symbol getEventName (String methodName, boolean isAdder) {
    int startIndex = (isAdder ? 3 : 6);
    String evtName = methodName.substring (startIndex, methodName.length () - 8);
    return Symbol.intern (evtName.toUpperCase ());
  }

  private void checkIfConstructor (Symbol methodKey) {
    Structure methodStruct = (Structure) methodTable.get (methodKey);
    if (methodStruct == null) // was a Property Accessor or an Event method
      return;
    String methodDeclaration = (String) methodStruct.getAttributeValue (INTERFACE_, null);
    String methodName = getMethodNameFromDeclaration (methodDeclaration);
    if (methodName == null)
      return;
    System.out.println ("Check if constructor " + methodName + " -> " + methodName.equals (className));
    if (methodName.equals (className))
      methodTable.remove (methodKey);
  }

  private Symbol createMemberStruct (String memberCode, int memberType) {
    String memberSignature = getSignature (memberCode, memberType);
    int currMemStartIndex = commentedClassCode.indexOf (memberSignature);
    MemberInfo ms = new MemberInfo (currMemStartIndex, currMemStartIndex + memberCode.length (), memberCode);
    int prevMemEndIndex;
    if (!members.isEmpty()) {
      MemberInfo prevM = (MemberInfo) members.lastElement ();
      prevMemEndIndex = prevM.endIndex;
    } else
      prevMemEndIndex = classStartIndex;
    //System.out.println ("(" + currMemStartIndex + ", " + (currMemStartIndex + memberCode.length ()) + ") [Last member ended at " + prevMemEndIndex + "]");
    members.addElement (ms);
    String comment = null;
    Enumeration e = comments.elements ();
    while (e.hasMoreElements ()) {
      CommentInfo docComment = (CommentInfo) e.nextElement ();
      int commStartIndex = docComment.startIndex;
      int commEndIndex   = docComment.endIndex;
      if (commStartIndex > prevMemEndIndex && commEndIndex < currMemStartIndex)
	comment = docComment.txt;
      if (commStartIndex > currMemStartIndex)
	break;
    }
    Symbol memberKey;
    if (memberType == FIELD)
      memberKey = createFieldStruct (memberCode, comment);
    else
      memberKey = createMethodStruct (memberCode, comment);
    if (comment == null) {
      comment = NO_COMMENTS;
      if (memberCode.indexOf (PUBLIC) >= 0) {
	if (undocumentedPublicMembers == null)
	  undocumentedPublicMembers = new Vector ();
	undocumentedPublicMembers.addElement (memberKey);
      }
    }
    return memberKey;
  }

  private Symbol createFieldStruct (String fieldCode, String comment) {
    String fieldDeclaration = getSignature (fieldCode, FIELD);
    int initStartIndex = fieldCode.indexOf (equalSign);
    String fieldName = getFieldNameFromDeclaration (fieldDeclaration);
    Symbol g2Name = backOutG2NameFromJavaName (fieldName);
    Structure fieldStruct = new Structure ();
    fieldStruct.setAttributeValue (FIELD_NAME_,  g2Name);
    fieldStruct.setAttributeValue (DECLARATION_, fieldDeclaration);
    fieldStruct.setAttributeValue (COMMENTS_, comment);
    if (initStartIndex > 0)
      fieldStruct.setAttributeValue (INITIAL_VALUE_, fieldCode.substring (initStartIndex + 1).trim ());
    fieldTable.put (g2Name, fieldStruct);
    return g2Name;
  }

  private String getFieldNameFromDeclaration (final String fieldDeclaration) {
    int spIndex = fieldDeclaration.trim().lastIndexOf (' ');
    return fieldDeclaration.trim().substring (spIndex + 1);
  }

  private Symbol backOutG2NameFromJavaName (String fieldName) {
    StringBuffer fName = new StringBuffer ();
    char c;
    for (int i=0; i<fieldName.length () - 1; i++) {
      c = fieldName.charAt (i);
      if (c == '_')
	c = '-';
      fName.append (c);
      if (c >= 'a' && c <= 'z' && (c = fieldName.charAt (i+1)) >= 'A' && c <= 'Z')
	fName.append ('-');
    }
    c = fieldName.charAt (fieldName.length () - 1);
    if (c != '_')
      fName.append (c);
    return Symbol.intern (fName.toString ().toUpperCase ());
  }

  private Symbol createMethodStruct (String methodCode, String comment) {
    String methodDeclaration = getSignature (methodCode, METHOD);
    int initStartIndex = methodCode.indexOf (openParen);
    String methodName = getMethodNameFromDeclaration (methodDeclaration);
    Symbol g2Name;
    if (methodName != null)
      g2Name = backOutG2NameFromJavaName (methodName);
    else
      g2Name = INSTANCE_INITIALIZER_;
    int n=0;
    String origNameString = g2Name.getPrintValue ();
    while (methodTable.get (g2Name) != null)
      g2Name = Symbol.intern (origNameString + "-" + n++);
    String methodImplCode = getCodeOfMethodBlock (methodCode);
    Structure methodStruct = new Structure ();
    methodStruct.setAttributeValue (METHOD_NAME_, g2Name);
    methodStruct.setAttributeValue (INTERFACE_, methodDeclaration);
    methodStruct.setAttributeValue (IMPLEMENTATION_, methodImplCode);
    methodStruct.setAttributeValue (COMMENTS_, comment);
    //System.out.println ("methodTable.put (" + g2Name + ", " + methodStruct + ")");
    methodTable.put (g2Name, methodStruct);
    return g2Name;
  }

  // NOTE: this does not need to be a true parser: it is presuming
  // valid syntax has been checked by a compiler.
  private static int getArgumentCountFromDeclaration(final String methodDeclaration) {
    String methodDec = methodDeclaration.trim ();
    int opArgStartIndex = methodDec.lastIndexOf ('(');
    int opArgEndIndex = methodDec.lastIndexOf (')');

    if (opArgStartIndex == -1 || opArgEndIndex == -1 ||
	(opArgEndIndex - opArgStartIndex <= 2))
      return 0;

    int argCount = 0;
    boolean hasNonSpaceChar = false;
    // Now count the number of commas, and add one (but only if
    // the parens don't just have spaces between them). I would
    // have tokenized, but I didn't want to have to mess with the
    // whole foo(type [] thing) problem.
    for (int i = opArgStartIndex; i <= opArgEndIndex; i++) {
      char ch = methodDec.charAt(i);
      switch (ch) {
      case ' ':
	break;
      case ',':
	argCount++;
	break;
      default:
	hasNonSpaceChar = true;
      }
    }

    if (hasNonSpaceChar)
      argCount++;

    return argCount;
  }

  private String getMethodNameFromDeclaration (final String methodDeclaration) {
	  String methodDec = methodDeclaration.trim ();
    //System.out.println ("MD = " + methodDeclaration);
    int opArgStartIndex = methodDec.lastIndexOf ('(');
    if (opArgStartIndex == -1) {
      methodDec = methodDec.trim ();
      if (methodDec.equals ("static"))
	return methodDec;
      else if (methodDec.equals (""))
	return null;
    }
    methodDec = methodDec.substring (0, opArgStartIndex);
    methodDec = methodDec.trim ();
    int spIndex = methodDec.lastIndexOf (' ');
    return methodDec.substring (spIndex + 1);
  }

  private String getCodeOfMethodBlock (final String methodCode) {
    int opIndex = methodCode.trim().indexOf (openParen);
    return methodCode.trim().substring (opIndex + 1, methodCode.length () - 1);
  }

  private String getSignature (String code, int type) {
    String endChar = (type == FIELD ? equalSign : openParen);
    int endIndex = code.indexOf (endChar);
    if (type == FIELD && endIndex < 0)
      return code.trim ();
    return code.substring (0, endIndex).trim ();
  }

  class TextBlock {

    int startIndex, endIndex;
    String txt;

    TextBlock (int start, int end, String textToSave) {
      startIndex = start;
      endIndex   = end;
      txt        = textToSave;
    }

    @Override
    public String toString () {
      return "[" + startIndex + "->" + endIndex + "] = " + txt + "\n";
    }

  }


  abstract class CodeElementInfo extends TextBlock {

    CommentInfo codeComment;

    CodeElementInfo (int start, int end, String eltCode) {
      super (start, end, eltCode);
    }

  }


  class CommentInfo extends TextBlock {

    CommentInfo (int start, int end, String comments) {
      super (start, end, comments);
    }
  }

  class MemberInfo extends CodeElementInfo {

    MemberInfo (int start, int end, String memCode) {
      super (start, end, memCode);
    }
  }

  class MethodInfo extends MemberInfo {
    
    MethodInfo (int start, int end, String methodCode) {
      super (start, end, methodCode);
    }
  }

}
