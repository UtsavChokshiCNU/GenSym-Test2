package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2WorkspaceViewImplTest extends G2TestBase<G2WorkspaceViewImpl> {

    @Override
    protected Class<G2WorkspaceViewImpl> forClass() {
        return G2WorkspaceViewImpl.class;
    }

    @Test
    public void test_getScaleOfView_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.SCALE_OF_VIEW_, "ABC");

        assertThat(instance.getScaleOfView()).isEqualTo("ABC");
    }


    @Test
    public void test_getWorkspaceOfView_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.WORKSPACE_OF_VIEW_, getStub(com.gensym.classes.KbWorkspace.class));

        assertThat(instance.getWorkspaceOfView()).isEqualTo(getStub(com.gensym.classes.KbWorkspace.class));
    }


}