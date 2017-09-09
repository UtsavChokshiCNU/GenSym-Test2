/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	UiSelectionEventListener.java
 *
 *   Modifications:
 *
 */
package com.gensym.cdggui.ui;

public interface UiSelectionEventListener {
    public void selectionGained(UiSelectionEvent event);
    public void selectionLost(UiSelectionEvent event);

}

