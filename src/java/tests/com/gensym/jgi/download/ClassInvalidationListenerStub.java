package com.gensym.jgi.download;

import com.gensym.util.Sequence;

public class ClassInvalidationListenerStub implements ClassInvalidationListener {
    public Sequence invalidatedClasses = new Sequence();

    @Override
    public void classesInvalidated(ClassInvalidationEvent cie) {
        invalidatedClasses.add(cie);
    }
}
