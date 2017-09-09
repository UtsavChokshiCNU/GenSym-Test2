package com.gensym.nols.dlg;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.URL;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import com.gensym.nols.main.NolMainFrame;

public class NolAboutDialog extends JDialog {

    protected static final String PRODUCT_NAME = "AboutDialog_productName";
    protected static final String PRODUCT_COPYRIGHT = "AboutDialog_copyright";
    protected static final String PRODUCT_RIGHTS_RESERVED = "AboutDialog_rightsReserved";
    protected static final String OK_BUTTON_LABEL = "OkButtonLabel";
	protected static final String CREDITS_BUTTON_LABEL = "CreditsButtonLabel";

	protected static final String VERSION = "AboutDialog_version";
	protected static final String REVISION = "AboutDialog_revision";


	private NolMainFrame frame;

	public NolAboutDialog(JFrame dw, String title) {
		super(dw, title, true);
        frame = (NolMainFrame)dw;	 
		getContentPane().add(getLabelsPanel(), BorderLayout.CENTER);
		getContentPane().add(getButtonsPanel(false), BorderLayout.PAGE_END);
        setBounds(150,150,450, 260);
	}

	private JPanel getButtonsPanel(boolean isCreditButtonNeeded){
		JPanel buttonsPanel = new JPanel();
		buttonsPanel.setLayout(new BoxLayout(buttonsPanel, BoxLayout.LINE_AXIS));
		JButton okButton = new JButton(frame.getNolResourceString(OK_BUTTON_LABEL));
		okButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				NolAboutDialog.this.dispose();
			}
		});
		okButton.setPreferredSize(new Dimension(75, 30));
		buttonsPanel.add(Box.createHorizontalGlue());
		buttonsPanel.add(okButton);
		if (isCreditButtonNeeded){
			JButton creditsButton = new JButton(frame.getNolResourceString(CREDITS_BUTTON_LABEL) + "...");
			creditsButton.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					frame.showOKDialog("Mark Kramer\tGang Chen\tBrian O. Bush\tEllen Gerlovin\tMary Ann Carberry");
				}
			});
			buttonsPanel.add(Box.createRigidArea(new Dimension(10, 0)));
			buttonsPanel.add(creditsButton);
		}
		buttonsPanel.add(Box.createRigidArea(new Dimension(30, 0)));
		buttonsPanel.setBorder(new EmptyBorder(0, 0, 10, 0));
		return buttonsPanel;
	}

	private JPanel getLabelsPanel(){
		JPanel labelsPanel = new JPanel();
		labelsPanel.setLayout(new BoxLayout(labelsPanel, BoxLayout.PAGE_AXIS));
		JLabel label = new JLabel(frame.getNolResourceString(PRODUCT_NAME));
        label.setVerticalAlignment(label.CENTER);
		URL url = this.getClass().getResource("logo.jpg");
		ImageIcon icon = new ImageIcon(url);
        label.setIcon(icon);
		label.setFont(new Font("Dialog", Font.BOLD, 32));
        label.setVerticalTextPosition(label.CENTER);
        label.setHorizontalTextPosition(label.RIGHT);
        JLabel label0 = new JLabel(frame.getNolResourceString(VERSION) + " " + frame.getNolResourceString(REVISION));
		label0.setFont(new Font("dialog", Font.BOLD, 12));
		JLabel label1 = new JLabel(frame.getNolResourceString(PRODUCT_COPYRIGHT));
		label1.setFont(new Font("dialog", 0, 14));
		JLabel label2 = new JLabel(frame.getNolResourceString(PRODUCT_RIGHTS_RESERVED));
		label2.setFont(new Font("dialog", 0, 14));
		labelsPanel.add(label);
		labelsPanel.add(Box.createRigidArea(new Dimension(0,10)));
		labelsPanel.add(label0);
		labelsPanel.add(Box.createRigidArea(new Dimension(0,10)));
		labelsPanel.add(label1);
		labelsPanel.add(Box.createRigidArea(new Dimension(0,10)));
		labelsPanel.add(label2);
		labelsPanel.setBorder(new EmptyBorder(20, 20, 10, 10));
		return labelsPanel;
	}
}

