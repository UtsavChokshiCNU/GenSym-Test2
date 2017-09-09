package com.gensym.nols.data;

import com.gensym.math.MathException;
import com.gensym.nols.data.function.FunctionInterface;
import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;
import org.mockito.Matchers;

import java.io.*;
import java.util.Random;
import java.util.Vector;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.greaterThan;
import static org.hamcrest.core.Is.is;
import static org.hamcrest.core.IsEqual.equalTo;
import static org.junit.Assert.*;
import static org.mockito.Mockito.never;
import static org.mockito.Mockito.verify;
import static org.powermock.api.mockito.PowerMockito.*;

public class PreprocessorTest {
    private static final Random randomGenerator = new Random();

    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final ByteArrayOutputStream errContent = new ByteArrayOutputStream();
    private final Vector<File> files = new Vector<>();

    @Rule
    public TemporaryFolder temporaryFolder = new TemporaryFolder();
    private Preprocessor sut;

    @Before
    public void before() {
        this.sut = new Preprocessor();

        outContent.reset();
        setupStreams();
    }

    @After
    public void after() {
        for (File file : files) {
            file.delete();
        }

        files.removeAllElements();
        cleanUpStreams();
    }

    @Test
    public void test_clone_always_clonesObject() throws CloneNotSupportedException {
        // Arrange
        String name = "Preprocessor Name";
        String comment = "Preprocessor Comment";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement("inputVarName1");
        variableNames.addElement("inputVarName2");
        variableNames.addElement("inputVarName3");

        Vector<String> variableTags = new Vector<>();
        variableTags.addElement("inputVarTag1");
        variableTags.addElement("inputVarTag2");
        variableTags.addElement("inputVarTag3");

        Vector<String> derivedVarNames = new Vector<>();
        derivedVarNames.addElement("derivedVarName1");
        derivedVarNames.addElement("derivedVarName2");
        derivedVarNames.addElement("derivedVarName3");

        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());

        this.sut = new Preprocessor(name, comment, variableNames, variableTags, derivedVarNames, formulas, anyBoolean());

        // Act
        Preprocessor result = (Preprocessor) this.sut.clone();

        // Assert
        assertNotNull(result);
        assertThat(result.getName(), is(equalTo(this.sut.getName())));
        assertThat(result.getComment(), is(equalTo(this.sut.getComment())));

        assertThat(formulas.size(), is(greaterThan(0)));
        for (Formula2 formula : formulas) {
            assertTrue(result.getFormulas().contains(formula));
        }

        assertThat(variableNames.size(), is(greaterThan(0)));
        for (String variableName : variableNames) {
            assertTrue(result.getVariableNames().contains(variableName));
        }

        assertThat(variableTags.size(), is(greaterThan(0)));
        for (String variableTag : variableTags) {
            assertTrue(result.getInputVariableTags().contains(variableTag));
        }

        assertThat(derivedVarNames.size(), is(greaterThan(0)));
        for (String derivedVarName : derivedVarNames) {
            assertTrue(result.getDerivedVariableNames().contains(derivedVarName));
        }
    }

    @Test
    public void test_getHasTimeStamps_always_retHasTimeStamps() {
        // Arrange
        boolean[] testCases = new boolean[]{true, false};

        for (boolean testCase : testCases) {
            this.sut = createPreprocessor(testCase);

            // Act & Assert
            assertThat(this.sut.getHasTimeStamps(), is(equalTo(testCase)));
        }
    }

    @Test
    public void test_getViewFilter_always_retViewFilter() throws MathException {
        // Arrange
        ViewFilter viewFilter = createViewFilter();
        this.sut = createPreprocessor(viewFilter);

        // Act & Assert
        assertThat(this.sut.getViewFilter(), is(equalTo(viewFilter)));
    }

    @Test
    public void test_setViewFilter_always_setsViewFilter() {
        // Arrange
        ViewFilter viewFilter = createViewFilter();

        // Act
        this.sut.setViewFilter(viewFilter);

        // Assert
        assertThat(this.sut.getViewFilter(), is(equalTo(viewFilter)));
    }

    @Test
    public void test_getItsHashCode_always_retHashCode() {
        // Arrange
        int hashcode = this.sut.hashCode();
        this.sut.initHasCode();

        // Act & Assert
        assertThat(this.sut.getItsHashCode(), is(equalTo(hashcode)));
    }

    @Test
    public void test_getInputVariableNames_createdWithoutParams_emptyList() {
        // Arrange
        // No arrangements

        // Act & Assert
        assertThat(this.sut.getInputVariableNames().size(), is(equalTo(0)));
    }

    @Test
    public void test_getInputVariableNames_createdWithPrep_sameVars() {
        // Arrange
        Preprocessor preprocessor = createPreprocessor();
        this.sut = new Preprocessor(preprocessor);

        // Act
        Vector result = this.sut.getInputVariableNames();

        // Assert
        assertThat(preprocessor.getInputVariableNames().size(), is(greaterThan(0)));
        for (Object variableName : preprocessor.getInputVariableNames()) {
            assertTrue(result.contains(variableName));
        }
    }

    @Test
    public void test_getInputVariableNames_createdWithVars_sameVars() {
        // Arrange
        Vector<String> variableNames = new Vector<>();
        variableNames.addElement("inputVarName1");
        variableNames.addElement("inputVarName2");
        variableNames.addElement("inputVarName3");

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), anyVector(), anyBoolean());

        // Act
        Vector result = this.sut.getInputVariableNames();

        // Assert
        assertThat(variableNames.size(), is(greaterThan(0)));
        for (String variableName : variableNames) {
            assertTrue(result.contains(variableName));
        }
    }

    @Test
    public void test_getNumberOfInputVariables_createdWithoutParams_zero() {
        // Arrange
        // No arrangements

        // Act & Assert
        assertThat(this.sut.getNumberOfInputVariables(), is(equalTo(0)));
    }

    @Test
    public void test_getNumberOfInputVariables_createdWithPrep_sameCount() {
        // Arrange
        Preprocessor preprocessor = createPreprocessor();
        this.sut = new Preprocessor(preprocessor);

        // Act
        int result = this.sut.getNumberOfInputVariables();

        // Assert
        assertThat(preprocessor.getInputVariableNames().size(), is(greaterThan(0)));
        assertThat(result, is(equalTo(preprocessor.getInputVariableNames().size())));
    }

    @Test
    public void test_getNumberOfInputVariables_createdWithVars_sameCount() {
        // Arrange
        Vector<String> variableNames = new Vector<>();
        variableNames.addElement("inputVarName1");
        variableNames.addElement("inputVarName2");
        variableNames.addElement("inputVarName3");

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), anyVector(), anyBoolean());

        // Act
        int result = this.sut.getNumberOfInputVariables();

        // Assert
        assertThat(variableNames.size(), is(greaterThan(0)));
        assertThat(result, is(equalTo(variableNames.size())));
    }

    @Test
    public void test_getDerivedVariableNames_noDerivedVars_emptyList() {
        // Arrange
        // No arrangements

        // Act & Assert
        assertThat(this.sut.getDerivedVariableNames().size(), is(equalTo(0)));
    }

    @Test
    public void test_getDerivedVariableNames_createdWithPrep_sameVars() {
        // Arrange
        Preprocessor preprocessor = createPreprocessor();
        this.sut = new Preprocessor(preprocessor);

        // Act
        Vector result = this.sut.getDerivedVariableNames();

        // Assert
        assertThat(preprocessor.getDerivedVariableNames().size(), is(greaterThan(0)));
        for (Object variableName : preprocessor.getDerivedVariableNames()) {
            assertTrue(result.contains(variableName));
        }
    }

    @Test
    public void test_getDerivedVariableNames_createdWithVars_sameVars() {
        // Arrange
        Vector<String> derivedVarNames = new Vector<>();
        derivedVarNames.addElement("derivedVarName1");
        derivedVarNames.addElement("derivedVarName2");
        derivedVarNames.addElement("derivedVarName3");

        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), derivedVarNames, anyVector(), anyBoolean());

        // Act
        Vector result = this.sut.getDerivedVariableNames();

        // Assert
        assertThat(derivedVarNames.size(), is(greaterThan(0)));
        for (String variableName : derivedVarNames) {
            assertTrue(result.contains(variableName));
        }
    }

    @Test
    public void test_getDerivedVariableNames_formulaHasVars_retVars() {
        // Arrange
        String inputVariable1 = "inputVar1";
        String inputVariable2 = "inputVar2";
        Vector<String> varNames = new Vector<>();
        varNames.addElement(inputVariable1);
        varNames.addElement(inputVariable2);

        String outputVariable1 = "outputVar1";

        Vector<String> inputs = new Vector<>();
        inputs.addElement(inputVariable1);

        Formula2 formula = createFormula();
        formula.addInput(inputVariable1);
        formula.addInput(inputVariable2);
        formula.addOutput(outputVariable1);

        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(formula);

        this.sut = new Preprocessor(anyString(), anyString(), varNames, anyVector(), anyVector(), formulas, anyBoolean());
        this.sut.setDerivedVarNames(null);

        // Act
        Vector result = this.sut.getDerivedVariableNames();

        // Assert
        assertTrue(result.contains(outputVariable1));
    }

    @Test
    public void test_getDerivedVariableNames_formulasNotFound_notRetVar() {
        // Arrange
        String inputVariable1 = "inputVar1";
        String inputVariable2 = "inputVar2";
        Vector<String> varNames = new Vector<>();
        varNames.addElement(inputVariable1);

        String outputVariable1 = "outputVar1";

        Vector<String> inputs = new Vector<>();
        inputs.addElement(inputVariable1);

        Formula2 formula = createFormula();
        formula.addInput(inputVariable2);
        formula.addOutput(outputVariable1);

        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(formula);

        this.sut = new Preprocessor(anyString(), anyString(), varNames, anyVector(), anyVector(), formulas, anyBoolean());
        this.sut.setDerivedVarNames(null);

        // Act
        Vector result = this.sut.getDerivedVariableNames();

        // Assert
        assertFalse(result.contains(outputVariable1));
    }

    @Test
    public void test_getNumberOfDerivedVariables_noDerivedVars_retZero() {
        // Arrange
        // No arrangements

        // Act & Assert
        assertThat(this.sut.getNumberOfDerivedVariables(), is(equalTo(0)));
    }

    @Test
    public void test_getNumberOfDerivedVariables_createdWithPrep_retVarCount() {
        // Arrange
        Preprocessor preprocessor = createPreprocessor();
        this.sut = new Preprocessor(preprocessor);

        // Act
        int result = this.sut.getNumberOfDerivedVariables();

        // Assert
        assertThat(preprocessor.getDerivedVariableNames().size(), is(greaterThan(0)));
        assertThat(result, is(equalTo(preprocessor.getDerivedVariableNames().size())));
    }

    @Test
    public void test_getNumberOfDerivedVariables_crtdWithVars_retSameCount() {
        // Arrange
        Vector<String> derivedVarNames = new Vector<>();
        derivedVarNames.addElement("derivedVarName1");
        derivedVarNames.addElement("derivedVarName2");
        derivedVarNames.addElement("derivedVarName3");

        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), derivedVarNames, anyVector(), anyBoolean());

        // Act
        int result = this.sut.getNumberOfDerivedVariables();

        // Assert
        assertThat(derivedVarNames.size(), is(greaterThan(0)));
        assertThat(result, is(equalTo(derivedVarNames.size())));
    }

    @Test
    public void test_getVariableNames_createdWithoutParams_retNoVars() {
        // Arrange
        // No arrangements

        // Act & Assert
        assertThat(this.sut.getVariableNames().size(), is(equalTo(0)));
    }

    @Test
    public void test_getVariableNames_createdWithPreprocessor_retSameVars() {
        // Arrange
        Preprocessor preprocessor = createPreprocessor();
        this.sut = new Preprocessor(preprocessor);

        // Act
        Vector result = this.sut.getVariableNames();

        // Assert
        assertThat(preprocessor.getVariableNames().size(), is(greaterThan(0)));
        assertThat(preprocessor.getDerivedVariableNames().size(), is(greaterThan(0)));
        for (Object variableName : preprocessor.getVariableNames()) {
            assertTrue(result.contains(variableName));
        }

        for (Object variableName : preprocessor.getDerivedVariableNames()) {
            assertTrue(result.contains(variableName));
        }
    }

    @Test
    public void test_getVariableNames_createdWithVarNames_retSameVars() {
        // Arrange
        Vector<String> variableNames = new Vector<>();
        variableNames.addElement("varName1");
        variableNames.addElement("varName2");
        variableNames.addElement("varName3");

        Vector<String> derivedVarNames = new Vector<>();
        derivedVarNames.addElement("derivedVarName1");
        derivedVarNames.addElement("derivedVarName2");
        derivedVarNames.addElement("derivedVarName3");

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), derivedVarNames, anyVector(), anyBoolean());

        // Act
        Vector result = this.sut.getVariableNames();

        // Assert
        assertThat(variableNames.size(), is(greaterThan(0)));
        assertThat(derivedVarNames.size(), is(greaterThan(0)));
        assertThat(result.size(), is(equalTo(variableNames.size() + derivedVarNames.size())));
        for (String variableName : variableNames) {
            assertTrue(result.contains(variableName));
        }

        for (String variableName : derivedVarNames) {
            assertTrue(result.contains(variableName));
        }
    }

    @Test
    public void test_getNumberOfVariables_createdWithoutParams_retZero() {
        // Arrange
        // No arrangements

        // Act & Assert
        assertThat(this.sut.getNumberOfVariables(), is(equalTo(0)));
    }

    @Test
    public void test_getNumberOfVariables_createdWithPreprocessor_retCount() {
        // Arrange
        Preprocessor preprocessor = createPreprocessor();
        this.sut = new Preprocessor(preprocessor);

        // Act
        int result = this.sut.getNumberOfVariables();

        // Assert
        assertThat(preprocessor.getNumberOfInputVariables(), is(greaterThan(0)));
        assertThat(preprocessor.getNumberOfDerivedVariables(), is(greaterThan(0)));
        assertThat(result, is(equalTo(preprocessor.getNumberOfInputVariables() + preprocessor.getNumberOfDerivedVariables())));
    }

    @Test
    public void test_getNumberOfVariables_createdWithVarNames_retCount() {
        // Arrange
        Vector<String> variableNames = new Vector<>();
        variableNames.addElement("varName1");
        variableNames.addElement("varName2");
        variableNames.addElement("varName3");

        Vector<String> derivedVarNames = new Vector<>();
        derivedVarNames.addElement("derivedVarName1");
        derivedVarNames.addElement("derivedVarName2");
        derivedVarNames.addElement("derivedVarName3");

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), derivedVarNames, anyVector(), anyBoolean());

        // Act
        int result = this.sut.getNumberOfVariables();

        // Assert
        assertThat(variableNames.size(), is(greaterThan(0)));
        assertThat(derivedVarNames.size(), is(greaterThan(0)));
        assertThat(result, is(equalTo(variableNames.size() + derivedVarNames.size())));
    }

    @Test
    public void test_getInputVariableTags_createdWithoutParams_retNoNames() {
        // Arrange
        // No arrangements

        // Act & Assert
        assertThat(this.sut.getInputVariableTags().size(), is(equalTo(0)));
    }

    @Test
    public void test_getInputVariableTags_createdWithPrep_retSameTags() {
        // Arrange
        Preprocessor preprocessor = createPreprocessor();
        this.sut = new Preprocessor(preprocessor);

        // Act
        Vector result = this.sut.getInputVariableTags();

        // Assert
        assertThat(preprocessor.getInputVariableTags().size(), is(greaterThan(0)));
        for (Object variableTag : preprocessor.getInputVariableTags()) {
            assertTrue(result.contains(variableTag));
        }
    }

    @Test
    public void test_getInputVariableTags_createdWithTags_retSameTags() {
        // Arrange
        Vector<String> variableTags = new Vector<>();
        variableTags.addElement("inputVarTag1");
        variableTags.addElement("inputVarTag2");
        variableTags.addElement("inputVarTag3");

        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), variableTags, anyVector(), anyVector(), anyBoolean());

        // Act
        Vector result = this.sut.getInputVariableTags();

        // Assert
        assertThat(variableTags.size(), is(greaterThan(0)));
        for (String variableTag : variableTags) {
            assertTrue(result.contains(variableTag));
        }
    }

    @Test
    public void test_getDataSeriesFromVariableName_dsExists_retDs() throws MathException {
        // Arrange
        DataSeries dataSeries = new DataSeries(anyInteger(), anyInteger());
        dataSeries.setName("dataSeries1");

        Vector<Variable> variables = new Vector<>();
        Variable variable = createVariable(dataSeries);
        variables.addElement(variable);

        dataSeries.setVariableParameters(0, variable.getTag(), variable.getName(), variable.getUnit());

        this.sut = new Preprocessor(anyString(), createProject(), variables, createViewFilter());

        // Act
        assertThat(this.sut.getDataSeriesFromVariableName(variable.getName()).getName(), is(equalTo(dataSeries.getName())));
    }

    @Test
    public void test_getDataSeriesFromVariableName_noDs_retNull() throws MathException {
        // Arrange
        DataSeries dataSeries = new DataSeries();
        dataSeries.setName("dataSeries1");

        Vector<Variable> variables = new Vector<>();
        Variable variable = createVariable(dataSeries);
        variables.addElement(variable);

        this.sut = new Preprocessor(anyString(), createProject(), variables, createViewFilter());

        // Act & Assert
        assertNull(this.sut.getDataSeriesFromVariableName(anyString()));
    }

    @Test
    public void test_getDataSeriesFromVariableName_dsInList_retDs() throws MathException {
        // Arrange
        DataSeries dataSeries = new DataSeries(anyInteger(), anyInteger());
        dataSeries.setName("dataSeries1");

        Variable variable = createVariable(dataSeries);
        dataSeries.setVariableParameters(0, variable.getTag(), variable.getName(), variable.getUnit());
        Vector<DataSeries> dataSeriesList = new Vector<>();
        dataSeriesList.addElement(dataSeries);

        Vector<Variable> variables = new Vector<>();
        variables.addElement(variable);

        // Act & Assert
        assertThat(this.sut.getDataSeriesFromVariableName(dataSeriesList, variable.getName()), is(equalTo(dataSeries)));
    }

    @Test
    public void test_getDataSeriesFromVariableName_dsNotInList_retNull() throws MathException {
        // Arrange
        DataSeries dataSeries = new DataSeries(anyInteger(), anyInteger());
        dataSeries.setName("dataSeries1");

        Variable variable = createVariable(dataSeries);
        dataSeries.setVariableParameters(0, variable.getTag(), variable.getName(), variable.getUnit());
        Vector<DataSeries> dataSeriesList = new Vector<>();
        dataSeriesList.addElement(dataSeries);

        Vector<Variable> variables = new Vector<>();
        variables.addElement(variable);

        // Act & Assert
        assertNull(this.sut.getDataSeriesFromVariableName(dataSeriesList, anyString()));
    }

    @Test
    public void test_getVariableFromVariableName_dsExists_retDs() throws MathException {
        // Arrange
        DataSeries dataSeries = new DataSeries(anyInteger(), anyInteger());
        dataSeries.setName("dataSeries1");

        Variable variable = createVariable(dataSeries);
        dataSeries.setVariableParameters(0, variable.getTag(), variable.getName(), variable.getUnit());

        Vector<Variable> variables = new Vector<>();
        variables.addElement(variable);

        this.sut = new Preprocessor(anyString(), createProject(), variables, createViewFilter());

        // Act & Assert
        assertThat(this.sut.getDataSeriesFromVariableName(variable.getName()).getName(), is(equalTo(dataSeries.getName())));
    }

    @Test
    public void test_getVariableFromVariableName_dsNotExist_retNull() throws MathException {
        // Arrange
        DataSeries dataSeries = new DataSeries(anyInteger(), anyInteger());
        dataSeries.setName("dataSeries1");

        Variable variable = createVariable(dataSeries);
        dataSeries.setVariableParameters(0, variable.getTag(), variable.getName(), variable.getUnit());

        Vector<Variable> variables = new Vector<>();
        variables.addElement(variable);

        this.sut = new Preprocessor(anyString(), createProject(), variables, createViewFilter());

        // Act & Assert
        assertNull(this.sut.getDataSeriesFromVariableName(anyString()));
    }

    @Test
    public void test_getOriginalVarNames_always_originalVars() throws MathException {
        // Arrange
        String inputVariable1 = "inVar1";
        String outputVariable1 = "outVar1";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariable1);

        Formula2 formula = createFormula();
        formula.addInput(inputVariable1);
        formula.addOutput(outputVariable1);

        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(formula);

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), formulas, anyBoolean());

        Vector<String> usedNames = new Vector<>();
        usedNames.addElement(inputVariable1);

        // Act
        Vector result = this.sut.getOriginalVarNames(usedNames);

        // Assert
        assertTrue(result.contains(inputVariable1));
    }

    @Test
    public void test_getOriginalVarNames_inputVarsMissing_addsVariables() throws MathException {
        // Arrange
        String inputVariable1 = "inVar1";
        String inputVariable2 = "inVar2";
        String inputVariable3 = "inVar3";
        String outputVariable1 = "outVar1";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariable1);
        variableNames.addElement(inputVariable2);
        variableNames.addElement(inputVariable3);

        Formula2 formula = createFormula();
        formula.addInput(inputVariable1);
        formula.addInput(inputVariable2);
        formula.addInput(inputVariable3);
        formula.addOutput(outputVariable1);

        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(formula);

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), formulas, anyBoolean());

        Vector<String> usedNames = new Vector<>();
        usedNames.addElement(inputVariable1);

        // Act
        Vector result = this.sut.getOriginalVarNames(usedNames);

        // Assert
        assertTrue(result.contains(inputVariable2));
        assertTrue(result.contains(inputVariable3));
    }

    @Test
    public void test_getOriginalVarNames_never_retOutputVariables() throws MathException {
        // Arrange
        String inputVariable1 = "inVar1";
        String outputVariable1 = "outVar1";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariable1);

        Vector<String> derivedVarNames = new Vector<>();
        derivedVarNames.addElement(outputVariable1);

        Formula2 formula = createFormula();
        formula.addInput(inputVariable1);
        formula.addOutput(outputVariable1);

        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(formula);

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), derivedVarNames, formulas, anyBoolean());

        Vector<String> usedNames = new Vector<>();
        usedNames.addElement(inputVariable1);
        usedNames.addElement(outputVariable1);

        // Act
        Vector result = this.sut.getOriginalVarNames(usedNames);

        // Assert
        assertFalse(result.contains(outputVariable1));
    }

    @Test
    public void test_getVarNamesUsedInFormulas_always_retVarsInUse() throws MathException {
        // Arrange
        String inputVariable1 = "inVar1";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariable1);

        Formula2 formula = createFormula();
        formula.addInput(inputVariable1);

        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(formula);

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), formulas, anyBoolean());

        // Act & Assert
        assertTrue(this.sut.getVarNamesUsedInFormulas().contains(inputVariable1));
    }

    @Test
    public void test_getVarNamesUsedInFormulas_always_retSubFormulaVars() throws MathException {
        // Arrange
        String inputVariable1 = "inVar1";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariable1);

        InnerFormula2 subFormula = new InnerFormula2();
        subFormula.addInput(inputVariable1);

        Formula2 formula = createFormula();
        formula.addInput(subFormula);

        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(formula);

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), formulas, anyBoolean());

        // Act & Assert
        assertTrue(this.sut.getVarNamesUsedInFormulas().contains(inputVariable1));
    }

    @Test
    public void test_initTransient_always_setsProject() throws MathException {
        // Arrange
        DataSeries dataSeries = new DataSeries(anyInteger(), anyInteger());
        dataSeries.setName("dataSeries1");

        Variable variable = createVariable(dataSeries);
        dataSeries.setVariableParameters(0, variable.getTag(), variable.getName(), variable.getUnit());

        Vector<Variable> variables = new Vector<>();
        variables.addElement(variable);

        this.sut = new Preprocessor(anyString(), createProject(), variables, createViewFilter());

        Project project = createProject();

        // Act
        this.sut.initTransient(project);

        // Assert
        assertThat(this.sut.getProject(), is(equalTo(project)));
    }

    @Test
    public void test_getNumberOfFormulas_always_retNumberOfFormulas() {
        // Arrange
        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());

        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), formulas, anyBoolean());

        // Act & Assert
        assertThat(this.sut.getNumberOfFormulas(), is(equalTo(formulas.size())));
    }

    @Test
    public void test_getFormula_formulaExists_retFormula() {
        // Arrange
        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());

        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), formulas, anyBoolean());

        assertThat(formulas.size(), is(greaterThan(0)));
        for (int i = 0; i < formulas.size(); i++) {
            Formula2 formula = formulas.get(i);

            // Act & Assert
            assertThat(this.sut.getFormula(i), is(equalTo(formula)));
        }
    }

    // Assert
    @Test(expected = IndexOutOfBoundsException.class)
    public void test_getFormula_formulaDoesNotExist_throwsException() {
        // Arrange
        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());

        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), formulas, anyBoolean());

        // Act
        this.sut.getFormula(formulas.size());
    }

    @Test
    public void test_getFormulas_always_retFormulas() {
        // Arrange
        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());

        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), formulas, anyBoolean());

        // Act
        Vector result = this.sut.getFormulas();

        // Assert
        for (Formula2 formula : formulas) {
            assertTrue(result.contains(formula));
        }
    }

    @Test
    public void test_addFormula_always_addsFormulaToEndOfVector() {
        // Arrange
        Formula2 formula = createFormula();

        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());

        int formulasExistingCount = formulas.size();

        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), formulas, anyBoolean());
        addEventListeners(this.sut);

        // Act
        boolean result = this.sut.addFormula(formula);

        // Assert
        assertTrue(result);
        assertThat(this.sut.getFormula(formulasExistingCount), is(equalTo(formula)));
    }

    @Test
    public void test_addFormula_always_invokesEvent() {
        // Arrange
        Formula2 formula = createFormula();

        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());

        int formulasExistingCount = formulas.size();

        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), formulas, anyBoolean());
        addEventListeners(this.sut);

        // Act
        boolean result = this.sut.addFormula(formula);

        // Assert
        assertTrue(result);
        assertThat(this.sut.getEventListeners().size(), is(equalTo(formulasExistingCount)));
        for (Object listener : sut.getEventListeners()) {
            PreprocessorListener preprocessorListener = (PreprocessorListener) listener;
            verify(preprocessorListener).FormulaListChanged(Matchers.any());
        }
    }

    @Test
    public void test_addFormula_always_addsFormulaAtIndex() {
        // Arrange
        Formula2 formula = createFormula();

        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());

        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), formulas, anyBoolean());
        addEventListeners(this.sut);

        int index = 0;

        // Act
        boolean result = this.sut.addFormula(formula, index);

        // Assert
        assertTrue(result);
        assertThat(this.sut.getFormula(index), is(equalTo(formula)));
    }

    @Test
    public void test_addFormulaByIndex_always_invokesEvent() {
        // Arrange
        Formula2 formula = createFormula();

        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());

        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), formulas, anyBoolean());
        addEventListeners(this.sut);

        // Act
        boolean result = this.sut.addFormula(formula, 0);

        // Assert
        assertTrue(result);
        assertThat(this.sut.getEventListeners().size(), is(greaterThan(0)));
        for (Object listener : sut.getEventListeners()) {
            PreprocessorListener preprocessorListener = (PreprocessorListener) listener;
            verify(preprocessorListener).FormulaListChanged(Matchers.any());
        }
    }

    @Test
    public void test_addFormulas_fileContainsFormulas_addsFormulas() {
        // Arrange
        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());

        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), formulas, anyBoolean());
        addEventListeners(this.sut);

        Vector<Formula2> newFormulas = new Vector<>();
        newFormulas.addElement(createFormula());
        newFormulas.addElement(createFormula());
        newFormulas.addElement(createFormula());

        // Act
        boolean result = this.sut.addFormulas(newFormulas);

        // Assert
        assertTrue(result);
        assertThat(newFormulas.size(), is(greaterThan(0)));
        for (Formula2 newFormula : newFormulas) {
            assertTrue(this.sut.getFormulas().contains(newFormula));
        }
    }

    @Test
    public void test_addFormulas_fileContainsFormulas_invokesEvent() {
        // Arrange
        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());

        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), formulas, anyBoolean());
        addEventListeners(this.sut);

        Vector<Formula2> newFormulas = new Vector<>();
        newFormulas.addElement(createFormula());
        newFormulas.addElement(createFormula());
        newFormulas.addElement(createFormula());

        // Act
        boolean result = this.sut.addFormulas(newFormulas);

        // Assert
        assertTrue(result);
        assertThat(this.sut.getEventListeners().size(), is(greaterThan(0)));
        for (Object listener : sut.getEventListeners()) {
            PreprocessorListener preprocessorListener = (PreprocessorListener) listener;
            verify(preprocessorListener).FormulaListChanged(Matchers.any());
        }
    }

    @Test
    public void test_addFormulas_always_addsFormulas() {
        // Arrange
        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());

        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), formulas, anyBoolean());
        addEventListeners(this.sut);

        Vector<Formula2> newFormulas = new Vector<>();
        newFormulas.addElement(createFormula());
        newFormulas.addElement(createFormula());
        newFormulas.addElement(createFormula());

        // Act
        boolean result = this.sut.addFormulas(newFormulas, 0);

        // Assert
        assertTrue(result);
        assertThat(newFormulas.size(), is(greaterThan(0)));
        for (Formula2 newFormula : newFormulas) {
            assertTrue(this.sut.getFormulas().contains(newFormula));
        }
    }

    @Test
    public void test_addFormulas_always_invokesEvent() {
        // Arrange
        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());

        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), formulas, anyBoolean());
        addEventListeners(this.sut);

        Vector<Formula2> newFormulas = new Vector<>();
        newFormulas.addElement(createFormula());
        newFormulas.addElement(createFormula());
        newFormulas.addElement(createFormula());

        // Act
        boolean result = this.sut.addFormulas(newFormulas, 0);

        // Assert
        assertTrue(result);
        assertThat(this.sut.getEventListeners().size(), is(greaterThan(0)));
        for (Object listener : sut.getEventListeners()) {
            PreprocessorListener preprocessorListener = (PreprocessorListener) listener;
            verify(preprocessorListener).FormulaListChanged(Matchers.any());
        }
    }

    @Test
    public void test_addFormulas_varsExist_addsFileFormula() throws IOException {
        // Arrange
        String inputVariable1 = "inputVar1";
        String inputVariable2 = "inputVar2";
        String inputVariable3 = "inputVar3";
        String inputVariable4 = "inputVar4";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariable1);
        variableNames.addElement(inputVariable2);
        variableNames.addElement(inputVariable3);
        variableNames.addElement(inputVariable4);

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), anyVector(), anyBoolean());
        addEventListeners(this.sut);

        Vector<Formula2> newFormulas = new Vector<>();
        Formula2 formula = createFormula();
        formula.setFunction(createFunction(1));
        formula.addInput(inputVariable1);
        formula.addInput(inputVariable2);
        formula.addOutput("outputVar1");
        formula.addOutput("outputVar2");
        newFormulas.addElement(formula);

        formula = createFormula();
        formula.setFunction(createFunction(2));
        formula.addInput(inputVariable3);
        formula.addInput(inputVariable4);
        formula.addOutput("outputVar3");
        formula.addOutput("outputVar4");
        newFormulas.addElement(formula);

        File file = createObjectFile(newFormulas);

        // Act
        boolean result = this.sut.addFormulas(null, file.getAbsolutePath());

        // Assert
        assertTrue(result);
        assertThat(newFormulas.size(), is(greaterThan(0)));
        for (int index = 0; index < newFormulas.size(); index++) {
            assertThat(this.sut.getFormula(index).toString(), is(equalTo(newFormulas.get(index).toString())));
        }
    }

    @Test
    public void test_addFormulasFromFile_varsExist_invokesEvent() throws IOException {
        // Arrange
        String inputVariable1 = "inputVar1";
        String inputVariable2 = "inputVar2";
        String inputVariable3 = "inputVar3";
        String inputVariable4 = "inputVar4";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariable1);
        variableNames.addElement(inputVariable2);
        variableNames.addElement(inputVariable3);
        variableNames.addElement(inputVariable4);

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), anyVector(), anyBoolean());
        addEventListeners(this.sut);

        Vector<Formula2> newFormulas = new Vector<>();
        Formula2 formula = createFormula();
        formula.setFunction(createFunction(1));
        formula.addInput(inputVariable1);
        formula.addInput(inputVariable2);
        formula.addOutput("outputVar1");
        formula.addOutput("outputVar2");
        newFormulas.addElement(formula);

        formula = createFormula();
        formula.setFunction(createFunction(2));
        formula.addInput(inputVariable3);
        formula.addInput(inputVariable4);
        formula.addOutput("outputVar3");
        formula.addOutput("outputVar4");
        newFormulas.addElement(formula);

        File file = createObjectFile(newFormulas);
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        // Act
        boolean result = this.sut.addFormulas(directory, filename);

        // Assert
        assertTrue(result);
        assertThat(this.sut.getEventListeners().size(), is(greaterThan(0)));
        for (Object listener : sut.getEventListeners()) {
            PreprocessorListener preprocessorListener = (PreprocessorListener) listener;
            verify(preprocessorListener).FormulaListChanged(Matchers.any());
        }
    }

    @Test
    public void test_addFormulas_varsNotExist_doesNotAddFileFormula() throws IOException {
        // Arrange
        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), anyVector(), anyBoolean());
        addEventListeners(this.sut);

        Vector<Formula2> newFormulas = new Vector<>();
        Formula2 formula = createFormula();
        formula.setFunction(createFunction(1));
        formula.addInput("inputVar1");
        formula.addInput("inputVar2");
        formula.addOutput("outputVar1");
        formula.addOutput("outputVar2");
        newFormulas.addElement(formula);

        formula = createFormula();
        formula.setFunction(createFunction(2));
        formula.addInput("inputVar3");
        formula.addInput("inputVar4");
        formula.addOutput("outputVar3");
        formula.addOutput("outputVar4");
        newFormulas.addElement(formula);

        File file = createObjectFile(newFormulas);

        // Act
        boolean result = this.sut.addFormulas(null, file.getAbsolutePath());

        // Assert
        assertFalse(result);
        assertThat(newFormulas.size(), is(greaterThan(0)));
        assertThat(this.sut.getFormulas().size(), is(equalTo(0)));
    }

    @Test
    public void test_addFormulas_varsNotExist_changedEventNotInvoked() throws IOException {
        // Arrange
        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), anyVector(), anyBoolean());
        addEventListeners(this.sut);

        Vector<Formula2> newFormulas = new Vector<>();
        Formula2 formula = createFormula();
        formula.setFunction(createFunction(1));
        formula.addInput("inputVar1");
        formula.addInput("inputVar2");
        formula.addOutput("outputVar1");
        formula.addOutput("outputVar2");
        newFormulas.addElement(formula);

        formula = createFormula();
        formula.setFunction(createFunction(2));
        formula.addInput("inputVar3");
        formula.addInput("inputVar4");
        formula.addOutput("outputVar3");
        formula.addOutput("outputVar4");
        newFormulas.addElement(formula);

        File file = createObjectFile(newFormulas);
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        // Act
        boolean result = this.sut.addFormulas(directory, filename);

        // Assert
        assertFalse(result);
        assertThat(this.sut.getEventListeners().size(), is(greaterThan(0)));
        for (Object listener : sut.getEventListeners()) {
            PreprocessorListener preprocessorListener = (PreprocessorListener) listener;
            verify(preprocessorListener, never()).FormulaListChanged(Matchers.any());
        }
    }

    @Test
    public void test_addFormulas_contentIsNotVector_retFalse() throws IOException {
        // Arrange
        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), anyVector(), anyBoolean());
        addEventListeners(this.sut);

        File file = createObjectFile(new Formula2());
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        // Act
        boolean result = this.sut.addFormulas(directory, filename);

        // Assert
        assertFalse(result);
        assertThat(this.sut.getEventListeners().size(), is(greaterThan(0)));
        for (Object listener : sut.getEventListeners()) {
            PreprocessorListener preprocessorListener = (PreprocessorListener) listener;
            verify(preprocessorListener, never()).FormulaListChanged(Matchers.any());
        }
    }

    @Test
    public void test_addFormulas_varsExist_addsFormula() throws IOException {
        // Arrange
        String inputVariable1 = "inputVar1";
        String inputVariable2 = "inputVar2";
        String inputVariable3 = "inputVar3";
        String inputVariable4 = "inputVar4";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariable1);
        variableNames.addElement(inputVariable2);
        variableNames.addElement(inputVariable3);
        variableNames.addElement(inputVariable4);

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), anyVector(), anyBoolean());
        addEventListeners(this.sut);

        Vector<Formula2> newFormulas = new Vector<>();
        Formula2 newFormula = createFormula();
        newFormula.setFunction(createFunction(1));
        newFormula.addInput(inputVariable1);
        newFormula.addInput(inputVariable2);
        newFormula.addOutput("outputVar1");
        newFormula.addOutput("outputVar2");
        newFormulas.addElement(newFormula);

        File file = createObjectFile(newFormulas);

        // Act
        boolean result = this.sut.addFormulas(null, file.getAbsolutePath(), 0);

        // Assert
        assertTrue(result);
        assertThat(this.sut.getFormula(0).toString(), is(equalTo(newFormula.toString())));
    }

    @Test
    public void test_addFormulas_varsExist_invokesEvent() throws IOException {
        // Arrange
        String inputVariable1 = "inputVar1";
        String inputVariable2 = "inputVar2";
        String inputVariable3 = "inputVar3";
        String inputVariable4 = "inputVar4";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariable1);
        variableNames.addElement(inputVariable2);
        variableNames.addElement(inputVariable3);
        variableNames.addElement(inputVariable4);

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), anyVector(), anyBoolean());
        addEventListeners(this.sut);

        Vector<Formula2> newFormulas = new Vector<>();
        Formula2 formula = createFormula();
        formula.setFunction(createFunction(1));
        formula.addInput(inputVariable1);
        formula.addInput(inputVariable2);
        formula.addOutput("outputVar1");
        formula.addOutput("outputVar2");
        newFormulas.addElement(formula);

        formula = createFormula();
        formula.setFunction(createFunction(2));
        formula.addInput(inputVariable3);
        formula.addInput(inputVariable4);
        formula.addOutput("outputVar3");
        formula.addOutput("outputVar4");
        newFormulas.addElement(formula);

        File file = createObjectFile(newFormulas);
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        // Act
        boolean result = this.sut.addFormulas(directory, filename, 0);

        // Assert
        assertTrue(result);
        assertThat(this.sut.getEventListeners().size(), is(greaterThan(0)));
        for (Object listener : sut.getEventListeners()) {
            PreprocessorListener preprocessorListener = (PreprocessorListener) listener;
            verify(preprocessorListener).FormulaListChanged(Matchers.any());
        }
    }

    @Test
    public void test_addFormulas_varsNotExist_doesNotAddFormula() throws IOException {
        // Arrange
        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), anyVector(), anyBoolean());
        addEventListeners(this.sut);

        Vector<Formula2> newFormulas = new Vector<>();
        Formula2 formula = createFormula();
        formula.setFunction(createFunction(1));
        formula.addInput("inputVar1");
        formula.addInput("inputVar2");
        formula.addOutput("outputVar1");
        formula.addOutput("outputVar2");
        newFormulas.addElement(formula);

        formula = createFormula();
        formula.setFunction(createFunction(2));
        formula.addInput("inputVar3");
        formula.addInput("inputVar4");
        formula.addOutput("outputVar3");
        formula.addOutput("outputVar4");
        newFormulas.addElement(formula);

        File file = createObjectFile(newFormulas);

        // Act
        boolean result = this.sut.addFormulas(null, file.getAbsolutePath(), 0);

        // Assert
        assertFalse(result);
        assertThat(newFormulas.size(), is(greaterThan(0)));
        assertThat(this.sut.getFormulas().size(), is(equalTo(0)));
    }

    @Test
    public void test_addFormulas_varsNotExist_doesNotInvokeChangedEvent() throws IOException {
        // Arrange
        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), anyVector(), anyBoolean());
        addEventListeners(this.sut);

        Vector<Formula2> newFormulas = new Vector<>();
        Formula2 formula = createFormula();
        formula.setFunction(createFunction(1));
        formula.addInput("inputVar1");
        formula.addInput("inputVar2");
        formula.addOutput("outputVar1");
        formula.addOutput("outputVar2");
        newFormulas.addElement(formula);

        File file = createObjectFile(newFormulas);
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        // Act
        boolean result = this.sut.addFormulas(directory, filename, 0);

        // Assert
        assertFalse(result);
        assertThat(this.sut.getEventListeners().size(), is(greaterThan(0)));
        for (Object listener : sut.getEventListeners()) {
            PreprocessorListener preprocessorListener = (PreprocessorListener) listener;
            verify(preprocessorListener, never()).FormulaListChanged(Matchers.any());
        }
    }

    @Test
    public void test_modifyFormula_indexIsLessThanZero_retFalse() {
        // Arrange
        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), anyVector(), anyBoolean());

        // Act
        boolean result = this.sut.modifyFormula(new Formula2(), -1);

        // Assert
        assertFalse(result);
    }

    @Test
    public void test_modifyFormula_indexIsOutsideOfArrayBounds_retFalse() {
        // Arrange
        String inputVariable1 = "inputVar1";
        String inputVariable2 = "inputVar2";
        String inputVariable3 = "inputVar3";
        String inputVariable4 = "inputVar4";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariable1);
        variableNames.addElement(inputVariable2);
        variableNames.addElement(inputVariable3);
        variableNames.addElement(inputVariable4);

        Vector<Formula2> formulas = new Vector<>();
        Formula2 formula = new Formula2();
        formula.addInput(inputVariable1);
        formula.addInput(inputVariable2);
        formula.addOutput("outVar1");
        formulas.addElement(formula);

        Formula2 modifiedFormula = new Formula2();
        modifiedFormula.addInput(inputVariable3);
        modifiedFormula.addInput(inputVariable4);
        formula.addOutput("outVar2");

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), formulas, anyBoolean());

        int index = formulas.size();

        // Act
        boolean result = this.sut.modifyFormula(modifiedFormula, index);

        // Assert
        assertFalse(result);
    }

    @Test
    public void test_modifyFormula_formulaVarsExist_modifiesFormula() {
        // Arrange
        String inputVariable1 = "inputVar1";
        String inputVariable2 = "inputVar2";
        String inputVariable3 = "inputVar3";
        String inputVariable4 = "inputVar4";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariable1);
        variableNames.addElement(inputVariable2);
        variableNames.addElement(inputVariable3);
        variableNames.addElement(inputVariable4);

        Vector<Formula2> formulas = new Vector<>();
        Formula2 formula = new Formula2();
        formula.addInput(inputVariable1);
        formula.addInput(inputVariable2);
        formula.addOutput("outVar1");
        formulas.addElement(formula);

        Formula2 modifiedFormula = new Formula2();
        modifiedFormula.addInput(inputVariable3);
        modifiedFormula.addInput(inputVariable4);
        formula.addOutput("outVar2");

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), formulas, anyBoolean());

        int index = 0;

        // Act
        boolean result = this.sut.modifyFormula(modifiedFormula, index);

        // Assert
        assertTrue(result);
        assertThat(this.sut.getFormula(index), is(equalTo(modifiedFormula)));
    }

    @Test
    public void test_removeFormula_indexIsLessThanZero_retFalse() {
        // Arrange
        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), anyVector(), anyBoolean());

        // Act & Assert
        assertFalse(this.sut.removeFormula(-1));
    }

    @Test
    public void test_removeFormula_indexIsOutsideOfArrayBounds_retFalse() {
        // Arrange
        String inputVariable1 = "inputVar1";
        String inputVariable2 = "inputVar2";
        String inputVariable3 = "inputVar3";
        String inputVariable4 = "inputVar4";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariable1);
        variableNames.addElement(inputVariable2);
        variableNames.addElement(inputVariable3);
        variableNames.addElement(inputVariable4);

        Vector<Formula2> formulas = new Vector<>();
        Formula2 formula = new Formula2();
        formula.addInput(inputVariable1);
        formula.addInput(inputVariable2);
        formula.addOutput("outVar1");
        formulas.addElement(formula);

        Formula2 modifiedFormula = new Formula2();
        modifiedFormula.addInput(inputVariable3);
        modifiedFormula.addInput(inputVariable4);
        formula.addOutput("outVar2");

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), formulas, anyBoolean());

        int index = formulas.size();

        // Act
        boolean result = this.sut.removeFormula(index);

        // Assert
        assertFalse(result);
    }

    @Test
    public void test_removeFormula_formulaExists_removesFormula() {
        // Arrange
        String inputVariable1 = "inputVar1";
        String inputVariable2 = "inputVar2";
        String inputVariable3 = "inputVar3";
        String inputVariable4 = "inputVar4";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariable1);
        variableNames.addElement(inputVariable2);
        variableNames.addElement(inputVariable3);
        variableNames.addElement(inputVariable4);

        Vector<Formula2> formulas = new Vector<>();
        Formula2 formula = new Formula2();
        formula.addInput(inputVariable1);
        formula.addInput(inputVariable2);
        formula.addOutput("outVar1");
        formulas.addElement(formula);

        formula = new Formula2();
        formula.addInput(inputVariable3);
        formula.addInput(inputVariable4);
        formula.addOutput("outVar2");
        formulas.addElement(formula);

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), formulas, anyBoolean());

        int index = 1;

        // Act
        boolean result = this.sut.removeFormula(index);

        // Assert
        assertTrue(result);
        assertTrue(this.sut.getFormulas().contains(formulas.get(0)));
        assertFalse(this.sut.getFormulas().contains(formulas.get(index)));
    }

    @Test
    public void test_moveFormula_indicesAreValid_movesFormula() {
        // Arrange
        Vector<Formula2> formulas = arrangeForMoveFormula();
        int from = 0;
        int to = formulas.size() - 1;

        // Act
        boolean result = this.sut.moveFormula(from, to);

        // Assert
        assertTrue(result);

        Formula2 newFormula2 = this.sut.getFormula(to);
        assertThat(newFormula2, is(equalTo(formulas.get(from))));
    }

    @Test
    public void test_moveFormula_fromIsGreaterThanTo_movesFormula() {
        // Arrange
        Vector<Formula2> formulas = arrangeForMoveFormula();
        int from = formulas.size() - 1;
        int to = 0;

        // Act
        boolean result = this.sut.moveFormula(from, to);

        // Assert
        assertTrue(result);

        Formula2 newFormula2 = this.sut.getFormula(to);
        assertThat(newFormula2, is(equalTo(formulas.get(from))));
    }

    @Test
    public void test_moveFormula_fromIsNegative_doesNotMoveFormula() {
        // Arrange
        arrangeForMoveFormula();
        int from = -1;
        int to = 0;

        // Act
        boolean result = this.sut.moveFormula(from, to);

        // Assert
        assertFalse(result);
    }

    @Test
    public void test_moveFormula_toIsNegative_doesNotMoveFormula() {
        // Arrange
        arrangeForMoveFormula();
        int from = 0;
        int to = -1;

        // Act
        boolean result = this.sut.moveFormula(from, to);

        // Assert
        assertFalse(result);
    }

    @Test
    public void test_moveFormula_fromIsAboveUpperBound_doesNotMoveFormula() {
        // Arrange
        Vector<Formula2> formulas = arrangeForMoveFormula();
        int from = formulas.size();
        int to = 1;

        // Act
        boolean result = this.sut.moveFormula(from, to);

        // Assert
        assertFalse(result);
    }

    @Test
    public void test_moveFormula_toIsAboveUpperBound_doesNotMoveFormula() {
        // Arrange
        Vector<Formula2> formulas = arrangeForMoveFormula();
        int from = 0;
        int to = formulas.size() + 1;

        // Act
        boolean result = this.sut.moveFormula(from, to);

        // Assert
        assertFalse(result);
    }

    @Test
    public void test_moveFormula_toIsEqualToFrom_retTrue() {
        // Arrange
        arrangeForMoveFormula();
        int from = 0;
        int to = 0;

        // Act
        boolean result = this.sut.moveFormula(from, to);

        // Assert
        assertTrue(result);
    }

    @Test
    public void test_updateFormulas_formulasNotUpdated_formulaApplied() throws MathException, NoSuchMethodException, FormulaException, InstantiationException, IllegalAccessException {
        // Arrange
        int dataSeriesCount = 2;
        int dataSeriesVariablesCount = 2;
        DataSeries dataSeries1 = createDataSeries(anyInteger(), dataSeriesVariablesCount);
        dataSeries1.setName("dataSeries1Name");

        DataSeries dataSeries2 = createDataSeries(anyInteger(), dataSeriesVariablesCount);
        dataSeries2.setName("dataSeries2Name");

        Variable variable1 = createVariable(dataSeries1, 1);
        Variable variable2 = createVariable(dataSeries1, 2);

        Variable variable3 = createVariable(dataSeries2, 3);
        Variable variable4 = createVariable(dataSeries2, 4);

        Vector<Variable> variables = new Vector<>();
        variables.addElement(variable1);
        variables.addElement(variable2);
        variables.addElement(variable3);
        variables.addElement(variable4);

        this.sut = new Preprocessor(anyString(), createProject(), variables, createViewFilter());

        int formulaSamples = 2;
        for (int i = 0; i < formulaSamples; i++) {
            Formula2Stub formula = new Formula2Stub();
            this.sut.addFormula(formula);
        }

        // Act
        this.sut.updateFormulas();

        // Assert
        assertThat(this.sut.getFormulas().size(), is(equalTo(formulaSamples)));
        assertThat(this.sut.getDataSeries().size(), is(equalTo(dataSeriesCount)));
        for (Object formula : sut.getFormulas()) {
            Formula2Stub formulaStub = (Formula2Stub) formula;
            assertTrue(formulaStub.hasAppliedFormula);
            assertNotNull(formulaStub.appliedFormulaUsingDataSeriesVector);

            for (Object dataSeries : sut.getDataSeries()) {
                assertTrue(formulaStub.appliedFormulaUsingDataSeriesVector.contains(dataSeries));
            }
        }
    }

    @Test
    public void test_updateFormulas_formulasUpdated_formulaNotApplied() throws MathException, NoSuchMethodException, FormulaException, InstantiationException, IllegalAccessException {
        // Arrange
        int dataSeriesCount = 2;
        int dataSeriesVariablesCount = 2;
        DataSeries dataSeries1 = createDataSeries(anyInteger(), dataSeriesVariablesCount);
        dataSeries1.setName("dataSeries1Name");

        DataSeries dataSeries2 = createDataSeries(anyInteger(), dataSeriesVariablesCount);
        dataSeries2.setName("dataSeries2Name");

        Variable variable1 = createVariable(dataSeries1, 1);
        Variable variable2 = createVariable(dataSeries1, 2);

        Variable variable3 = createVariable(dataSeries2, 3);
        Variable variable4 = createVariable(dataSeries2, 4);

        Vector<Variable> variables = new Vector<>();
        variables.addElement(variable1);
        variables.addElement(variable2);
        variables.addElement(variable3);
        variables.addElement(variable4);

        this.sut = new Preprocessor(anyString(), createProject(), variables, createViewFilter());

        int formulaSamples = 2;
        for (int i = 0; i < formulaSamples; i++) {
            Formula2Stub formula = new Formula2Stub();
            this.sut.addFormula(formula);
        }

        this.sut.updateFormulas();

        // Clearing flags before updating formulas again.
        for (Object formula : sut.getFormulas()) {
            ((Formula2Stub) formula).hasAppliedFormula = false;
            ((Formula2Stub) formula).appliedFormulaUsingDataSeriesVector = null;
        }

        // Act
        this.sut.updateFormulas();

        // Assert
        assertThat(this.sut.getFormulas().size(), is(equalTo(formulaSamples)));
        assertThat(this.sut.getDataSeries().size(), is(equalTo(dataSeriesCount)));
        for (Object formula : sut.getFormulas()) {
            Formula2Stub formulaStub = (Formula2Stub) formula;
            assertFalse(formulaStub.hasAppliedFormula);
        }
    }

    @Test
    public void test_reapplyPreprocessor_always_invokesApplyFormula() throws MathException, NoSuchMethodException, InstantiationException, FormulaException, IllegalAccessException {
        // Arrange
        arrangeForReapplyPreprocessor();

        // Act
        this.sut.reapplyPreprocessor();

        // Assert
        assertThat(sut.getFormulas().size(), is(greaterThan(0)));
        for (Object formula : sut.getFormulas()) {
            Formula2Stub formulaStub = (Formula2Stub) formula;
            assertTrue(formulaStub.hasAppliedFormula);
        }
    }

    // Assert
    @Test(expected = FormulaException.class)
    public void test_reapplyPreprocessor_applyFormulaException_throwsException() throws MathException, NoSuchMethodException, InstantiationException, FormulaException, IllegalAccessException {
        // Arrange
        arrangeForReapplyPreprocessor();
        ((Formula2Stub) sut.getFormula(0)).formulaException = new FormulaException("Failed to apply formula.");

        // Act
        this.sut.reapplyPreprocessor();
    }

    // Assert
    @Test(expected = FormulaException.class)
    public void test_reapplyPreprocessor_applyMathException_throwsException() throws MathException, NoSuchMethodException, InstantiationException, FormulaException, IllegalAccessException {
        // Arrange
        arrangeForReapplyPreprocessor();
        ((Formula2Stub) sut.getFormula(0)).mathException = new MathException("Failed to apply formula.");

        // Act
        this.sut.reapplyPreprocessor();
    }

    // Assert
    @Test(expected = MathException.class)
    public void test_applyPreprocessor_varsCountMismatch_throwsException() throws MathException, NoSuchMethodException, InstantiationException, FormulaException, IllegalAccessException {
        // Arrange
        String inputVariable1 = "inputVar1";
        String inputVariable2 = "inputVar2";
        String inputVariable3 = "inputVar3";
        String inputVariable4 = "inputVar4";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariable1);
        variableNames.addElement(inputVariable2);
        variableNames.addElement(inputVariable3);
        variableNames.addElement(inputVariable4);

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), anyVector(), anyBoolean());

        Vector<DataSeries> inputData = new Vector<>();
        // 1 means dataSeries contains 1 variable only
        DataSeries dataSeries = new DataSeries(anyInteger(), 1);
        dataSeries.setVariableParameters(0, anyString(), inputVariable1, anyString());
        inputData.addElement(dataSeries);

        // 1 means dataSeries contains 1 variable only
        dataSeries = new DataSeries(anyInteger(), 1);
        dataSeries.setVariableParameters(0, anyString(), inputVariable2, anyString());
        inputData.addElement(dataSeries);

        // 1 means dataSeries contains 1 variable only
        dataSeries = new DataSeries(anyInteger(), 1);
        dataSeries.setVariableParameters(0, anyString(), inputVariable3, anyString());
        inputData.addElement(dataSeries);

        // Data series list does not contains variable 4. Hence, variables size is not same and will throw exception.

        // Act
        this.sut.applyPreprocessor(inputData, anyVector());
    }

    @Test
    public void test_applyPreprocessor_variablesCountMatch_setsDataSource() throws MathException, NoSuchMethodException, InstantiationException, FormulaException, IllegalAccessException {
        // Arrange
        Vector<DataSeries> inputData = arrangeForApplyPreprocessor();
        Vector<DataSeries> outputData = new Vector<>();

        // Act
        this.sut.applyPreprocessor(inputData, outputData);

        // Assert
        assertThat(outputData.size(), is(greaterThan(0)));
        for (DataSeries dataSeries : outputData) {
            assertThat(dataSeries.getDataSource(), is(equalTo(this.sut)));
        }
    }

    @Test
    public void test_applyPreprocessor_variablesCountSame_invokesEvent() throws MathException, NoSuchMethodException, InstantiationException, FormulaException, IllegalAccessException {
        // Arrange
        Vector<DataSeries> inputData = arrangeForApplyPreprocessor();

        // Act
        this.sut.applyPreprocessor(inputData, anyVector());

        // Assert
        assertThat(this.sut.getEventListeners().size(), is(greaterThan(0)));
        for (Object listener : sut.getEventListeners()) {
            PreprocessorListener preprocessorListener = (PreprocessorListener) listener;
            verify(preprocessorListener).DataChanged(Matchers.any());
        }
    }

    @Test
    public void test_saveFormulas_always_savesFormulasToFile() throws IOException {
        // Arrange
        File file = createFile();
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");

        Vector<Formula2> formulas = new Vector<>();
        Formula2 formula = createFormula();
        formula.addInput("input1");
        formula.addInput("input2");
        formula.addOutput("output1");
        formulas.addElement(formula);

        formula = createFormula();
        formula.addInput("input3");
        formula.addInput("input4");
        formula.addOutput("output2");
        formulas.addElement(formula);

        this.sut = new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), formulas, anyBoolean());

        // Act
        this.sut.saveFormulasBinary(directory, filename);

        // Assert
        Vector<Formula2> actuals = readFormulas(file.getAbsolutePath());
        assertThat(formulas.size(), is(greaterThan(0)));
        for (int i = 0; i < formulas.size(); i++) {
            Formula2 expected = formulas.get(i);
            Formula2 actual = actuals.get(i);

            assertThat(expected.getInputs().size(), is(greaterThan(0)));
            for (Object input : expected.getInputs()) {
                assertTrue(actual.getInputs().contains(input));
            }

            assertThat(expected.getOutputs().size(), is(greaterThan(0)));
            for (Object output : expected.getOutputs()) {
                assertTrue(actual.getOutputs().contains(output));
            }
        }
    }

    @Test
    public void test_saveFormulas_always_savesContentsToFile() throws IOException {
        // Arrange
        File file = createFile();

        Vector<Formula2> contents = new Vector<>();
        Formula2 formula = createFormula();
        formula.addInput("input1");
        formula.addInput("input2");
        formula.addOutput("output1");
        contents.addElement(formula);

        formula = createFormula();
        formula.addInput("input3");
        formula.addInput("input4");
        formula.addOutput("output2");
        contents.addElement(formula);

        // Act
        this.sut.saveFormulasBinary(null, file.getAbsolutePath(), contents);

        // Assert
        Vector<Formula2> actuals = readFormulas(file.getAbsolutePath());
        assertThat(contents.size(), is(greaterThan(0)));
        for (int i = 0; i < contents.size(); i++) {
            Formula2 expected = contents.get(i);
            Formula2 actual = actuals.get(i);

            assertThat(expected.getInputs().size(), is(greaterThan(0)));
            for (Object input : expected.getInputs()) {
                assertTrue(actual.getInputs().contains(input));
            }

            assertThat(expected.getOutputs().size(), is(greaterThan(0)));
            for (Object output : expected.getOutputs()) {
                assertTrue(actual.getOutputs().contains(output));
            }
        }
    }

    @Test
    public void test_saveFormulasBinary_objNotSerializable_retFalse() throws IOException {
        // Arrange
        File file = createFile();
        Vector contents = new Vector();
        NonSerializableClass obj = new NonSerializableClass();
        contents.addElement(obj);

        // Act & Assert
        this.sut.saveFormulasBinary(null, file.getAbsolutePath(), contents);
    }

    @Test
    public void test_saveFormulasBinaryWithDir_objNotSerializable_retFalse() throws IOException {
        // Arrange
        File file = createFile();
        String filename = file.getName();
        String directory = file.getAbsolutePath().replace(filename, "");
        Vector contents = new Vector();
        NonSerializableClass obj = new NonSerializableClass();
        contents.addElement(obj);

        // Act & Assert
        this.sut.saveFormulasBinary(directory, filename);
    }

    @Test
    public void test_setTimeStamps_dataSeriesFound_updatesTimeStamps() throws MathException {
        // Arrange
        DataSeries dataSeries = new DataSeries(anyInteger(), anyInteger());
        dataSeries.setName("dataSeries1");

        Vector<Variable> variables = new Vector<>();
        Variable variable = createVariable(dataSeries);
        variables.addElement(variable);

        dataSeries.setVariableParameters(0, variable.getTag(), variable.getName(), variable.getUnit());

        this.sut = new Preprocessor(anyString(), createProject(), variables, createViewFilter());

        long[] timeStamps = new long[]{1, 2, 3};
        ((DataSeries) this.sut.getDataSeries().get(0)).setTimeStamps(timeStamps);

        long[] newTimeStamps = new long[]{4, 5, 6};
        DataSeries dataSeries2 = new DataSeries(anyInteger(), anyInteger());
        dataSeries2.setName(dataSeries.getName());
        dataSeries2.setTimeStamps(newTimeStamps);

        // Act
        this.sut.setTimeStamps(dataSeries2);

        // Assert
        DataSeries actual = (DataSeries) this.sut.getDataSeries().get(0);
        assertThat(newTimeStamps.length, is(greaterThan(0)));
        for (int i = 0; i < newTimeStamps.length; i++) {
            assertThat(actual.getTimeStamps()[i], is(equalTo(newTimeStamps[i])));
        }
    }

    @Test
    public void test_setTimeStamps_dataSeriesNotFound_keepsOldTimeStamps() throws MathException {
        // Arrange
        DataSeries dataSeries = new DataSeries(anyInteger(), anyInteger());
        dataSeries.setName("dataSeries1");

        Vector<Variable> variables = new Vector<>();
        Variable variable = createVariable(dataSeries);
        variables.addElement(variable);

        dataSeries.setVariableParameters(0, variable.getTag(), variable.getName(), variable.getUnit());

        this.sut = new Preprocessor(anyString(), createProject(), variables, createViewFilter());

        long[] timeStamps = new long[]{1, 2, 3};
        ((DataSeries) this.sut.getDataSeries().get(0)).setTimeStamps(timeStamps);

        // Act
        this.sut.setTimeStamps(anyDataSeries());

        // Assert
        DataSeries actual = (DataSeries) this.sut.getDataSeries().get(0);
        assertThat(timeStamps.length, is(greaterThan(0)));
        for (int i = 0; i < timeStamps.length; i++) {
            assertThat(actual.getTimeStamps()[i], is(equalTo(timeStamps[i])));
        }
    }

    @Test
    public void test_getInputNamesDerivedVarsFormulasForModel_always_setVars() {
        // Arrange
        String inputVariableInModel1 = "inVar1";
        String inputVariableInModel2 = "inVar2";
        String inputVariableNotInModel1 = "inVar3";
        String inputVariableNotInModel2 = "inVar4";

        String outputVariableInModel1 = "outVar1";
        String outputVariableInModel2 = "outVar2";
        String outputVariableNotInModel1 = "outVar3";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariableInModel1);
        variableNames.addElement(inputVariableInModel2);
        variableNames.addElement(inputVariableNotInModel1);
        variableNames.addElement(inputVariableNotInModel2);

        Vector<String> derivedNames = new Vector<>();
        derivedNames.addElement(outputVariableInModel1);
        derivedNames.addElement(outputVariableInModel2);
        derivedNames.addElement(outputVariableNotInModel1);

        Vector<Formula2> formulas = new Vector<>();
        Formula2 formulaBeingUsedInModel1 = new Formula2();
        formulaBeingUsedInModel1.addInput(inputVariableInModel1);
        formulaBeingUsedInModel1.addOutput(outputVariableInModel1);
        formulas.addElement(formulaBeingUsedInModel1);

        Formula2 formulaBeingUsedInModel2 = new Formula2();
        formulaBeingUsedInModel2.addInput(inputVariableInModel2);
        formulaBeingUsedInModel2.addOutput(outputVariableInModel2);
        formulas.addElement(formulaBeingUsedInModel2);

        String inputVariable5 = "inVar5";
        Formula2 formulaNotBeingUsedInModel = new Formula2();
        formulaNotBeingUsedInModel.addInput(inputVariable5);
        formulas.addElement(formulaNotBeingUsedInModel);

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), derivedNames, formulas, anyBoolean());

        Vector<String> allVarNamesForModel = new Vector<>();
        allVarNamesForModel.addElement(outputVariableInModel1);
        allVarNamesForModel.addElement(outputVariableInModel2);
        Vector<String> inputNamesForModel = new Vector<>();
        Vector<String> derivedVarNamesForModel = new Vector<>();
        Vector<Formula2> formulasForModel = new Vector<>();

        // Act
        this.sut.getInputNamesDerivedVarsFormulasForModel(allVarNamesForModel, inputNamesForModel, derivedVarNamesForModel, formulasForModel);

        // Assert
        // Input variable names vector should contain all input variables being used in model
        assertTrue(inputNamesForModel.contains(inputVariableInModel1));
        assertTrue(inputNamesForModel.contains(inputVariableInModel2));

        // Input variable names vector should not contain any input variables not being used in model
        assertFalse(inputNamesForModel.contains(inputVariableNotInModel1));
        assertFalse(inputNamesForModel.contains(inputVariableNotInModel2));

        // Derived variable names vector should contain all derived variables being used in model
        assertTrue(derivedVarNamesForModel.contains(outputVariableInModel1));
        assertTrue(derivedVarNamesForModel.contains(outputVariableInModel2));

        // Derived variable names vector should not contain any derived variables not being used in model
        assertFalse(derivedVarNamesForModel.contains(outputVariableNotInModel1));

        // Formulas vector should contain all formulas being used in model
        assertTrue(formulasForModel.contains(formulaBeingUsedInModel1));
        assertTrue(formulasForModel.contains(formulaBeingUsedInModel2));

        // Formulas vector should not contain any formula not being used in model
        assertFalse(formulasForModel.contains(formulaNotBeingUsedInModel));
    }

    @Test
    public void test_resampleData_always_resamplesData() {
        // Arrange
        Vector<DataSeries> dataSeriesList = new Vector<>();

        DataSeries dataSeries = mock(DataSeries.class);
        dataSeriesList.addElement(dataSeries);

        dataSeries = mock(DataSeries.class);
        dataSeriesList.addElement(dataSeries);

        this.sut.setDataSeries(dataSeriesList);

        long startTime = System.currentTimeMillis();
        long interval = 1000; // 1 second
        long endTime = startTime + interval;

        // Act
        this.sut.resampleData(startTime, endTime, interval);

        // Assert
        assertThat(this.sut.getDataSeries().size(), is(greaterThan(0)));
        for (Object ds : this.sut.getDataSeries()) {
            verify((DataSeries)ds).resampleData(startTime, endTime, interval);
        }
    }

    @Test
    public void test_resampleDataByIndex_indexBelowLowerBound_noDataResample() {
        // Arrange
        Vector<DataSeries> dataSeriesList = new Vector<>();

        DataSeries dataSeries = mock(DataSeries.class);
        dataSeriesList.addElement(dataSeries);

        dataSeries = mock(DataSeries.class);
        dataSeriesList.addElement(dataSeries);

        this.sut.setDataSeries(dataSeriesList);

        long startTime = System.currentTimeMillis();
        long interval = 1000; // 1 second
        long endTime = startTime + interval;

        // Act
        this.sut.resampleData(startTime, endTime, interval, -1);

        // Assert
        assertThat(this.sut.getDataSeries().size(), is(greaterThan(0)));
        for (Object ds : this.sut.getDataSeries()) {
            verify((DataSeries)ds, never()).resampleData(startTime, endTime, interval);
        }
    }

    @Test
    public void test_resampleDataByIndex_indexAboveUpperBound_noDataResample() {
        // Arrange
        Vector<DataSeries> dataSeriesList = new Vector<>();

        DataSeries dataSeries = mock(DataSeries.class);
        dataSeriesList.addElement(dataSeries);

        dataSeries = mock(DataSeries.class);
        dataSeriesList.addElement(dataSeries);

        this.sut.setDataSeries(dataSeriesList);

        long startTime = System.currentTimeMillis();
        long interval = 1000; // 1 second
        long endTime = startTime + interval;

        // Act
        this.sut.resampleData(startTime, endTime, interval, sut.getDataSeries().size());

        // Assert
        assertThat(this.sut.getDataSeries().size(), is(greaterThan(0)));
        for (Object ds : this.sut.getDataSeries()) {
            verify((DataSeries)ds, never()).resampleData(startTime, endTime, interval);
        }
    }

    @Test
    public void test_resampleDataByIndex_indexWithinBounds_resamplesData() {
        // Arrange
        Vector<DataSeries> dataSeriesList = new Vector<>();

        DataSeries dataSeries = mock(DataSeries.class);
        dataSeriesList.addElement(dataSeries);

        dataSeries = mock(DataSeries.class);
        dataSeriesList.addElement(dataSeries);

        this.sut.setDataSeries(dataSeriesList);

        long startTime = System.currentTimeMillis();
        long interval = 1000; // 1 second
        long endTime = startTime + interval;

        // Act
        this.sut.resampleData(startTime, endTime, interval, 0);

        // Assert
        assertThat(this.sut.getDataSeries().size(), is(greaterThan(0)));
        verify(this.sut.getDataSeries(0)).resampleData(startTime, endTime, interval);
        verify(this.sut.getDataSeries(1), never()).resampleData(startTime, endTime, interval);
    }

    private void addEventListeners(Preprocessor preprocessor) {
        preprocessor.addListener(createPreprocessorListener());
        preprocessor.addListener(createPreprocessorListener());
        preprocessor.addListener(createPreprocessorListener());
    }

    private boolean anyBoolean() {
        return false;
    }

    private DataSeries anyDataSeries() {
        return new DataSeries();
    }

    private int anyInteger() {
        // Random integer between 1 and 5.
        return randomGenerator.nextInt(5) + 1;
    }

    private String anyString() {
        return "Any String";
    }

    private Vector anyVector() {
        return new Vector();
    }

    private Vector<Formula2> arrangeForMoveFormula() {
        String inputVariable1 = "inputVar1";
        String inputVariable2 = "inputVar2";
        String inputVariable3 = "inputVar3";
        String inputVariable4 = "inputVar4";
        String inputVariable5 = "inputVar5";
        String inputVariable6 = "inputVar6";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariable1);
        variableNames.addElement(inputVariable2);
        variableNames.addElement(inputVariable3);
        variableNames.addElement(inputVariable4);
        variableNames.addElement(inputVariable5);
        variableNames.addElement(inputVariable6);

        Vector<Formula2> formulas = new Vector<>();
        Formula2 formula1 = new Formula2();
        formula1.addInput(inputVariable1);
        formula1.addInput(inputVariable2);
        formula1.addOutput("outVar1");
        formulas.addElement(formula1);

        Formula2 formula2 = new Formula2();
        formula2.addInput(inputVariable3);
        formula2.addInput(inputVariable4);
        formula2.addOutput("outVar2");
        formulas.addElement(formula2);

        Formula2 formula3 = new Formula2();
        formula3.addInput(inputVariable5);
        formula3.addInput(inputVariable6);
        formula3.addOutput("outVar3");
        formulas.addElement(formula3);

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), formulas, anyBoolean());
        return formulas;
    }

    private Vector<DataSeries> arrangeForApplyPreprocessor() throws MathException {
        String inputVariable1 = "inputVar1";
        String inputVariable2 = "inputVar2";
        String inputVariable3 = "inputVar3";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement(inputVariable1);
        variableNames.addElement(inputVariable2);
        variableNames.addElement(inputVariable3);

        this.sut = new Preprocessor(anyString(), anyString(), variableNames, anyVector(), anyVector(), anyVector(), anyBoolean());
        addEventListeners(this.sut);

        Vector<DataSeries> inputData = new Vector<>();

        // 1 means dataSeries contains 1 variable only
        DataSeries dataSeries = new DataSeries(anyInteger(), 1);
        DataSeries dataSeriesSpy = spy(dataSeries);
        Variable variable = dataSeries.getVarByIndex(0);
        variable.setName(inputVariable1);
        variable.setDataSeries(dataSeriesSpy);
        inputData.addElement(dataSeriesSpy);

        // 1 means dataSeries contains 1 variable only
        dataSeries = new DataSeries(anyInteger(), 1);
        dataSeriesSpy = spy(dataSeries);
        variable = dataSeries.getVarByIndex(0);
        variable.setName(inputVariable2);
        variable.setDataSeries(dataSeriesSpy);
        inputData.addElement(dataSeriesSpy);

        // 1 means dataSeries contains 1 variable only
        dataSeries = new DataSeries(anyInteger(), 1);
        dataSeriesSpy = spy(dataSeries);
        variable = dataSeries.getVarByIndex(0);
        variable.setName(inputVariable3);
        variable.setDataSeries(dataSeriesSpy);
        inputData.addElement(dataSeriesSpy);

        return inputData;
    }

    private void arrangeForReapplyPreprocessor() throws MathException {
        int dataSeriesVariablesCount = 2;

        Vector<DataSeries> dataSeriesList = new Vector<>();
        DataSeries dataSeries1 = createDataSeries(anyInteger(), dataSeriesVariablesCount);
        dataSeries1.setName("dataSeries1Name");
        dataSeriesList.addElement(dataSeries1);

        DataSeries dataSeries2 = createDataSeries(anyInteger(), dataSeriesVariablesCount);
        dataSeries2.setName("dataSeries2Name");
        dataSeriesList.addElement(dataSeries2);

        // Creating two variables for data series 1
        Variable variable1 = createVariable(dataSeries1, 1);
        Variable variable2 = createVariable(dataSeries1, 2);
        dataSeries1.setVariableParameters(0, variable1.getTag(), variable1.getName(), variable1.getUnit());
        dataSeries1.setVariableParameters(1, variable2.getTag(), variable2.getName(), variable2.getUnit());

        // Creating two variables for data series 2
        Variable variable3 = createVariable(dataSeries2, 3);
        Variable variable4 = createVariable(dataSeries2, 4);
        dataSeries2.setVariableParameters(0, variable3.getTag(), variable3.getName(), variable3.getUnit());
        dataSeries2.setVariableParameters(1, variable4.getTag(), variable4.getName(), variable4.getUnit());

        // Adding all the variables to variables list
        Vector<Variable> variables = new Vector<>();
        variables.addElement(variable1);
        variables.addElement(variable2);
        variables.addElement(variable3);
        variables.addElement(variable4);

        // Creating data series list in project raw data source.
        Project project = createProject();
        RawDataSource dataSource = project.getRawDataSource();

        Vector<DataSeries> dataSourceDataSeriesList = new Vector<>();
        DataSeries dataSourceDataSeries1 = createDataSeries(dataSeries1.getRow(), dataSeriesVariablesCount);
        dataSourceDataSeries1.setName(dataSeries1.getName());
        dataSourceDataSeriesList.addElement(dataSourceDataSeries1);

        DataSeries dataSourceDataSeries2 = createDataSeries(dataSeries2.getRow(), dataSeriesVariablesCount);
        dataSourceDataSeries2.setName(dataSeries2.getName());
        dataSourceDataSeriesList.addElement(dataSourceDataSeries2);

        dataSource.setDataSeries(dataSourceDataSeriesList);

        // Creating two variables for data source data series 1
        Variable dataSourceVariable1 = createVariable(dataSourceDataSeries1, 1);
        Variable dataSourceVariable2 = createVariable(dataSourceDataSeries1, 2);
        dataSourceDataSeries1.setVariableParameters(0, dataSourceVariable1.getTag(), dataSourceVariable1.getName(), dataSourceVariable1.getUnit());
        dataSourceDataSeries1.setVariableParameters(1, dataSourceVariable2.getTag(), dataSourceVariable2.getName(), dataSourceVariable2.getUnit());

        // Creating two variables for data source data series 2
        Variable dataSourceVariable3 = createVariable(dataSourceDataSeries2, 3);
        Variable dataSourceVariable4 = createVariable(dataSourceDataSeries2, 4);
        dataSourceDataSeries2.setVariableParameters(0, dataSourceVariable3.getTag(), dataSourceVariable3.getName(), dataSourceVariable3.getUnit());
        dataSourceDataSeries2.setVariableParameters(1, dataSourceVariable4.getTag(), dataSourceVariable4.getName(), dataSourceVariable4.getUnit());

        this.sut = new Preprocessor(anyString(), project, variables, createViewFilter());
        this.sut.setDataSeries(dataSeriesList);

        int formulaSamples = 2;
        for (int i = 0; i < formulaSamples; i++) {
            Formula2Stub formula = new Formula2Stub();
            this.sut.addFormula(formula);
        }
    }

    private void cleanUpStreams() {
        System.setErr(null);
        System.setOut(null);
    }

    private DataSeries createDataSeries(int rows, int cols) throws MathException {
        return new DataSeries(rows, cols);
    }

    private File createFile() throws IOException {
        File file = temporaryFolder.newFile();
        files.addElement(file);
        return file;
    }

    private Formula2 createFormula() {
        Formula2 formula = new Formula2();
        formula.setInputs(new Vector());
        formula.setOutputs(new Vector());
        return formula;
    }

    private FunctionInterface createFunction(int number) {
        return new FunctionInterfaceStub(number);
    }

    private File createObjectFile(Object object) throws IOException {
        File file = temporaryFolder.newFile();
        FileOutputStream fos = null;
        GZIPOutputStream gzos = null;
        ObjectOutputStream out = null;

        try {
            fos = new FileOutputStream(file);
            gzos = new GZIPOutputStream(fos);
            out = new ObjectOutputStream(gzos);

            out.writeObject(object);
        } catch (Exception e) {
            fail("Failed to create formulas file.");
        } finally {
            if (out != null) {
                out.close();
            } else if (gzos != null) {
                gzos.close();
            } else if (fos != null) {
                fos.close();
            }
        }

        files.addElement(file);
        return file;
    }

    private PreprocessorListener createPreprocessorListener() {
        return mock(PreprocessorListener.class);
    }

    private Preprocessor createPreprocessor() {
        String name = "PreprocessorName";
        String comment = "PreprocessorComment";

        Vector<String> variableNames = new Vector<>();
        variableNames.addElement("inputVarName1");
        variableNames.addElement("inputVarName2");
        variableNames.addElement("inputVarName3");

        Vector<String> variableTags = new Vector<>();
        variableTags.addElement("inputVarTag1");
        variableTags.addElement("inputVarTag2");
        variableTags.addElement("inputVarTag3");

        Vector<String> derivedVarNames = new Vector<>();
        derivedVarNames.addElement("derivedVarName1");
        derivedVarNames.addElement("derivedVarName2");
        derivedVarNames.addElement("derivedVarName3");

        Vector<Formula2> formulas = new Vector<>();
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());
        formulas.addElement(createFormula());

        return new Preprocessor(name, comment, variableNames, variableTags, derivedVarNames, formulas, anyBoolean());
    }

    private Preprocessor createPreprocessor(boolean hasTimeStamps) {
        return new Preprocessor(anyString(), anyString(), anyVector(), anyVector(), anyVector(), anyVector(), hasTimeStamps);
    }

    private Preprocessor createPreprocessor(ViewFilter viewFilter) throws MathException {
        DataSeries dataSeries = new DataSeries();

        Vector<Variable> variables = new Vector<>();
        Variable variable = createVariable(dataSeries);
        variables.addElement(variable);

        return new Preprocessor(anyString(), createProject(), variables, viewFilter);
    }

    private Project createProject() {
        Project project = new Project();
        project.setRawDataSource(new RawDataSource());
        return project;
    }

    private Variable createVariable(DataSeries dataSeries) {
        return createVariable(dataSeries, 1);
    }

    private Variable createVariable(DataSeries dataSeries, int number) {
        Variable variable = new Variable();

        variable.setName("VariableName" + number);
        variable.setTag("VariableTag" + number);
        variable.setUnit("VariableUnit" + number);
        variable.setDataSeries(dataSeries);

        Variable variableSpy = spy(variable);
        when(variableSpy.getDataSeries()).thenCallRealMethod();

        return variableSpy;
    }

    private ViewFilter createViewFilter() {
        return mock(ViewFilter.class);
    }

    private Vector<Formula2> readFormulas(String path) throws IOException {
        FileInputStream fis = null;
        GZIPInputStream gzis = null;
        ObjectInputStream ois = null;
        Vector<Formula2> formulas = null;

        try {
            fis = new FileInputStream(path);
            gzis = new GZIPInputStream(fis);
            ois = new ObjectInputStream(gzis);

            formulas = (Vector<Formula2>) ois.readObject();
        } catch (Exception ex) {
            fail("Failed to read formula contents.");
        } finally {
            if (ois != null) {
                ois.close();
            } else if (gzis != null) {
                gzis.close();
            } else if (fis != null) {
                fis.close();
            }
        }

        return formulas;
    }

    private void setupStreams() {
        System.setOut(new PrintStream(outContent));
        System.setErr(new PrintStream(errContent));
    }

    private class Formula2Stub extends Formula2 {
        private boolean hasAppliedFormula = false;
        private Vector appliedFormulaUsingDataSeriesVector = null;
        private FormulaException formulaException = null;
        private MathException mathException = null;

        @Override
        public void applyFormula(Vector dataSeriesVector) throws MathException, FormulaException {
            if (formulaException != null) {
                throw formulaException;
            } else if (mathException != null) {
                throw mathException;
            }

            hasAppliedFormula = true;
            appliedFormulaUsingDataSeriesVector = dataSeriesVector;
        }
    }

    private class NonSerializableClass {
    }
}
