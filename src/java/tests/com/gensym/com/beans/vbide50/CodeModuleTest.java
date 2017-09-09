package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class CodeModuleTest extends ActiveXDispatchableTestBase {

    private CodeModule component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new CodeModule(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(724), new Variant(748))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(724), new Variant(748));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(123))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(123));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(967))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(967));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(833), new Variant(865), new
                Variant(42L), new Variant(42L), new Variant(48))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(833), new Variant(865), 42L, 42L, new Variant(48));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(679), new
                Variant(42L), new Variant(42), new Variant(543), new Variant(794), new Variant(921), new Variant(659))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(679), 42L, 42, new Variant(543), new Variant(794), new
                                Variant(921), new Variant(659));
                    }
                });
    }

    @Test
    public void test_getAxParent_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020000).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxParent();
                    }
                });
    }

    @Test
    public void test_getAxVBE_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020001).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<VBE>() {
                    @Override
                    public VBE invoke() throws ActiveXException {
                        return component.getAxVBE();
                    }
                });
    }

    @Test
    public void test_getAxName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxName();
                    }
                });
    }

    @Test
    public void test_setAxName_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("GoPKtNnbKj"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName("GoPKtNnbKj");
                    }
                });
    }

    @Test
    public void test_AddFromString_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020004).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("cNkHiuRTxl"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddFromString("cNkHiuRTxl");
                    }
                });
    }

    @Test
    public void test_AddFromFile_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020005).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("iBYotRAXLR"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AddFromFile("iBYotRAXLR");
                    }
                });
    }

    @Test
    public void test_getAxLines_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020006).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(42), new Variant(42))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxLines(42, 42);
                    }
                });
    }

    @Test
    public void test_getAxCountOfLines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020007).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCountOfLines();
                    }
                });
    }

    @Test
    public void test_InsertLines_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020008).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant("gzxKZgkHCW"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.InsertLines(42, "gzxKZgkHCW");
                    }
                });
    }

    @Test
    public void test_DeleteLines_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020009).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DeleteLines(42, 42);
                    }
                });
    }

    @Test
    public void test_ReplaceLine_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6002000a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant("zEfvzWtxVd"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.ReplaceLine(42, "zEfvzWtxVd");
                    }
                });
    }

    @Test
    public void test_getAxProcStartLine_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6002000b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant("krqkgZTBQD"), new
                Variant(42))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxProcStartLine("krqkgZTBQD", 42);
                    }
                });
    }

    @Test
    public void test_getAxProcCountLines_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6002000c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant("JQFSxlKRwC"), new
                Variant(42))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxProcCountLines("JQFSxlKRwC", 42);
                    }
                });
    }

    @Test
    public void test_getAxProcBodyLine_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6002000d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant("KosNUBvuWU"), new
                Variant(42))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxProcBodyLine("KosNUBvuWU", 42);
                    }
                });
    }

    @Test
    public void test_getAxProcOfLine_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6002000e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET).args(new Variant(42), new Variant(42))
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxProcOfLine(42, 42);
                    }
                });
    }

    @Test
    public void test_getAxCountOfDeclarationLines_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6002000f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxCountOfDeclarationLines();
                    }
                });
    }

    @Test
    public void test_CreateEventProc_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020010).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("HOAmXgKsLQ"), new Variant
                ("ppeKqzPPqF"))
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.CreateEventProc("HOAmXgKsLQ", "ppeKqzPPqF");
                    }
                });
    }

    @Test
    public void test_Find_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020011).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("LsKCOFLtsd"), new Variant
                (632), new Variant(669), new Variant(840), new Variant(355), new Variant(false), new Variant(false),
                new Variant(false))
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.Find("LsKCOFLtsd", new Variant(632), new Variant(669), new Variant(840), new
                                Variant(355), false, false, false);
                    }
                });
    }

    @Test
    public void test_getAxCodePane_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020012).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxCodePane();
                    }
                });
    }

    @Test
    public void test_getAxMembers_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020013).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxMembers();
                    }
                });
    }

}