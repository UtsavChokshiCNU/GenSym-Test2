package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class dispReferencesEventsTest extends ActiveXDispatchableTestBase {

    private dispReferencesEvents component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new dispReferencesEvents(axProxy);
    }

    @Test
    public void test_ItemAdded_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Reference.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ItemAdded(getMock(Reference.class));
                    }
                });
    }

    @Test
    public void test_ItemRemoved_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Reference.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ItemRemoved(getMock(Reference.class));
                    }
                });
    }

}