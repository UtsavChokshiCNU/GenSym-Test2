package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class ControlFormatTest extends ActiveXDispatchableTestBase {

    private ControlFormat component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new ControlFormat(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(993), new Variant(614))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(993), new Variant(614));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(267))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(267));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(301))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(301));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(505), new Variant(885), new
                Variant(42L), new Variant(42L), new Variant(650))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(505), new Variant(885), 42L, 42L, new Variant(650));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(431), new
                Variant(42L), new Variant(42), new Variant(484), new Variant(351), new Variant(921), new Variant(701))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(431), 42L, 42, new Variant(484), new Variant(351), new
                                Variant(921), new Variant(701));
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
    public void test_AddItem_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x353).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("rPpBruPaMv"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddItem("rPpBruPaMv");
                    }
                });
    }

    @Test
    public void test_AddItem_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x353).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("nacvDGLpjo"), new Variant(417))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddItem("nacvDGLpjo", new Variant(417));
                    }
                });
    }

    @Test
    public void test_RemoveAllItems_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x355).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RemoveAllItems();
                    }
                });
    }

    @Test
    public void test_RemoveItem_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x354).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RemoveItem(42);
                    }
                });
    }

    @Test
    public void test_RemoveItem_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x354).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(468))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RemoveItem(42, new Variant(468));
                    }
                });
    }

    @Test
    public void test_getAxDropDownLines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x350).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxDropDownLines();
                    }
                });
    }

    @Test
    public void test_setAxDropDownLines_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x350).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDropDownLines(42);
                    }
                });
    }

    @Test
    public void test_getAxEnabled_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x258).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxEnabled();
                    }
                });
    }

    @Test
    public void test_setAxEnabled_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x258).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxEnabled(false);
                    }
                });
    }

    @Test
    public void test_getAxLargeChange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x34d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxLargeChange();
                    }
                });
    }

    @Test
    public void test_setAxLargeChange_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x34d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLargeChange(42);
                    }
                });
    }

    @Test
    public void test_getAxLinkedCell_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x422).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxLinkedCell();
                    }
                });
    }

    @Test
    public void test_setAxLinkedCell_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x422).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("KWkSVJCopr"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLinkedCell("KWkSVJCopr");
                    }
                });
    }

    @Test
    public void test_List_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x35d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.List();
                    }
                });
    }

    @Test
    public void test_List_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x35d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(529))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.List(new Variant(529));
                    }
                });
    }

    @Test
    public void test_getAxListCount_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x351).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxListCount();
                    }
                });
    }

    @Test
    public void test_setAxListCount_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x351).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxListCount(42);
                    }
                });
    }

    @Test
    public void test_getAxListFillRange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x34f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxListFillRange();
                    }
                });
    }

    @Test
    public void test_setAxListFillRange_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x34f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("rrlAjTEOwm"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxListFillRange("rrlAjTEOwm");
                    }
                });
    }

    @Test
    public void test_getAxListIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x352).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxListIndex();
                    }
                });
    }

    @Test
    public void test_setAxListIndex_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x352).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxListIndex(42);
                    }
                });
    }

    @Test
    public void test_getAxLockedText_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x268).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxLockedText();
                    }
                });
    }

    @Test
    public void test_setAxLockedText_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x268).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxLockedText(false);
                    }
                });
    }

    @Test
    public void test_getAxMax_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x34a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMax();
                    }
                });
    }

    @Test
    public void test_setAxMax_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x34a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMax(42);
                    }
                });
    }

    @Test
    public void test_getAxMin_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x34b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMin();
                    }
                });
    }

    @Test
    public void test_setAxMin_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x34b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMin(42);
                    }
                });
    }

    @Test
    public void test_getAxMultiSelect_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x20).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMultiSelect();
                    }
                });
    }

    @Test
    public void test_setAxMultiSelect_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x20).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMultiSelect(42);
                    }
                });
    }

    @Test
    public void test_getAxPrintObject_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x26a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxPrintObject();
                    }
                });
    }

    @Test
    public void test_setAxPrintObject_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x26a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPrintObject(false);
                    }
                });
    }

    @Test
    public void test_getAxSmallChange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x34c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxSmallChange();
                    }
                });
    }

    @Test
    public void test_setAxSmallChange_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x34c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSmallChange(42);
                    }
                });
    }

    @Test
    public void test_getAx_Default_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAx_Default();
                    }
                });
    }

    @Test
    public void test_setAx_Default_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAx_Default(42);
                    }
                });
    }

    @Test
    public void test_getAxValue_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxValue();
                    }
                });
    }

    @Test
    public void test_setAxValue_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxValue(42);
                    }
                });
    }

}