package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.reflect.Field;
import java.util.Scanner;
import java.util.Vector;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;

import com.gensym.math.datafit.ArchitectureParameters;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.datafit.TrainableModel;

public class NolGenOptimizationTest {
	private static final double DELTA = 0.1;

	private final double anyDouble = 0;
	private final int anyInt = 0;
	private final String anyString = "";

	private Constraint constraint;
	private File tempDirectory;
	private NolGenOptimization sut;
	private Objective objective;
	private String directory;
	private Vector<Variable> objectiveInnerVariables;
	private Vector<Variable> variables;

	@Rule
	public TemporaryFolder temporaryFolder = new TemporaryFolder();

	@Before
	public void setup() {
		constraint = new Constraint();
		objective = new Objective();
		objectiveInnerVariables = new Vector<Variable>();
		variables = new Vector();

		sut = new NolGenOptimization();
	}

	@Test
	public void test_ConstructorWithName_Always_CreatesOptimizationWithName() {
		// Arrange
		String name = "Nol Optmization Name";

		// Act
		sut = new NolGenOptimization(name);

		// Assert
		assertEquals(name, sut.getName());
	}

	@Test
	public void test_Comment_Always_ValueIsPersisted() {
		// Arrange
		String comment = "Nol Gen Optimization Comment";
		sut.setComment(comment);

		// Act & Assert
		assertEquals(comment, sut.getComment());
	}

	@Test
	public void test_Name_Always_ValueIsPersisted() {
		// Arrange
		String name = "Nol Gen Optimization Name";
		sut.setName(name);

		// Act & Assert
		assertEquals(name, sut.getName());
	}

	@Test
	public void test_ObjSen_Always_ValueIsPersisted() {
		// Arrange
		int objSen = 101;
		sut.setObjSen(objSen);

		// Act & Assert
		assertEquals(objSen, sut.getObjSen());
	}

	@Test
	public void test_StatusFlag_Always_ReturnsStatusFlag() {
		// Arrange
		// No arrangements

		// Act & Assert
		assertEquals(0, sut.getStatusFlag());
	}

	@Test
	public void test_StatusMessage_Always_ReturnsStatusMessage() {
		// Arrange
		// No arrangements

		// Act & Assert
		assertEquals("", sut.getStatusMessage());
	}

	@Test
	public void test_toString_Always_ReturnsOptimizationName() {
		// Arrange
		String name = "Nol Optimization Name";
		sut.setName(name);

		// Act & Assert
		assertEquals(name, sut.toString());
	}

	@Test
	public void test_Objective_Always_ValueIsPersisted() {
		// Arrange
		sut.setObjective(objective);

		// Act & Assert
		assertEquals(objective, sut.getObjective());
	}

	@Test
	public void test_addConstraint_Always_AddsContraintToOptimizationProblem() {
		// Arrange
		constraint.setName("Constraint 1");

		// Act
		sut.addConstraint(constraint);

		// Assert
		assertTrue(sut.getConstraints().contains(constraint));
	}

	@Test
	public void test_removeConstraint_ConstraintExists_RemovesContraintFromOptimizationProblem() {
		// Arrange
		Constraint constraint1, constraint2, constraint3;
		sut.addConstraint(constraint1 = new Constraint(anyInt, "Constraint 1", anyString, anyDouble));
		sut.addConstraint(constraint2 = new Constraint(anyInt, "Constraint 2", anyString, anyDouble));
		sut.addConstraint(constraint3 = new Constraint(anyInt, "Constraint 3", anyString, anyDouble));

		// Act
		sut.removeConstraint(constraint2);

		// Assert
		assertEquals(2, sut.getConstraints().size());
		assertTrue(sut.getConstraints().contains(constraint1));
		assertFalse(sut.getConstraints().contains(constraint2));
		assertTrue(sut.getConstraints().contains(constraint3));
	}

	// Assert
	@Test
	public void test_removeConstraint_ConstraintDoesNotExist_DoesNotThrowException() {
		// Arrange
		Constraint constraint1, constraint2, constraint3;
		sut.addConstraint(constraint1 = new Constraint(anyInt, "Constraint 1", anyString, anyDouble));
		constraint2 = new Constraint();
		sut.addConstraint(constraint3 = new Constraint(anyInt, "Constraint 3", anyString, anyDouble));

		// Act
		sut.removeConstraint(constraint2);

		// Assert
		assertEquals(2, sut.getConstraints().size());
		assertTrue(sut.getConstraints().contains(constraint1));
		assertTrue(sut.getConstraints().contains(constraint3));
	}

	@Test
	public void test_addVariable_Always_AddsVariableToOptimizationProblem() {
		// Arrange
		Variable variable = new Variable();

		// Act
		sut.addVariable(variable);

		// Assert
		assertTrue(sut.getVariables().contains(variable));
	}

	@Test
	public void test_removeVariable_VariableExists_RemovesVariableFromOptimizationProblem() {
		// Arrange
		Variable variable1, variable2, variable3;
		sut.addVariable(variable1 = new Variable());
		sut.addVariable(variable2 = new Variable());
		sut.addVariable(variable3 = new Variable());

		// Act
		sut.removeVariable(variable2);

		// Assert
		assertEquals(2, sut.getVariables().size());
		assertTrue(sut.getVariables().contains(variable1));
		assertFalse(sut.getVariables().contains(variable2));
		assertTrue(sut.getVariables().contains(variable3));
	}

	@Test
	public void test_removeVariable_VariableDoesNotExist_DoesNotThrowException() {
		// Arrange
		Variable variable1, variable2, variable3;
		sut.addVariable(variable1 = new Variable());
		variable2 = new Variable();
		sut.addVariable(variable3 = new Variable());

		// Act
		sut.removeVariable(variable2);

		// Assert
		assertEquals(2, sut.getVariables().size());
		assertTrue(sut.getVariables().contains(variable1));
		assertTrue(sut.getVariables().contains(variable3));
	}

	@Test
	public void test_setVariables_Always_SetsVariablesInOptimizationProblem() {
		// Arrange
		Vector<Variable> variables = new Vector<Variable>();
		Variable variable = new Variable();
		variable.setName("variable1Name");
		variables.addElement(variable);

		// Act
		sut.setVariables(variables);

		// Assert
		assertTrue(sut.getVariables().containsAll(variables));
	}

	@Test
	public void test_addModel_Always_AddsModelToOptimizationProblem() {
		// Arrange
		NolModel2 model = new NolModel2();
		model.setName("nolModel1Name");

		// Act
		sut.addModel(model);

		// Assert
		assertTrue(sut.getModels().contains(model));
	}

	@Test
	public void test_setModels_Always_SetsModelsFromOptimizationProblem() {
		// Arrange
		Vector<NolModel2> models = new Vector<NolModel2>();
		NolModel2 model = new NolModel2();
		model.setName("nolModel1Name");
		models.addElement(model);

		// Act
		sut.setModels(models);

		// Assert
		assertTrue(sut.getModels().containsAll(models));
	}

	@Test
	public void test_getSense_VectorHasConstraints_ReturnsSumOfAllConstraintsSense() {
		// Arrange
		Constraint constraint1 = new Constraint(anyInt, anyString, "A", anyDouble);
		Constraint constraint2 = new Constraint(anyInt, anyString, "B", anyDouble);
		Constraint constraint3 = new Constraint(anyInt, anyString, "C", anyDouble);
		Vector<Constraint> constrains = new Vector<Constraint>();
		constrains.addElement(constraint1);
		constrains.addElement(constraint2);
		constrains.addElement(constraint3);

		// Act
		String result = sut.getSense(constrains);

		// Assert
		assertEquals("ABC", result);
	}

	@Test
	public void test_getSense_VectorIsEmpty_ReturnsEmptyString() {
		// Arrange
		Vector<Constraint> constrains = new Vector<Constraint>();

		// Act
		String result = sut.getSense(constrains);

		// Assert
		assertEquals("", result);
	}

	@Test
	public void test_getCContent_Always_ContentContainsIncludes() {
		// Arrange
		arrangeForGetCContent(true);

		// Act & Assert
		validateStringContainsIncludes(sut.getCContent());
	}

	@Test
	public void test_getCContent_Always_ContentContainsFuncEval() {
		// Arrange
		arrangeForGetCContent(true);

		// Act & Assert
		validateStringContainsFuncEval(sut.getCContent());
	}

	@Test
	public void test_getCContent_Always_ContentContainsJacobianSyn() {
		// Arrange
		arrangeForGetCContent(true);

		// Act
		String result = sut.getCContent();

		// Assert
		assertTrue(result.contains(ProblemFixedContent.getJacobianSyn()));
	}

	@Test
	public void test_getCContent_Always_ContentContainsSolvenlpSyn() {
		// Arrange
		arrangeForGetCContent(true);

		// Act & Assert
		validateStringContainsSolvenlpSyn(sut.getCContent());
	}

	@Test
	public void test_getCContent_ThereAreNoConstraints_ContentContainsSolvenlpSyn() {
		// Arrange
		arrangeForGetCContent(false);

		// Act & Assert
		validateStringContainsSolvenlpSyn(sut.getCContent());
	}

	@Test
	public void test_getCContent_Always_ContentContainsJsolveNLPSyn() {
		// Arrange
		arrangeForGetCContent(true);

		// Act & Assert
		validateStringContainsJsolveNLPSyn(sut.getCContent());
	}

	@Test
	public void test_writeToFile_Always_ContentContainsIncludes() throws IOException, NoSuchFieldException,
			SecurityException, IllegalArgumentException, IllegalAccessException {
		// Arrange
		arrangeForWriteToFile(true);

		// Act
		sut.writeToFile(directory);

		// Assert
		String content = getOptProbFileContent(directory);
		validateStringContainsIncludes(content);
	}

	@Test
	public void test_writeToFile_Always_ContentContainsFuncEval() throws IOException, NoSuchFieldException,
			SecurityException, IllegalArgumentException, IllegalAccessException {
		// Arrange
		arrangeForWriteToFile(true);

		// Act
		sut.writeToFile(directory);

		// Assert
		String content = getOptProbFileContent(directory);
		validateStringContainsFuncEval(content);
	}

	@Test
	public void test_writeToFile_Always_ContentContainsJacobianSyn() throws IOException, NoSuchFieldException,
			SecurityException, IllegalArgumentException, IllegalAccessException {
		// Arrange
		arrangeForWriteToFile(true);

		// Act
		sut.writeToFile(directory);

		// Assert
		String content = getOptProbFileContent(directory);
		assertTrue(content.contains(ProblemFixedContent.getJacobianSyn()));
	}

	@Test
	public void test_writeToFile_Always_ContentContainsSolvenlpSyn() throws IOException, NoSuchFieldException,
			SecurityException, IllegalArgumentException, IllegalAccessException {
		// Arrange
		arrangeForWriteToFile(true);

		// Act
		sut.writeToFile(directory);

		// Assert
		String content = getOptProbFileContent(directory);
		validateStringContainsSolvenlpSyn(content);
	}

	@Test
	public void test_writeToFile_ThereAreNoConstraints_ContentContainsSolvenlpSyn() throws IOException,
			NoSuchFieldException, SecurityException, IllegalArgumentException, IllegalAccessException {
		// Arrange
		arrangeForWriteToFile(false);

		// Act
		sut.writeToFile(directory);

		// Assert
		String content = getOptProbFileContent(directory);
		validateStringContainsSolvenlpSyn(content);
	}

	@Test
	public void test_writeToFile_Always_ContentContainsJsolveNLPSyn() throws IOException, NoSuchFieldException,
			SecurityException, IllegalArgumentException, IllegalAccessException {
		// Arrange
		arrangeForWriteToFile(true);

		// Act
		sut.writeToFile(directory);

		// Assert
		String content = getOptProbFileContent(directory);
		validateStringContainsJsolveNLPSyn(content);
	}

	@Test
	public void test_writeToFile_Always_AddsIncludesToModelsSourceFile() throws IOException, NoSuchFieldException,
			SecurityException, IllegalArgumentException, IllegalAccessException {
		// Arrange
		arrangeForWriteToFile(false);

		// Act
		sut.writeToFile(directory);

		// Assert
		String content = getModelsSourceContents(directory);
		validateStringContainsModelSourceIncludes(content);
	}

	@Test
	public void test_writeToFile_Always_AddsModelContentsToModelsSourceFile() throws IOException, NoSuchFieldException,
			SecurityException, IllegalArgumentException, IllegalAccessException {
		// Arrange
		arrangeForWriteToFile(false);

		// Act
		sut.writeToFile(directory);

		// Assert
		String content = getModelsSourceContents(directory);
		validateStringContainsModelContents(content);
	}

	@Test
	public void test_writeToFile_Always_AddsIncludesToModelsHeaderFile() throws IOException, NoSuchFieldException,
			SecurityException, IllegalArgumentException, IllegalAccessException {
		// Arrange
		arrangeForWriteToFile(false);

		// Act
		sut.writeToFile(directory);

		// Assert
		String content = getModelsHeaderContents(directory);
		validateStringContainsModelHeaderIncludes(content);
	}

	@Test
	public void test_writeToFile_Always_AddsModelHeaderContentsToModelsHeaderFile() throws IOException,
			NoSuchFieldException, SecurityException, IllegalArgumentException, IllegalAccessException {
		// Arrange
		arrangeForWriteToFile(false);

		// Act
		sut.writeToFile(directory);

		// Assert
		String content = getModelsHeaderContents(directory);
		validateStringContainsModelHeaderContents(content);
	}

	@Test
	public void test_getInits_OptimizationDoesNotHaveVariables_ReturnsEmptyArray() {
		// Arrange
		// No arrangements

		// Act
		double[] result = sut.getInits();

		// Assert
		assertEquals(0, result.length);
	}

	@Test
	public void test_getInits_OptimizationHasVariables_ReturnsIndependentVariablesInitialValue() {
		// Arrange
		arrangeVariables();

		// Act
		double[] result = sut.getInits();

		// Assert
		int i = 0;
		for (Variable var : (Vector<Variable>) sut.getVariables()) {
			if (var.getDependencyFlag() == 0) {
				assertEquals(var.getInitialValue(), result[i++], DELTA);
			}
		}
	}

	@Test
	public void test_getExogenousValues_OptimizationDoesNotHaveVariables_ReturnsEmptyArray() {
		// Arrange
		// No arrangements

		// Act
		double[] result = sut.getExogenousValues();

		// Assert
		assertEquals(0, result.length);
	}

	@Test
	public void test_getExogenousValues_OptimizationHasVariables_ReturnsExogenousVariablesInitialValue() {
		// Arrange
		arrangeVariables();

		// Act
		double[] result = sut.getExogenousValues();

		// Assert
		int i = 0;
		for (Variable var : (Vector<Variable>) sut.getVariables()) {
			if (var.getDependencyFlag() != 0) {
				assertEquals(var.getInitialValue(), result[i++], DELTA);
			}
		}
	}

	@Test
	public void test_getIndependentUpperBounds_OptimizationDoesNotHaveVariables_ReturnsEmptyArray() {
		// Arrange
		// No arrangements

		// Act
		double[] result = sut.getIndependentUpperBounds();

		// Assert
		assertEquals(0, result.length);
	}

	@Test
	public void test_getIndependentUpperBounds_OptimizationHasVariables_ReturnsIndependentVariablesHardUpperBound() {
		// Arrange
		arrangeVariables();

		// Act
		double[] result = sut.getIndependentUpperBounds();

		// Assert
		int i = 0;
		for (Variable var : (Vector<Variable>) sut.getVariables()) {
			if (var.getDependencyFlag() == 0) {
				assertEquals(var.getHardUpperBound(), result[i++], DELTA);
			}
		}
	}

	@Test
	public void test_getIndependentLowerBounds_OptimizationDoesNotHaveVariables_ReturnsEmptyArray() {
		// Arrange
		// No arrangements

		// Act
		double[] result = sut.getIndependentLowerBounds();

		// Assert
		assertEquals(0, result.length);
	}

	@Test
	public void test_getIndependentLowerBounds_OptimizationHasVariables_ReturnsIndependentVariablesHardLowerBound() {
		// Arrange
		arrangeVariables();

		// Act
		double[] result = sut.getIndependentLowerBounds();

		// Assert
		int i = 0;
		for (Variable var : (Vector<Variable>) sut.getVariables()) {
			if (var.getDependencyFlag() == 0) {
				assertEquals(var.getHardLowerBound(), result[i++], DELTA);
			}
		}
	}

	@Test
	public void test_MaxIteration_Always_ValueIsPersisted() {
		// Arrange
		int maxValue = 9999;
		sut.setMaxIteration(maxValue);

		// Act & Assert
		assertEquals(maxValue, sut.getMaxIteration());
	}

	@Test
	public void test_Calculated_IsSetAsTrue_ReturnsTrue() {
		// Arrange
		sut.setCalculated(true);

		// Act & Assert
		assertTrue(sut.isCalculated());
	}

	@Test
	public void test_Calculated_IsSetAsFalse_ReturnsFalse() {
		// Arrange
		sut.setCalculated(false);

		// Act & Assert
		assertFalse(sut.isCalculated());
	}

	private void arrangeForGetCContent(boolean arrConstraints) {
		if (arrConstraints) {
			arrangeConstraints();
		}

		arrangeObjective();
		arrangeVariables();
	}

	private void arrangeForWriteToFile(boolean arrConstraints) throws IOException, NoSuchFieldException,
			SecurityException, IllegalArgumentException, IllegalAccessException {
		if (arrConstraints) {
			arrangeConstraints();
		}

		arrangeObjective();
		arrangeVariables();
		arrangeUsedModels();
		arrangeTemporaryDirectory();
	}

	private void arrangeConstraints() {
		// Adding more than 1 constraints and variables in each constraints
		// to verify system functionality.
		int constraintsCount = 3;
		int constraintVariablesCount = 3;
		for (int i = 0; i < constraintsCount; i++) {
			constraint = new Constraint();

			Variable variable;
			for (int j = 0; j < constraintVariablesCount; j++) {
				variable = new Variable();
				variable.setName("contraint" + (i + 1) + "InnerVariable" + (j + 1) + "Name");
				constraint.addInnerVariable(variable);
			}

			constraint.setContent("constraint" + (i + 1) + "Content;");
			sut.addConstraint(constraint);
		}
	}

	private void arrangeObjective() {
		// Adding more than 1 objectives to verify system functionality.
		int objectivesCount = 3;
		for (int i = 0; i < objectivesCount; i++) {
			Variable variable = new Variable();
			variable.setName("objectiveInnerVariable" + (i + 1) + "Name");
			objectiveInnerVariables.addElement(variable);
			objective.addInnerVariable(variable);
		}

		objective.setContent("objectiveContent;");
		sut.setObjective(objective);
	}

	private void arrangeTemporaryDirectory() throws IOException {
		tempDirectory = temporaryFolder.newFolder();
		directory = tempDirectory.getAbsolutePath();
	}

	private void arrangeUsedModels()
			throws NoSuchFieldException, SecurityException, IllegalArgumentException, IllegalAccessException {
		NolModel2 model = createModel();
		sut.addModel(model);
	}

	private void arrangeVariables() {
		// Adding more than 1 independent variables to verify system
		// functionality.
		int independentVariablesCount = 2;
		for (int i = 0; i < independentVariablesCount; i++) {
			Variable variable = new Variable();
			variable.setName("indepVariable" + (i + 1) + ".Name");
			variable.setDependencyFlag(0);
			variable.setInitialValue(Math.random());
			variable.setHardLowerBound(Math.random() * 10);
			variable.setHardUpperBound(Math.random() * 100);
			sut.addVariable(variable);
		}

		// Adding more than 1 dependent variables to verify system
		// functionality.
		int dependentVariablesCount = 2;
		for (int i = 0; i < dependentVariablesCount; i++) {
			Variable variable = new Variable();
			variable.setName("depVariable" + (i + 1) + ".Name");
			variable.setDependencyFlag(1);
			variable.setInitialValue(Math.random());
			variable.setHardLowerBound(Math.random() * 10);
			variable.setHardUpperBound(Math.random() * 100);
			sut.addVariable(variable);
		}
	}

	private NolModel2 createModel()
			throws NoSuchFieldException, SecurityException, IllegalArgumentException, IllegalAccessException {
		Vector<TrainableModel> netModels = new Vector<TrainableModel>();
		netModels.addElement(new TrainableModel(new ArchitectureParameters(0, 0, 0, 0)));
		EnsembleModel net = new EnsembleModel(new ArchitectureParameters(0, 0, 0, 0));
		Field modelsFieldInfo = EnsembleModel.class.getDeclaredField("models");
		modelsFieldInfo.setAccessible(true);
		modelsFieldInfo.set(net, netModels);

		return new NolModel2(net, "model1Name", new Vector(), new Vector(), new Vector(), new Vector(),
				new Preprocessor());
	}

	private String getFileContents(String filename) throws FileNotFoundException {
		return getFileContents(directory, filename);
	}

	private String getFileContents(String dir, String filename) throws FileNotFoundException {
		File file = dir == null ? new File(filename) : new File(dir, filename);
		return file != null ? new Scanner(file).useDelimiter("\\Z").next() : "";
	}

	private String getModelsHeaderContents(String dir) throws FileNotFoundException {
		return getFileContents(dir, "models.h");
	}

	private String getModelsSourceContents(String dir) throws FileNotFoundException {
		return getFileContents(dir, "models.c");
	}

	private String getOptProbFileContent(String dir) throws FileNotFoundException {
		return getFileContents(dir, "OptProb.c");
	}

	private void validateStringContainsIncludes(String result) {
		assertTrue(result.contains(ProblemFixedContent.getIncludes()));
		assertEquals(0, result.indexOf(ProblemFixedContent.getIncludes()));
	}

	private void validateStringContainsFuncEval(String content) {
		assertTrue(content.contains(ProblemFixedContent.getFuncevalSyn()));
		int funcEvalStartIndex = content.indexOf(ProblemFixedContent.getFuncevalSyn());
		int funcEvalEndIndex = content.indexOf("}", funcEvalStartIndex);

		// Validate objective's inner variables are declared.
		assertTrue(content.contains(sut.getObjective().getInternalVarString()));
		assertTrue(content.indexOf(sut.getObjective().getInternalVarString()) > funcEvalStartIndex);
		assertTrue(content.indexOf(sut.getObjective().getInternalVarString()) < funcEvalEndIndex);

		// Validate constraints' inner variables are declared.
		for (Object object : sut.getConstraints()) {
			Constraint cnstraint = (Constraint) object;
			assertTrue(content.contains(cnstraint.getInternalVarString()));
			validateSubStringIsInBetween(content, cnstraint.getInternalVarString(), funcEvalStartIndex,
					funcEvalEndIndex);
		}

		Vector<Variable> sutVariables = sut.getVariables();

		// Validate variables are declared.
		for (Variable var : sutVariables) {
			String expectedStatement = "double " + var.getName().replace(".", "_") + ";";
			assertTrue(content.contains(expectedStatement));
			validateSubStringIsInBetween(content, expectedStatement, funcEvalStartIndex, funcEvalEndIndex);
		}

		// Validate independent variables are initialized
		int i = 0;
		for (Variable var : sutVariables) {
			if (var.getDependencyFlag() == 0) {
				String expectedStatement = "= var[" + i + "];";
				assertTrue(content.contains(expectedStatement));
				validateSubStringIsInBetween(content, expectedStatement, funcEvalStartIndex, funcEvalEndIndex);
			}
		}

		// Validate independent variables are initialized
		i = 0;
		for (Variable var : sutVariables) {
			if (var.getDependencyFlag() == 1) {
				String expectedStatement = var.getName().replace(".", "_") + " = exog" + i++ + ";";
				assertTrue(content.contains(expectedStatement));
				validateSubStringIsInBetween(content, expectedStatement, funcEvalStartIndex, funcEvalEndIndex);
			}
		}

		// Validate objective content is added
		assertTrue(content.contains(sut.getObjective().getContent()));
		validateSubStringIsInBetween(content, sut.getObjective().getContent(), funcEvalStartIndex, funcEvalEndIndex);

		// Validate constraints' content is added
		for (Constraint cnstraint : (Vector<Constraint>) sut.getConstraints()) {
			assertTrue(content.contains(cnstraint.getContentString()));
			validateSubStringIsInBetween(content, cnstraint.getContentString(), funcEvalStartIndex, funcEvalEndIndex);
		}
	}

	private void validateStringContainsModelHeaderIncludes(String content) {
		assertTrue(content.contains("#include <math.h>"));
	}

	private void validateStringContainsModelHeaderContents(String content) {
		Vector<NolModel2> usedModels = sut.getModels();
		for (NolModel2 usedModel : usedModels) {
			assertTrue(content.contains(usedModel.getModelHeader()));
		}
	}

	private void validateStringContainsModelSourceIncludes(String content) {
		assertTrue(content.contains("#include <math.h>"));
		assertTrue(content.contains("#include <stdio.h>"));
		assertTrue(content.contains("#include <stdlib.h>"));
		assertTrue(content.contains("#include <ctype.h>"));
		assertTrue(content.contains("#include \"nnet.h\""));
		assertTrue(content.contains("#include \"models.h\""));
	}

	private void validateStringContainsModelContents(String content) {
		Vector<NolModel2> usedModels = sut.getModels();
		for (NolModel2 usedModel : usedModels) {
			assertTrue(content.contains(usedModel.getModelContents()));
		}
	}

	private void validateStringContainsSolvenlpSyn(String content) {
		int constraintsCount = sut.getConstraints().size();
		assertTrue(content.contains(ProblemFixedContent.getFuncevalSyn()));
		assertTrue(content.contains(ProblemFixedContent.getSolvenlpFinishedContent(constraintsCount, false)));
		int solvenlpSynStartIndex = content.indexOf(ProblemFixedContent.getFuncevalSyn());
		int solvenlpSynEndIndex = content
				.indexOf(ProblemFixedContent.getSolvenlpFinishedContent(constraintsCount, false));

		int independentVariables = 0;
		for (Variable var : (Vector<Variable>) sut.getVariables()) {
			if (var.getDependencyFlag() == 0) {
				independentVariables++;
			}
		}

		validateSubStringIsInBetween(content, "INTARG numcols = " + independentVariables + ";", solvenlpSynStartIndex,
				solvenlpSynEndIndex);
		validateSubStringIsInBetween(content, "INTARG numrows = " + sut.getConstraints().size() + ";",
				solvenlpSynStartIndex, solvenlpSynEndIndex);
		validateSubStringIsInBetween(content, "INTARG objsen = " + sut.getObjSen() + ";", solvenlpSynStartIndex,
				solvenlpSynEndIndex);
		validateSubStringIsInBetween(content, "double obj[" + independentVariables + "];", solvenlpSynStartIndex,
				solvenlpSynEndIndex);

		validateSubStringIsInBetween(content, "LPINTARG matbeg = NULL;", solvenlpSynStartIndex, solvenlpSynEndIndex);
		validateSubStringIsInBetween(content, "LPINTARG matcnt = NULL;", solvenlpSynStartIndex, solvenlpSynEndIndex);
		validateSubStringIsInBetween(content, "HPINTARG matind = NULL;", solvenlpSynStartIndex, solvenlpSynEndIndex);
		validateSubStringIsInBetween(content, "LPREALARG rngval = NULL;", solvenlpSynStartIndex, solvenlpSynEndIndex);
		validateSubStringIsInBetween(content,
				"INTARG nzspace = " + (independentVariables * sut.getConstraints().size()) + ";", solvenlpSynStartIndex,
				solvenlpSynEndIndex);
		validateSubStringIsInBetween(content, "int derivflag = 1;", solvenlpSynStartIndex, solvenlpSynEndIndex);
		validateSubStringIsInBetween(content, "HPROBLEM lp = NULL;", solvenlpSynStartIndex, solvenlpSynEndIndex);

		if (constraintsCount > 0) {
			validateSubStringIsInBetween(content, "double rhs[" + constraintsCount + "];", solvenlpSynStartIndex,
					solvenlpSynEndIndex);
			validateSubStringIsInBetween(content, "double matval[" + (independentVariables * constraintsCount) + "];",
					solvenlpSynStartIndex, solvenlpSynEndIndex);
			validateSubStringIsInBetween(content, "double piout[" + constraintsCount + "], slack[" + constraintsCount
					+ "], dj[" + independentVariables + "];", solvenlpSynStartIndex, solvenlpSynEndIndex);

			String sense = sut.getSense(sut.getConstraints());
			validateSubStringIsInBetween(content, "char sense[" + sense.length() + "] = \"" + sense + "\";",
					solvenlpSynStartIndex, solvenlpSynEndIndex);
		} else {
			validateSubStringIsInBetween(content, "dj[" + independentVariables + "];", solvenlpSynStartIndex,
					solvenlpSynEndIndex);
		}
	}

	private void validateStringContainsJsolveNLPSyn(String content) {
		assertTrue(content.contains(ProblemFixedContent.getJsolveNLPSyn()));
		assertTrue(content.contains(ProblemFixedContent.getJsolveNLPContent()));
	}

	private void validateSubStringIsInBetween(String string, String subString, int startIndex, int endIndex) {
		assertTrue(string.indexOf(subString) > startIndex);
		assertTrue(string.indexOf(subString) < endIndex);
	}
}
