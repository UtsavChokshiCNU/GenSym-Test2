package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class dispVBComponentsEventsTest extends ActiveXDispatchableTestBase {

    private dispVBComponentsEvents component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new dispVBComponentsEvents(axProxy);
    }

    @Test
    public void test_ItemAdded_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(284))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ItemAdded(new Variant(284));
                    }
                });
    }

    @Test
    public void test_ItemRemoved_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(498))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ItemRemoved(new Variant(498));
                    }
                });
    }

    @Test
    public void test_ItemRenamed_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(878), new Variant("xYpgKrGuor"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ItemRenamed(new Variant(878), "xYpgKrGuor");
                    }
                });
    }

    @Test
    public void test_ItemSelected_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(992))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ItemSelected(new Variant(992));
                    }
                });
    }

    @Test
    public void test_ItemActivated_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(76))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ItemActivated(new Variant(76));
                    }
                });
    }

    @Test
    public void test_ItemReloaded_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(234))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ItemReloaded(new Variant(234));
                    }
                });
    }

}