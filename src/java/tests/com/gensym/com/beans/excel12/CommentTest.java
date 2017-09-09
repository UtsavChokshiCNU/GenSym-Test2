package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class CommentTest extends ActiveXDispatchableTestBase {

    private Comment component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Comment(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(269), new Variant(323))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(269), new Variant(323));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(419))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(419));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(89))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(89));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(728), new Variant(385), new
                Variant(42L), new Variant(42L), new Variant(434))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(728), new Variant(385), 42L, 42L, new Variant(434));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(411), new
                Variant(42L), new Variant(42), new Variant(968), new Variant(847), new Variant(808), new Variant(575))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(411), 42L, 42, new Variant(968), new Variant(847), new
                                Variant(808), new Variant(575));
                    }
                });
    }

    @Test
    public void test_getAxApplication_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x94).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ExcelApplication>() {
                    @Override
                    public ExcelApplication invoke() throws ActiveXException {
                        return component.getAxApplication();
                    }
                });
    }

    @Test
    public void test_getAxCreator_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x95).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCreator();
                    }
                });
    }

    @Test
    public void test_getAxParent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x96).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchableValue(new Returns<ActiveXDispatchable>() {
                    @Override
                    public ActiveXDispatchable invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_getAxAuthor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x23e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxAuthor();
                    }
                });
    }

    @Test
    public void test_getAxShape_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x62e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Shape>() {
                    @Override
                    public Shape invoke() throws ActiveXException {
                        return component.getAxShape();
                    }
                });
    }

    @Test
    public void test_getAxVisible_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x22e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxVisible();
                    }
                });
    }

    @Test
    public void test_setAxVisible_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x22e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxVisible(false);
                    }
                });
    }

    @Test
    public void test_Text_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x8a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.Text();
                    }
                });
    }

    @Test
    public void test_Text_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x8a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(658))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.Text(new Variant(658));
                    }
                });
    }

    @Test
    public void test_Text_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x8a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(581), new Variant(267))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.Text(new Variant(581), new Variant(267));
                    }
                });
    }

    @Test
    public void test_Text_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x8a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(936), new Variant(790), new Variant
                (405))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.Text(new Variant(936), new Variant(790), new Variant(405));
                    }
                });
    }

    @Test
    public void test_Delete_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x75).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Delete();
                    }
                });
    }

    @Test
    public void test_Next_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f6).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<Comment>() {
                    @Override
                    public Comment invoke() throws ActiveXException {
                        return component.Next();
                    }
                });
    }

    @Test
    public void test_Previous_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1f7).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<Comment>() {
                    @Override
                    public Comment invoke() throws ActiveXException {
                        return component.Previous();
                    }
                });
    }

}