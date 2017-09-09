package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class NameTest extends ActiveXDispatchableTestBase {

    private Name component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new Name(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(504), new Variant(684))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(504), new Variant(684));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(261))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(261));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(298))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(298));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(647), new Variant(868), new
                Variant(42L), new Variant(42L), new Variant(644))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(647), new Variant(868), 42L, 42L, new Variant(644));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(398), new
                Variant(42L), new Variant(42), new Variant(469), new Variant(151), new Variant(890), new Variant(963))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(398), 42L, 42, new Variant(469), new Variant(151), new
                                Variant(890), new Variant(963));
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
    public void test_getAx_Default_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAx_Default();
                    }
                });
    }

    @Test
    public void test_getAxIndex_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x1e6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxIndex();
                    }
                });
    }

    @Test
    public void test_getAxCategory_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3a6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxCategory();
                    }
                });
    }

    @Test
    public void test_setAxCategory_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3a6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("ySBMHKoMFG"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCategory("ySBMHKoMFG");
                    }
                });
    }

    @Test
    public void test_getAxCategoryLocal_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3a7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxCategoryLocal();
                    }
                });
    }

    @Test
    public void test_setAxCategoryLocal_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3a7).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("vIdEfkXECt"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCategoryLocal("vIdEfkXECt");
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
    public void test_getAxMacroType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3a8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxMacroType();
                    }
                });
    }

    @Test
    public void test_setAxMacroType_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3a8).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMacroType(42);
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
    public void test_setAxName_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("oEeXMrTIvH"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName("oEeXMrTIvH");
                    }
                });
    }

    @Test
    public void test_getAxRefersTo_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3aa).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxRefersTo();
                    }
                });
    }

    @Test
    public void test_setAxRefersTo_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3aa).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(717))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRefersTo(new Variant(717));
                    }
                });
    }

    @Test
    public void test_getAxShortcutKey_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x255).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxShortcutKey();
                    }
                });
    }

    @Test
    public void test_setAxShortcutKey_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x255).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("nGQiOPbfeW"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxShortcutKey("nGQiOPbfeW");
                    }
                });
    }

    @Test
    public void test_getAxValue_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxValue();
                    }
                });
    }

    @Test
    public void test_setAxValue_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("zsQYTEHutU"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxValue("zsQYTEHutU");
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
    public void test_getAxNameLocal_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3a9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxNameLocal();
                    }
                });
    }

    @Test
    public void test_setAxNameLocal_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3a9).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("znzREdsxqD"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxNameLocal("znzREdsxqD");
                    }
                });
    }

    @Test
    public void test_getAxRefersToLocal_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3ab).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxRefersToLocal();
                    }
                });
    }

    @Test
    public void test_setAxRefersToLocal_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3ab).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(254))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRefersToLocal(new Variant(254));
                    }
                });
    }

    @Test
    public void test_getAxRefersToR1C1_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3ac).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxRefersToR1C1();
                    }
                });
    }

    @Test
    public void test_setAxRefersToR1C1_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3ac).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(209))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRefersToR1C1(new Variant(209));
                    }
                });
    }

    @Test
    public void test_getAxRefersToR1C1Local_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x3ad).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxRefersToR1C1Local();
                    }
                });
    }

    @Test
    public void test_setAxRefersToR1C1Local_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3ad).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(123))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxRefersToR1C1Local(new Variant(123));
                    }
                });
    }

    @Test
    public void test_getAxRefersToRange_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x488).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<Range>() {
                    @Override
                    public Range invoke() throws ActiveXException {
                        return component.getAxRefersToRange();
                    }
                });
    }

}