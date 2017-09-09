package com.gensym.wksp.configurations;

import com.gensym.core.GensymApplication;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import java.awt.event.*;
import java.awt.*; 
import java.util.*;
import com.gensym.dispatcher.*;
import com.gensym.wksp.*;
import com.gensym.classes.Root;
import com.gensym.classes.Block;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.G2Definition;
import com.gensym.classes.ClassDefinition;
import com.gensym.dlg.WarningDialog;    

//DUMPING:
// main menu choice restrictions
// global keyboard command restrictions
public class ConfigurationSupport //listens to the userMode
implements ConfigurationSymbols, NonMenuChoices
{
  private static final Symbol ROOT_ = Symbol.intern ("ROOT");
  private static final Symbol CURRENT_ = Symbol.intern ("CURRENT");
  private static Symbol userMode;
  private static final Symbol MARK_TO_STRIP_TEXT_ = Symbol.intern("MARK-TO-STRIP-TEXT");
  private static final Symbol MARK_TO_STRIP_TEXT_A_ = Symbol.intern("MARK-TO-STRIP-TEXT-*");
  private static final Symbol MARK_NOT_TO_STRIP_TEXT_ = Symbol.intern("MARK-NOT-TO-STRIP-TEXT");
  private static final Symbol MARK_NOT_TO_STRIP_TEXT_A_ = Symbol.intern("MARK-NOT-TO-STRIP-TEXT-*");
  private static final Symbol REMOVE_DO_NOT_STRIP_TEXT_MARK_ = Symbol.intern("REMOVE-DO-NOT-STRIP-TEXT-MARK");
  private static final Symbol REMOVE_DO_NOT_STRIP_TEXT_MARK_A_ = Symbol.intern("REMOVE-DO-NOT-STRIP-TEXT-MARK-*");
  private static final Symbol REMOVE_STRIP_TEXT_MARK_ = Symbol.intern("REMOVE-STRIP-TEXT-MARK");
  private static final Symbol REMOVE_STRIP_TEXT_MARK_A_ = Symbol.intern("REMOVE-STRIP-TEXT-MARK-*");
  private static final Symbol NUPEC_DYNAMIC_GENERIC_RULE_DISPLAY_ = Symbol.intern("NUPEC-DYNAMIC-GENERIC-RULE-DISPLAY");
  private static final Symbol NUPEC_DESCRIBE_CHAINING_ = Symbol.intern("NUPEC-DESCRIBE-CHAINING");
  private static final Symbol NUPEC_BACKWARD_CHAINING_ = Symbol.intern("NUPEC-BACKWARD-CHAINING");
  private static final Symbol NUPEC_DYNAMIC_BACKWARD_CHAINING_ = Symbol.intern("NUPEC-DYNAMIC-BACKWARD-CHAINING");
  private static final Symbol NUPEC_DYNAMIC_RULE_INVOCATION_DISPLAY_ = Symbol.intern("NUPEC-DYNAMIC-RULE-INVOCATION-DISPLAY");
  private static final Symbol MOVE_ = Symbol.intern("MOVE");
  private static final Symbol KEY_CODE_ = Symbol.intern ("KEY-CODE");
  private static Symbol[] hiddenSystemMenuChoices = 
  {MARK_TO_STRIP_TEXT_, MARK_TO_STRIP_TEXT_A_, MARK_NOT_TO_STRIP_TEXT_, MARK_NOT_TO_STRIP_TEXT_A_,
   REMOVE_DO_NOT_STRIP_TEXT_MARK_, REMOVE_DO_NOT_STRIP_TEXT_MARK_A_,
   REMOVE_STRIP_TEXT_MARK_, REMOVE_STRIP_TEXT_MARK_A_, NUPEC_DYNAMIC_BACKWARD_CHAINING_,
   NUPEC_DYNAMIC_GENERIC_RULE_DISPLAY_, NUPEC_DESCRIBE_CHAINING_, NUPEC_BACKWARD_CHAINING_,
   NUPEC_DYNAMIC_RULE_INVOCATION_DISPLAY_, MOVE_};
  private static final Symbol FINAL_RESTRICTION_TYPE_ = Symbol.intern ("FINAL-RESTRICTION-TYPE");
  private static final Symbol PERMITTED_SET_ = Symbol.intern ("PERMITTED-SET");
  private static final Symbol PROHIBITED_SET_ = Symbol.intern ("PROHIBITED-SET");
  public static final int CLASS = 0;
  public static final int ALL = 1;
  public static final int LOCAL = 2;

  //JDK_BUG_4117523 is a sun bug in jdk versions prior to 1.2
  //on solaris ONLY, in which the mouse modifiers of a mousePressed event
  //(ie: ((InputEvent)e).getModifiers()) is not correctly set to 
  //InputEvent.BUTTON1_MASK when just the left button is pressed.
  //More simply, it is set to zero instead of sixteen.
  private static boolean JDK_BUG_4117523_IS_PRESENT = false;
  static {
    try {
      JDK_BUG_4117523_IS_PRESENT = isSolaris() && isJdkLessThan1_2();
    } catch (Exception e) {
      //if we don't match then assume the bug is not in effect
    }
  }

  private static boolean isSolaris() {
    return System.getProperty ("os.name").toLowerCase().indexOf ("solaris") >= 0;
  }

  private static boolean isJdkLessThan1_2() {
    String version = System.getProperty("java.version");
    if (version.equals("") )
      return false;
    if (version.length() == 1) 
      return Integer.parseInt(version) <= 1;

    int indexOfFirstPeriod = version.indexOf('.');
    if (indexOfFirstPeriod == -1) 
      return false;//two digit major version case

    String majorVersionStr = version.substring(0, indexOfFirstPeriod);
    int majorVersion = Integer.parseInt(majorVersionStr);
    if (majorVersion > 1)
      return false;
    else if (majorVersion < 1)
      return true;

    int indexOfSecondPeriod = version.indexOf('.', indexOfFirstPeriod + 1);
    if (indexOfSecondPeriod == -1 )  // e.g. "1.2"
      indexOfSecondPeriod = version.length();

    String minorVersionStr = version.substring(indexOfFirstPeriod + 1, indexOfSecondPeriod);
    int minorVersion = Integer.parseInt(minorVersionStr);
    return minorVersion < 2;
  }
  
  private static boolean hiddenMenuChoice(Symbol systemMenuChoice) {
    boolean hidden = false;
    for (int i=0;i<hiddenSystemMenuChoices.length&&!hidden; i++) {
      if (hiddenSystemMenuChoices[i].equals(systemMenuChoice))
 	hidden = true;
    }
    return hidden;
  }

  private static Vector getItemConfiguration(Item item)
       throws G2AccessException
  {
    Vector configurations = new Vector();
    Sequence configuration
      = (((Item)item).getItemConfigurationSnapshot());
    if (configuration != null)
      configurations.addElement(configuration);
    return configurations;
  }
  
  private static Vector getConfigurations(Item item)
       throws G2AccessException
  {
    Vector configurations = getItemConfigurations(item);
    Vector instanceConfigurations = getInstanceConfigurations(item);
    for (Enumeration e = instanceConfigurations.elements();
	 e.hasMoreElements();) {
      Object next = e.nextElement();
      configurations.addElement(next);
    }
    return configurations;
  }
  
  private static Vector getItemConfigurations(Item item)
  throws G2AccessException
  {
    return item.getCompleteConfigurationSnapshot();
  }

  private static final Item getKBConfiguration(Item item)
       throws G2AccessException
  {
    G2Access context = (G2Access)((ImplAccess)item).getContext();
    return (Item)((G2Access)context).getUniqueNamedItem(KB_CONFIGURATION_,
							KB_CONFIGURATION_);
  }

  private boolean userDefinedClass(Symbol className) {
    return false;
  }

  private static Vector getInstanceConfiguration(ClassDefinition definition)
              throws G2AccessException
  {
    Vector configurations = new Vector();
    Sequence configuration
      = definition.getInstanceConfiguration();
    if (configuration != null)
      configurations.addElement(configuration);
    return configurations;
  }

  private static Vector getInstanceConfigurations(Item item)
       throws G2AccessException
  {
    Vector configurations = new Vector();
    Sequence inhPathSeq
      = item.getDefinition ().getClassInheritancePath ();
    Symbol[] classInheritancePath = new Symbol [inhPathSeq.size ()];
    inhPathSeq.copyInto (classInheritancePath);
    for (int i=0; i<classInheritancePath.length;i++) {
      Symbol superClassName = classInheritancePath[i];
      G2Access context
	= (G2Access)((ImplAccess)item).getContext(); //hack for now
      try {
	G2Definition superClass = context.getClassManager().getDefinition(superClassName);
	if (superClass instanceof ClassDefinition) {
	  Sequence configuration
	    = (((com.gensym.classes.Definition)superClass).getInstanceConfiguration());
	  if (configuration != null)
	    configurations.addElement(configuration);
	}
      } catch (Exception e) {
	Trace.exception (e);
      }
    }
    return configurations;
  }

  private static boolean modeMatchesApplicableUserModes(Structure applicableUserModes,
							Symbol currentUserMode)
  {
    boolean negative
      = ((Boolean)applicableUserModes.getAttributeValue(NEGATIVE_, Boolean.FALSE)).booleanValue();
    Sequence modes
      = (Sequence)applicableUserModes.getAttributeValue(MODES_, new Sequence());
    return (modes.contains(currentUserMode)?!negative:negative);
  }

  private static boolean itemIsOfClass(Item item,
				       Symbol className)
       throws G2AccessException
  {
    return item.isInstanceOfG2Class (className);
  }

  private static boolean itemMatchesApplicableItems(Item item,
						    Sequence applicableItems)
       throws G2AccessException
  {
    boolean matched = false;
    Enumeration e = applicableItems.elements();
    while (e.hasMoreElements() && !matched) {
      matched = itemIsOfClass(item, (Symbol)e.nextElement());
    }
    return matched;
  }

  private static Symbol adjustChoicesForCurrentRestrictions(Symbol currentRestrictionType,
							    Sequence currentMenuChoices,
							    Vector permittedSet,
							    Vector prohibitedSet,
							    Symbol finalRestrictionType) {
    boolean hitFinalRestrictionType = false;
    if (currentRestrictionType.equals(EXCLUDE_ABSOLUTELY_)) {
      Enumeration e = currentMenuChoices.elements();
      while (e.hasMoreElements()) {
	Object currentChoice = e.nextElement();
	permittedSet.removeElement(currentChoice);
	prohibitedSet.addElement(currentChoice);
      }
    } else if (finalRestrictionType == null) {
      boolean including = true;//is true for INCLUDE_ADDITIONALLY also
      if (currentRestrictionType.equals(INCLUDE_))
	hitFinalRestrictionType = true;
      else if (currentRestrictionType.equals(EXCLUDE_)) {
	hitFinalRestrictionType = true;
	including = false;
      } else if (currentRestrictionType.equals(EXCLUDE_ADDITIONALLY_))
	including = false;
      Enumeration e = currentMenuChoices.elements();
      while (e.hasMoreElements()) {
	Object currentChoice = e.nextElement();
	if (including && !prohibitedSet.contains(currentChoice))
	  permittedSet.addElement(currentChoice);
	else if (!including && !permittedSet.contains(currentChoice))
	  prohibitedSet.addElement(currentChoice);
      }
    }
    return (hitFinalRestrictionType?currentRestrictionType:finalRestrictionType);
  }

  /**
   * @param newMode a Symbol named a G2 user mode.
   * Sets the current userMode that will be used by
   * this classes methods.
   */
  public static void setUserMode(Symbol newMode) {
    userMode = newMode;
  }

  /**
   * @param item the Item for which to find restrictions.
   * @param operationType a Symbol naming the operation type
   * of an item configuration statement.
   * @see OperationTypes
   * @return a Structure whose attribute named by CHOICE_RESTRICTIONS_
   * is a Sequence of Symbols naming G2 menu choices, and whose
   * attribute named by PERMITTED_ is a Boolean that dictates whether
   * these menu choices should be included or excluded.
   */
  public static Structure getChoiceRestrictions(Item item,
						// if we do table-menu-choices
						// then we also need applicable-attributes
						Symbol operationType)
       throws G2AccessException
  {
    Vector configurations = getConfigurations(item);
    return getChoiceRestrictions(item, operationType, configurations, true);
  }

  private static Structure getChoiceRestrictions(Item item,
						 Symbol operationType,
						 Vector configurations,
						 boolean matchItem)
       throws G2AccessException
  {
    Sequence permittedSet = new Sequence(), prohibitedSet = new Sequence();
    Symbol finalRestrictionType = null;
    Enumeration e = configurations.elements();
    boolean isProprietary = item.isProprietaryThroughContainment();
    while(e.hasMoreElements()) {
      Sequence currentConfiguration = (Sequence)e.nextElement();
      Enumeration clauseStructs = currentConfiguration.elements();
      while (clauseStructs.hasMoreElements()) {
	Structure currentClauseStruct = (Structure)clauseStructs.nextElement();
	Symbol currentClauseType = (Symbol)currentClauseStruct.getAttributeValue(TYPE_, null);
	if (currentClauseType.equals(CONFIGURE_USER_INTERFACE_)) {
	  Sequence clauseSequence = (Sequence)currentClauseStruct.getAttributeValue(CLAUSES_, null);
	  Enumeration clauses = clauseSequence.elements();
	  while (clauses.hasMoreElements()) {
	    Structure currentClause = (Structure)clauses.nextElement();
	    Structure applicableUserModes
	    = (Structure) currentClause.getAttributeValue(APPLICABLE_USER_MODES_, null);
	    if (applicableUserModes!= null &&
		modeMatchesApplicableUserModes(applicableUserModes, userMode)) {
	      Sequence statementsSequence
		= (Sequence)currentClause.getAttributeValue(STATEMENTS_, null);
	      finalRestrictionType = doChoiceRestrictions(operationType,
							  matchItem,
							  item,
							  statementsSequence,
							  permittedSet,
							  prohibitedSet,
							  finalRestrictionType);
	    }
	  }
	} else if (currentClauseType.equals(RESTRICT_PROPRIETARY_ITEMS_) &&
		   isProprietary) {
	  Sequence clauseSequence = (Sequence)currentClauseStruct.getAttributeValue(CLAUSES_, null);
	  finalRestrictionType = doChoiceRestrictions(operationType,
						      matchItem,
						      item,
						      clauseSequence,
						      permittedSet,
						      prohibitedSet,
						      finalRestrictionType);
	}
      }
    }
    Structure choiceRestrictions = new Structure();
    if (finalRestrictionType == null) finalRestrictionType = EXCLUDE_;
    boolean permitted = finalRestrictionType.equals(INCLUDE_);
    choiceRestrictions.setAttributeValue(PERMITTED_, new Boolean(permitted));
    choiceRestrictions.setAttributeValue(CHOICE_RESTRICTIONS_, permitted?permittedSet:prohibitedSet);
    return choiceRestrictions;
  }

  public static Symbol doChoiceRestrictions(Symbol operationType,
					    boolean matchItem,
					    Item item,
					    Sequence statementsSequence,
					    Sequence permittedSet,
					    Sequence prohibitedSet,
					    Symbol finalRestrictionType)
       throws G2AccessException {
    int length = statementsSequence.size();
    Object[] statements = new Object[length];
    statementsSequence.copyInto(statements);
    for (int i=length-1;i>=0;i--) {
      Structure currentStatement = (Structure)statements[i];
      Symbol currentOperationType
	= (Symbol)currentStatement.getAttributeValue(OPERATION_TYPE_, null);
      if (operationType.equals(currentOperationType) &&
	  (!matchItem ||
	   itemMatchesApplicableItems
	   (item,
	    (Sequence)currentStatement.getAttributeValue(APPLICABLE_ITEMS_, null)))) {
	Symbol currentRestrictionType
	  = (Symbol)currentStatement.getAttributeValue(RESTRICTION_TYPE_, null);
	Symbol attributeNameForChoices
	  = (ATTRIBUTE_VISIBILITY_.equals(operationType)?ATTRIBUTES_:MENU_CHOICES_);
	Sequence currentChoices
	  =(Sequence)currentStatement.getAttributeValue(attributeNameForChoices, null);
	finalRestrictionType
	  = adjustChoicesForCurrentRestrictions(currentRestrictionType,
						currentChoices,
						permittedSet,
						prohibitedSet,
						finalRestrictionType);
      }
    }
    return finalRestrictionType;
  }


  /**
   * @param defaultChoices a Sequence of Symbols naming the default menu choices.
   * @param choiceRestrictions a Sequence of Symbols naming restricted menu choices.
   * @param permitted a boolean that dictates whether a menu choice
   *  contained within choiceRestrictions should be allowed or disallowed.
   * @return a new Sequence of Symbols contained within defaultChoices that are not
   * restricted.
   */
  public static Sequence filterChoicesByRestrictions(Sequence defaultChoices,
						     Sequence choiceRestrictions,
						     boolean permitted)
  {
    Sequence filteredMenuChoices = new Sequence();
    if (defaultChoices != null) {
      Enumeration e = defaultChoices.elements();
      Symbol choice;
      while(e.hasMoreElements()) {
	choice = (Symbol) e.nextElement();
	if (!hiddenMenuChoice(choice) &&
	    (choiceRestrictions.contains(choice)? permitted : !permitted))
	  filteredMenuChoices.addElement(choice);
      }
    }
    return filteredMenuChoices;
  }

  /**
   * @param item the Item for which to determine whether the choice is available
   * @param choice the Choice whose availablity is in question.
   * @return true iff the choice is available.
   * @see Choice
   */
  public static boolean choiceIsAvailable(Item item,
					  Choice choice)
       throws G2AccessException
  {
    //NEED isProprietary() method on Item
    Symbol operationType = choice.getOperationType();
    Structure restrictions = getChoiceRestrictions(item, operationType);
    Sequence choiceRestrictions
      = (Sequence)restrictions.getAttributeValue(CHOICE_RESTRICTIONS_,null);
    Boolean permitted = (Boolean)restrictions.getAttributeValue(PERMITTED_, null);
    Symbol choiceName = choice.getName();
    return (choiceRestrictions.contains(choiceName) ?
	    permitted.booleanValue():!permitted.booleanValue());
  }

  /**
   * TBD
   */
  /*  public static MovementConstraint getMovementConstraint(Item item) 
  {
    NEED isProprietary() method on Item
    do standard config search and stop when hit constrain_moving.
    return a constrainedRegion Structure. (rectangle or grid)
  }
  */

  /**
   * TBD
   */
  /*public static Action getConsequentAction(Item item,
					   UIEvent event) 
  {
    NEED isProprietary() method on Item

    pressing, releasing, typing
    don't allow absolutely
    do standard search and stop at first one
    that matches.
  }
  */

  /**
   * TBD
   */
  /*public static Action getConsequentAction(Item item,
					   UICommand command) 
  {
    NEED isProprietary() method on Item
    SELECTING:(allows absolutely)
    do standard search, keeping track of first
    selecting clause, looking for first absolutely-selecting
    clause if one exists.
  }
  */

  /**
   * TBD
   */
  /*public static Structure getProperties(Item item)
  {
    return null;
  }
  */
  
  /**
   * TBD
   */
  /*public static Sequence getComments(Item item)
  {
    return null;
  }
  */
  /**
   * TBD
   */
  /*public static boolean isNetworkAccessAvailable(Item item,or null
						 Symbol accessType)
  {
    return false;
  }   
  */
  private static int nonMenuChoiceAWTEventId(Symbol nonMenuChoice)
       throws UnsupportedConfigurationException
  { 
    if (MOVE_OBJECT_.equals(nonMenuChoice))
      return MouseEvent.MOUSE_DRAGGED;
    else if (MOVE_OBJECTS_BEYOND_WORKSPACE_MARGIN_.equals(nonMenuChoice))
      return MouseEvent.MOUSE_RELEASED;
    else
      throw new UnsupportedConfigurationException("Non Menu Choice  " +
						  nonMenuChoice);
  }

  private static Condition nonMenuCondition(Symbol nonMenuChoice,
					    Condition applicableItems)
       throws UnsupportedConfigurationException
  {
    try {
      Condition cond
	=  new AndCondition(new AndCondition
			    (new EventCondition(java.awt.event.MouseEvent.class),
			     new AWTEventIdCondition(nonMenuChoiceAWTEventId(nonMenuChoice))),
			    applicableItems);
      if (MOVE_OBJECTS_BEYOND_WORKSPACE_MARGIN_.equals(nonMenuChoice))
	return new AndCondition(new SimpleCondition
				(SimpleCondition.EQUAL,
				 new VariableReference("uiMode", Integer.TYPE),
				 new ConstantReference(Integer.TYPE,
						       new Integer(WorkspaceViewListener.DRAG))),
				cond);
      else
	return cond;
    } catch (NonStaticMethodException nsme) {
      Trace.exception(nsme);
      return null;
    }
  }
  
  private static Node nonMenuAction(Symbol nonMenuChoice,
				    boolean include,
				    WorkspaceViewListener handler)
       throws UnsupportedConfigurationException
  {
    try {
      if (MOVE_OBJECT_.equals(nonMenuChoice)) {
	if (include)
	  return new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
				  "doDragDrag", handler, new EventReference(MouseEvent.class));
	else
	  return new G2Action(null);
      } else if (MOVE_OBJECTS_BEYOND_WORKSPACE_MARGIN_.equals(nonMenuChoice)) {
	return new SimpleAction("com.gensym.wksp.WorkspaceViewListener",
				"doDragRelease", handler,
				new Reference[]
				{ new EventReference(MouseEvent.class),
				    new ConstantReference(Boolean.TYPE,
							  new Boolean(include))});
      } else
	throw new UnsupportedConfigurationException("Non Menu Choice: " +
						    nonMenuChoice);
    } catch(NonStaticMethodException nsme) {
      Trace.exception(nsme);
      return null;
    } catch(NoSuchMethodException nsuchme) {
      Trace.exception(nsuchme);
      return null;
    } catch(ClassNotFoundException cnfe) {
      Trace.exception(cnfe);
      return null;
    }
  }

  private static Condition StatementCondition(Structure statement,
					      Symbol operationType,
					      boolean allowThisItemConfigurations,
					      Item item)
       throws UnsupportedConfigurationException
  {
    try {
      Condition condition  = new OperationTypeCondition(statement);
      Sequence applicableItems = (Sequence)statement.getAttributeValue(APPLICABLE_ITEMS_, null);
      if (applicableItems != null)
	condition = new AndCondition(condition,
				     new ApplicableItemsCondition(applicableItems,
								  operationType,
								  allowThisItemConfigurations,
								  item));
      Structure keyCode = (Structure)statement.getAttributeValue(KEY_CODE_, null);
      if (keyCode != null) {
	Condition keyCodeCondition = null;
	//see comment above JDK_BUG_4117523_IS_PRESENT declaration.
	if (JDK_BUG_4117523_IS_PRESENT && PRESSING_.equals(operationType)) 
	  keyCodeCondition = new KeyCodeCondition(keyCode, true);
	else 
	  keyCodeCondition = new KeyCodeCondition(keyCode);
	condition = new AndCondition(condition, keyCodeCondition);	
      }
      //TYPE_OF_REGION, CONSTRAINED_REGION
      return condition;
    } catch(G2AccessException g2ae) {
      Trace.exception(g2ae);
      return null;
    } 
  }

  private static Node StatementAction(Structure statement,
				      WorkspaceViewListener handler)
  {
    Object consequentAction
      = statement.getAttributeValue(CONSEQUENT_ACTION_, null);
    if (consequentAction instanceof Symbol)
      return new G2Action((Symbol)consequentAction);
    else 
      return new G2Action(NOTHING_);
  }
  
  public static Decision getDecisionTree(Item item,
					 boolean allowProprietaryRestrictions,
					 int configurationType,
					 WorkspaceViewListener handler)
       throws G2AccessException
  {
    Vector configurations = null;
    switch (configurationType) {
      // Uses a snapshot
    case LOCAL: configurations = getItemConfiguration(item); break;
    case CLASS: configurations = getInstanceConfiguration((ClassDefinition)item); break;
    case ALL: configurations = getConfigurations(item); break;
    default: Trace.exception(new Exception("Unknown configurationType " + configurationType));
      return null;
    }
    boolean allowThisItemConfigurations=(configurationType == LOCAL ||
					 configurationType == ALL);
    return getDecisionTree(item,
			   allowProprietaryRestrictions,
			   allowThisItemConfigurations,
			   configurations,
			   handler);
  }

  public static Decision getDecisionTree(Item item,
					 boolean allowProprietaryRestrictions,
					 boolean allowThisItemConfigurations,
					 Vector configurations,
					 WorkspaceViewListener handler)
       throws G2AccessException
  {
    Decision defaultDecision = new Decision(new FalseCondition(),
					    new Noop(), new Noop());
    Structure rootAndCurrentDecisions = new Structure();
    rootAndCurrentDecisions.setAttributeValue(ROOT_, defaultDecision);
    rootAndCurrentDecisions.setAttributeValue(CURRENT_, defaultDecision);
    Structure nonMenuChoicesTable = new Structure();
    Structure absoluteNonMenuChoicesTable = new Structure();
    Vector precedenceList = new Vector();
    Enumeration e = configurations.elements();
    while(e.hasMoreElements()) {
      Sequence currentConfiguration = (Sequence)e.nextElement();
      Enumeration clauseStructs = currentConfiguration.elements();
      while (clauseStructs.hasMoreElements()) {
	Structure currentClauseStruct = (Structure)clauseStructs.nextElement();
	Symbol currentClauseType = (Symbol)currentClauseStruct.getAttributeValue(TYPE_, null);	
	if (currentClauseType.equals(CONFIGURE_USER_INTERFACE_)) {
	  Sequence clauseSequence = (Sequence)currentClauseStruct.getAttributeValue(CLAUSES_, null);
	  Enumeration clauses = clauseSequence.elements();
	  while (clauses.hasMoreElements()) {
	    Structure currentClause = (Structure)clauses.nextElement();
	    Structure applicableUserModes
	    = (Structure) currentClause.getAttributeValue(APPLICABLE_USER_MODES_, null);
	    if (applicableUserModes!= null &&
		modeMatchesApplicableUserModes(applicableUserModes, userMode)) {
	      Sequence statementsSequence
		= (Sequence)currentClause.getAttributeValue(STATEMENTS_, null);
	      doConfigurationStatements(statementsSequence,
					allowThisItemConfigurations,
					item,
					handler,
					absoluteNonMenuChoicesTable,
					nonMenuChoicesTable,
					rootAndCurrentDecisions,
					precedenceList);
	    }
	  }
	} else if (currentClauseType.equals(RESTRICT_PROPRIETARY_ITEMS_) &&
		   allowProprietaryRestrictions) {
	  Sequence clauseSequence = (Sequence)currentClauseStruct.getAttributeValue(CLAUSES_, null);
	  doConfigurationStatements(clauseSequence,
				    allowThisItemConfigurations,
				    item,
				    handler,
				    absoluteNonMenuChoicesTable,
				    nonMenuChoicesTable,
				    rootAndCurrentDecisions,
				    precedenceList);
	}
      }
    }
    try {
      Enumeration classNames = nonMenuChoicesTable.getAttributeNames();	
      while (classNames.hasMoreElements()) {
	Symbol className = (Symbol)classNames.nextElement();
	if (!precedenceList.contains(className)) {
	  Structure entry = (Structure)nonMenuChoicesTable.getAttributeValue(className);
	  doEntry(className,entry, rootAndCurrentDecisions, handler);
	}
      }
      classNames = precedenceList.elements();
      while (classNames.hasMoreElements()) {
	Symbol className = (Symbol)classNames.nextElement();
	Structure entry = (Structure)nonMenuChoicesTable.getAttributeValue(className);
	doEntry(className,entry, rootAndCurrentDecisions, handler);
      }
      classNames = absoluteNonMenuChoicesTable.getAttributeNames();	
      while (classNames.hasMoreElements()) {
	Symbol className = (Symbol)classNames.nextElement();
	Sequence excludedChoices = (Sequence)absoluteNonMenuChoicesTable.getAttributeValue(className);
	excludeNonMenuChoices(className,
			      excludedChoices,
			      handler,
			      rootAndCurrentDecisions);
      }
    } catch (NoSuchAttributeException nsae) {
      Trace.exception(nsae);
    }
      
    return (Decision)rootAndCurrentDecisions.getAttributeValue(ROOT_, null);
  }
  private static void doEntry(Symbol className,
		       Structure entry,
		       Structure rootAndCurrentDecisions,
		       WorkspaceViewListener handler)
       throws NoSuchAttributeException, G2AccessException
  {
    Symbol finalRestrictionType =
      (Symbol)entry.getAttributeValue(FINAL_RESTRICTION_TYPE_, EXCLUDE_); 
    boolean permitted = finalRestrictionType.equals(INCLUDE_);
    Vector permittedSet = (Vector)entry.getAttributeValue(PERMITTED_SET_);
    Vector prohibitedSet = (Vector)entry.getAttributeValue(PROHIBITED_SET_);
    doNonMenuChoices(className,
		     permitted,
		     permitted?permittedSet:prohibitedSet,
		     handler,
		     rootAndCurrentDecisions);
  }

  private static Sequence supportedChoices = new Sequence();
  static {
    supportedChoices.addElement(MOVE_OBJECT_);
    supportedChoices.addElement(MOVE_OBJECTS_BEYOND_WORKSPACE_MARGIN_);
  }
  
  private static void doNonMenuChoices(Symbol className,
				       boolean permitted,
				       Vector choices,
				       WorkspaceViewListener handler,
				       Structure rootAndCurrentDecisions)
       throws G2AccessException
  {
    /*System.out.println("CONFIGURING NMC for " + className +
		       "PERMITTED = " + permitted +
		       "CHOICES = " + choices);*/
    Sequence applicableItems = new Sequence();
    applicableItems.addElement(className);
    Condition applicableItemsCondition
      = new ApplicableItemsCondition(applicableItems, NON_MENU_, false, null);
    Enumeration nonMenuChoices = supportedChoices.elements();
    while (nonMenuChoices.hasMoreElements()) {
      Symbol nonMenuChoice = (Symbol)nonMenuChoices.nextElement();
      boolean include = (choices.contains(nonMenuChoice)? permitted : !permitted);
      try {
	doNonMenuChoice(nonMenuChoice, include, handler, true,//???
			applicableItemsCondition, rootAndCurrentDecisions);
      } catch(UnsupportedConfigurationException uce) {
	notifyUserOfUnsupportedConfiguration(uce);
      }
    }
  }

  private static void excludeNonMenuChoices(Symbol className,
					    Vector choices,
					    WorkspaceViewListener handler,
					    Structure rootAndCurrentDecisions)
       throws G2AccessException
  {
    /*System.out.println("EXCLUDING NMC for " + className +
		       "CHOICES = " + choices);*/
    Sequence applicableItems = new Sequence();
    applicableItems.addElement(className);
    Condition applicableItemsCondition
      = new ApplicableItemsCondition(applicableItems, NON_MENU_, false, null);
    Enumeration nonMenuChoices = choices.elements();
    while (nonMenuChoices.hasMoreElements()) {
      Symbol nonMenuChoice = (Symbol)nonMenuChoices.nextElement();
      if (supportedChoices.contains(nonMenuChoice)) {
	try {
	  doNonMenuChoice(nonMenuChoice, false, handler, true,//???
			  applicableItemsCondition, rootAndCurrentDecisions);
	} catch(UnsupportedConfigurationException uce) {
	  notifyUserOfUnsupportedConfiguration(uce);
	}
      }
    }
  }
   
  private static void doConfigurationStatements(Sequence statementsSequence,
						boolean allowThisItemConfigurations,
						Item item,
						WorkspaceViewListener handler,
						Structure absoluteNonMenuChoicesTable,
						Structure nonMenuChoicesTable,
						Structure rootAndCurrentDecisions,
						Vector precedenceList)
       throws G2AccessException
  {
    int length = statementsSequence.size();
    Object[] statements = new Object[length];
    statementsSequence.copyInto(statements);
    for (int i=length-1;i>=0;i--) {
      Structure currentStatement = (Structure)statements[i];
      Symbol operationType = operationType(currentStatement);
      boolean isAbsolute = statementIsAbsolute(currentStatement);	  
      if (NON_MENU_.equals(operationType)) {
	collectNonMenuChoices(currentStatement,
			      item,
			      handler,
			      nonMenuChoicesTable,
			      absoluteNonMenuChoicesTable,
			      rootAndCurrentDecisions,
			      precedenceList,
			      isAbsolute);
      } else {
	try {
	  adjustTree(rootAndCurrentDecisions,
		     StatementCondition(currentStatement,
					operationType,
					allowThisItemConfigurations,
					item),
		     StatementAction(currentStatement,
				     handler),
		     isAbsolute);
	  } catch(UnsupportedConfigurationException uce) {
	    uce = new UnsupportedConfigurationException(currentStatement, uce.getMessage());
	    notifyUserOfUnsupportedConfiguration(uce);	    
	  }
      }
    }
  }

  private static Structure defaultEntry()
  {
    Structure entry = new Structure();
    entry.setAttributeValue(PERMITTED_SET_, new Vector());
    entry.setAttributeValue(PROHIBITED_SET_, new Vector());
    return entry;
  }

  private static void adjustChoicesForCurrentRestrictions(Symbol restrictionType,
							  Sequence menuChoices,
							  Vector precedenceList,
							  Structure entry,
							  Symbol applicableClass)
       throws NoSuchAttributeException
  {
    Symbol currentFinalRestrictionType =
      (Symbol)entry.getAttributeValue(FINAL_RESTRICTION_TYPE_, null);
    Symbol finalRestrictionType
      = adjustChoicesForCurrentRestrictions(restrictionType,
					    menuChoices,
					    (Vector)entry.getAttributeValue(PERMITTED_SET_),
					    (Vector)entry.getAttributeValue(PROHIBITED_SET_),
					    currentFinalRestrictionType);
    if (currentFinalRestrictionType == null && finalRestrictionType != null) {
      entry.setAttributeValue(FINAL_RESTRICTION_TYPE_, finalRestrictionType);
      precedenceList.insertElementAt(applicableClass,0);
    }
  }
  
  private static void collectNonMenuChoices(Structure statement,
					    Item item,
					    WorkspaceViewListener handler,
					    Structure nonMenuChoicesTable,
					    Structure absoluteNonMenuChoicesTable,
					    Structure rootAndCurrentDecisions,
					    Vector precedenceList,
					    boolean isAbsolute)
       throws G2AccessException
  {
    Sequence applicableItems = (Sequence)statement.getAttributeValue(APPLICABLE_ITEMS_, null);
    if (applicableItems != null) {
      Sequence menuChoices = (Sequence)statement.getAttributeValue(MENU_CHOICES_, new Sequence());
      Symbol restrictionType = restrictionType(statement);
      Enumeration e = applicableItems.elements();
      while(e.hasMoreElements()) {
	Symbol applicableClass = (Symbol)e.nextElement();
	try {
	  if (EXCLUDE_ABSOLUTELY_.equals(restrictionType)) {
	    Sequence absoluteEntry =
	      (Sequence)absoluteNonMenuChoicesTable.getAttributeValue(applicableClass, null);
	    if (absoluteEntry == null) {
	      absoluteEntry = new Sequence();
	      //System.out.println("CREATING ABSOLUTE ENTRY for " + applicableClass);
	      absoluteNonMenuChoicesTable.setAttributeValue(applicableClass, absoluteEntry);
	    }
	    Enumeration ee = menuChoices.elements();
	    while(ee.hasMoreElements()) {
	      Object choice = ee.nextElement();
	      if (supportedChoices.contains(choice))
		absoluteEntry.addElement(choice);
	      else {
		UnsupportedConfigurationException uce =
		  new UnsupportedConfigurationException(statement,
							"Non menu choice: " + choice);
		notifyUserOfUnsupportedConfiguration(uce);
	      }
	    }
	  } else {
	    Structure entry =
	      (Structure)nonMenuChoicesTable.getAttributeValue(applicableClass, null);
	    if (entry == null) {
	      entry = defaultEntry();
	      //System.out.println("COLLECTING CLASS " + applicableClass);
	      nonMenuChoicesTable.setAttributeValue(applicableClass, entry);
	    }
	    adjustChoicesForCurrentRestrictions(restrictionType,
						menuChoices,
						precedenceList,
						entry,
						applicableClass);
	  }
	} catch (NoSuchAttributeException nsae) {
	  //entry was initialized incorrectly
	  Trace.exception(nsae);
	}
      }
    }
  }
	
  private static void doNonMenuChoice(Symbol nonMenuChoice,
				      boolean include,
				      WorkspaceViewListener handler,
				      boolean isAbsolute,
				      Condition applicableItemsCondition,
				      Structure rootAndCurrentDecisions)
     throws UnsupportedConfigurationException
  {
    Condition nonMenuCondition
      = nonMenuCondition(nonMenuChoice, applicableItemsCondition);
    Node nonMenuAction
      = nonMenuAction(nonMenuChoice, include, handler);
    adjustTree(rootAndCurrentDecisions,
	       nonMenuCondition,
	       nonMenuAction,
	       isAbsolute);
  }

  private static void adjustTree(Structure rootAndCurrentDecisions,
				 Condition newCondition,
				 Node newAction,
				 boolean addAtRoot) 
  {
    Decision nextDecision = new Decision(newCondition,
					 newAction,
					 new Noop());
    if (addAtRoot) {
      Decision oldRoot
	= (Decision)rootAndCurrentDecisions.getAttributeValue(ROOT_, null);
      Decision newRoot = nextDecision;
      newRoot.setFalseNode(oldRoot);
      rootAndCurrentDecisions.setAttributeValue(ROOT_, newRoot);
    } else {
      Decision currentDecision
	= (Decision)rootAndCurrentDecisions.getAttributeValue(CURRENT_, null);    
      currentDecision.setFalseNode(nextDecision);
      rootAndCurrentDecisions.setAttributeValue(CURRENT_, nextDecision);
    }
  }

  private static boolean beChatty = false;

  private static void notifyUserOfUnsupportedConfiguration(UnsupportedConfigurationException uce)
  {
    if (GensymApplication.getDevOption() && beChatty) {
      Structure statement = uce.getConfigurationStatement();
      String message =
	"unsupported configuration:\n   " + uce.getMessage();
      if (statement != null)
	message = "Statement:\n   " + statement + "\n\ncontains " + message;
      WarningDialog warningDialog = new WarningDialog(null,
						      "Unsupported configuration",
						      false,
						      message,
						      null);
      warningDialog.setVisible(true);    
    }
  }

  public static void setVerboseWarning (boolean warningState) {
    beChatty = warningState;
  }
  
  private static Symbol restrictionType(Structure statement)
  {
    if (NON_MENU_.equals(operationType(statement))) 
      return (Symbol)statement.getAttributeValue(RESTRICTION_TYPE_, null);
    return null;
  }

  private static Symbol operationType(Structure statement)
  {
    return (Symbol)statement.getAttributeValue(OPERATION_TYPE_, null);
  }
  
  private static boolean statementIsAbsolute(Structure statement)
  {
    return (EXCLUDE_ABSOLUTELY_.equals(restrictionType(statement)) ||
	    SELECTING_ABSOLUTELY_.equals(operationType(statement)));
  }

}
					   
