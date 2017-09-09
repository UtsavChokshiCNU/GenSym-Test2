package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class TextFrameTest extends ActiveXDispatchableTestBase {

    private TextFrame component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new TextFrame(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(604), new Variant(516))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(604), new Variant(516));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(98))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(98));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(153))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(153));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(205), new Variant(848), new
                Variant(42L), new Variant(42L), new Variant(851))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(205), new Variant(848), 42L, 42L, new Variant(851));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(94), new
                Variant(42L), new Variant(42), new Variant(166), new Variant(257), new Variant(308), new Variant(966))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(94), 42L, 42, new Variant(166), new Variant(257), new
                                Variant(308), new Variant(966));
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
    public void test_getAxMarginBottom_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6d1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxMarginBottom();
                    }
                });
    }

    @Test
    public void test_setAxMarginBottom_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6d1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMarginBottom(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxMarginLeft_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6d2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxMarginLeft();
                    }
                });
    }

    @Test
    public void test_setAxMarginLeft_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6d2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMarginLeft(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxMarginRight_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6d3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxMarginRight();
                    }
                });
    }

    @Test
    public void test_setAxMarginRight_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6d3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMarginRight(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxMarginTop_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6d4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsFloat(new Returns<Float>() {
                    @Override
                    public Float invoke() throws ActiveXException {
                        return component.getAxMarginTop();
                    }
                });
    }

    @Test
    public void test_setAxMarginTop_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6d4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42.32f))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMarginTop(42.32f);
                    }
                });
    }

    @Test
    public void test_getAxOrientation_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x86).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxOrientation();
                    }
                });
    }

    @Test
    public void test_setAxOrientation_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x86).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOrientation(42);
                    }
                });
    }

    @Test
    public void test_Characters_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x25b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsDispatchable(new Returns<Characters>() {
                    @Override
                    public Characters invoke() throws ActiveXException {
                        return component.Characters();
                    }
                });
    }

    @Test
    public void test_Characters_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x25b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(411))
                .verifyReturnsDispatchable(new Returns<Characters>() {
                    @Override
                    public Characters invoke() throws ActiveXException {
                        return component.Characters(new Variant(411));
                    }
                });
    }

    @Test
    public void test_Characters_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x25b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(793), new Variant(677))
                .verifyReturnsDispatchable(new Returns<Characters>() {
                    @Override
                    public Characters invoke() throws ActiveXException {
                        return component.Characters(new Variant(793), new Variant(677));
                    }
                });
    }

    @Test
    public void test_getAxHorizontalAlignment_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x88).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxHorizontalAlignment();
                    }
                });
    }

    @Test
    public void test_setAxHorizontalAlignment_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x88).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHorizontalAlignment(42);
                    }
                });
    }

    @Test
    public void test_getAxVerticalAlignment_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x89).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxVerticalAlignment();
                    }
                });
    }

    @Test
    public void test_setAxVerticalAlignment_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x89).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxVerticalAlignment(42);
                    }
                });
    }

    @Test
    public void test_getAxAutoSize_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x266).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxAutoSize();
                    }
                });
    }

    @Test
    public void test_setAxAutoSize_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x266).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAutoSize(false);
                    }
                });
    }

    @Test
    public void test_getAxReadingOrder_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3cf).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxReadingOrder();
                    }
                });
    }

    @Test
    public void test_setAxReadingOrder_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3cf).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxReadingOrder(42);
                    }
                });
    }

    @Test
    public void test_getAxAutoMargins_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6d5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxAutoMargins();
                    }
                });
    }

    @Test
    public void test_setAxAutoMargins_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6d5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAutoMargins(false);
                    }
                });
    }

}