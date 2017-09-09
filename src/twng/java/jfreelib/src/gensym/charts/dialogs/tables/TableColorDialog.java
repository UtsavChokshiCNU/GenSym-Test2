package gensym.charts.dialogs.tables;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
import org.jfree.ui.RefineryUtilities;

/**
 * Select color dialog
 */
public class TableColorDialog extends JDialog implements ActionListener {
    /**
     * Generated serial version UID
     */
    private static final long serialVersionUID = 5120993783588778552L;

    /**
     * Colors source
     */
    private TableColorSource source;
    
    /**
     * Color button of the text
     */
    private TableColorButton textBtn;
    
    /**
     * Color button of the out lines
     */
    private TableColorButton outLineBtn;
    
    /**
     * Group of the radio buttons
     */
    private ButtonGroup applyToBtns = new ButtonGroup();

    /**
     * Constructor
     * @param owner frame which owns dialog
     */
    public TableColorDialog(Frame owner, TableColorSource colorSource,
            int tableRow, int tableColumn) {
        super(owner, "Change colors", true);
        source = colorSource;

        // user grid bag layout fot the component
        GridBagLayout layout = new GridBagLayout();
        getContentPane().setLayout(layout);

        // Initialize labels and buttons
        initButtons(layout, tableRow, tableColumn);
        initLabels(layout);

        pack();
        RefineryUtilities.centerFrameOnScreen(this);
    }

    /**
     * {@inheritDoc}
     */
    public void actionPerformed(ActionEvent e) {
        if (e.getActionCommand().equals("ok")) {
            int row = -1, column = -1;
            TableColorRButton button = getSelectedButton();
            if (button != null) {
                row = button.getRow();
                column = button.getColumn();
            }
            source.setTextColor(row, column, textBtn.getColor());
            source.setOutlineColor(row, column, outLineBtn.getColor());
        }
        dispose();
    }

    /**
     * Gets selected radio button
     * @return selected button
     */
    private TableColorRButton getSelectedButton() {
        for (Enumeration<AbstractButton> elems = applyToBtns.getElements();
                elems.hasMoreElements();) {
            AbstractButton element = elems.nextElement();
            if (element instanceof TableColorRButton) {
                TableColorRButton button = (TableColorRButton) element;
                if (button.isSelected()) {
                    return button;
                }
            }
        }
        return null;
    }

    /**
     * Return grid constraints
     * @param gridx x position
     * @param gridy y position
     * @return grid constraints
     */
    private GridBagConstraints getConstraints(int gridx, int gridy) {
        GridBagConstraints cons = new GridBagConstraints();
        cons.insets = new Insets(10, 10, 5, 5);
        cons.fill = GridBagConstraints.BOTH;
        cons.gridx = gridx;
        cons.gridy = gridy;
        return cons;
    }

    /**
     * Initialization of the dialog buttons
     * @param layout grid layout
     * @param tableRow row
     * @param tableColumn column
     */
    private void initButtons(GridBagLayout layout, int tableRow, int tableColumn) {
        textBtn = new TableColorButton(source.getTextColor(tableRow, tableColumn), 50, 20);
        outLineBtn = new TableColorButton(source.getOutlineColor(tableRow, tableColumn), 50, 20);

        JButton cancelBtn = new JButton("Cancel");
        cancelBtn.setActionCommand("cancel");
        cancelBtn.addActionListener(this);

        JButton okBtn = new JButton("OK");
        okBtn.setActionCommand("ok");
        okBtn.addActionListener(this);

        // create the layout
        layout.setConstraints(textBtn, getConstraints(1, 0));
        getContentPane().add(textBtn);

        layout.setConstraints(outLineBtn, getConstraints(1, 1));
        getContentPane().add(outLineBtn);

        layout.setConstraints(cancelBtn, getConstraints(1, 3));
        getContentPane().add(cancelBtn);

        layout.setConstraints(okBtn, getConstraints(0, 3));
        getContentPane().add(okBtn);


        boolean doSelect = true;
        JPanel radioPanel = new JPanel();
        radioPanel.setLayout(new GridLayout(2, 2));
        if (tableRow != -1 && tableColumn != -1) {
            JRadioButton cell = new TableColorRButton("Cell", doSelect, tableRow, tableColumn);
        radioPanel.add(cell);
            applyToBtns.add(cell);
            doSelect = false;
        }
        
        if (tableRow != -1) {
            JRadioButton row = new TableColorRButton("Row", doSelect, tableRow, -1);
        radioPanel.add(row);
            applyToBtns.add(row);
            doSelect = false;
        }

        if (tableColumn != -1) {
            JRadioButton column = new TableColorRButton("Column", doSelect, -1, tableColumn);
        radioPanel.add(column);
            applyToBtns.add(column);
            doSelect = false;
        }

        JRadioButton table = new TableColorRButton("Table", doSelect, -1, -1);
        radioPanel.add(table);
        applyToBtns.add(table);

        layout.setConstraints(radioPanel, getConstraints(1, 2));
        getContentPane().add(radioPanel);

        // set the 'Cancel' button as default
        getRootPane().setDefaultButton(cancelBtn);

    }

    /**
     * Initialization of the dialog labels
     * @param layout grid layout
     */
    private void initLabels(GridBagLayout layout) {
        JLabel textColorLabel = new JLabel("Text Color:");
        JLabel outlineColorLabel = new JLabel("OutLine Color:");
        JLabel applyToLabel = new JLabel("Apply To Current:");

        layout.setConstraints(textColorLabel, getConstraints(0, 0));
        getContentPane().add(textColorLabel);

        layout.setConstraints(outlineColorLabel, getConstraints(0, 1));
        getContentPane().add(outlineColorLabel);

        layout.setConstraints(applyToLabel, getConstraints(0, 2));
        getContentPane().add(applyToLabel);
    }
}
