package com.gensym.nols.data;
import java.util.*;
/** The listener interface for receiving gensym data datasource events. */
public interface RawDataSourceListener extends DataSourceListener{
	public void LabelCategoryAdded(RawDataEvent e) ;
	public void LabelCategoryRemoved(RawDataEvent e);
	public void DataPointsLabeled(RawDataEvent e);
	public void LabelOrderChanged(RawDataEvent e);
	public void LabelNameChanged(RawDataEvent e);
	public void LabelColorChanged(RawDataEvent e);
	public void DataSeriesAdded(RawDataEvent e);
	public void DataSeriesRemoved(RawDataEvent e);
}
	
