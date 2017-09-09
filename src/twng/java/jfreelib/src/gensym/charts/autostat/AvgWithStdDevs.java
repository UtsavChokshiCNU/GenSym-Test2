package gensym.charts.autostat;

/**
 * Average statistic with some extension (used standard deviation)
 */
public class AvgWithStdDevs extends AvgAutoStatInfo {

    /**
     * Quantity of standard deviations for indention
     */
    private int stdDevsIndention = 0;

    /**
     * Constructor
     * @param stdDev count of standard deviation to indention
     */
    public AvgWithStdDevs(int stdDev) {
        super(getStaticName(stdDev));
        this.stdDevsIndention = stdDev;
    }

    /**
     * {@inheritDoc}
     */
    public double calculate() {
        return super.calculate() + stdDevsIndention * getStdDev();
    }

    /**
     * Get unique name by type
     * @param stdDevs type
     * @return class name
     */
    private static String getStaticName(int stdDevs) {
        String name = "Avg";
        if (stdDevs != 0) {
            name += " " + stdDevs + "std devs";
        }
        return name;
    }

    /**
     * Calculate standard deviation for some statistical selection
     * @return standard deviation
     */
    private double getStdDev() {
        Double summ = 0.0;
        Double average = super.calculate();
        for (Double y : getData()) {
            summ += Math.pow(Math.abs(y - average), 2);
        }
        return getData().size() > 0 ? Math.pow(summ / getData().size(), 0.5) : 0.0;
    }
}
