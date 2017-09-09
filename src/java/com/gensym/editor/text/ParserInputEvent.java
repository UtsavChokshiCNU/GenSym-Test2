/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ParserInputEvent.java
 *
 */
package com.gensym.editor.text;


/** This event is issued by any text source that wants to drive the
 * G2 grammar. It supports all of the information needed adding or
 * deleting single characters or regions of text and for repositioning
 * the cursor that the parser will generate prompts against. It includes
 * a set of constants that name the individual event types that a
 * ParserInputEventListener (parser) must implement as methods, so that the
 * event can serve as a standalone record of the transactions from the
 * text source to the parser, e.g. to support undo.
 * @author David McDonald
 * @version 1.1
 * @undocumented -- final Text Editor API is still under review
 */

/* To do:  update equals and compare methods to handle
 *           unequal regions.
 */


public class ParserInputEvent extends java.util.EventObject {


  private static boolean debug = false;


  //----- int's for the types so they can go in Switch statements ---

  private int id;
  /** Indicates the particular type of ParserInputEvent that has occurred.
   * Its value is an int that can be conviently accessed through one of the
   * five constants: CURSOR_CHANGE, ADDED_CHARACTER, DELETED_CHARACTER,
   * ADDED_REGION, and DELETED_REGION.  Two additional ids are defined,
   * NO_CHANGE, to cover that possibility, though it would not normally
   * trigger an event, REPLACED_REGION, for the situation where
   * the number of characters has not changed but some of their identites
   * has. Note that any replacement will logically consist of some
   * additions and deletions, but we permit the implementer to gloss over
   * this level of detail, for example because the change occurred very
   * quickly and seems like a single action.  Similarly there is the
   * REPLACED_UNEQUAL_REGIONS where we have to keep two sets of position
   * indicies in order to have a complete descriptions..
   * @undocumented -- final Text Editor API is still under review
   */
  public int getID() { return id; }

  /** Defines an id for the situation where there is no change in
   * the text, the cursor position, or anything else that might
   * be of interest to the parser.
   * @undocumented -- final Text Editor API is still under review
   */
  public static final int NO_CHANGE          = -1;


  /** Defines the id for the cursorPositionChanged() method.
   * @see com.gensym.editor.text.G2SideParser#cursorPositionChanged
   * @undocumented -- final Text Editor API is still under review
   */
  public static final int CURSOR_CHANGE      = 0;

  /** Defines the id for the characterAdded() method.
   * @see com.gensym.editor.text.G2SideParser#characterAdded
   * @undocumented -- final Text Editor API is still under review
   */
  public static final int ADDED_CHARACTER    = 1;

  /** Defines the id for the characterDeleted() method.
   * @see com.gensym.editor.text.G2SideParser#characterDeleted
   * @undocumented -- final Text Editor API is still under review
   */
  public static final int DELETED_CHARACTER  = 2;

  /** Defines the id for the regionAdded() method.
   * @see com.gensym.editor.text.G2SideParser#regionAdded
   * @undocumented -- final Text Editor API is still under review
   */
  public static final int ADDED_REGION       = 3;

  /** Defines the id for the regionDeleted() method.
   * @see com.gensym.editor.text.G2SideParser#regionDeleted
   * @undocumented -- final Text Editor API is still under review
   */
  public static final int DELETED_REGION     = 4;

  /** Defines the id for the replacedRegion() method.
   * @see com.gensym.editor.text.G2SideParser#replacedRegion
   * @undocumented -- final Text Editor API is still under review
   */
  public static final int REPLACED_REGION    = 5;

  /**  Defines the id for the replacedUnEqualRegions() method.
   * @undocumented -- final Text Editor API is still under review
   */
  public static final int REPLACED_UNEQUAL_REGIONS  = 6;

 

  //---------------------------------------------------
  //------ Constructors and member variables ----------
  //---------------------------------------------------


  //------- No change -----------

  public ParserInputEvent(Object source) {
    super(source);
    id = NO_CHANGE;
  }



  //------- Cursor movement ------------

  String text;
  /** Returns the entire text that is being edited. Note that the need
   * to include this argument in all ParserInputEvents is a reflection
   * of the fact that we are temporarily using a protocol that requires
   * it, wasteful as it is. In the course of time this requirement will
   * be removed as alteratives are developed and put into place.
   * @undocumented -- final Text Editor API is still under review
   */
  public String getText() { return text; }

  /** Allows you to specify the reference text against which the event
   * will be interpreted. The text must reflect the state of affairs
   * that holds -after- the event has had its effect. This can be
   * useful in constructing inverse events for undo/redo.
   * @undocumented -- final Text Editor API is still under review
   */
  public void setText(String s) { text = s; }



  boolean update;
  /** Returns a boolean indicating whether the parser should issue its
   * customary updates to the prompts and status after it processes 
   * this event. Usually it should, but there are situations where
   * the ParserInputEvent is known by its issuer to be only the first
   * of several input events that are going to be sent one after the
   * other in quick succession, in which case only the last of the
   * series of events should lead to an update.
   * @undocumented -- final Text Editor API is still under review
   */
  public boolean updateQ() { return update; }



  int cursor;
  /** Returns the location of the text's cursor at the time of the event.
   * This could represent a change to the cursor without any change in
   * the text (by using the mouse to move it to somewhere else in the
   * text, or it could be a side-effect of an addition or deletion,
   * in which case its logical location will depend on just what
   * the event was and is documented with those methods.
   * Note that the cursor is defined to lie between characters.
   *   For now the cursor value is always the same as the relevant
   * caretPosition of the event since there is no way to programmatically
   * change the texts and so all adjustments will be manual.
   * @undocumented -- final Text Editor API is still under review
   */
  public int getCursor() { return cursor; }

  int oldCursor;
  /** Returns the location the cursor had been at the moment of the
   * previous event. A cursor movement takes the cursor from that
   * location to new location (the value of getCursor).
   * @undocumented -- final Text Editor API is still under review
   */
  public int getOldCursor() { return oldCursor; }



  /** This version of the constructor is to be used when the text change
   * is just a difference in the location of the cursor. The propagation of
   * this event through the parser will result in the generation of a new set
   * of prompts that are appropriate for the new position.
   * @undocumented -- final Text Editor API is still under review
   */
  public ParserInputEvent(Object source, 
			  int newCursorPosition, int oldCursorPosition,
			  boolean update, String text) {
    super(source);
    cursor = newCursorPosition;
    oldCursor = oldCursorPosition;
    this.update = update;
    this.text = text;
    id = CURSOR_CHANGE;
    character = "";  // a non-null value for the benefit of comparators
    regionText = "";
  }

  

  //-------- Single character adds/deletes ----------

  String character;
  /** This returns a string consisting of a single character that was 
   * added/deleted in this event. 
   * @undocumented -- final Text Editor API is still under review
   */
  public String getCharacter() { return character; }


  int characterPosition;
  /** When a character is added or deleted, there is no requirement that the
   * cursor that designates what perspective the parser should provide  for
   * its prompts is the same 'cursor' at which the addition or deletion occurred.
   * Consequently, this method should be used to determine the position at
   * which the change in the text occurred. 
   *    If the event is the addition of a character, then this is the (between-
   * character) position just to the new character's left, i.e. the position of
   * the text-insertion cursor just before the addition occurred. 
   *    If the event is the deletion of a character, then this the position
   * just to the right of where the character had been, i.e., the place wher
   * a text-insertion cursor would have had to have been for the character to
   * have been deleted using the Backspace key.
   * @undocumented -- final Text Editor API is still under review
   */
  public int getCharacterPosition() { return characterPosition; }


  /** This constructor should be used for single character additions or
   * deletions. 
   * @undocumented -- final Text Editor API is still under review
   */
  public ParserInputEvent(Object source, String character,
			  int positionOfCharacter,
			  int cursorPosition, int oldCursorPosition,
			  boolean update, int eventID, String text) {
    super(source);
    cursor = cursorPosition;
    oldCursor = oldCursorPosition;
    this.character = character;
    characterPosition = positionOfCharacter;
    this.update = update;
    this.text = text;
    id = eventID;
    regionText = "";  // a non-null value for the benefit of comparators
  }

  




  //------- Multiple character ('region') adds/deletes --------

  String regionText;
  /** Returns the string of characters that was added or deleted
   * @undocumented -- final Text Editor API is still under review
   */
  public String getRegionText() { return regionText; }

  int regionStartPosition;
  /** Returns an int representing the position just to the left of
   * the first character of the region that was added/deleted.
   * @undocumented -- final Text Editor API is still under review
   */
  public int getRegionStart() { return regionStartPosition; }

  int regionEndPosition;
  /** Returns an int representing the position just to the right of
   * the last character of the region that was added/deleted.
   * @undocumented -- final Text Editor API is still under review
   */
  public int getRegionEnd() { return regionEndPosition; }



  /** This constructor should be used for the addition or deletion of
   * regions of text consisting of more than one character where the
   * characters are all contiguous.
   * @undocumented -- final Text Editor API is still under review
   */
  public ParserInputEvent(Object source, String characters,
			  int startPosition, int endPosition, 
			  int cursorPosition, int oldCursorPosition,
			  boolean update, int eventID, String text) {
    super(source);
    cursor = cursorPosition;
    oldCursor = oldCursorPosition;
    regionText = characters;
    regionStartPosition = startPosition;
    regionEndPosition = endPosition;
    this.update = update;
    id = eventID;
    this.text = text;
    character = "";  // a non-null value for the benefit of comparators
  }





  //-------- Replacements (same number of characters)  ------------

  String oldRegion;
  /* When the event is a replacement, this returns the string of
   * characters that was removed. */
  public String getOldRegion() { return oldRegion; }
  /* When the event is a replacement, this sets the string of
   * characters that was removed. */
  public void setOldRegion(String r) { oldRegion = r; }

  String newRegion;
   /* When the event is a replacement, this returns the string
    * of characters that was introduced, replacing the characters
    * of the 'old' region. */
  public String getNewRegion() { return newRegion; }
   /* When the event is a replacement,, this sets the string
    * of characters that replaces the old region. */
  public void setNewRegion(String r) { newRegion = r; }


  /** This constructor should be used for the replacement of one
   * string of characters with another string of equal length
   * at the same beginning/ending positions. 
   * @undocumented -- final Text Editor API is still under review
   */
  public ParserInputEvent(Object source, 
			  String oldRegion, String newRegion,
			  int startPosition, int endPosition, 
			  int cursorPosition, int oldCursorPosition,
			  boolean update, int eventID, 
			  String text) {
    super(source);
    cursor = cursorPosition;
    oldCursor = oldCursorPosition;
    this.oldRegion = oldRegion;
    this.newRegion = newRegion;
    regionStartPosition = startPosition;
    regionEndPosition = endPosition;
    this.update = update;
    id = eventID;
    this.text = text;
    character = "";  // a non-null value for the benefit of comparators
  }




  //-------- Replacements, unequal numbers of characters ------

  int oldStartPosition;
  /** For unequal replacement events, returns the start position
   * of the region that was replaced in this event. */
  public int getOldStartPosition() { return oldStartPosition; }
  /** Sets the start position of the region that was replaced in
   * an unequal replacement event. */
  public void setOldStartPosition(int p) { oldStartPosition = p; }


  int newStartPosition;
  /** For unequal replacement events, returns the start position
   * of the region that replaced the old region in this event. */
  public int getNewStartPosition() { return newStartPosition; }
  /** Sets the start position of the region that replaced the old
   * region in an unequal replacement event. */
  public void setNewStartPosition(int p) { newStartPosition = p; }


  int oldEndPosition;
  /** For unequal replacement events, returns the end position
   * of the region that was replaced in this event. */
  public int getOldEndPosition() { return oldEndPosition; }
  /** Sets the end position of the region that was replaced in
   * an unequal replacement event. */
  public void setOldEndPosition(int p) { oldEndPosition = p; }


  int newEndPosition;
  /** For unequal replacement events, returns the end position
   * of the region that replaced the old region in this event. */
  public int getNewEndPosition() { return newEndPosition; }
  /** Sets the end position of the region that replaced the old
   * region in an unequal replacement event. */
  public void setnewEndPosition(int p) { newEndPosition = p; }


  /** This constructor should be used when an region of the text
   * (of any length) has been replaced with a string of a different
   * length. Note that two sets of start/end positions must be
   * supplied.
   */
  public ParserInputEvent(Object source, 
			  String oldRegion, String newRegion,
			  int oldStartPosition, int oldEndPosition, 
			  int newStartPosition, int newEndPosition,
 			  int cursorPosition, int oldCursorPosition,
			  boolean update, int eventID, 
			  String text) {
    super(source);
    cursor = cursorPosition;
    oldCursor = oldCursorPosition;
    this.oldRegion = oldRegion;
    this.newRegion = newRegion;
    this.oldStartPosition = oldStartPosition;
    this.oldEndPosition = oldEndPosition;
    this.newStartPosition = newStartPosition;
    this.newEndPosition = newEndPosition;
    this.update = update;
    id = eventID;
    this.text = text;
    character = "";  // a non-null value for the benefit of comparators
  }





  //---------- utility methods ---------

  public static String nameEvent(int e) {
    switch (e) {
    case NO_CHANGE:
      return "No_Change";
    case CURSOR_CHANGE:
      return "Cursor_Change";
    case ADDED_CHARACTER:
      return "Added_Character";
    case DELETED_CHARACTER:
      return "Deleted_Character";
    case ADDED_REGION:
      return "Added_Region";
    case DELETED_REGION:
      return "Deleted_Region";
    case REPLACED_REGION:
      return "Replaced_Region";
    case REPLACED_UNEQUAL_REGIONS:
      return "Replaced_Unequal_Regions";
    default:
      return "Unknown";
    }
  }

  // Hmmm... the above would be redundant with the below except that
  // above we work from type ids and below we have the full event
  // object and can give more information. 

  /*
   * @undocumented -- final Text Editor API is still under review
   */
  @Override
  public String toString() {
    String s;
    switch (id) {
    case CURSOR_CHANGE:
      s = "Cursor moved to " + cursor + " from " + oldCursor; 
      break;
    case ADDED_CHARACTER:
      s = "Added \"" + character + "\" at " + cursor;
      break;
    case DELETED_CHARACTER:
      s = "Deleted \"" + character + "\" at " + cursor;
      break;
    case ADDED_REGION:
      s = "Added \"" + regionText + "\" between " +
	regionStartPosition + " and " + regionEndPosition;
      break;
    case DELETED_REGION:
      s = "Deleted \"" + regionText + "\" between " +
	regionStartPosition + " and " + regionEndPosition;
      break;
    case REPLACED_REGION:
      s = "Replaced \"" + oldRegion + "\" with \"" +
	 newRegion + "\"\n  between " + 
	regionStartPosition + " and " + regionEndPosition;
      break;
    case REPLACED_UNEQUAL_REGIONS:
      s = "Replaced \"" + oldRegion + "\"" +
	"\n    from " + oldStartPosition + " to " + oldEndPosition +
	"\n    with \"" + newRegion +
	"\n    from " + newStartPosition + " to " + newEndPosition;
      break;
    default:
      s = "ill-formed ParserInputEvent";
      break;
    }
    return s;
  }


  public static String description(ParserInputEvent e) {
    String s =
	 "ParserInputEvent: a " + nameEvent( e.getID() ) + " event.";
	 
    switch ( e.getID() ) {
    case CURSOR_CHANGE:
      s += "\n with cursor position " + e.getCursor() + 
	   " moved from " + e.getOldCursor();
      break;
    case ADDED_CHARACTER:  case DELETED_CHARACTER:
      s += "\n the character is \""  + e.getCharacter() + "\"" +
	   "\n at position " + e.getCharacterPosition();
      break;
    case ADDED_REGION: case DELETED_REGION:
      s += "\n the region is \"" + e.getRegionText() + "\"" +
	   "\n starting at " + e.getRegionStart() + 
	   " and ending at " + e.getRegionEnd();
      break;
    case REPLACED_REGION:
      s += "\n removing the region \"" + e.getOldRegion() + "\"" +
	   "\n and replacing it with \"" + e.getNewRegion() + "\"" +	
	   "\n starting at " + e.getRegionStart() + 
	   " and ending at " + e.getRegionEnd();
      break;
    case REPLACED_UNEQUAL_REGIONS:
      s += "\n removing the region \"" + e.getOldRegion() + "\"" +
	   "\n   which starts at " + e.getOldStartPosition() +
	   " and ends at " + e.getOldEndPosition() +
	   "\n and replacing it with \"" + e.getNewRegion() +
	   "\n   which starts at " + e.getNewStartPosition() +
	   " and ends at " + e.getNewEndPosition() ;
      break;
    default:
    }
    return s;
  }

  @Override
  public boolean equals(Object obj) {
	if(obj == null || !this.getClass().equals(obj.getClass()) ){
		return false;
	}
	 
	ParserInputEvent e = (ParserInputEvent) obj;
	
	boolean isEquals = id == e.getID() && cursor == e.getCursor() ;
	isEquals = isEquals && oldCursor == e.getOldCursor() && character.equals(e.getCharacter());
	isEquals = isEquals && characterPosition == e.getCharacterPosition(); 
	isEquals = isEquals && regionText.equals(e.getRegionText()) && regionStartPosition == e.getRegionStart();
	
	return isEquals && regionEndPosition == e.getRegionEnd();
  }
  
  @Override 
  public int hashCode(){
	final int prime = 31;
  	int result = 1;
  	result = prime * result + ((this.regionText == null) ? 0 : this.regionText.hashCode());
  	result = prime * result + ((this.character == null) ? 0 : this.character.hashCode());
  	result = prime * result + this.id;
  	result = prime * result + this.cursor;
  	result = prime * result + this.oldCursor;
  	result = prime * result + this.characterPosition;
  	result = prime * result + this.regionStartPosition;
  	result = prime * result + this.regionEndPosition;
  	return result;  
  }

  public void compareTo(ParserInputEvent e) {
    if (debug) {
      if (id != e.getID())
	System.out.println("The IDs are different");
      if (cursor != e.getCursor())
	System.out.println("The cursor positions are different");
      if (oldCursor != e.getOldCursor())
	System.out.println("The old cursor positions are different");
      if ( !character.equals(e.getCharacter()))
	System.out.println("The characters are different");
      if (characterPosition != e.getCharacterPosition())
	System.out.println("The character positions are different");
      if ( !regionText.equals(e.getRegionText()))
	System.out.println("The regions are different");
      if (regionStartPosition != e.getRegionStart())
	System.out.println("The region start positions are different");
      if (regionEndPosition != e.getRegionEnd())
	System.out.println("The region end positions are different");
    } 
  }



  public static ParserInputEvent invertEvent(ParserInputEvent e) {
    int newID;
    switch ( e.getID() ) {
    case ADDED_CHARACTER:
      newID = DELETED_CHARACTER;
      break;
    case DELETED_CHARACTER:
      newID = ADDED_CHARACTER;
      break;
    case ADDED_REGION:
      newID = DELETED_REGION;
      break;
    case DELETED_REGION:
      newID = ADDED_REGION;
      break;
    case REPLACED_REGION:
      newID = REPLACED_REGION;
      break;
    case REPLACED_UNEQUAL_REGIONS:
      newID = REPLACED_UNEQUAL_REGIONS;
      break;
    case CURSOR_CHANGE:
      newID = CURSOR_CHANGE;
      break;
    default:
      newID = NO_CHANGE;
    }

    ParserInputEvent i;
    Object s = e.getSource();
    switch ( newID ) {
    case ADDED_CHARACTER:
      /* Converting it from a Delete_Character event. The character position
       * had been where the cursor was after the character was deleted,
       * so we have to convert it to be where the cursor will be after
       * this character is added, i.e. add the length of the character
       * to it (so to speak). */
      i = new ParserInputEvent( s, e.getCharacter(),
				e.getCharacterPosition() + 1, 
				e.getOldCursor(), e.getCursor(), //e.getCursor() + 1,
				e.updateQ(), newID, e.getText() );
      break;
    case DELETED_CHARACTER:
      /* Converting from Add_Character, so move the positions over to
       * reflect the left rather than the right side of the character. */
      i = new ParserInputEvent( s, e.getCharacter(),
				e.getCharacterPosition() - 1,
				e.getOldCursor(), e.getCursor(), //e.getCursor() - 1,
				e.updateQ(), newID, e.getText() );
      break;
    case ADDED_REGION:
      /* Converting from Delete_Region. Cursor now has to move to the right end of the region. */
    case DELETED_REGION:
      /* Converting from Add_Region. Cursor now has to move to the left end of the region. */
      i = new ParserInputEvent( s, e.getRegionText(),
				e.getRegionStart(), e.getRegionEnd(),
				e.getOldCursor(), e.getCursor(),  //e.getRegionStart(),
				e.updateQ(), newID, e.getText() );
      break;
    case REPLACED_REGION:
      i = new ParserInputEvent( s, 
				e.getNewRegion(), e.getOldRegion(),
				e.getRegionStart(), e.getRegionEnd(),
				e.getOldCursor(), e.getCursor(),
				e.updateQ(), newID, e.getText() );
      break;
    case REPLACED_UNEQUAL_REGIONS:
      i = new ParserInputEvent( s,
				e.getNewRegion(), e.getOldRegion(),
				e.getNewStartPosition(), e.getNewEndPosition(),
				e.getOldStartPosition(), e.getOldEndPosition(),
				e.getOldCursor(), e.getCursor(),
				e.updateQ(), newID, e.getText() );
      break;
    case CURSOR_CHANGE:
      i = new ParserInputEvent( s, e.getOldCursor(), e.getCursor(),
				e.updateQ(), e.getText() );
      break;
    default:
      i = new ParserInputEvent( s );
    }

    return i;
  }

  /** Does a type-specific determination of where the changed
   * text of this event begins and ends.
   * @return a Range object.
   */
  public Range endPoints() {
    switch (id) {
    
    case ADDED_CHARACTER:
      return new Range(oldCursor, cursor);
    case ADDED_REGION:
    case REPLACED_REGION:
      return new Range(regionStartPosition, regionEndPosition);
    case REPLACED_UNEQUAL_REGIONS:
      return new Range(newStartPosition, newEndPosition);
    case NO_CHANGE:
    case CURSOR_CHANGE:
    case DELETED_REGION:
    case DELETED_CHARACTER:
    default:
      return Range.undefinedRange();
    }
  }


} // end of the class
