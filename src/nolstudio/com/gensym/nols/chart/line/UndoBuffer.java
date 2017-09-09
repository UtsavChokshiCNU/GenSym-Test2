package com.gensym.nols.chart.line;

import java.lang.Object;

public class UndoBuffer {
	private Object[] buffer;
	private int size;
	private boolean full;
	private int firstPosition;
	private int lastPosition;
	private int undoCount;
	private int eventsStored;
	private boolean locked;

	public UndoBuffer(int size) {
		super();
		buffer = new Object[size];
		this.size = size;
		firstPosition = 0;
		lastPosition = -1;
		undoCount = 0;
		eventsStored = 0;
		full = false;
		locked = false;
	}

	public void storeEvent(Object event) {
		if (locked) return;
		lastPosition++;
		if (full) firstPosition++;
		if (lastPosition == size) { // beyond end of buffer
			lastPosition = 0;
			full = true;  // if not already
		}
		if (firstPosition == size) firstPosition = 0;
		if (!full) eventsStored++;
		undoCount = 0;
		// put event at lastPosition
		//System.out.println("storing event at "+lastPosition);
		buffer[lastPosition] = event;
	}

	public void lock(boolean l) {
		locked = l;
	}


	public Object getUndoEvent() {
		if (undoCount == eventsStored) return null;
		int undoPosition = lastPosition - undoCount;
		if (undoPosition < 0) undoPosition += size;
		//System.out.println("undoing event "+undoPosition);
		undoCount++;
		//System.out.println("undo count = "+undoCount);
		return buffer[undoPosition];
	}

	public Object getRedoEvent() {
		if (undoCount == 0) return null;
		undoCount--;
		int redoPosition = lastPosition - undoCount;
		if (redoPosition < 0) redoPosition += size;
		//System.out.println("redoing event "+redoPosition);
		return buffer[redoPosition];
	}

	public void clearUndoBuffer() {
		for (int i=0; i< size; i++) buffer[i] = null;
		firstPosition = 0;
		lastPosition = -1;
		undoCount = 0;
		eventsStored = 0;
		full = false;
	}

}