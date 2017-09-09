package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class dispSelectedVBControlsEventsTest extends ActiveXDispatchableTestBase {

    private dispSelectedVBControlsEvents component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new dispSelectedVBControlsEvents(axProxy);
    }

    @Test
    public void test_ItemAdded_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(VBControl.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ItemAdded(getMock(VBControl.class));
                    }
                });
    }

    @Test
    public void test_ItemRemoved_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(VBControl.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ItemRemoved(getMock(VBControl.class));
                    }
                });
    }

}