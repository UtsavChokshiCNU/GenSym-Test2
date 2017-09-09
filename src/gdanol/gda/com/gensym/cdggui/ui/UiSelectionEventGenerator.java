/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	UiSelectionEventGenerator.java
 *
 *   Modifications:
 *
 */
package com.gensym.cdggui.ui;

public interface UiSelectionEventGenerator {
    public void fireUiSelectionEvent();
    public void addUiSelectionEventListener(UiSelectionEventListener sel);
    public void removeUiSelectionEventListener(UiSelectionEventListener sel);
}

