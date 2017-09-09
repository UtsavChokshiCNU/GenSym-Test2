package gensym.charts;

import gensym.charts.j3d.Plot3D;
import gensym.charts.scrolling.ChartScrolling;

import java.util.Timer;
import java.util.TimerTask;

/**
 * Auto rotation classss
 */
public class AutoRotation3D {

    /** Plot of the chart */
    private ChartScrolling scrolling = null;

    /** Timer for auto rotation */
    private Timer timer = null;

    /** Auto rotation increment */
    private int rotationIncrement = -1;

    /** Rotation speed */
    private int rotationSpeed = 500;

    /** Plot3D of the chart */
    private Plot3D plot;

    /**
     * Constructor
     */
    public AutoRotation3D(ChartScrolling scrolling, Plot3D plot) {
        this.scrolling = scrolling;
        this.plot = plot;
    }

    /**
     * Sets rotation speed for auto rotation
     * @param speed of rotation
     */
    public void setSpeed(int speed) {
        rotationSpeed = speed;
    }

    /**
     * Gets auto rotation speed
     * @return auto rotation speed
     */
    public int getSpeed() {
        return rotationSpeed;
    }

    /**
     * Sets rotation increment for auto rotation
     * @param increment of auto rotation (e.g. 15 degree)
     */
    public void setIncrement(int increment) {
        rotationIncrement = (int) (increment * scrolling.getScrollItemsCount() / 360);
    }

    /**
     * Gets auto rotation increment
     * @return auto rotation increment
     */
    public int getIncrement() {
        return rotationIncrement;
    }

    /**
     * Checks auto rotation
     * @return true if auto rotation running
     */
    public boolean isRunning() {
        return timer != null;
    }

    /**
     * Starts or stops auto rotation
     * @param command, true if need to start
     */
    public void doAutoRotation3D(boolean command) {
        if (command && !isRunning()) {
            timer = new Timer();
            timer.scheduleAtFixedRate(new TimerTask() {

                /**
                 *  Schedule of the task
                 */
                public void run() {
                    if (scrolling.getScrollItemPos() + getIncrement() < 0) {
                        scrolling.updateScrollingPos(scrolling.getScrollItemsCount() - 1);
                    } else if (scrolling.getScrollItemPos() +
                            getIncrement() > scrolling.getScrollItemsCount()) {
                        scrolling.updateScrollingPos(0);
                    } else {
                        scrolling.updateScrollingPos(scrolling.getScrollItemPos() + getIncrement());
                    }
                }
            }, 0, getSpeed());

            plot.setRotationMode();

        } else if (!command && isRunning()) {
            timer.cancel();
            timer = null;
            plot.leaveRotationMode();
        }
    }
}
