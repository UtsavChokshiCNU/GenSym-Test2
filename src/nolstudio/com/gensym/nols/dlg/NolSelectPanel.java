package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.net.*;

import javax.swing.*;
import javax.swing.border.*;

public class NolSelectPanel  extends JPanel{
	public NolList availableList;
	public NolList selectedList;
	public JButton selectButton;
	public JButton deSelectButton;
	public JPanel availListPane;
	public JPanel selectedListPane;
	private DefaultListModel availableListModel;
	private DefaultListModel selectedListModel;
	private ControlAction actionListener;
	private Vector contents;
	private Vector listeners;

	public NolSelectPanel (String title){
		this(title, new Vector());
	}

	public NolSelectPanel (String title, Vector contents){
		this.contents = contents;
		setLayout(new NolSelectPanelLayout());
		setBorder(BorderFactory.createTitledBorder(title));
		actionListener = new ControlAction();
		listeners = new Vector();
	
		URL url = this.getClass().getResource("right.gif");
		ImageIcon butIcon = new ImageIcon(url);

		selectButton = new JButton(butIcon);
 		selectButton.addActionListener(actionListener);

		url = this.getClass().getResource("left.gif");
		butIcon = new ImageIcon(url);

		deSelectButton = new JButton(butIcon);
 		deSelectButton.addActionListener(actionListener);

		availListPane = new JPanel();
		availListPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"Exclude:", TitledBorder.LEFT , TitledBorder.TOP));
		availListPane.setLayout(new GridLayout());
		availableList = new NolList(getAvailableListModel());
		availableList.setBackground(Color.white);
		JScrollPane listScrollPane = new JScrollPane(availableList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		availListPane.add(listScrollPane);

		selectedListPane = new JPanel();
		selectedListPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
				"Include:", TitledBorder.LEFT , TitledBorder.TOP));
		selectedListPane.setLayout(new GridLayout());
		selectedList = new NolList(getSelectedListModel());
		selectedList.setBackground(Color.white);
		listScrollPane = new JScrollPane(selectedList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		selectedListPane.add(listScrollPane);

		add(selectButton);
		add(deSelectButton);
		add(availListPane);
		add(selectedListPane);
		initList(true);
	}

	public void addListener(NolSelectPanelListener l){
		listeners.addElement(l);
	}

	public void removeListener(NolSelectPanelListener l){
		listeners.removeElement(l);
	}

	public void clearListener(){
		listeners.removeAllElements();
	}

	public DefaultListModel getAvailableListModel() {
		if (availableListModel == null) {
			availableListModel = new DefaultListModel();	
		}
		return availableListModel;
	}	
	public DefaultListModel getSelectedListModel() {
		if (selectedListModel == null) {
			selectedListModel = new DefaultListModel();	
		}
		return selectedListModel;
	}	

	public void setSelectedContents(Vector contents){
		this.contents = contents;
		initList(true);
	}

	public void setContents(Vector contents){
		this.contents = contents;
		initList(false);
	}

	public void setContents(Vector contents,Vector selected){
		this.contents = contents;
		initList(selected);
	}

	public Vector getContents(){
		return contents;
	}

	private void initList(Vector selected) {
		getAvailableListModel().removeAllElements();
		getSelectedListModel().removeAllElements();
		selectedList.addObjects(selected);
		Vector notSelected = new Vector(0,10);
		for(int i=0;i<contents.size();i++){
			Object obj = contents.elementAt(i);
			if(!selected.contains(obj)){
				notSelected.addElement(obj);
			}
		}
		availableList.addObjects(notSelected);
	}

	private void initList(boolean selected){
		int n = contents.size();
		getAvailableListModel().removeAllElements();
		getSelectedListModel().removeAllElements();
		if(selected){
			selectedList.addObjects(contents);
		}else {
			availableList.addObjects(contents);
		}
	}

	private void fireListChangeEvent(){
		int c=listeners.size();
		for(int i=0;i<c;i++){
			NolSelectPanelListener l = (NolSelectPanelListener)listeners.elementAt(i);
			l.listChanged();
		}
	}

	/**Control action implementation */
    class ControlAction extends AbstractAction {
		ControlAction() {super("controlAction");}
		@Override
		public void actionPerformed(ActionEvent e) {
			if(e.getSource().equals(selectButton)){
				if(getAvailableListModel().size()==0) {
					return;
				}
				Object[] vars = availableList.getSelectedValues();
				for(int i=0;i<vars.length;i++){
					if(!getSelectedListModel().contains(vars[i])){
						boolean reachEnd = true;
						int index = contents.indexOf(vars[i]);
						for(int j=0;j<getSelectedListModel().size();j++){
							int newIndex = contents.indexOf(getSelectedListModel().elementAt(j));
							if(index <newIndex){
								reachEnd = false;
 								getSelectedListModel().insertElementAt(vars[i],j);
								break;
							}
						}
						if(reachEnd)
							getSelectedListModel().addElement(vars[i]);
					}
					if(getAvailableListModel().contains(vars[i]))
						getAvailableListModel().removeElement(vars[i]);	
				}
			}else if(e.getSource().equals(deSelectButton)){
				if(getSelectedListModel().size()==0){
					return;
				}
				Object[] vars = selectedList.getSelectedValues();
				for(int i=0;i<vars.length;i++){
					if(getSelectedListModel().contains(vars[i]))
						getSelectedListModel().removeElement(vars[i]);
					if(!getAvailableListModel().contains(vars[i])){
						boolean reachEnd = true;
						int index = contents.indexOf(vars[i]);
						for(int j=0;j<getAvailableListModel().size();j++){
							int newIndex = contents.indexOf(getAvailableListModel().elementAt(j));
							if(index <newIndex){
								reachEnd = false;
 								getAvailableListModel().insertElementAt(vars[i],j);
								break;
							}
						}
						if(reachEnd)
							getAvailableListModel().addElement(vars[i]);
					}
				}
			}
			fireListChangeEvent();
			availableList.clearSelection();
			selectedList.clearSelection();
			availListPane.repaint();
			selectedListPane.repaint();
			availListPane.validate();
			selectedListPane.validate();
		}
    }
		
	class NolSelectPanelLayout implements LayoutManager {

		public NolSelectPanelLayout() {
			super();
		}
		
		@Override
		public void addLayoutComponent(String name, Component comp) {}

		@Override
		public void removeLayoutComponent(Component comp) {}

	    @Override
		public Dimension preferredLayoutSize(Container parent) {
			Insets insets = parent.getInsets();  // top, left, bottom, right insets around chart contained
			return new Dimension(insets.left + insets.right + 300, 
				     insets.top + insets.bottom + 200);
		}

	    @Override
		public Dimension minimumLayoutSize(Container parent) {
			Insets insets = parent.getInsets();
			return new Dimension(insets.left + insets.right + 300, 
				     insets.top + insets.bottom + 200);
		}
		@Override
		public void layoutContainer(Container parent) {
			NolSelectPanel panel = (NolSelectPanel) parent;
			if (parent.getComponentCount() == 0) {
				return;
			}
			Insets insets = parent.getInsets();
			Rectangle bounds = parent.getBounds();
			int width = bounds.width - (insets.left + insets.right);
			int height = bounds.height - (insets.top + insets.bottom);
			int left = insets.left;
			int top = insets.top;
			int right = left + width;
			int bottom = top + height;
			JPanel availListPanel = panel.availListPane;
			JPanel selectedListPanel = panel.selectedListPane;
			JButton sel = panel.selectButton;
			JButton des = panel.deSelectButton;
			int listWidth = width/2 - 25;
			if(listWidth<10){
				listWidth = 10;
			}
			int listHeight = height;
			availListPanel.setBounds(left, top,listWidth,listHeight);
			selectedListPanel.setBounds(right-listWidth, top, listWidth , listHeight);
			int bleft = left+ width/2 - 15; 
			sel.setBounds(bleft,top+height/2-30,30,20);
			des.setBounds(bleft,top+height/2+10,30,20);
			panel.repaint(0l);

		}
	}
}

