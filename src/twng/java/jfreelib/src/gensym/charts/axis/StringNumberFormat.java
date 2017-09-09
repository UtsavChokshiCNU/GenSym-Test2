package gensym.charts.axis;

import java.text.NumberFormat;
import java.text.DecimalFormat;
import java.text.FieldPosition;
import java.text.ParsePosition;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Vector;

public class StringNumberFormat extends NumberFormat {

    /** Generated serial version UID */
    private static final long serialVersionUID = 4806454995336242539L;

    /** Default number format */
    public static final NumberFormat DEFAULT_NUMBER_FORMAT = new DecimalFormat();

    /**
     * Data source interface
     */
    public static interface DataSource {
        /**
         * Return index of given value
         * @param value the value
         * @return value index or -1 if value is not present
         */
        public int indexOf(double value);

        /**
         * Returns value by index
         * @param index value index
         * @return value by index or null if index is invalid
         */
        public Double getValue(int index);
    }

    /**
     * Data source
     */
    private DataSource source = null;

    /**
     * Default format
     */
    private NumberFormat format = null;

    /**
     * List of labels for axis
     */
    private Vector<String> labels = new Vector<String>();

    /**
     * Constructor
     * @param source the data source
     */
    public StringNumberFormat(DataSource source) {
        setSource(source);
    }
    
    /**
     * Sets data source
     * @param source the new data source
     */
    public final void setSource(DataSource source) {
        this.source = source;
    }
    
    /**
     * Returns data source
     * @return the data source
     */
    public DataSource getSource() {
        return source;
    }
    
    /**
     * Sets default number format
     * @param format
     */
    public void setDefaultNumberFormat(NumberFormat format) {
        this.format = format;
    }

    /**
     * Sets label for value
     * @param index label index
     * @param label new label
     */
    public void setLabel(int index, String label) {
        if (labels.size() <= index) {
            labels.setSize(index + 1);
        }
        labels.set(index, label);
    }
            
    /**
     * {@inheritDoc}
     */
    public StringBuffer format(double number,
            StringBuffer toAppendTo, FieldPosition pos) {

        int index = -1;
        if (getSource() != null) {
            index = getSource().indexOf(number);
        }
        if (index >= 0 && index < labels.size()) {
            toAppendTo.append(labels.get(index));
        } else if (labels.size() == 0 && toAppendTo != null) {
           NumberFormat defFormat = format;
           if (defFormat == null) {
                defFormat = DEFAULT_NUMBER_FORMAT;
           }
           return defFormat.format(number, toAppendTo, pos);
        }
        return toAppendTo;
    }

    /**
     * {@inheritDoc}
     */
    public StringBuffer format(long number, StringBuffer toAppendTo,
            FieldPosition pos) {
        return format((double) number, toAppendTo, pos);
    }

    /**
     * {@inheritDoc}
     */
    public Number parse(String source, ParsePosition parsePosition) {
        return null;
    }

    /**
     * Tests if list of replacing items is empty
     * @return true if list of replacing items is empty
     */
    public boolean isEmpty() {
        return labels.isEmpty();
    }

    /**
     * Returns labels map (value => label)
     * @return labels map
     */
    public Map<Double, String> getLabels() {
        Map<Double, String> map = new LinkedHashMap<Double, String>();
        int index = 0;
        for (String label : labels) {
            Double value = getSource() != null ? getSource().getValue(index++) : null;
            if (value == null) {
                break;
            }

            map.put(value, label);
        }
        return map;
    }
}
