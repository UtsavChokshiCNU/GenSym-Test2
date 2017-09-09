package com.gensym.nols.chart.line;

public class Range {
	public Number lowerBound;
	public Number upperBound;

	public Range(Number lb, Number ub) {
		super();
		lowerBound = lb;
		upperBound = ub;
	}

	// is union ever used?
	public Range union(Range r) {
		// should never be conflicting types
		if (lowerBound instanceof Double && r.lowerBound instanceof Double) {
			double lb = Math.min(lowerBound.doubleValue(), r.lowerBound.doubleValue());
			double ub = Math.max(upperBound.doubleValue(), r.upperBound.doubleValue());
			return new Range(lb, ub);
		}
		else if (lowerBound instanceof Long && r.lowerBound instanceof Long) {
			long lb = Math.min(lowerBound.longValue(), r.lowerBound.longValue());
			long ub = Math.max(upperBound.longValue(), r.upperBound.longValue());
			return new Range(lb, ub);
		}
		else {  // hopefully, an int
			int lb = Math.min(lowerBound.intValue(), r.lowerBound.intValue());
			int ub = Math.max(upperBound.intValue(), r.upperBound.intValue());
			return new Range(lb, ub);
		}
	}
}