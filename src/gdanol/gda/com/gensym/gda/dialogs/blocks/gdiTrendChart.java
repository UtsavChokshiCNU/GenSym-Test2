
package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.gda.controls.*;
import com.gensym.ntw.TwAccess;
import com.gensym.controls.LimitMode;

public class gdiTrendChart extends BlocksDialog {
    
    public gdiTrendChart() {}

    public gdiTrendChart(java.awt.Frame frame) {
        super(frame);

        trendChartName = new ComboBoxEditor();
        dpanel.placeAttributeEditor(trendChartName, TREND_CHART_NAME_, 
            dpanel.symbolFieldType, 10);
        
        maximumNumberOfDataPoints = new SpinEditor(1, Integer.MAX_VALUE, 1);
        dpanel.placeAttributeEditor(maximumNumberOfDataPoints, MAXIMUM_NUMBER_OF_DATA_POINTS_, 
            dpanel.integerFieldType, 20);
            
        maximumAgeOfDataPoints = new IntervalEditor();
        dpanel.placeAttributeEditor(maximumAgeOfDataPoints, MAXIMUM_AGE_OF_DATA_POINTS_, 
            dpanel.integerFieldType, 30);
        
        minIntervalBetweenDataPoints = new IntervalEditor();
        dpanel.placeAttributeEditor(minIntervalBetweenDataPoints, MIN_INTERVAL_BETWEEN_DATA_POINTS_, 
            dpanel.quantityFieldType, 40);
            
        updateTimeInterval = new IntervalEditor();
        dpanel.placeAttributeEditor(updateTimeInterval, UPDATE_TIME_INTERVAL_, 
            dpanel.integerFieldType, 50);
        
        eraseHystoryWhenReset = new CheckBoxEditor();
        dpanel.placeAttributeEditor(eraseHystoryWhenReset, ERASE_HYSTORY_WHEN_RESET_, 60);
            
    }
        

    protected ComboBoxEditor trendChartName;
    protected SpinEditor maximumNumberOfDataPoints;
    protected IntervalEditor maximumAgeOfDataPoints;
    protected IntervalEditor minIntervalBetweenDataPoints;
    protected IntervalEditor updateTimeInterval;
    protected CheckBoxEditor eraseHystoryWhenReset;

    protected final static Symbol TREND_CHART_NAME_ = Symbol.intern("GDL-TREND-CHART-NAME");
    protected final static Symbol MAXIMUM_NUMBER_OF_DATA_POINTS_ = Symbol.intern("GDL-TREND-CHART-HISTORY-NO-OF-DATA-POINTS");
    protected final static Symbol MAXIMUM_AGE_OF_DATA_POINTS_ = Symbol.intern("GDL-TREND-CHART-HISTORY-AGE-OF-DATA-POINTS");
    protected final static Symbol MIN_INTERVAL_BETWEEN_DATA_POINTS_ = Symbol.intern("GDL-TREND-CHART-HISTORY-INTERVAL");
    protected final static Symbol UPDATE_TIME_INTERVAL_ = Symbol.intern("GDL-TREND-CHART-UPDATE-INTERVAL");
    protected final static Symbol ERASE_HYSTORY_WHEN_RESET_ = Symbol.intern("GDL-TREND-CHART-DELETE-HISTORY-IF-RESET");

}