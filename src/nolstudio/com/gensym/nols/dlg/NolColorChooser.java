package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

import com.gensym.nols.util.*;
import com.gensym.nols.main.*;

public class NolColorChooser extends JDialog {
    protected static final String OK_BUTTON_LABEL = "OkButtonLabel";
    protected static final String CANCEL_BUTTON_LABEL = "CancelButtonLabel";
    protected static final String AVAILABLE_COLORS_LABEL = "ColorChooser_availableLabel";
    protected static final String SELECTED_COLOR_LABEL = "ColorChooser_selectedLabel";

	private JFrame parent;
	private ColorComponent[] colorBlocks;
	private ColorComponent selectedColorBlock;
	private JButton okButton, cancelButton;
	private boolean isOk;
	private Color selectedColor;
	private int selectedBlockIndex;


	public NolColorChooser(JFrame dw, String title) {
		super(dw, title, true);
		parent = dw;
        JPanel workPane = new JPanel();
 		workPane.setBorder(BorderFactory.createTitledBorder(((NolMainFrame)parent).getNolResourceString(AVAILABLE_COLORS_LABEL)));
		workPane.setLayout(new GridLayout(8,8,1,1));
		colorBlocks = new ColorComponent[64];
		for(int i=0;i<64;i++){
			Color c = ColorMap.colors[i];
			colorBlocks[i] = new ColorComponent(this,i,c);
			workPane.add(colorBlocks[i]);
		}
        JPanel selectedPane = new JPanel();
 		selectedPane.setBorder(BorderFactory.createTitledBorder(((NolMainFrame)parent).getNolResourceString(SELECTED_COLOR_LABEL)));
		selectedPane.setLayout(new GridLayout(1,3));
		Color c = ColorMap.colors[64];
		selectedColorBlock = new ColorComponent(this,-1,c);
		selectedPane.add(new JPanel());
		selectedPane.add(selectedColorBlock);
		selectedPane.add(new JPanel());

		getContentPane().setLayout(new BorderLayout());
		JPanel centerPane = new JPanel();
		centerPane.setLayout(new BoxLayout(centerPane, BoxLayout.Y_AXIS));
		centerPane.add(workPane);
		centerPane.add(selectedPane);
		getContentPane().add("Center",centerPane);
		getContentPane().add("East",getControlPanel());

        pack();
	}

	private JPanel getControlPanel(){
		ButtonAction buttonListener = new ButtonAction();
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(5,1,5,5));
		okButton = new JButton(((NolMainFrame)parent).getNolResourceString(OK_BUTTON_LABEL));
		okButton.addActionListener(buttonListener);
  		pane0.add(okButton);
		cancelButton = new JButton(((NolMainFrame)parent).getNolResourceString(CANCEL_BUTTON_LABEL));
		cancelButton.addActionListener(buttonListener);
  		pane0.add(cancelButton);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}
	public boolean getResult(){
		return this.isOk;
	}

	public Color getSelectedColor(){
		return selectedColor;
	}

	public void setSelectedColor(int blockIndex, Color color){
		colorBlocks[selectedBlockIndex].setBackground(getBackground());
		colorBlocks[selectedBlockIndex].repaint();
		colorBlocks[selectedBlockIndex].validate();
		selectedColor = color;
		selectedBlockIndex = blockIndex;
		colorBlocks[selectedBlockIndex].setBackground(Color.black);
		colorBlocks[selectedBlockIndex].repaint();
		colorBlocks[selectedBlockIndex].validate();
		selectedColorBlock.setForeground(color);
		selectedColorBlock.repaint();
		selectedColorBlock.validate();
	}

    class ButtonAction extends AbstractAction {

		ButtonAction() {
			super("title");
		}

        @Override
		public void actionPerformed(ActionEvent event) {
			if (event.getSource().equals(okButton)) {
				isOk = true;
			}else if(event.getSource().equals(cancelButton)){
				isOk = false;
			}
			NolColorChooser.this.setVisible(false);
		}
    }

	class ColorComponent extends JComponent implements MouseListener {
		private int blockIndex;
		private Color color;
		private Dimension displaySize;
		private NolColorChooser holder;

		public ColorComponent(NolColorChooser holder, int blockIndex, Color color) {
			super();
			this.holder = holder;
			this.blockIndex = blockIndex;
			this.color = color;
			setBackground(holder.getBackground());
			setForeground(color);
			displaySize = new Dimension(20,15);
			this.addMouseListener(this);
		}

		@Override
		public boolean isOpaque(){return true;}
		@Override
		public void setPreferredSize(Dimension size){
			super.setPreferredSize(size);
			this.displaySize = size;
		}
		@Override
		public void setMinimumSize(Dimension size){
			super.setMinimumSize(size);
			this.displaySize = size;
		}
		@Override
		public Dimension getPreferredSize(){
			return displaySize;
		}
		@Override
		public Dimension getMinimumSize(){
			return displaySize;
		}
		@Override
		public void paintComponent(Graphics g) {
			Dimension d = getSize();
			g.setColor(this.getForeground());
			g.fill3DRect(3, 3, d.width-3, d.height-3,true);
			g.setColor(this.getBackground());
			g.drawRect(1, 1, d.width-2, d.height-2);
		}

		@Override
		public void mousePressed(MouseEvent m) {}
		@Override
		public void mouseEntered(MouseEvent m) {}
		@Override
		public void mouseExited(MouseEvent m) {}
		@Override
		public void mouseReleased(MouseEvent m) {}
		public void mouseDragged(MouseEvent m) {}
		public void mouseMoved(MouseEvent m) {}
		@Override
		public void mouseClicked(MouseEvent m) {
//			System.out.println("mouseClicked in block" + blockIndex); 
			if(blockIndex != -1)
				holder.setSelectedColor(blockIndex, color); 
		}
	}
}
