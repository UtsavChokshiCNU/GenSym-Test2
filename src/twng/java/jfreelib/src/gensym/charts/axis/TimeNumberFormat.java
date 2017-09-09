package gensym.charts.axis;

import java.text.*;
import java.util.Date;
import java.util.Locale;

public class TimeNumberFormat extends NumberFormat {
    /**
     * Generated serial version UID
     */
    private static final long serialVersionUID = 7155148678726672452L;
    
    /* Time converting constants */
    private static final double yearsToSkip = 25569.0000;
    private static final double secPerDay = 86400.0000;
    private static final double milli = 1000.0000;
    private static final double delta = 7200000.0000;


    /**
     * DateTime format for data conversion
     */
    private DateFormat dateFormat = DateFormat.getDateTimeInstance(SimpleDateFormat.SHORT, SimpleDateFormat.SHORT, Locale.ENGLISH);

    /**
     * {@inheritDoc}
     */
    public StringBuffer format(double number, StringBuffer toAppendTo, FieldPosition pos) {
        return dateFormat.format(convertTime(number), toAppendTo, pos);
    }

    /**
     * {@inheritDoc}
     */
    public StringBuffer format(long number, StringBuffer toAppendTo, FieldPosition pos) {
        return format((double) number, toAppendTo, pos);
    }

    /**
     * {@inheritDoc}
     */
    public Number parse(String source, ParsePosition parsePosition) {
        return null;
    }
    
    static private Date convertTime(double unix) {
        double date = secPerDay * milli * (unix - yearsToSkip) - delta;
        return new Date((long) date);
    }
}
