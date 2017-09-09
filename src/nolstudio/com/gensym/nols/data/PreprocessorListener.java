package com.gensym.nols.data;
import java.util.*;
/** The listener interface for receiving gensym data datasource events. */
public interface PreprocessorListener extends DataSourceListener{
	public void FormulaListChanged(PreprocessorEvent e) ;
	public void DataChanged(PreprocessorEvent e) ;
}
	
