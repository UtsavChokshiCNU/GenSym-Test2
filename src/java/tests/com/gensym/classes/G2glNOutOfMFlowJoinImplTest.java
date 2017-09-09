package com.gensym.classes;

import com.gensym.classes.G2TestBase;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class G2glNOutOfMFlowJoinImplTest extends G2TestBase<G2glNOutOfMFlowJoinImpl> {

    @Override
    protected Class<G2glNOutOfMFlowJoinImpl> forClass() {
        return G2glNOutOfMFlowJoinImpl.class;
    }

    @Test
    public void test_setNumberOfBranchesToSynchronize_GivenValue_SetsAsAttributeValue() throws Exception {
        instance.setNumberOfBranchesToSynchronize(42);

        assertThat(attributes.getAttributeValue(SystemAttributeSymbols.NUMBER_OF_BRANCHES_TO_SYNCHRONIZE_)).isEqualTo(42);
    }
    @Test
    public void test_getNumberOfBranchesToSynchronize_HadPreviouslySetAttributeValue_ReturnsExpected() throws Exception {
        attributes.setAttributeValue(SystemAttributeSymbols.NUMBER_OF_BRANCHES_TO_SYNCHRONIZE_, 42);

        assertThat(instance.getNumberOfBranchesToSynchronize()).isEqualTo(42);
    }


}