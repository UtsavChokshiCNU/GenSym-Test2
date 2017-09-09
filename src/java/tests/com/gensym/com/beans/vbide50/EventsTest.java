package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class EventsTest extends ActiveXDispatchableTestBase {

    private Events component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Events(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(713), new Variant(129))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(713), new Variant(129));
                    }
                });
    }

    @Test
    public void test_AddRef_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsLong(new Returns<Long>() {
                    @Override
                    public Long invoke() throws ActiveXException {
                        return component.AddRef();
                    }
                });
    }

    @Test
    public void test_Release_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsLong(new Returns<Long>() {
                    @Override
                    public Long invoke() throws ActiveXException {
                        return component.Release();
                    }
                });
    }

    @Test
    public void test_GetTypeInfoCount_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(960))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(960));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(241))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(241));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(368), new Variant(477), new
                Variant(42L), new Variant(42L), new Variant(152))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(368), new Variant(477), 42L, 42L, new Variant(152));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(229), new
                Variant(42L), new Variant(42), new Variant(649), new Variant(934), new Variant(367), new Variant(306))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(229), 42L, 42, new Variant(649), new Variant(934), new
                                Variant(367), new Variant(306));
                    }
                });
    }

    @Test
    public void test_getAxVBProjectsEvents_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxVBProjectsEvents();
                    }
                });
    }

    @Test
    public void test_getAxVBComponentsEvents_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(490))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxVBComponentsEvents(new Variant(490));
                    }
                });
    }

    @Test
    public void test_getAxReferencesEvents_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xca).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(505))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxReferencesEvents(new Variant(505));
                    }
                });
    }

    @Test
    public void test_getAxVBControlsEvents_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xcb).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(769), new Variant(getMock
                (VBForm.class)))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxVBControlsEvents(new Variant(769), getMock(VBForm.class));
                    }
                });
    }

    @Test
    public void test_getAxSelectedVBControlsEvents_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xcc).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(581), new Variant(getMock
                (VBForm.class)))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxSelectedVBControlsEvents(new Variant(581), getMock(VBForm.class));
                    }
                });
    }

    @Test
    public void test_getAxCommandBarEvents_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xcd).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(getMock(ActiveXDispatchable
                .class)))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxCommandBarEvents(getMock(ActiveXDispatchable.class));
                    }
                });
    }

    @Test
    public void test_getAxFileControlEvents_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xce).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(290))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxFileControlEvents(new Variant(290));
                    }
                });
    }

}