package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;
import gensym.charts.GraphChart;
import gensym.charts.autostat.*;

public class AutoStatSubsetsProperty extends PropValueBase<Integer> {
    /**
     * Sum all subsets per point
     */
    public static final int PEAS_SUMPP = 51;
    
    /**
     * Minimum all subsets all points
     */
    public static final int PEAS_MINAP = 1;
    
    /**
     * Minimum all subsets per point
     */
    public static final int PEAS_MINPP = 52;
    
    /**
     * Maximum all subsets all points
     */
    public static final int PEAS_MAXAP = 2;
    
    /**
     * Maximum all subsets per point
     */
    public static final int PEAS_MAXPP = 53;
    
    /**
     * Average all subsets all points
     */
    public static final int PEAS_AVGAP = 3;
    
    /**
     * Average all subsets per point
     */
    public static final int PEAS_AVGPP = 54;
    
    /**
     * Average plus 1 Std Dev all points
     */
    public static final int PEAS_P1SDAP = 4;
    
    /**
     * Average plus 1 Std Dev per point
     */
    public static final int PEAS_P1SDPP = 55;

    /**
     * Average plus 2 Std Devs all points
     */
    public static final int PEAS_P2SDAP = 5;
    
    /**
     * Average plus 2 Std Devs per point
     */
    public static final int PEAS_P2SDPP = 56;
    
    /**
     * Average plus 3 Std Devs all points
     */
    public static final int PEAS_P3SDAP = 6;
    
    /**
     * Average plus 3 Std Devs per point
     */
    public static final int PEAS_P3SDPP = 57;
    
    /**
     * Average minus 1 Std Dev all points
     */
    public static final int PEAS_M1SDAP = 7;
    
    /**
     * Average minus 1 Std Dev per point
     */
    public static final int PEAS_M1SDPP = 58;
   
    /**
     * Average minus 2 Std Devs all points
     */
    public static final int PEAS_M2SDAP = 8;
    
    /**
     * Average minus 2 Std Devs per point
     */
    public static final int PEAS_M2SDPP = 59;
    
    /**
     * Average minus 3 Std Devs all points
     */
    public static final int PEAS_M3SDAP = 9;
    
    /**
     * Average minus 3 Std Devs per point
     */
    public static final int PEAS_M3SDPP = 60;
    
    /**
     * Pareto ascending accumulated percent line
     */
    public static final int PEAS_PARETO_ASC = 90;
    
    /**
     * Pareto descending accumulated percent line
     */
    public static final int PEAS_PARETO_DEC = 91;
    
    /**
     * Returns auto stat info by specified type
     * @param type auto stat type
     * @return auto stat info
     */
    private AutoStatInfo getAutoStat(int type) {
        switch (type) {
        case PEAS_SUMPP:
            return new SumAutoStatInfo();
            
        case PEAS_MINAP:
        case PEAS_MINPP:
            return new MinAutoStatInfo();
            
        case PEAS_MAXAP:
        case PEAS_MAXPP:
            return new MaxAutoStatInfo();
            
        case PEAS_AVGAP:
        case PEAS_AVGPP:
            return new AvgAutoStatInfo();

        case PEAS_P1SDAP:
        case PEAS_P1SDPP:
            return new AvgWithStdDevs(1);
            
        case PEAS_P2SDAP:
        case PEAS_P2SDPP:
            return new AvgWithStdDevs(2);

        case PEAS_P3SDAP:
        case PEAS_P3SDPP:
            return new AvgWithStdDevs(3);
            
        case PEAS_M1SDAP:
        case PEAS_M1SDPP:
            return new AvgWithStdDevs(-1);

        case PEAS_M2SDAP:
        case PEAS_M2SDPP:
            return new AvgWithStdDevs(-2);

        case PEAS_M3SDAP:
        case PEAS_M3SDPP:
            return new AvgWithStdDevs(-3);
        }
        
        return null;
    }
    
    /**
     * Tests if stat is used for all points
     * @param type stat type
     * @return true if stat is used for all points
     */
    private boolean isStatForAllPoints(int type) {
        switch (type) {
        case PEAS_MINAP:
        case PEAS_MAXAP:
        case PEAS_AVGAP:
        case PEAS_P1SDAP:
        case PEAS_P2SDAP:
        case PEAS_P3SDAP:
        case PEAS_M1SDAP:
        case PEAS_M2SDAP:
        case PEAS_M3SDAP:
            return true;
        }
        return false;
    }

    /**
     * Constructor
     */
    public AutoStatSubsetsProperty() {
        super(3300, "auto-stat-subsets");
    }

    /**
     * {@inheritDoc}
     * Sets bitmap gradient mode flag
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            if (value != PEAS_PARETO_ASC && value != PEAS_PARETO_DEC) {
                graph.addAutoStatSubset(getAutoStat(value), isStatForAllPoints(value));
            } else {
                graph.addParetoAutoStatSubset(value == PEAS_PARETO_ASC);
            }
        }
    }
}
