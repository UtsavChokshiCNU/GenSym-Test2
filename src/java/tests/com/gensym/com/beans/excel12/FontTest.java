package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class FontTest extends ActiveXDispatchableTestBase {

    private Font component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Font(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(815), new Variant(649))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(815), new Variant(649));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(474))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(474));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(73))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(73));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(948), new Variant(427), new
                Variant(42L), new Variant(42L), new Variant(79))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(948), new Variant(427), 42L, 42L, new Variant(79));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(786), new
                Variant(42L), new Variant(42), new Variant(190), new Variant(566), new Variant(167), new Variant(351))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(786), 42L, 42, new Variant(190), new Variant(566), new
                                Variant(167), new Variant(351));
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
    public void test_getAxBackground_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxBackground();
                    }
                });
    }

    @Test
    public void test_setAxBackground_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xb4).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(488))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBackground(new Variant(488));
                    }
                });
    }

    @Test
    public void test_getAxBold_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxBold();
                    }
                });
    }

    @Test
    public void test_setAxBold_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(58))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxBold(new Variant(58));
                    }
                });
    }

    @Test
    public void test_getAxColor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x63).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxColor();
                    }
                });
    }

    @Test
    public void test_setAxColor_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x63).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(278))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxColor(new Variant(278));
                    }
                });
    }

    @Test
    public void test_getAxColorIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x61).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxColorIndex();
                    }
                });
    }

    @Test
    public void test_setAxColorIndex_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x61).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(217))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxColorIndex(new Variant(217));
                    }
                });
    }

    @Test
    public void test_getAxFontStyle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxFontStyle();
                    }
                });
    }

    @Test
    public void test_setAxFontStyle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xb1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(475))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFontStyle(new Variant(475));
                    }
                });
    }

    @Test
    public void test_getAxItalic_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x65).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxItalic();
                    }
                });
    }

    @Test
    public void test_setAxItalic_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x65).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(112))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxItalic(new Variant(112));
                    }
                });
    }

    @Test
    public void test_getAxName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxName();
                    }
                });
    }

    @Test
    public void test_setAxName_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(130))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName(new Variant(130));
                    }
                });
    }

    @Test
    public void test_getAxOutlineFont_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xdd).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxOutlineFont();
                    }
                });
    }

    @Test
    public void test_setAxOutlineFont_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xdd).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(633))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOutlineFont(new Variant(633));
                    }
                });
    }

    @Test
    public void test_getAxShadow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxShadow();
                    }
                });
    }

    @Test
    public void test_setAxShadow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(452))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShadow(new Variant(452));
                    }
                });
    }

    @Test
    public void test_getAxSize_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x68).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxSize();
                    }
                });
    }

    @Test
    public void test_setAxSize_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x68).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(393))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSize(new Variant(393));
                    }
                });
    }

    @Test
    public void test_getAxStrikethrough_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x69).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxStrikethrough();
                    }
                });
    }

    @Test
    public void test_setAxStrikethrough_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x69).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(284))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxStrikethrough(new Variant(284));
                    }
                });
    }

    @Test
    public void test_getAxSubscript_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxSubscript();
                    }
                });
    }

    @Test
    public void test_setAxSubscript_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xb3).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(388))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSubscript(new Variant(388));
                    }
                });
    }

    @Test
    public void test_getAxSuperscript_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxSuperscript();
                    }
                });
    }

    @Test
    public void test_setAxSuperscript_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xb2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(229))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSuperscript(new Variant(229));
                    }
                });
    }

    @Test
    public void test_getAxUnderline_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxUnderline();
                    }
                });
    }

    @Test
    public void test_setAxUnderline_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(900))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxUnderline(new Variant(900));
                    }
                });
    }

}