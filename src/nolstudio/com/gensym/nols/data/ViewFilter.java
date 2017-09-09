package com.gensym.nols.data;
import java.io.Serializable;
import java.util.Vector;

public class ViewFilter implements Cloneable, Serializable{
	static final long serialVersionUID = 1L;

	private LabelPattern[] patternsToShow;  // its members are instances of LabelPattern
	private LabelPattern[] patternsToHide;
	public Vector existLabels;

	public ViewFilter() {
		// creates a selection query that, by default, selects all patterns
		super();
		patternsToShow = new LabelPattern[0];
//		patternsToShow[0] = new LabelPattern();
		patternsToHide = new LabelPattern[0];
		existLabels = new Vector();
	}

	public ViewFilter(Vector show, Vector hide, Vector labels) {
		this();
		for(int i=0;i<labels.size();i++){
			existLabels.addElement(labels.elementAt(i));
		}
		int nshow = show.size();
		int nhide = hide.size();
		if (nshow > 0) {
			patternsToShow = new LabelPattern[nshow];
			for (int i=0; i<nshow; i++) {
				patternsToShow[i] = (LabelPattern) show.elementAt(i);
			}
		}
		if (nhide > 0) {
			patternsToHide = new LabelPattern[nhide];
			for (int i=0; i<nhide; i++) {
				patternsToHide[i] = (LabelPattern) hide.elementAt(i);
			}
		}
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		ViewFilter cloned = (ViewFilter) super.clone();
		cloned.existLabels = existLabels == null ? null : (Vector) existLabels.clone();
		return cloned;
	}

	public LabelPattern[] getPatternsToShow(){
		return this.patternsToShow;
	}

	public void setPatternsToShow(LabelPattern[] patterns){
		if(patterns == null ) {
			this.patternsToShow = new LabelPattern[0];
		}
		else this.patternsToShow = patterns;
	}

	public LabelPattern[] getPatternsToHide(){
		return this.patternsToHide;
	}

	public void setPatternsToHide(LabelPattern[] patterns){
		if(patterns == null ){
			this.patternsToHide = new LabelPattern[0];
		}
		else this.patternsToHide = patterns;
	}

	
	public boolean isVisible(boolean[][] labelMatrix, int rowNumber) {
		// see if this point is to be shown with this view filter
		boolean showIt = false;
		int i = 0;
		if(patternsToShow.length==0) {
			showIt = true;
		}else {
			while(!showIt && i<patternsToShow.length) {	
				if(patternsToShow[i].matchesPattern(labelMatrix, rowNumber)){
					showIt = true;
				}
				i++;
			}
		}
		if (!showIt || patternsToHide.length==0) {
			return showIt;
		}
		// now see if point must be hidden
		for(i=0;i<patternsToHide.length;i++) {
			if(patternsToHide[i].matchesPattern(labelMatrix, rowNumber)){
				return false;
			}
		}
		return true;
	}

	public boolean hasLabel(NolLabel lab){
		for(int i=0;i<patternsToShow.length;i++){
			if(patternsToShow[i].hasLabel(lab))
				return true;
		}
		for(int i=0;i<patternsToHide.length;i++){
			if(patternsToHide[i].hasLabel(lab))
				return true;
		}
		return false;
	}

}

/*	public void determineVisibility(int varNumber, int firstRow, int lastRow, SelectionQuery q, boolean[] results) {
		Vector show = q.patternsToShow;
		Vector hide = q.patternsToHide;
		LabelPattern pattern;
		Vector labelsT, labelsF;
		int requiredTrueLabel, requiredFalseLabel, rowNumber, i, j;
		boolean hasRequiredTrues, hasRequiredFalses, showIt;
		for(rowNumber=firstRow; rowNumber<=lastRow; rowNumber++) {
			showIt = false;
			// see if this point is to be shown
			for(i=0; i<show.size(); i++) {
				pattern = (LabelPattern) show.elementAt(i);	
				labelsT = pattern.labelsPresent;
				labelsF = pattern.labelsAbsent;
				hasRequiredTrues = true;
				for (j=0; j<labelsT.size(); j++) {
					requiredTrueLabel = (int) labelsT.elementAt(j);
					if(!((Vector) labels.elementAt(requiredLabel)).elementAt(varNumber)[rowNumber]) {
						hasRequiredTrues = false;
						break;
					}
				}
				hasRequiredFalses = true;
				for (j=0; j<labelsF.size(); j++) {
					requiredFalseLabel = (int) labelsF.elementAt(j);
					if(labels[requiredLabel][varNumber][rowNumber]) {
						hasRequiredFalses = false;
						break;
					}
				}
				if (hasRequiredTrues && hasRequiredFalses) {
					// this point is selected to show
					showIt = true;
					break;  // don't try and match other patterns
				}
			}
			// now see if point must be hidden
			if (showIt) {  // don't waste time on points not selected
				for(i=0; i<hide.size(); i++) {
					pattern = (LabelPattern) hide.elementAt(i);	
					labelsT = pattern.labelsPresent;
					labelsF = pattern.labelsAbsent;
					hasRequiredTrues = true;
					for (j=0; j<labelsT.size(); j++) {
						requiredTrueLabel = (int) labelsT.elementAt(j);
						if(!labels[requiredLabel][varNumber][rowNumber]) {
							hasRequiredTrues = false;
							break;
						}
					}
					hasRequiredFalses = true;
					for (j=0; j<labelsF.size(); j++) {
						requiredFalseLabel = (int) labelsF.elementAt(j);
						if(labels[requiredLabel][varNumber][rowNumber]) {
							hasRequiredFalses = false;
							break;
						}
					}
					if (hasRequiredTrues && hasRequiredFalses) {
						// matches the pattern
						showIt = false;
						break;
					}
				}
			}
			results[rowNumber] = showIt;
		}
	}



}

	public void evaluateQuery(int[] labels, int firstRow, int lastRow, boolean[] results) {
		LabelPattern pattern;
		Vector labelsT, labelsF;
		int requiredTrueLabel, requiredFalseLabel, rowNumber, i, j;
		boolean hasRequiredTrues, hasRequiredFalses, showIt;
		for(rowNumber=firstRow; rowNumber<=lastRow; rowNumber++) {
			showIt = false;
			// see if this point is to be shown
			for(i=0; i<patternsToShow.size(); i++) {
				pattern = (LabelPattern) patternsToShow.elementAt(i);	
				labelsT = pattern.labelsPresent;
				labelsF = pattern.labelsAbsent;
				hasRequiredTrues = true;
				for (j=0; j<labelsT.size(); j++) {
					requiredTrueLabel = (int) labelsT.elementAt(j);
					if(!((Vector) labels.elementAt(requiredLabel)).elementAt(varNumber)[rowNumber]) {
						hasRequiredTrues = false;
						break;
					}
				}
				hasRequiredFalses = true;
				for (j=0; j<labelsF.size(); j++) {
					requiredFalseLabel = (int) labelsF.elementAt(j);
					if(labels[requiredLabel][varNumber][rowNumber]) {
						hasRequiredFalses = false;
						break;
					}
				}
				if (hasRequiredTrues && hasRequiredFalses) {
					// this point is selected to show
					showIt = true;
					break;  // don't try and match other patterns
				}
			}
			// now see if point must be hidden
			if (showIt) {  // don't waste time on points not selected
				for(i=0; i<hide.size(); i++) {
					pattern = (LabelPattern) hide.elementAt(i);	
					labelsT = pattern.labelsPresent;
					labelsF = pattern.labelsAbsent;
					hasRequiredTrues = true;
					for (j=0; j<labelsT.size(); j++) {
						requiredTrueLabel = (int) labelsT.elementAt(j);
						if(!labels[requiredLabel][varNumber][rowNumber]) {
							hasRequiredTrues = false;
							break;
						}
					}
					hasRequiredFalses = true;
					for (j=0; j<labelsF.size(); j++) {
						requiredFalseLabel = (int) labelsF.elementAt(j);
						if(labels[requiredLabel][varNumber][rowNumber]) {
							hasRequiredFalses = false;
							break;
						}
					}
					if (hasRequiredTrues && hasRequiredFalses) {
						// matches the pattern
						showIt = false;
						break;
					}
				}
			}
			results[rowNumber] = showIt;
		}
	}

} */
