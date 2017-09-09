package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class DataLabelsTest extends ActiveXDispatchableTestBase {

    private DataLabels component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new DataLabels(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(681), new Variant(168))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(681), new Variant(168));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(157))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(157));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(531))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(531));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(312), new Variant(874), new
                Variant(42L), new Variant(42L), new Variant(894))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(312), new Variant(874), 42L, 42L, new Variant(894));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(642), new
                Variant(42L), new Variant(42), new Variant(78), new Variant(930), new Variant(896), new Variant(394))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(642), 42L, 42, new Variant(78), new Variant(930), new
                                Variant(896), new Variant(394));
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
    public void test_getAxName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxName();
                    }
                });
    }

    @Test
    public void test_Select_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xeb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Select();
                    }
                });
    }

    @Test
    public void test_getAxBorder_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x80).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Border>() {
                    @Override
                    public Border invoke() throws ActiveXException {
                        return component.getAxBorder();
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
    public void test_getAxInterior_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x81).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Interior>() {
                    @Override
                    public Interior invoke() throws ActiveXException {
                        return component.getAxInterior();
                    }
                });
    }

    @Test
    public void test_getAxFill_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<ChartFillFormat>() {
                    @Override
                    public ChartFillFormat invoke() throws ActiveXException {
                        return component.getAxFill();
                    }
                });
    }

    @Test
    public void test__Dummy9_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10009).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy9();
                    }
                });
    }

    @Test
    public void test__Dummy10_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1000a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy10();
                    }
                });
    }

    @Test
    public void test_getAxFont_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x92).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Font>() {
                    @Override
                    public Font invoke() throws ActiveXException {
                        return component.getAxFont();
                    }
                });
    }

    @Test
    public void test_getAxHorizontalAlignment_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x88).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxHorizontalAlignment();
                    }
                });
    }

    @Test
    public void test_setAxHorizontalAlignment_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x88).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(615))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxHorizontalAlignment(new Variant(615));
                    }
                });
    }

    @Test
    public void test__Dummy13_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1000d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy13();
                    }
                });
    }

    @Test
    public void test_getAxOrientation_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x86).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxOrientation();
                    }
                });
    }

    @Test
    public void test_setAxOrientation_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x86).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(55))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOrientation(new Variant(55));
                    }
                });
    }

    @Test
    public void test_getAxShadow_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxShadow();
                    }
                });
    }

    @Test
    public void test_setAxShadow_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x67).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShadow(false);
                    }
                });
    }

    @Test
    public void test__Dummy16_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10010).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy16();
                    }
                });
    }

    @Test
    public void test__Dummy17_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x10011).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component._Dummy17();
                    }
                });
    }

    @Test
    public void test_getAxVerticalAlignment_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x89).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxVerticalAlignment();
                    }
                });
    }

    @Test
    public void test_setAxVerticalAlignment_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x89).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(862))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxVerticalAlignment(new Variant(862));
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
    public void test_getAxAutoScaleFont_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x5f5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxAutoScaleFont();
                    }
                });
    }

    @Test
    public void test_setAxAutoScaleFont_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5f5).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(479))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAutoScaleFont(new Variant(479));
                    }
                });
    }

    @Test
    public void test_getAxAutoText_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x87).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxAutoText();
                    }
                });
    }

    @Test
    public void test_setAxAutoText_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x87).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAutoText(false);
                    }
                });
    }

    @Test
    public void test_getAxNumberFormat_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxNumberFormat();
                    }
                });
    }

    @Test
    public void test_setAxNumberFormat_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc1).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("CzdCDXJXjt"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxNumberFormat("CzdCDXJXjt");
                    }
                });
    }

    @Test
    public void test_getAxNumberFormatLinked_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xc2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxNumberFormatLinked();
                    }
                });
    }

    @Test
    public void test_setAxNumberFormatLinked_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc2).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxNumberFormatLinked(false);
                    }
                });
    }

    @Test
    public void test_getAxShowLegendKey_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xab).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxShowLegendKey();
                    }
                });
    }

    @Test
    public void test_setAxShowLegendKey_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xab).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShowLegendKey(false);
                    }
                });
    }

    @Test
    public void test_getAxType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxType();
                    }
                });
    }

    @Test
    public void test_setAxType_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(23))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxType(new Variant(23));
                    }
                });
    }

    @Test
    public void test_getAxPosition_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x85).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxPosition();
                    }
                });
    }

    @Test
    public void test_setAxPosition_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x85).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPosition(42);
                    }
                });
    }

    @Test
    public void test_getAxCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x76).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCount();
                    }
                });
    }

    @Test
    public void test_Item_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xaa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(716))
                .verifyReturnsDispatchable(new Returns<DataLabel>() {
                    @Override
                    public DataLabel invoke() throws ActiveXException {
                        return component.Item(new Variant(716));
                    }
                });
    }

    @Test
    public void test__NewEnum_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0xfffffffc).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsGenericValue(new Returns<Object>() {
                    @Override
                    public Object invoke() throws ActiveXException {
                        return component._NewEnum();
                    }
                });
    }

}