package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class dispVBProjectsEventsTest extends ActiveXDispatchableTestBase {

    private dispVBProjectsEvents component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new dispVBProjectsEvents(axProxy);
    }

    @Test
    public void test_ItemAdded_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(788))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ItemAdded(new Variant(788));
                    }
                });
    }

    @Test
    public void test_ItemRemoved_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(941))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ItemRemoved(new Variant(941));
                    }
                });
    }

    @Test
    public void test_ItemRenamed_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(585), new Variant("IrIDDXXeff"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ItemRenamed(new Variant(585), "IrIDDXXeff");
                    }
                });
    }

    @Test
    public void test_ItemActivated_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(286))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ItemActivated(new Variant(286));
                    }
                });
    }

}