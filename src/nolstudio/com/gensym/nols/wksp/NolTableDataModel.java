package com.gensym.nols.wksp;

import java.awt.*;
import java.util.*;
import java.text.*;
import com.gensym.math.matrix.*;

import com.gensym.nols.data.*;
//import com.gensym.nols.util.*;

import com.gensym.DEBUG;
	
public class NolTableDataModel implements TableDataModel, RawDataSourceListener,
	PreprocessorListener{

		private Vector tableDataEventListeners;
		private boolean isDefault;

		private DataSource dataSource;
		private DataSeries dataSeries;
		private int[] focusedCell;
		private int sigDigits;
		private Calendar calendar;
		private SimpleDateFormat dateFormat;		
		private SimpleDateFormat timeFormat;
		private int rows,columns;
		private Matrix data;
		private long[] times;
		private boolean hasTimeStamps;

		public NolTableDataModel()	{	
			super();
			isDefault = true;
			focusedCell = new int[2];
			focusedCell[0] = 0;
			focusedCell[1] = 0;
			tableDataEventListeners = new Vector();
			dateFormat = new SimpleDateFormat("MM/dd/yy");
			timeFormat = new SimpleDateFormat("H:mm:ss");
			rows = -1;
			columns = -1;
			sigDigits = 5;
			hasTimeStamps = true;
		}

		public NolTableDataModel(DataSeries ds){
			this();
			dataSeries = ds;
			dataSource = ds.getDataSource();
			dataSource.addListener(this);
			isDefault = false;
			data = ds.getDataMatrix();
			hasTimeStamps = ds.getHasTimeStamps();
			if(hasTimeStamps)
				times = ds.getTimeStamps();
			rows = getNumberOfRows();
			columns = getNumberOfColumns();
		}

		public void setSigDigits(int numberOfDigits){
			sigDigits = numberOfDigits;
		}

		public int getSigDigits(){
			return sigDigits;
		}

		@Override
		public void addTableDataEventListener(TableModelListener l){
			tableDataEventListeners.addElement(l);

		}
		@Override
		public void removeTableDataEventListener(TableModelListener l){
			tableDataEventListeners.removeElement(l);

		}

		@Override
		public void clearTableDataEventListener(){
			tableDataEventListeners.removeAllElements();
		}

		private void fireTableDataEvent(TableDataEvent e){
			for(int i=0;i<tableDataEventListeners.size();i++){
				TableModelListener l = (TableModelListener)tableDataEventListeners.elementAt(i);
				l.tableDataChanged(e);
			}
		}

		@Override
		public String getColumnName(int c){
			if(isDefault){
				String s = "Column"+c;
				return s;
			}else{
				if(c < getNumberOfColumns()){
					if(hasTimeStamps){
						if(c == 0) {
							return "Date";
						}
						if(c == 1) {
							return "Time";				
						}
						Variable varObj = dataSeries.getVarByIndex(c-2);
						return varObj.getName();
					}else{
						Variable varObj = dataSeries.getVarByIndex(c);
						return varObj.getName();
					}
				}
				String s = "Column"+c;
				return s;
			}
		}

		@Override
		public String getRowName(int r){
			return " "+String.valueOf(r);
		}

		@Override
		public String getValueAt(int r,int c){
			String s = "";
			if(isDefault) {
				return s;
			}
			if(c < getNumberOfColumns() && r < getNumberOfRows()){
				if(hasTimeStamps){
					if(c==0){
						s = dateFormat.format(new Date(times[r]));
						return s;
					}else if(c==1){
						s = timeFormat.format(new Date(times[r]));
						return s;
					}else{
						try{
							double d = data.get(r,c-2);	  //gchen 3/9/98
							 s = DataUtilities.doubleToString(d,sigDigits); 
						}catch(Exception e){
							System.err.println("Non-Fatal exception: " + e.getMessage());
							e.printStackTrace();
						}
						return s;
					}
				}else{
					try{
						double d = data.get(r,c);	  //gchen 3/9/98
						 s = DataUtilities.doubleToString(d,sigDigits); 
					}catch(Exception e){
						System.err.println("Non-Fatal exception: " + e.getMessage());
						e.printStackTrace();
					}
					return s;
				}
			}
			return "";
		}


		@Override
		public Color getBackgroundColor(int r,int c){
			if(!(dataSource instanceof RawDataSource)){
				return Color.white;
			}else{
				RawDataSource datsr = (RawDataSource)dataSource;
				if(c < getNumberOfColumns() && r < getNumberOfRows()){
					if(hasTimeStamps){
						if(c<2){
							return Color.white;
						}
						Variable varObj = dataSeries.getVarByIndex(c-2);
						boolean[] labelArray = datsr.getPointLabels(varObj,r);
						return datsr.getProject().getLabelColor(labelArray);
					}else{
						Variable varObj = dataSeries.getVarByIndex(c);
						boolean[] labelArray = datsr.getPointLabels(varObj,r);
						return datsr.getProject().getLabelColor(labelArray);
					}
				}
			}
			return Color.white;
		}
		
		@Override
		public int getNumberOfRows(){
			if(dataSeries != null)
				return dataSeries.getRow();
			return 0;
		}
		
		@Override
		public int getNumberOfColumns(){
			if(dataSeries == null){
				return 0;
			}
			if(hasTimeStamps)
				return dataSeries.getColumn()+2;
			return dataSeries.getColumn();
		}		

		@Override
		public void selectCell(int r, int c){
			if(!(dataSource instanceof RawDataSource)){
				return;
			}

			if(hasTimeStamps){
				if(c>(dataSeries.getColumn()+1)){
					return;
				}
			}else{
				if(c>(dataSeries.getColumn()-1)) {
					return;
				}
			}
			if(r>dataSeries.getRow()-1) {
				return;
			}

			if((hasTimeStamps && c>1)||(!hasTimeStamps && c>=0)){
				if(r >=0){
					RawDataSource datsr = (RawDataSource)dataSource;
					boolean labelSelectStatus = datsr.getSelectStatus();
					int labelNumber = datsr.getProject().getTopLabelIndex();
					int[] rowNumbers = new int[1];
					rowNumbers[0] = r;
					Variable varObj;
					if(hasTimeStamps)
						varObj = dataSeries.getVarByIndex(c-2);
					else
						varObj = dataSeries.getVarByIndex(c);
					datsr.labelPoints(labelNumber,varObj,rowNumbers,labelSelectStatus);
					focusedCell[0] = c;
					focusedCell[1] = r;
				}
			}
		}

		@Override
		public void selectRow (int r){
			if(!(dataSource instanceof RawDataSource)) {
				return;
			}
			if(r>(dataSeries.getRow()-1)) {
				return;
			}
			RawDataSource datsr = (RawDataSource)dataSource;
			boolean labelSelectStatus = datsr.getSelectStatus();
			int labelNumber = datsr.getProject().getTopLabelIndex();
			Vector varObjs = dataSeries.getVarObjects();
			Hashtable varObjsAndRowNumber = new Hashtable();
			for(int	i=0;i<varObjs.size();i++){
				Variable varObj = (Variable)varObjs.elementAt(i);
				int[] rowNumbers = new int[1];
				rowNumbers[0] = r;
				varObjsAndRowNumber.put(varObj,	rowNumbers);
			}
			datsr.labelPoints(labelNumber,varObjsAndRowNumber,labelSelectStatus);
			focusedCell[0] = 0;
			focusedCell[1] = r;
		}

		@Override
		public void selectColumn (int c){
			if(!(dataSource instanceof RawDataSource)) 
				return;
			
			if(hasTimeStamps && c<=1) 
				return;
			
			if(c<0) 
				return;

			if((hasTimeStamps && c>(dataSeries.getColumn()+1)) || c>(dataSeries.getColumn()-1))
				return;
			
			RawDataSource datsr = (RawDataSource)dataSource;
			int labelNumber = datsr.getProject().getTopLabelIndex();
			Variable varObj;
			if(hasTimeStamps)
				varObj = dataSeries.getVarByIndex(c-2);
			else
				varObj = dataSeries.getVarByIndex(c);
			boolean labelSelectStatus = datsr.getSelectStatus();
			datsr.labelPoints(labelNumber,varObj,labelSelectStatus);
			focusedCell[0] = c;
			focusedCell[1] = 0;
		}

		@Override
		public void shiftSelectCell(int r, int c){					
			if(!(dataSource instanceof RawDataSource)){
				return;
			}
			if(hasTimeStamps){
				if(c>(dataSeries.getColumn()+1)){
					return;
				}
			}else{
				if(c>(dataSeries.getColumn()-1)) {
					return;
				}
			}
			if(r>(dataSeries.getRow()-1)) {
				return;
			}

			if(focusedCell[0] == c && focusedCell[1] ==r) {
				return;
			}
			if(hasTimeStamps && c<=1) {
				return;
			}
			if(c<0) {
				return;
			}
			int c1 = Math.min(c,focusedCell[0]);
			int c2 = Math.max(c,focusedCell[0]);
			int r1 = Math.min(r,focusedCell[1]);
			int r2 = Math.max(r,focusedCell[1]);
			selectArea(r1, c1, r2, c2);
		}

		@Override
		public void selectArea(int rr1, int cc1, int rr2, int cc2){
			if(!(dataSource instanceof RawDataSource)) {
				return;
			}
			int c1 = Math.min(cc1,cc2);
			int c2 = Math.max(cc1,cc2);
			int r1 = Math.min(rr1,rr2);
			int r2 = Math.max(rr1,rr2);

			int col = dataSeries.getColumn();
			int row = dataSeries.getRow();

			if(hasTimeStamps){
				if(c1>(col+1)){
					return;
				}
				if(c2>(col+1)) {
					c2=col+1;
				}
			}else{
				if(c1>(col-1)){
					return;
				}
				if(c2>(col-1)) {
					c2=col-1;
				}
			}
			if(r1>(row-1)) {
				return;
			}
			if(r2>(row-1)){
				r2 = row-1;
			}

			if(hasTimeStamps){
				if(c1<2) {
					c1=2;
				}
				if(c2<2) {
					return;
				}
			}
			RawDataSource datsr = (RawDataSource)dataSource;
			boolean labelSelectStatus = datsr.getSelectStatus();
			int labelNumber = datsr.getProject().getTopLabelIndex();
			Vector varObjs = dataSeries.getVarObjects();
			Vector varObjsForLabel = new Vector();
			if(hasTimeStamps){
				for(int	i=c1-2;i<=c2-2;i++){
					varObjsForLabel.addElement(varObjs.elementAt(i));
				}
			}else{
				for(int	i=c1;i<=c2;i++){
					varObjsForLabel.addElement(varObjs.elementAt(i));
				}
			}
			datsr.labelPoints(labelNumber,varObjsForLabel,r1,r2,labelSelectStatus);
			focusedCell[0] = c1;
			focusedCell[1] = r1;
		}

		@Override
		public void LabelCategoryAdded(RawDataEvent evt){} 
		@Override
		public void LabelCategoryRemoved(RawDataEvent evt){
			if(!(dataSource instanceof RawDataSource)) {
				return;
			}
			TableDataEvent e = new TableDataEvent(this, "labelChanged",new int[0]);
			fireTableDataEvent(e);		
		}
		@Override
		public void LabelNameChanged(RawDataEvent evt) {}
		@Override
		public void LabelColorChanged(RawDataEvent evt) {
			if(!(dataSource instanceof RawDataSource)){
				return;
			}
			TableDataEvent e = new TableDataEvent(this, "labelChanged",new int[0]);
			fireTableDataEvent(e);		
		}
		@Override
		public void LabelOrderChanged(RawDataEvent evt) {
			if(!(dataSource instanceof RawDataSource)) {
				return;
			}
			if(DEBUG.debugFlag){
				System.out.println("Get label order event");
			}
			TableDataEvent e = new TableDataEvent(this, "labelChanged",new int[0]);
			fireTableDataEvent(e);		
		}
		@Override
		public void DataPointsLabeled(RawDataEvent evt){
			if(DEBUG.debugFlag){
				System.out.println("Get labeling event1");
			}
			if(!(dataSource instanceof RawDataSource)) {
				return;
			}
			if(DEBUG.debugFlag){
				System.out.println("Get labeling event2");
			}
			TableDataEvent e = new TableDataEvent(this, "labelChanged",new int[0]);
			fireTableDataEvent(e);		
		}
		@Override
		public void FormulaListChanged(PreprocessorEvent evt){}
		@Override
		public void DataSeriesAdded(RawDataEvent e){}
		@Override
		public void DataSeriesRemoved(RawDataEvent e){}
		@Override
		public void DataChanged(PreprocessorEvent evt) {
			Vector dataBanks = evt.getDataSeries();
			boolean found = false;
			for(int i=0;i<dataBanks.size();i++){
				DataSeries ds = (DataSeries)dataBanks.elementAt(i);
				if(ds.equals(dataSeries)){
					found = true;
					break;
				}
			}
			if(found){
				rows = getNumberOfRows();
				columns = getNumberOfColumns();
				data = dataSeries.getDataMatrix();
				TableDataEvent e = new TableDataEvent(this, "dataChanged",new int[0]);
				fireTableDataEvent(e);
			}
		}

/*		public void transformerMaskChanged(TransformerEvent evt){}
		public void transformerDataChanged(TransformerEvent evt){
			if(dataSourceFlag != 0) return;
			int [] indeces = transformer.getVariableNumbers(dataSeriesIndex);
			rows = transformer.getNumberOfRows(indeces[0]);
			columns = indeces.length+2;

			//gchen 3/9/98
 			Vector dv = transformer.getTransformedData();
			DataSeries ds = (DataSeries)dv.elementAt(dataSeriesIndex);
			data = ds.getDataMatrix();

			TableDataEvent e = new TableDataEvent(this, "dataChanged",new int[0]);
			fireTableDataEvent(e);
		}
		public void transformerVariableAdded(TransformerEvent evt){}
		public void transformerVariableRemoved(TransformerEvent evt){}
		public void transfomerTransformListChanged(TransformerEvent evt){}
		public void transfomerLabelCategoryAdded(TransformerEvent evt){
			if(dataSourceFlag != 0) return;
			TableDataEvent e = new TableDataEvent(this, "labelChanged",new int[0]);
			fireTableDataEvent(e);		
		}
		public void transfomerLabelCategoryRemoved(TransformerEvent evt){
			TableDataEvent e = new TableDataEvent(this, "labelChanged",new int[0]);
			fireTableDataEvent(e);		
		}

		public void transfomerDataPointsLabeled(TransformerEvent evt){
			if(dataSourceFlag != 0) return;
//			System.out.println("get labeling event");
			String id = evt.getIdentifier();
			int [] indeces = transformer.getVariableNumbers(dataSeriesIndex);
			int varNumber = evt.getVariableNumber();
			int[] rows = evt.getRowNumber();
			if(varNumber == -1 && rows.length==4){
				// check wether in this data series. 
				if(rows[0]<indeces[0] || rows[0] >indeces[indeces.length-1]) return;

				int[] coords  = new int[4];
				coords[0] = rows[0]+2 - indeces[0];
				coords[1] = rows[1];
				coords[2] = rows[2]+2 - indeces[0];
				coords[3] = rows[3];
				//need work!
				TableDataEvent e = new TableDataEvent(this, "labeling",coords);
				fireTableDataEvent(e);
			}else if(varNumber == -1 && rows.length==1){
				int[] coords  = new int[2];
				coords[0] = -1;
				coords[1] = rows[0];
				TableDataEvent e = new TableDataEvent(this, "labeling",coords);
				fireTableDataEvent(e);
			}else if(rows.length == 0){
				// check wether in this data series. 
				if(varNumber == -1){
					TableDataEvent e = new TableDataEvent(this, "labelChanged",new int[0]);
					fireTableDataEvent(e);		
				}else{
					if(varNumber<indeces[0] || varNumber >indeces[indeces.length-1]) return;
					int[] coords  = new int[2];
					coords[0] = varNumber+2 - indeces[0];
					coords[1] = -1;
					TableDataEvent e = new TableDataEvent(this, "labeling",coords);
					fireTableDataEvent(e);
				}
			}else if(varNumber != -1){
				// check wether in this data series. 
//				System.out.println("get labeling in variable: "+varNumber);
				if(varNumber<indeces[0] || varNumber >indeces[indeces.length-1]) return;
				if(rows.length==1){
					int[] coords  = new int[2];
					coords[0] = varNumber+2 - indeces[0];
					coords[1] = rows[0];
					TableDataEvent e = new TableDataEvent(this, "labeling",coords);
					fireTableDataEvent(e);
				}else{
					int[] coords  = new int[2];
					coords[0] = varNumber+2 - indeces[0];
					coords[1] = -1;
					TableDataEvent e = new TableDataEvent(this, "labeling",coords);
					fireTableDataEvent(e);
				}
			}
		}	
		public void transformerTransformerChanged(TransformerEvent evt){}

/** Clear the links in this spreadsheet for garbage collection.*/
	public void clearAll(){
/*		if(dataSourceFlag == 0){
			transformer.removeTransformerListener(this);
			tableDataEventListeners.removeAllElements();
			tableDataEventListeners = null;
			transformer = null;
			focusedCell = null;
			calendar = null;
			dateFormat = null;		
			timeFormat = null;
			data = null;
		}
*/	}

	public SimpleDateFormat getDateFormat(){
		return dateFormat;	
	}
	public void setDateFormat(SimpleDateFormat f){
		dateFormat = f;	
	}
	public SimpleDateFormat getTimeFormat(){
		return timeFormat;	
	}
	public void setTimeFormat(SimpleDateFormat f){
		timeFormat = f;	
	}

}
