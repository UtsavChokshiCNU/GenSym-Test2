package com.gensym.ntw.util;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.ntw.TwAccess;

public class FileProgressEvent extends java.util.EventObject {
  public static final int FILE_ADDED = 0;
  public static final int FILE_REMOVED = 1;
  private static final Integer ZERO = 0;    
  private int id;
  private Structure data;
  private static final Symbol
  MODULE_OF_FILE_IN_PROGRESSQ_ = Symbol.intern ("MODULE-OF-FILE-IN-PROGRESS?"),
    NAMESTRING_OF_FILE_IN_PROGRESSQ_ = Symbol.intern ("NAMESTRING-OF-FILE-IN-PROGRESS?"),
    PROGRESS_THROUGH_FILE_ = Symbol.intern ("PROGRESS-THROUGH-FILE"),  
    LENGTH_OF_FILE_IN_CHARACTERSQ_ = Symbol.intern ("LENGTH-OF-FILE-IN-CHARACTERS?"),
    FIXNUM_TIME_OF_LAST_FILE_PROGRESS_DISPLAY_UPDATE_ = Symbol.intern ("FIXNUM-TIME-OF-LAST-FILE-PROGRESS-DISPLAY-UPDATE"),
    DIRECTION_OF_FILE_PROGRESSQ_ = Symbol.intern ("DIRECTION-OF-FILE-PROGRESS?"),
    STATUS_OF_FILE_PROGRESSQ_ = Symbol.intern ("STATUS-OF-FILE-PROGRESS?"),
    MODULE_THAT_REQUIRED_THISQ_ = Symbol.intern ("MODULE-THAT-REQUIRED-THIS?"),
    MODULES_THIS_REQUIRED_ = Symbol.intern ("MODULES-THIS-REQUIRED"),
    NUMBER_OF_KB_CHARACTERS_SO_FARQ_ = Symbol.intern ("NUMBER-OF-KB-CHARACTERS-SO-FAR?"),
    UNITS_FOR_PROGRESS_THROUGH_FILE_ = Symbol.intern ("UNITS-FOR-PROGRESS-THROUGH-FILE"),
    TOTAL_NUMBER_OF_ITEMS_ = Symbol.intern ("TOTAL-NUMBER-OF-ITEMS"),
    ITEMS_ = Symbol.intern ("ITEMS"),
    //LINES_ = Symbol.intern ("LINES"),
    OPEN_ = Symbol.intern ("OPEN"),
    INPUT_ = Symbol.intern ("INPUT"),
    OUTPUT_ = Symbol.intern ("OUTPUT");
  private static final String WRITING = "writing";
  private static final String LOADING = "loading";

  @Override
  public String toString() {
    return data.toString();
  }
  
  public FileProgressEvent(TwAccess source,
			   Structure fileProgressData,
			   boolean isDelete)
  {
    super (source);
    this.data = fileProgressData;
    id = isDelete?FILE_REMOVED:FILE_ADDED;
  }

  public int getTotalNumberOfItems() {
   Integer itemCount = (Integer)data.getAttributeValue(TOTAL_NUMBER_OF_ITEMS_, ZERO);
    if (itemCount == null)
      itemCount = ZERO;
    return itemCount.intValue();    
  }

  public boolean isItemMode() {
    return ITEMS_.equals(getUnitsForProgressThroughFile());
  }

  public int getPercentageDone() {
    int total,current; 
    if (isItemMode()) {
      total = getTotalNumberOfItems();
      current = getProgress();
    } else {
      total = getLengthOfFileInCharacters();
      current = getProgressInCharacters();
    }
    if (total == 0) {
    	return 0;
    }
    return (current*100)/total;
  }
  
  public Symbol getUnitsForProgressThroughFile() {
    return (Symbol)data.getAttributeValue(UNITS_FOR_PROGRESS_THROUGH_FILE_, null);
  }
  
  public Symbol getModuleName() {
    return (Symbol)data.getAttributeValue(MODULE_OF_FILE_IN_PROGRESSQ_, null);
  }

  public String getFileName() {
    return (String)data.getAttributeValue(NAMESTRING_OF_FILE_IN_PROGRESSQ_, null);
  }

  public int getProgressInCharacters() {
   Integer chars = (Integer)data.getAttributeValue(NUMBER_OF_KB_CHARACTERS_SO_FARQ_, ZERO);
    if (chars == null)
      chars = ZERO;
    return chars.intValue();
  }
  
  public int getProgress() {
    return ((Integer)data.getAttributeValue(PROGRESS_THROUGH_FILE_, ZERO)).intValue();
  }

  public int getLengthOfFileInCharacters() {
    Integer length = (Integer)data.getAttributeValue(LENGTH_OF_FILE_IN_CHARACTERSQ_, null);
    if (length == null)
      length = ZERO;
    return length.intValue();
  }  

  public int getTimeOfLastUpdate() {
    return ((Integer)data.getAttributeValue(FIXNUM_TIME_OF_LAST_FILE_PROGRESS_DISPLAY_UPDATE_,
					    ZERO)).intValue();
  }

  public Symbol getDirection() {
    return (Symbol)data.getAttributeValue(DIRECTION_OF_FILE_PROGRESSQ_, null);
  }

  public String getStatus() {
    Object status = (Symbol)data.getAttributeValue(STATUS_OF_FILE_PROGRESSQ_, null);
    if (status == null) 
      status = OPEN_;
    if (OPEN_.equals(status)) {
      Symbol direction = getDirection();
      if (OUTPUT_.equals(direction))
	status = WRITING;
      else if (INPUT_.equals(direction))
	status = LOADING;
      else
	status = status.toString().toLowerCase();
    } else
      status = status.toString().toLowerCase();
    return (String)status;
  }

  public Symbol getRequiringModule() {
    return (Symbol)data.getAttributeValue(MODULE_THAT_REQUIRED_THISQ_, null);
  }

  public Sequence getRequiredModules() {
    return (Sequence) data.getAttributeValue(MODULES_THIS_REQUIRED_, null);
  }
  
  /**
   * The id indicating the type of event
   */
  public int getID () {
    return id;
  }

}
