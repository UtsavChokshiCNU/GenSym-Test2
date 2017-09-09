package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ProjectTemplateEventsTest extends ActiveXDispatchableTestBase {

    private ProjectTemplateEvents component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new ProjectTemplateEvents(axProxy);
    }

    @Test
    public void test_CheckIn_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckIn();
                    }
                });
    }

    @Test
    public void test_CheckOut_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.CheckOut();
                    }
                });
    }

    @Test
    public void test_Fetch_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Fetch();
                    }
                });
    }

    @Test
    public void test_UncheckOut_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.UncheckOut();
                    }
                });
    }

}