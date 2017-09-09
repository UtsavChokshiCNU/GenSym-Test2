package com.gensym.nols.dlg;

import java.awt.Toolkit;
import java.io.Serializable;
import java.util.Vector;

import javax.swing.JFrame;

import com.gensym.math.MathException;
import com.gensym.math.rank.Rank;
import com.gensym.nols.main.NolMainFrame;


public class RankThread implements Runnable, Cloneable, Serializable {   // why Serializable??
    protected static final String rankProgressBarTitle = "RankThread_progressBarTitle";
    protected static final String rankWaitMessage = "RankThread_waitMessage";

	private NolProgressBarDialog progressDialog;
	private Rank rank;
	private NolNewModelWizard holder;
	private Vector inVars;
	private Vector inputDelays;
	private Vector outVars;
	private Vector ratings;

	public RankThread(NolNewModelWizard holder, Vector inVars, Vector inputDelays, Vector outVars, Vector ratings) {
		// cache information to be used on this thread
		this.holder = holder;
		this.inVars = inVars;
		this.inputDelays = inputDelays;
		this.outVars = outVars;
		this.ratings = ratings;
		this.rank = new Rank();
		JFrame frame =  holder.getFrame();
		// how many events?
		int numberOfCalculations = 0;
		for(int i=0;i<inputDelays.size();i++) {
			numberOfCalculations += ((long[]) inputDelays.elementAt(i)).length;
		}
		progressDialog = new NolProgressBarDialog(frame, ((NolMainFrame)frame).getNolResourceString(rankProgressBarTitle), 
			((NolMainFrame)frame).getNolResourceString(rankWaitMessage), numberOfCalculations);
		rank.addListener(progressDialog);
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		RankThread cloned = (RankThread) super.clone();
		
		cloned.rank = rank == null ? null : new Rank(rank);
		cloned.inVars = inVars == null ? null : (Vector) inVars.clone();
		cloned.outVars = outVars == null ? null : (Vector) outVars.clone();
		cloned.ratings = ratings == null ? null : (Vector) ratings.clone();
		cloned.inputDelays = inputDelays == null ? null : (Vector) inputDelays.clone();
		return cloned;
	}

	@Override
	public void run () {
		progressDialog.setLocation(300,300);
		progressDialog.setSize(250,150);
		progressDialog.setVisible(true);
		progressDialog.setThread(Thread.currentThread()); 
		try{
//			System.out.println("inVars"+ inVars.size());
//			System.out.println("inputDelays"+ inputDelays.size());
//			System.out.println("outVars"+ outVars.size());
//			for(int i=0;i<inVars.size();i++){
//				System.out.println("inVars "+ inVars.elementAt(i).toString());
//			}
//			for(int i=0;i<inVars.size();i++){
//				long[] ls = (long[])inputDelays.elementAt(i);
///				System.out.println("inVars ls"+ ls.length);
//				System.out.println("inVars ls[0]"+ ls[0]);
//			}
//			for(int i=0;i<outVars.size();i++){
//				System.out.println("outVars "+ outVars.elementAt(i).toString());
//			}
			rank.performRanking(inVars,inputDelays,outVars,ratings);
			holder.receiveRatingResults(inVars,inputDelays,outVars,ratings);
		} catch(MathException evt) {
			System.err.println("exception in RankThread "+ evt.getMessage());
			evt.printStackTrace();
		}
		Toolkit.getDefaultToolkit().beep();
		progressDialog.dispose();
	}
}