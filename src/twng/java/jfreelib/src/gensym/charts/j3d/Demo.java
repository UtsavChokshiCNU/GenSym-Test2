package gensym.charts.j3d;

import gensym.charts.j3d.renderers.*;

import java.awt.event.*;
import java.awt.*;

import javax.swing.*;
import javax.swing.event.*;

import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.ui.RectangleEdge;
import org.jfree.ui.RefineryUtilities;
import org.jfree.util.ShapeUtilities;

/**
 * RotationMouseAdapter class changes plotting during rotation
 */
class DemoRotationMouseAdapter extends MouseAdapter {

    /** Demo pane 3D */
    private DemoPanel3D pane;

    /**
     * Constructor
     * @param pane demo pane
     */
    public DemoRotationMouseAdapter(DemoPanel3D pane) {
        this.pane = pane;
    }

    /**
     * {@inheritDoc}
     */
    public void mousePressed(MouseEvent e) {
        if (e.getClickCount() == 1) {
            pane.getPlot().setPlottingDetails(pane.
                    getRotationCombo().getSelectedIndex());
            pane.getPlot().setContourVisible(true);
            pane.getPlot().datasetChanged(null);
        }
    }

    /**
     * {@inheritDoc}
     */
    public void mouseReleased(MouseEvent e) {
        pane.getPlot().setPlottingDetails(Renderer3D.DETAILS_FULL);
        pane.getPlot().setContourVisible(false);
        pane.getPlot().datasetChanged(null);
    }
}

/**
 * Demo panel
 */
class DemoPanel3D extends JPanel {

    /** Generated serial version UID */
    private static final long serialVersionUID = -3717030746312003276L;
    
    /** Rotation details & Plotting method: 0 value */
    public static final String PERD_WIREFRAME = "Wireframe";

    /** Rotation details: 1 value */
    public static final String PERD_PLOTTINGMETHOD = "Use plotting method";

    /** Rotation details: 2 value */
    public static final String PERD_FULLDETAIL = "Full details";


    /** Plotting method: 0 value */
    public static final String PGPM_POINT = "Points";

    /** Plotting method: 1 value */
    public static final String PEGPM_LINE = "Lines";

    /** Plotting method: 2 value */
    public static final String PEGPM_POINTSPLUSLINE = "Points + Lines";


    /** Plotting method: 1 value */
    public static final String PEGPM_SURFACE = "Surface";

    /** Plotting method: 2 value */
    public static final String PEGPM_SURFACE_SHADING = "Surface with Shading";

    /** Plotting method: 3 value */
    public static final String PEGPM_SURFACE_PIXELS = "Surface with Pixels";

    /** Plotting method: 4 value */
    public static final String PEGPM_SURFACE_CONTOURS = "Surface with Contours";


    /** Rotation detail values*/
    public static final String[] ROTATION_DETAIL_VALUES
            = {PERD_WIREFRAME, PERD_PLOTTINGMETHOD, PERD_FULLDETAIL};

    /** Plotting method values for PEPM-3DBAR PolyMode*/
    public static final String[] PLOTTING_METHOD_3DBAR = {PERD_WIREFRAME,
        PEGPM_SURFACE, PEGPM_SURFACE_SHADING, PEGPM_SURFACE_PIXELS};

    /** Plotting method values for PEPM-SURFACEPOLYGONS PolyMode*/
    public static final String[] PLOTTING_METHOD_SURFACEPOLYGONS = {PERD_WIREFRAME,
        PEGPM_SURFACE, PEGPM_SURFACE_SHADING, PEGPM_SURFACE_PIXELS, PEGPM_SURFACE_CONTOURS};

    /** Plotting method values for PEPM-SCATTER PolyMode*/
    public static final String[] PLOTTING_METHOD_SCATTER
            = {PGPM_POINT, PEGPM_LINE, PEGPM_POINTSPLUSLINE};

    /** 3D Plot */
    private Plot3D plot;

    /** Rotation combobox*/
    private JComboBox rotationCombo = new JComboBox(ROTATION_DETAIL_VALUES);

    /**
     * Constructor
     * @param plot 3D plot
     * @param title chart title 
     * @param xAngle angle to rotate around X axis
     * @param yAngle angle to rotate around Y axis
     * @param zAngle angle to rotate around Z axis
     */
    public DemoPanel3D(final Plot3D plot, String title,
            int xAngle, int yAngle, int zAngle, String[] comboValues) {
        super(new BorderLayout());
        this.plot = plot;

        Font font = Axis3D.DEFAULT_AXIS_LABEL_FONT.deriveFont(Font.BOLD);

        plot.getXAxis().setLabel("X axis");
        plot.getXAxis().setLabelPaint(Color.DARK_GRAY);
        plot.getXAxis().setLabelFont(font);
        
        plot.getYAxis().setLabel("Y axis");
        plot.getYAxis().setLabelPaint(Color.DARK_GRAY);
        plot.getYAxis().setLabelFont(font);

        plot.getZAxis().setLabel("Z axis");
        plot.getZAxis().setLabelPaint(new Color(0x00, 0x7F, 0x00));
        plot.getZAxis().setLabelFont(font);
        plot.getZAxis().setTickLabelPaint(Color.blue);
        
        final JFreeChart chart = new JFreeChart(plot);
        chart.setTitle(title);
        chart.getLegend().setPosition(RectangleEdge.TOP);
        
        plot.setBackgroundPaint(Color.LIGHT_GRAY);
        plot.setOutlinePaint(Color.BLACK);
        plot.setOutlineStroke(new BasicStroke(1));

        final ChartPanel panel = new ChartPanel(chart);
        add(panel, BorderLayout.CENTER);

        // zooming
        panel.addMouseWheelListener(new MouseWheelListener() {
            public void mouseWheelMoved(MouseWheelEvent e) {
                double zoom = e.getWheelRotation() > 0 ? 0.1 : -0.1;
                plot.zoom(zoom, true);
            }
        });

        // moving
        panel.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() > 1) {
                    // center plot
                    plot.zoom(1);
                    plot.moveScreen(0, 0, false);
                }
            }

            public void mouseReleased(MouseEvent e) {
                setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
            }
        });

        panel.addMouseMotionListener(new MouseMotionAdapter() {
            private boolean moving = false;
            private Point lastPoint = null;
            public void mouseDragged(MouseEvent e) {
                moving = panel.getChartRenderingInfo().getPlotInfo().getDataArea().contains(e.getX(), e.getY());
                if (getCursor().getType() != Cursor.HAND_CURSOR) {
                    lastPoint = null;
                }
                if (moving) {
                    setCursor(new Cursor(Cursor.HAND_CURSOR));
                    if (lastPoint != null) {
                        plot.moveScreen(e.getX() - lastPoint.getX(), e.getY() - lastPoint.getY(), true);
                    }
                    lastPoint = (Point) e.getPoint().clone();
                }
            }
        });

        JPanel controls = getSliders(xAngle, yAngle, zAngle, comboValues);
        final JCheckBox legends = new JCheckBox("Show legend", true);
        controls.add(legends);
        legends.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                chart.getLegend().setVisible(legends.isSelected());
            }
        });
        
        add(controls, BorderLayout.SOUTH);
    }

    /**
     * Added comboboxes to the panel
     * @param controls panel to add
     * @param comboValues values of plotting combobox
     */
    private void addComboBoxes(JPanel controls, String[] comboValues) {
        // Rotation detail combo
        JPanel pane = new JPanel(new GridLayout(2, 1));
        final JLabel rotationDetailsLabel = new JLabel("Rotation details:", JLabel.CENTER);
        pane.add(rotationDetailsLabel);
        rotationCombo.setBackground(Color.LIGHT_GRAY);
        rotationCombo.setForeground(Color.BLACK);
        pane.add(rotationCombo);
        controls.add(pane);

        // Plotting method combo
        pane = new JPanel(new GridLayout(2, 1));
        final JLabel plottingMethodLabel = new JLabel("Plotting method:", JLabel.CENTER);
        pane.add(plottingMethodLabel);
        final JComboBox plottingCombo = new JComboBox(comboValues);
        plottingCombo.setBackground(Color.LIGHT_GRAY);
        plottingCombo.setForeground(Color.BLACK);
        plot.setPlottingMethod(0);
        plottingCombo.addItemListener(new ItemListener() {
            public void itemStateChanged(ItemEvent ie) {
                getPlot().setPlottingMethod(plottingCombo.getSelectedIndex());
            }
        });
        pane.add(plottingCombo);
        controls.add(pane);
    }

    /**
     * Gets sliders component
     * @param xAngle angle to rotate around X axis
     * @param yAngle angle to rotate around Y axis
     * @param zAngle angle to rotate around Z axis
     * @return sliders component
     */
    private JPanel getSliders(int xAngle, int yAngle, int zAngle, String[] comboValues) {
        JPanel controls = new JPanel(new GridLayout(2, 3));

        JPanel slider = new JPanel(new GridLayout(2, 1));
        final JLabel xAngleLabel = new JLabel("", JLabel.CENTER);
        slider.add(xAngleLabel);

        // X angle slider
        final JSlider sliderPhi = new JSlider(-180, 180);
        sliderPhi.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                double phi = Math.PI * sliderPhi.getValue() / 180;
                xAngleLabel.setText("X angle: " + sliderPhi.getValue());
                plot.rotateAroundX(phi);
            }
        });
        sliderPhi.addMouseListener(new DemoRotationMouseAdapter(this));
        sliderPhi.setValue(xAngle);
        slider.add(sliderPhi);
        controls.add(slider);

        slider = new JPanel(new GridLayout(2, 1));
        final JLabel yAngleLabel = new JLabel("", JLabel.CENTER);
        slider.add(yAngleLabel);

        // Y angle slider
        final JSlider sliderXi = new JSlider(-180, 180);
        sliderXi.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                double xi = Math.PI * sliderXi.getValue() / 180;
                yAngleLabel.setText("Y angle: " + sliderXi.getValue());
                plot.rotateAroundY(xi);
            }
        });
        sliderXi.addMouseListener(new DemoRotationMouseAdapter(this));
        sliderXi.setValue(yAngle);
        slider.add(sliderXi);
        controls.add(slider);

        slider = new JPanel(new GridLayout(2, 1));
        final JLabel zAngleLabel = new JLabel("", JLabel.CENTER);
        slider.add(zAngleLabel);

        // Z angle slider
        final JSlider sliderRho = new JSlider(-180, 180);
        sliderRho.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                double rho = Math.PI * sliderRho.getValue() / 180;
                zAngleLabel.setText("Z angle: " + sliderRho.getValue());
                plot.rotateAroundZ(rho);
            }
        });
        sliderRho.addMouseListener(new DemoRotationMouseAdapter(this));
        sliderRho.setValue(zAngle);
        slider.add(sliderRho);
        controls.add(slider);

        addComboBoxes(controls, comboValues);

        return controls;
    }

    /**
     * Gets plot
     * @return plot instace of Plot3D
     */
    public Plot3D getPlot() {
        return plot;
    }

    /**
     * Gets rotation combo
     * @return rotation combo
     */
    public JComboBox getRotationCombo() {
        return rotationCombo;
    }
}

/**
 * Demo class demonstrate 3D charts abilities
 */
public class Demo extends JFrame {
    /**
     * Generated serial version UID
     */
    private static final long serialVersionUID = 2040169600518532408L;
    
    /**
     * Constructor
     * @param title frame title
     */
    public Demo(String title) {
        super(title);
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                System.exit(0);
            }
        });

        JPanel contentMain = new JPanel(new BorderLayout());
        contentMain.setPreferredSize(new Dimension(600, 400));

        contentMain.add(getTabs());

        getContentPane().add(contentMain);
        RefineryUtilities.centerFrameOnScreen(this);
        pack();

    }

    /**
     * Gets tabs component
     * @return tabs component
     */
    private Component getTabs() {
        JTabbedPane tabs = new JTabbedPane();
        tabs.add("Bar 3D", new DemoPanel3D(getBarPlot(),
                "Bar 3D Chart", 80, -180, -120, DemoPanel3D.PLOTTING_METHOD_3DBAR));
        tabs.add("Surface 3D", new DemoPanel3D(getSurfacePlot(),
                "Surface 3D Chart", -129, -18, -22, DemoPanel3D.PLOTTING_METHOD_SURFACEPOLYGONS));
        tabs.add("Points 3D", new DemoPanel3D(getSimplePlot(),
                "Points 3D Chart", -137, 23, -68, DemoPanel3D.PLOTTING_METHOD_SCATTER));
        return tabs;
    }

    /**
     * Creates bar plot
     * @return the bar plot
     */
    private Plot3D getBarPlot() {
        Dataset3D dataset = new Dataset3D();
        int subsets = 5;
        int ncols = 10;

        BarRenderer3D renderer = new BarRenderer3D();
        String names[] = new String[]{"One", "Two", "Three", "Four", "Five"};
        for (int s = 0; s < subsets; s++) {
            Series3D series = new Series3D("Bar " + names[s % names.length]);
            for (int p = 0; p < ncols; p++) {
                double x = p + 1;
                double z = 15.0 * Math.sin((s + 1) * 0.5) + 15.0 * Math.cos((p + 1) * 0.24);
                double y = s + 1;
                series.addPoint3D(new Point3D(x, y, z));
            }
            dataset.addSeries(series);
            renderer.setSeriesOutlinePaint(s, Color.BLACK);
        }
        renderer.setLegendSupported(true);

        Plot3D plot = new Plot3D(dataset, new Axis3D(), new Axis3D(), new Axis3D());
        plot.setRenderer(renderer);

        for (int p = 0; p < ncols; p++) {
            plot.getXAxis().getLabelFormat().setLabel(p, "Point " + p);
        }
        for (int s = 0; s < subsets; s++) {
            plot.getYAxis().getLabelFormat().setLabel(s, (String) dataset.getSeriesKey(s));
        }
        return plot;
    }

    /**
     * Create surface plot
     * @return the surface plot 
     */
    private Plot3D getSurfacePlot() {
        Dataset3D dataset = new Dataset3D();
        SurfaceRenderer3D renderer = new SurfaceRenderer3D();
        for (int s = 0; s < 20; s++) {
            Series3D series = new Series3D("series" + s);
            for (int p = 0; p < 20; p++) {
                double x = 50 + (p * 150);
                double y = 50 + (s * 150);
                double z = (5 + 35.0 * Math.cos((p - 10) * .4)) * (5 + 10.0 * Math.sin((s - 10) * .34));
                series.addPoint3D(new Point3D(x, y, z));
            }
            dataset.addSeries(series);
            renderer.setSeriesOutlinePaint(s, Color.BLACK);
        }

        Plot3D plot = new Plot3D(dataset, new Axis3D(), new Axis3D(), new Axis3D());
        plot.setRenderer(renderer);
        return plot;
    }

    /**
     * Createas line plot
     * @return the line plot
     */
    private Plot3D getSimplePlot() {
        Dataset3D dataset = new Dataset3D();

        // Number of points/subset
        int n = 50;

        // First two subsets
        for (int s = 0; s < 2; s++) {
            Series3D series = new Series3D("Series " + s);
            for (int p = 0; p < n - 1; p++) {
                double x = 5.0 * Math.cos(p * 0.24);
                double z = 0;
                if (s == 0) {
                    z = (35.0 * Math.cos(p * 0.22)) + (10.0 * Math.sin((s * 0.1) * 0.94));
                } else {
                    z = (35.0 * Math.cos(p * 0.08)) + (10.0 * Math.cos((s * 0.25) * 0.6));
                }
                double y = 25.0 * Math.sin(p * 0.08);
                series.addPoint3D(new Point3D(x, y, z));
            }
            dataset.addSeries(series);
        }

        // Second two subsets
        for (int s = 0; s < 2; s++) {
            Series3D series = new Series3D("Series " + (s + 2));
            for (int p = 0; p < n - 1; p++) {
                double x = 25.0 * Math.cos(p * 0.14) + 40;
                double z = 0;
                if (s == 0) {
                    z = (35.0 * Math.cos(p * 0.2)) + (10.0 * Math.sin((s * 0.1) * 0.74));
                } else {
                    z = (35.0 * Math.cos(p * 0.1)) + (10.0 * Math.cos((s * 0.25) * 0.74));
                }
                z += 40.0;
                double y = 5.0 * Math.sin(p * 0.16) + 40;
                series.addPoint3D(new Point3D(x, y, z));
            }
            dataset.addSeries(series);
        }

        // Third two subsets
        for (int s = 0; s < 2; s++) {
            Series3D series = new Series3D("Series " + (s + 4));
            for (int p = 0; p < n - 1; p++) {
                double x = 15.0 * Math.cos(p * 0.07) - 70;
                double z = 0;
                if (s == 0) {
                    z = (35.0 * Math.cos(p * 0.08)) + (10.0 * Math.sin((s * 0.07) * 0.64));
                } else {
                    z = (35.0 * Math.cos(p * 0.2)) + (10.0 * Math.cos((s * .15) * 1.94));
                }
                z += 40.0;
                double y = 15.0 * Math.sin(p * 0.09) + 60;
                series.addPoint3D(new Point3D(x, y, z));
            }
            dataset.addSeries(series);
        }

        // Fourth two subsets
        for (int s = 0; s < 2; s++) {
            Series3D series = new Series3D("Series " + (s + 6));
            for (int p = 0; p < n - 1; p++) {
                double x = 15.0 * Math.cos(p * 0.12) - 60;
                double z = 0;
                if (s == 0) {
                    z = (35.0 * Math.cos(p * 0.3)) + (10.0 * Math.sin((s * 0.08) * 1.74));
                } else {
                    z = (35.0 * Math.cos(p * 0.2)) + (10.0 * Math.cos((s * 0.75) * 0.774));
                }
                z -= 40.0;
                double y = 45.0 * Math.sin(p * 0.36) - 60;
                series.addPoint3D(new Point3D(x, y, z));
            }
            dataset.addSeries(series);
        }

        // Fifth two subsets
        for (int s = 0; s < 2; s++) {
            Series3D series = new Series3D("Series " + (s + 8));
            for (int p = 0; p < n - 1; p++) {
                double x = 50.0 * Math.cos(p * 0.14) + 20;
                double z = 0;
                if (s == 0) {
                    z = (25.0 * Math.cos(p * 0.1)) + (10.0 * Math.sin((s * 0.02) * 3.74));
                } else {
                    z = (55.0 * Math.cos(p * 0.2)) + (10.0 * Math.cos((s * 0.05) * 5.74));
                }
                z += 40.0;
                double y = 15.0 * Math.sin(p * 0.16) - 80;
                series.addPoint3D(new Point3D(x, y, z));
            }
            dataset.addSeries(series);
        }

        Plot3D plot = new Plot3D(dataset, new Axis3D(), new Axis3D(), new Axis3D());
        LineAndShapeRenderer3D renderer = new LineAndShapeRenderer3D();
        for (int i = 0; i < 10; i += 3) {
            renderer.setSeriesShape(i, ShapeUtilities.createDiagonalCross(1, 3));
            renderer.setSeriesShape(i + 1, ShapeUtilities.createRegularCross(1, 3));
            renderer.setSeriesShape(i + 2, ShapeUtilities.createDiamond(3));
        }
        plot.setRenderer(renderer);
        return plot;
    }

    /**
     * Main function
     * @param args command line args
     */
    public static void main(String[] args) {
        new Demo("3D Charts Demo").setVisible(true);
    }
}
