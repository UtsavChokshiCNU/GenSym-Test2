package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class dispCommandBarControlEventsTest extends ActiveXDispatchableTestBase {

    private dispCommandBarControlEvents component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new dispCommandBarControlEvents(axProxy);
    }

    @Test
    public void test_Click_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(ActiveXDispatchable.class)),
                new Variant(237), new Variant(667))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Click(getMock(ActiveXDispatchable.class), new Variant(237), new Variant(667));
                    }
                });
    }

}