package com.gensym.nols.data;
import java.util.*;
/** The listener interface for receiving gensym data transform events. */
public interface ProjectListener{
	public void DataFileFormatSetted(ProjectEvent e) ;
	public void DataFileFormatRemoved(ProjectEvent e) ;
	
}
	
