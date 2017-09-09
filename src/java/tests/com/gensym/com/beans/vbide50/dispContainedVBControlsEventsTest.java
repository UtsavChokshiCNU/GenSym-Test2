package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class dispContainedVBControlsEventsTest extends ActiveXDispatchableTestBase {

    private dispContainedVBControlsEvents component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new dispContainedVBControlsEvents(axProxy);
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

    @Test
    public void test_ItemRenamed_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(VBControl.class)), new
                Variant("WYOjCVIFMg"), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ItemRenamed(getMock(VBControl.class), "WYOjCVIFMg", 42);
                    }
                });
    }

}