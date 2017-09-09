package com.gensym.com.beans.excel12;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXDispatchable;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class AutoCorrectTest extends ActiveXDispatchableTestBase {

    private AutoCorrect component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new AutoCorrect(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(144), new Variant(605))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(144), new Variant(605));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(781))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(781));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(605))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(605));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(371), new Variant(83), new
                Variant(42L), new Variant(42L), new Variant(681))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(371), new Variant(83), 42L, 42L, new Variant(681));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(203), new
                Variant(42L), new Variant(42), new Variant(294), new Variant(697), new Variant(266), new Variant(201))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(203), 42L, 42, new Variant(294), new Variant(697), new
                                Variant(266), new Variant(201));
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
    public void test_AddReplacement_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x47a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("nVRyJfgNFN"), new Variant
                ("tlNMzijzLy"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddReplacement("nVRyJfgNFN", "tlNMzijzLy");
                    }
                });
    }

    @Test
    public void test_getAxCapitalizeNamesOfDays_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x47e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxCapitalizeNamesOfDays();
                    }
                });
    }

    @Test
    public void test_setAxCapitalizeNamesOfDays_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x47e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCapitalizeNamesOfDays(false);
                    }
                });
    }

    @Test
    public void test_DeleteReplacement_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x47b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("nNwqOUFVkz"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DeleteReplacement("nNwqOUFVkz");
                    }
                });
    }

    @Test
    public void test_ReplacementList_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x47f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.ReplacementList();
                    }
                });
    }

    @Test
    public void test_ReplacementList_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x47f).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(340))
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.ReplacementList(new Variant(340));
                    }
                });
    }

    @Test
    public void test_getAxReplaceText_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x47c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxReplaceText();
                    }
                });
    }

    @Test
    public void test_setAxReplaceText_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x47c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxReplaceText(false);
                    }
                });
    }

    @Test
    public void test_getAxTwoInitialCapitals_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x47d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxTwoInitialCapitals();
                    }
                });
    }

    @Test
    public void test_setAxTwoInitialCapitals_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x47d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTwoInitialCapitals(false);
                    }
                });
    }

    @Test
    public void test_getAxCorrectSentenceCap_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x653).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxCorrectSentenceCap();
                    }
                });
    }

    @Test
    public void test_setAxCorrectSentenceCap_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x653).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCorrectSentenceCap(false);
                    }
                });
    }

    @Test
    public void test_getAxCorrectCapsLock_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x654).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxCorrectCapsLock();
                    }
                });
    }

    @Test
    public void test_setAxCorrectCapsLock_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x654).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxCorrectCapsLock(false);
                    }
                });
    }

}