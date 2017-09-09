package com.gensym.com.beans.office20;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

public class IFindTest extends ActiveXDispatchableTestBase {

    private IFind component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new IFind(axProxy);
    }

    @Test
    public void test_QueryInterface_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60000000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(340), new Variant(848))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.QueryInterface(new Variant(340), new Variant(848));
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
        on(0x60010000).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(74))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfoCount(new Variant(74));
                    }
                });
    }

    @Test
    public void test_GetTypeInfo_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010001).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42L), new Variant(42L), new
                Variant(109))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetTypeInfo(42L, 42L, new Variant(109));
                    }
                });
    }

    @Test
    public void test_GetIDsOfNames_FiveArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010002).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(273), new Variant(693), new
                Variant(42L), new Variant(42L), new Variant(683))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.GetIDsOfNames(new Variant(273), new Variant(693), 42L, 42L, new Variant(683));
                    }
                });
    }

    @Test
    public void test_Invoke_EightArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60010003).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(42), new Variant(33), new
                Variant(42L), new Variant(42), new Variant(332), new Variant(601), new Variant(580), new Variant(379))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Invoke(42, new Variant(33), 42L, 42, new Variant(332), new Variant(601), new
                                Variant(580), new Variant(379));
                    }
                });
    }

    @Test
    public void test_getAxSearchPath_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxSearchPath();
                    }
                });
    }

    @Test
    public void test_getAxName_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020001).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxName();
                    }
                });
    }

    @Test
    public void test_getAxSubDir_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020002).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxSubDir();
                    }
                });
    }

    @Test
    public void test_getAxTitle_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020003).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxTitle();
                    }
                });
    }

    @Test
    public void test_getAxAuthor_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020004).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxAuthor();
                    }
                });
    }

    @Test
    public void test_getAxKeywords_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020005).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxKeywords();
                    }
                });
    }

    @Test
    public void test_getAxSubject_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020006).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxSubject();
                    }
                });
    }

    @Test
    public void test_getAxOptions_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020007).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxOptions();
                    }
                });
    }

    @Test
    public void test_getAxMatchCase_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020008).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxMatchCase();
                    }
                });
    }

    @Test
    public void test_getAxText_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020009).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxText();
                    }
                });
    }

    @Test
    public void test_getAxPatternMatch_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6002000a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsBoolean(new Returns<Boolean>() {
                    @Override
                    public Boolean invoke() throws ActiveXException {
                        return component.getAxPatternMatch();
                    }
                });
    }

    @Test
    public void test_getAxDateSavedFrom_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6002000b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxDateSavedFrom();
                    }
                });
    }

    @Test
    public void test_getAxDateSavedTo_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6002000c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxDateSavedTo();
                    }
                });
    }

    @Test
    public void test_getAxSavedBy_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6002000d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsString(new Returns<String>() {
                    @Override
                    public String invoke() throws ActiveXException {
                        return component.getAxSavedBy();
                    }
                });
    }

    @Test
    public void test_getAxDateCreatedFrom_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6002000e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxDateCreatedFrom();
                    }
                });
    }

    @Test
    public void test_getAxDateCreatedTo_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6002000f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsVariant(new Returns<Variant>() {
                    @Override
                    public Variant invoke() throws ActiveXException {
                        return component.getAxDateCreatedTo();
                    }
                });
    }

    @Test
    public void test_getAxView_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020010).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxView();
                    }
                });
    }

    @Test
    public void test_getAxSortBy_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020011).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxSortBy();
                    }
                });
    }

    @Test
    public void test_getAxListBy_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020012).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxListBy();
                    }
                });
    }

    @Test
    public void test_getAxSelectedFile_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020013).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxSelectedFile();
                    }
                });
    }

    @Test
    public void test_getAxResults_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020014).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsDispatchable(new Returns<IFoundFiles>() {
                    @Override
                    public IFoundFiles invoke() throws ActiveXException {
                        return component.getAxResults();
                    }
                });
    }

    @Test
    public void test_Show_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x60020015).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.Show();
                    }
                });
    }

    @Test
    public void test_setAxSearchPath_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x0).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("zbQvVfJxdc"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSearchPath("zbQvVfJxdc");
                    }
                });
    }

    @Test
    public void test_setAxName_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020001).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("uTXScfRqUz"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxName("uTXScfRqUz");
                    }
                });
    }

    @Test
    public void test_setAxSubDir_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020002).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSubDir(false);
                    }
                });
    }

    @Test
    public void test_setAxTitle_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020003).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("bialXdlXdf"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxTitle("bialXdlXdf");
                    }
                });
    }

    @Test
    public void test_setAxAuthor_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020004).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("HkTfFgzPod"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxAuthor("HkTfFgzPod");
                    }
                });
    }

    @Test
    public void test_setAxKeywords_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020005).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("MghqwflAbH"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxKeywords("MghqwflAbH");
                    }
                });
    }

    @Test
    public void test_setAxSubject_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020006).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("XMLASdIWZi"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSubject("XMLASdIWZi");
                    }
                });
    }

    @Test
    public void test_setAxOptions_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020007).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxOptions(42);
                    }
                });
    }

    @Test
    public void test_setAxMatchCase_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020008).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxMatchCase(false);
                    }
                });
    }

    @Test
    public void test_setAxText_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020009).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("ihOfinmmLX"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxText("ihOfinmmLX");
                    }
                });
    }

    @Test
    public void test_setAxPatternMatch_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6002000a).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(false))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxPatternMatch(false);
                    }
                });
    }

    @Test
    public void test_setAxDateSavedFrom_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6002000b).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(955))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDateSavedFrom(new Variant(955));
                    }
                });
    }

    @Test
    public void test_setAxDateSavedTo_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6002000c).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(149))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDateSavedTo(new Variant(149));
                    }
                });
    }

    @Test
    public void test_setAxSavedBy_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6002000d).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant("BFevJiwLRz"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSavedBy("BFevJiwLRz");
                    }
                });
    }

    @Test
    public void test_setAxDateCreatedFrom_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6002000e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(789))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDateCreatedFrom(new Variant(789));
                    }
                });
    }

    @Test
    public void test_setAxDateCreatedTo_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6002000f).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(940))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxDateCreatedTo(new Variant(940));
                    }
                });
    }

    @Test
    public void test_setAxView_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020010).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxView(42);
                    }
                });
    }

    @Test
    public void test_setAxSortBy_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020011).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSortBy(42);
                    }
                });
    }

    @Test
    public void test_setAxListBy_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020012).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxListBy(42);
                    }
                });
    }

    @Test
    public void test_setAxSelectedFile_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x60020013).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxSelectedFile(42);
                    }
                });
    }

    @Test
    public void test_Execute_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6002002a).dispatchType(ActiveXRuntimeConstants.AX_INVOKE)
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Execute();
                    }
                });
    }

    @Test
    public void test_Load_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6002002b).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("iiMMmcBRWv"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Load("iiMMmcBRWv");
                    }
                });
    }

    @Test
    public void test_Save_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6002002c).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("xxilVnMEjn"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Save("xxilVnMEjn");
                    }
                });
    }

    @Test
    public void test_Delete_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6002002d).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("lyeKOjiPKy"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.Delete("lyeKOjiPKy");
                    }
                });
    }

    @Test
    public void test_getAxFileType_ZeroArgs_ShouldRedirectToProxy() throws Exception {
        on(0x6002002e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYGET)
                .verifyReturnsInt(new Returns<Integer>() {
                    @Override
                    public Integer invoke() throws ActiveXException {
                        return component.getAxFileType();
                    }
                });
    }

    @Test
    public void test_setAxFileType_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6002002e).dispatchType(ActiveXRuntimeConstants.AX_PROPERTYSET).args(new Variant(42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.setAxFileType(42);
                    }
                });
    }

}