package com.gensym.com.beans.vbide50;

import com.gensym.com.ActiveXCastException;
import com.gensym.com.ActiveXException;
import com.gensym.com.ActiveXRuntimeConstants;
import com.gensym.com.Variant;
import com.gensym.com.beans.ActiveXDispatchableTestBase;
import org.junit.Before;
import org.junit.Test;

import java.util.Vector;

public class FileControlEventsTest extends ActiveXDispatchableTestBase {

    private FileControlEvents component;

    @Before
    public void setUp() throws ActiveXCastException {
        component = new FileControlEvents(axProxy);
    }

    @Test
    public void test_AfterAddFile_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x1).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("amCKBZnIQC"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AfterAddFile("amCKBZnIQC");
                    }
                });
    }

    @Test
    public void test_AfterChangeFileName_ThreeArgs_ShouldRedirectToProxy() throws Exception {
        on(0x2).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant((short) 42), new Variant
                ("bJPawxdySL"), new Variant("yHZXSLkJix"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AfterChangeFileName((short) 42, "bJPawxdySL", "yHZXSLkJix");
                    }
                });
    }

    @Test
    public void test_AfterCloseFile_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x3).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Vector.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AfterCloseFile(getMock(Vector.class));
                    }
                });
    }

    @Test
    public void test_AfterWriteFile_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x4).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("OUcMgdhMrG"), new Variant((short) 42))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AfterWriteFile("OUcMgdhMrG", (short) 42);
                    }
                });
    }

    @Test
    public void test_AfterRemoveFile_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x5).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("NJTuGDYFbD"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AfterRemoveFile("NJTuGDYFbD");
                    }
                });
    }

    @Test
    public void test_BeforeLoadFile_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0x6).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Vector.class)))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.BeforeLoadFile(getMock(Vector.class));
                    }
                });
    }

    @Test
    public void test_DoGetAddFileName_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x7).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(getMock(Vector.class)), new Variant
                (998))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DoGetAddFileName(getMock(Vector.class), new Variant(998));
                    }
                });
    }

    @Test
    public void test_DoGetNewFileName_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0x8).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant((short) 42), new Variant(557), new
                Variant("IBPsmeCJRf"), new Variant(26))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DoGetNewFileName((short) 42, new Variant(557), "IBPsmeCJRf", new Variant(26));
                    }
                });
    }

    @Test
    public void test_DoGetOpenProjectName_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0x9).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant(481), new Variant(737))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.DoGetOpenProjectName(new Variant(481), new Variant(737));
                    }
                });
    }

    @Test
    public void test_RequestChangeFileName_FourArgs_ShouldRedirectToProxy() throws Exception {
        on(0xa).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant((short) 42), new Variant
                ("xJqjdgcKdx"), new Variant("mLIUtlsiYL"), new Variant(510))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RequestChangeFileName((short) 42, "xJqjdgcKdx", "mLIUtlsiYL", new Variant(510));
                    }
                });
    }

    @Test
    public void test_RequestWriteFile_TwoArgs_ShouldRedirectToProxy() throws Exception {
        on(0xb).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("IMZTLcPxRr"), new Variant(416))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.RequestWriteFile("IMZTLcPxRr", new Variant(416));
                    }
                });
    }

    @Test
    public void test_AfterNewProject_OneArg_ShouldRedirectToProxy() throws Exception {
        on(0xc).dispatchType(ActiveXRuntimeConstants.AX_INVOKE).args(new Variant("mnqNAooGyA"))
                .verifyNoReturn(new Void() {
                    @Override
                    public void invoke() throws ActiveXException {
                        component.AfterNewProject("mnqNAooGyA");
                    }
                });
    }

}