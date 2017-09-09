package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class MenuLineEventsTest extends ActiveXDispatchableTestBase {

    private MenuLineEvents component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new MenuLineEvents(axProxy);
    }

    @Test
    public void test_AfterClick_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AfterClick();
                    }
                });
    }

}