package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import static org.mockito.Mockito.verify;
import static org.powermock.api.mockito.PowerMockito.mock;
import static org.powermock.api.mockito.PowerMockito.when;
import static org.powermock.api.support.membermodification.MemberMatcher.method;
import static org.powermock.api.support.membermodification.MemberModifier.suppress;

import org.junit.Before;
import org.junit.Test;

public class Project2Test {
	private Project2 sut;

	@Before
	public void setup() {
		sut = new Project2();
		suppress(method(Project.class, "initDataTreeForTransientField"));
	}

	@Test
	public void test_constructor_always_nameIsPersisted() {
		// Arrange
		String name = "Project Name";
		sut = new Project2(name);

		// Act & Assert
		assertEquals(name, sut.getName());
	}

	@Test
	public void test_constructor_initializeFromProject_nameIsPersisted() {
		// Arrange
		String name = "Project Name";
		Project project = new Project(name);
		sut = new Project2(project);

		// Act & Assert
		assertEquals(name, sut.getName());
	}

	@Test
	public void test_addBpnModel_modelDoesNotExist_addsModel() {
		// Arrange
		NolBpnModel existingModel = createBpnModel("Existing Model Name");
		NolBpnModel missingModel = createBpnModel("Non Existing Model Name");
		sut.addBpnModel(existingModel);

		// Act
		sut.addBpnModel(missingModel);

		// Assert
		assertTrue(sut.getBpnModels().contains(existingModel));
		assertTrue(sut.getBpnModels().contains(missingModel));
	}

	@Test
	public void test_addBpnModel_modelAlreadyExists_updatesModel() {
		// Arrange
		NolBpnModel oldModel = createBpnModel("Same Model Name");
		sut.addBpnModel(oldModel);
		NolBpnModel newModel = createBpnModel("Same Model Name");

		// Act
		sut.addBpnModel(newModel);

		// Assert
		assertTrue(sut.getBpnModels().contains(newModel));
		assertFalse(sut.getBpnModels().contains(oldModel));
	}

	@Test
	public void test_deleteBpnModel_indexIsOutOfBound_doesNotRemoveAnyModel() {
		// Arrange
		NolBpnModel model = createBpnModel("Model Name");
		sut.addBpnModel(model);

		// Act
		sut.deleteBpnModel(1);

		// Assert
		assertTrue(sut.getBpnModels().contains(model));
	}

	@Test
	public void test_deleteBpnModel_indexIsValid_removesModelFromSpecifiedIndex() {
		// Arrange
		NolBpnModel model1 = createBpnModel("Model 1 Name");
		NolBpnModel model2 = createBpnModel("Model 2 Name");
		NolBpnModel model3 = createBpnModel("Model 3 Name");
		sut.addBpnModel(model1);
		sut.addBpnModel(model2);
		sut.addBpnModel(model3);

		// Act
		sut.deleteBpnModel(1);

		// Assert
		assertTrue(sut.getBpnModels().contains(model1));
		assertFalse(sut.getBpnModels().contains(model2));
		assertTrue(sut.getBpnModels().contains(model3));
	}

	@Test
	public void test_deleteBpnModel_modelIsInvalid_doesNotRemoveAnyModel() {
		// Arrange
		NolBpnModel model1 = createBpnModel("Model 1 Name");
		NolBpnModel model2 = createBpnModel("Model 2 Name");
		NolBpnModel model3 = createBpnModel("Model 3 Name");
		sut.addBpnModel(model1);
		sut.addBpnModel(model2);

		// Act
		sut.deleteBpnModel(model3);

		// Assert
		assertTrue(sut.getBpnModels().contains(model1));
		assertTrue(sut.getBpnModels().contains(model2));
	}

	@Test
	public void test_deleteBpnModel_modelIsValid_removesSpecifiedModel() {
		// Arrange
		NolBpnModel model1 = createBpnModel("Model 1 Name");
		NolBpnModel model2 = createBpnModel("Model 2 Name");
		NolBpnModel model3 = createBpnModel("Model 3 Name");
		sut.addBpnModel(model1);
		sut.addBpnModel(model2);
		sut.addBpnModel(model3);

		// Act
		sut.deleteBpnModel(model3);

		// Assert
		assertTrue(sut.getBpnModels().contains(model1));
		assertTrue(sut.getBpnModels().contains(model2));
		assertFalse(sut.getBpnModels().contains(model3));
	}

	@Test
	public void test_deleteBpnModel_modelIsRemovedMoreThanOnce_removesModelOnceAndIgnoresOtherCalls() {
		// Arrange
		NolBpnModel model1 = createBpnModel("Model 1 Name");
		NolBpnModel model2 = createBpnModel("Model 2 Name");
		NolBpnModel model3 = createBpnModel("Model 3 Name");
		sut.addBpnModel(model1);
		sut.addBpnModel(model2);
		sut.addBpnModel(model3);

		// Act
		sut.deleteBpnModel(model3);
		sut.deleteBpnModel(model3);

		// Assert
		assertTrue(sut.getBpnModels().contains(model1));
		assertTrue(sut.getBpnModels().contains(model2));
		assertFalse(sut.getBpnModels().contains(model3));
	}

	@Test
	public void test_getNumberOfBpnModels_always_returnsNumberOfAddedBpnModels() {
		// Arrange
		NolBpnModel model1 = createBpnModel("Model 1 Name");
		NolBpnModel model2 = createBpnModel("Model 2 Name");
		NolBpnModel model3 = createBpnModel("Model 3 Name");
		sut.addBpnModel(model1);
		sut.addBpnModel(model2);
		sut.addBpnModel(model3);

		// Act & Assert
		assertEquals(3, sut.getNumberOfBpnModels());
	}

	@Test
	public void test_getNumberOfBpnModels_modelsAreAddedAndDeleted_returnsCorrectNumberOfBpnModels() {
		// Arrange
		NolBpnModel model1 = createBpnModel("Model 1 Name");
		NolBpnModel model2 = createBpnModel("Model 2 Name");
		NolBpnModel model3 = createBpnModel("Model 3 Name");
		sut.addBpnModel(model1);
		sut.addBpnModel(model2);
		sut.addBpnModel(model3);
		sut.deleteBpnModel(model1);
		sut.deleteBpnModel(model2);

		// Act & Assert
		assertEquals(1, sut.getNumberOfBpnModels());
	}

	@Test
	public void test_deleteBpnModel_indexIsLessThanZero_doesNotRemoveAnyModel() {
		// Arrange
		NolBpnModel model = createBpnModel("Model Name");
		sut.addBpnModel(model);

		// Act
		sut.deleteBpnModel(-1);

		// Assert
		assertTrue(sut.getBpnModels().contains(model));
	}

	@Test
	public void test_getBpnModelIndexByName_modelExists_ReturnsModelIndex() {
		// Arrange
		NolBpnModel model1 = createBpnModel("Model 1 Name");
		NolBpnModel model2 = createBpnModel("Model 2 Name");
		NolBpnModel model3 = createBpnModel("Model 3 Name");
		sut.addBpnModel(model1);
		sut.addBpnModel(model2);
		sut.addBpnModel(model3);

		// Act & Assert
		assertEquals(0, sut.getBpnModelIndexByName(model1.getName()));
		assertEquals(1, sut.getBpnModelIndexByName(model2.getName()));
		assertEquals(2, sut.getBpnModelIndexByName(model3.getName()));
	}

	@Test
	public void test_getBpnModelIndexByName_modelDoesNotExist_returnsMinusOne() {
		// Arrange
		NolBpnModel existingModel = createBpnModel("Existing Model Name");
		NolBpnModel missingModel = createBpnModel("Missing Model Name");
		sut.addBpnModel(existingModel);

		// Act & Assert
		assertEquals(-1, sut.getBpnModelIndexByName(missingModel.getName()));
	}

	// Assert
	@Test(expected = IndexOutOfBoundsException.class)
	public void test_getBpnModel_indexIsInvalid_throwsIndexOutOfBoundsException() {
		// Arrange
		// No arrangements

		// Act
		sut.getBpnModel(0);
	}

	@Test
	public void test_getBpnModel_indexIsValid_returnsModelOnSpecifiedIndex() {
		// Arrange
		NolBpnModel model1 = createBpnModel("Model 1 Name");
		NolBpnModel model2 = createBpnModel("Model 2 Name");
		NolBpnModel model3 = createBpnModel("Model 3 Name");
		sut.addBpnModel(model1);
		sut.addBpnModel(model2);
		sut.addBpnModel(model3);

		// Act & Assert
		assertEquals(model1, sut.getBpnModel(0));
		assertEquals(model2, sut.getBpnModel(1));
		assertEquals(model3, sut.getBpnModel(2));
	}

	@Test
	public void test_addAnnModel_modelDoesNotExist_addsModel() {
		// Arrange
		NolAnnModel existingModel = createAnnModel("Existing Model Name");
		NolAnnModel missingModel = createAnnModel("Non Existing Model Name");
		sut.addAnnModel(existingModel);

		// Act
		sut.addAnnModel(missingModel);

		// Assert
		assertTrue(sut.getAnnModels().contains(existingModel));
		assertTrue(sut.getAnnModels().contains(missingModel));
	}

	@Test
	public void test_addAnnModel_modelAlreadyExists_updatesModel() {
		// Arrange
		NolAnnModel oldModel = createAnnModel("Same Model Name");
		sut.addAnnModel(oldModel);
		NolAnnModel newModel = createAnnModel("Same Model Name");

		// Act
		sut.addAnnModel(newModel);

		// Assert
		assertTrue(sut.getAnnModels().contains(newModel));
		assertFalse(sut.getAnnModels().contains(oldModel));
	}

	@Test
	public void test_deleteAnnModel_indexIsOutOfBound_doesNotRemoveAnyModel() {
		// Arrange
		NolAnnModel model = createAnnModel("Model Name");
		sut.addAnnModel(model);

		// Act
		sut.deleteAnnModel(1);

		// Assert
		assertTrue(sut.getAnnModels().contains(model));
	}

	@Test
	public void test_deleteAnnModel_indexIsValid_removesModelFromSpecifiedIndex() {
		// Arrange
		NolAnnModel model1 = createAnnModel("Model 1 Name");
		NolAnnModel model2 = createAnnModel("Model 2 Name");
		NolAnnModel model3 = createAnnModel("Model 3 Name");
		sut.addAnnModel(model1);
		sut.addAnnModel(model2);
		sut.addAnnModel(model3);

		// Act
		sut.deleteAnnModel(1);

		// Assert
		assertTrue(sut.getAnnModels().contains(model1));
		assertFalse(sut.getAnnModels().contains(model2));
		assertTrue(sut.getAnnModels().contains(model3));
	}

	@Test
	public void test_deleteAnnModel_modelIsInvalid_doesNotRemoveAnyModel() {
		// Arrange
		NolAnnModel model1 = createAnnModel("Model 1 Name");
		NolAnnModel model2 = createAnnModel("Model 2 Name");
		NolAnnModel model3 = createAnnModel("Model 3 Name");
		sut.addAnnModel(model1);
		sut.addAnnModel(model2);

		// Act
		sut.deleteAnnModel(model3);

		// Assert
		assertTrue(sut.getAnnModels().contains(model1));
		assertTrue(sut.getAnnModels().contains(model2));
	}

	@Test
	public void test_deleteAnnModel_modelIsValid_removesSpecifiedModel() {
		// Arrange
		NolAnnModel model1 = createAnnModel("Model 1 Name");
		NolAnnModel model2 = createAnnModel("Model 2 Name");
		NolAnnModel model3 = createAnnModel("Model 3 Name");
		sut.addAnnModel(model1);
		sut.addAnnModel(model2);
		sut.addAnnModel(model3);

		// Act
		sut.deleteAnnModel(model3);

		// Assert
		assertTrue(sut.getAnnModels().contains(model1));
		assertTrue(sut.getAnnModels().contains(model2));
		assertFalse(sut.getAnnModels().contains(model3));
	}

	@Test
	public void test_deleteAnnModel_modelIsRemovedMoreThanOnce_removesModelOnceAndIgnoresOtherCalls() {
		// Arrange
		NolAnnModel model1 = createAnnModel("Model 1 Name");
		NolAnnModel model2 = createAnnModel("Model 2 Name");
		NolAnnModel model3 = createAnnModel("Model 3 Name");
		sut.addAnnModel(model1);
		sut.addAnnModel(model2);
		sut.addAnnModel(model3);

		// Act
		sut.deleteAnnModel(model3);
		sut.deleteAnnModel(model3);

		// Assert
		assertTrue(sut.getAnnModels().contains(model1));
		assertTrue(sut.getAnnModels().contains(model2));
		assertFalse(sut.getAnnModels().contains(model3));
	}

	@Test
	public void test_getNumberOfAnnModels_always_returnsNumberOfAddedAnnModels() {
		// Arrange
		NolAnnModel model1 = createAnnModel("Model 1 Name");
		NolAnnModel model2 = createAnnModel("Model 2 Name");
		NolAnnModel model3 = createAnnModel("Model 3 Name");
		sut.addAnnModel(model1);
		sut.addAnnModel(model2);
		sut.addAnnModel(model3);

		// Act & Assert
		assertEquals(3, sut.getNumberOfAnnModels());
	}

	@Test
	public void test_getNumberOfAnnModels_modelsAreAddedAndDeleted_returnsCorrectNumberOfAnnModels() {
		// Arrange
		NolAnnModel model1 = createAnnModel("Model 1 Name");
		NolAnnModel model2 = createAnnModel("Model 2 Name");
		NolAnnModel model3 = createAnnModel("Model 3 Name");
		sut.addAnnModel(model1);
		sut.addAnnModel(model2);
		sut.addAnnModel(model3);
		sut.deleteAnnModel(model1);
		sut.deleteAnnModel(model2);

		// Act & Assert
		assertEquals(1, sut.getNumberOfAnnModels());
	}

	@Test
	public void test_deleteAnnModel_indexIsLessThanZero_doesNotRemoveAnyModel() {
		// Arrange
		NolAnnModel model = createAnnModel("Model Name");
		sut.addAnnModel(model);

		// Act
		sut.deleteAnnModel(-1);

		// Assert
		assertTrue(sut.getAnnModels().contains(model));
	}

	@Test
	public void test_getAnnModelIndexByName_modelExists_ReturnsModelIndex() {
		// Arrange
		NolAnnModel model1 = createAnnModel("Model 1 Name");
		NolAnnModel model2 = createAnnModel("Model 2 Name");
		NolAnnModel model3 = createAnnModel("Model 3 Name");
		sut.addAnnModel(model1);
		sut.addAnnModel(model2);
		sut.addAnnModel(model3);

		// Act & Assert
		assertEquals(0, sut.getAnnModelIndexByName(model1.getName()));
		assertEquals(1, sut.getAnnModelIndexByName(model2.getName()));
		assertEquals(2, sut.getAnnModelIndexByName(model3.getName()));
	}

	@Test
	public void test_getAnnModelIndexByName_modelDoesNotExist_returnsMinusOne() {
		// Arrange
		NolAnnModel existingModel = createAnnModel("Existing Model Name");
		NolAnnModel missingModel = createAnnModel("Missing Model Name");
		sut.addAnnModel(existingModel);

		// Act & Assert
		assertEquals(-1, sut.getAnnModelIndexByName(missingModel.getName()));
	}

	// Assert
	@Test(expected = IndexOutOfBoundsException.class)
	public void test_getAnnModel_indexIsInvalid_throwsIndexOutOfBoundsException() {
		// Arrange
		// No arrangements

		// Act
		sut.getAnnModel(0);
	}

	@Test
	public void test_getAnnModel_indexIsValid_returnsModelOnSpecifiedIndex() {
		// Arrange
		NolAnnModel model1 = createAnnModel("Model 1 Name");
		NolAnnModel model2 = createAnnModel("Model 2 Name");
		NolAnnModel model3 = createAnnModel("Model 3 Name");
		sut.addAnnModel(model1);
		sut.addAnnModel(model2);
		sut.addAnnModel(model3);

		// Act & Assert
		assertEquals(model1, sut.getAnnModel(0));
		assertEquals(model2, sut.getAnnModel(1));
		assertEquals(model3, sut.getAnnModel(2));
	}

	@Test
	public void test_addRbfnModel_modelDoesNotExist_addsModel() {
		// Arrange
		NolRbfnModel existingModel = createRbfnModel("Existing Model Name");
		NolRbfnModel missingModel = createRbfnModel("Non Existing Model Name");
		sut.addRbfnModel(existingModel);

		// Act
		sut.addRbfnModel(missingModel);

		// Assert
		assertTrue(sut.getRbfnModels().contains(existingModel));
		assertTrue(sut.getRbfnModels().contains(missingModel));
	}

	@Test
	public void test_addRbfnModel_modelAlreadyExists_updatesModel() {
		// Arrange
		NolRbfnModel oldModel = createRbfnModel("Same Model Name");
		sut.addRbfnModel(oldModel);
		NolRbfnModel newModel = createRbfnModel("Same Model Name");

		// Act
		sut.addRbfnModel(newModel);

		// Assert
		assertTrue(sut.getRbfnModels().contains(newModel));
		assertFalse(sut.getRbfnModels().contains(oldModel));
	}

	@Test
	public void test_deleteRbfnModel_indexIsOutOfBound_doesNotRemoveAnyModel() {
		// Arrange
		NolRbfnModel model = createRbfnModel("Model Name");
		sut.addRbfnModel(model);

		// Act
		sut.deleteRbfnModel(1);

		// Assert
		assertTrue(sut.getRbfnModels().contains(model));
	}

	@Test
	public void test_deleteRbfnModel_indexIsValid_removesModelFromSpecifiedIndex() {
		// Arrange
		NolRbfnModel model1 = createRbfnModel("Model 1 Name");
		NolRbfnModel model2 = createRbfnModel("Model 2 Name");
		NolRbfnModel model3 = createRbfnModel("Model 3 Name");
		sut.addRbfnModel(model1);
		sut.addRbfnModel(model2);
		sut.addRbfnModel(model3);

		// Act
		sut.deleteRbfnModel(1);

		// Assert
		assertTrue(sut.getRbfnModels().contains(model1));
		assertFalse(sut.getRbfnModels().contains(model2));
		assertTrue(sut.getRbfnModels().contains(model3));
	}

	@Test
	public void test_deleteRbfnModel_modelIsInvalid_doesNotRemoveAnyModel() {
		// Arrange
		NolRbfnModel model1 = createRbfnModel("Model 1 Name");
		NolRbfnModel model2 = createRbfnModel("Model 2 Name");
		NolRbfnModel model3 = createRbfnModel("Model 3 Name");
		sut.addRbfnModel(model1);
		sut.addRbfnModel(model2);

		// Act
		sut.deleteRbfnModel(model3);

		// Assert
		assertTrue(sut.getRbfnModels().contains(model1));
		assertTrue(sut.getRbfnModels().contains(model2));
	}

	@Test
	public void test_deleteRbfnModel_modelIsValid_removesSpecifiedModel() {
		// Arrange
		NolRbfnModel model1 = createRbfnModel("Model 1 Name");
		NolRbfnModel model2 = createRbfnModel("Model 2 Name");
		NolRbfnModel model3 = createRbfnModel("Model 3 Name");
		sut.addRbfnModel(model1);
		sut.addRbfnModel(model2);
		sut.addRbfnModel(model3);

		// Act
		sut.deleteRbfnModel(model3);

		// Assert
		assertTrue(sut.getRbfnModels().contains(model1));
		assertTrue(sut.getRbfnModels().contains(model2));
		assertFalse(sut.getRbfnModels().contains(model3));
	}

	@Test
	public void test_deleteRbfnModel_modelIsRemovedMoreThanOnce_removesModelOnceAndIgnoresOtherCalls() {
		// Arrange
		NolRbfnModel model1 = createRbfnModel("Model 1 Name");
		NolRbfnModel model2 = createRbfnModel("Model 2 Name");
		NolRbfnModel model3 = createRbfnModel("Model 3 Name");
		sut.addRbfnModel(model1);
		sut.addRbfnModel(model2);
		sut.addRbfnModel(model3);

		// Act
		sut.deleteRbfnModel(model3);
		sut.deleteRbfnModel(model3);

		// Assert
		assertTrue(sut.getRbfnModels().contains(model1));
		assertTrue(sut.getRbfnModels().contains(model2));
		assertFalse(sut.getRbfnModels().contains(model3));
	}

	@Test
	public void test_getNumberOfRbfnModels_always_returnsNumberOfAddedRbfnModels() {
		// Arrange
		NolRbfnModel model1 = createRbfnModel("Model 1 Name");
		NolRbfnModel model2 = createRbfnModel("Model 2 Name");
		NolRbfnModel model3 = createRbfnModel("Model 3 Name");
		sut.addRbfnModel(model1);
		sut.addRbfnModel(model2);
		sut.addRbfnModel(model3);

		// Act & Assert
		assertEquals(3, sut.getNumberOfRbfnModels());
	}

	@Test
	public void test_getNumberOfRbfnModels_modelsAreAddedAndDeleted_returnsCorrectNumberOfRbfnModels() {
		// Arrange
		NolRbfnModel model1 = createRbfnModel("Model 1 Name");
		NolRbfnModel model2 = createRbfnModel("Model 2 Name");
		NolRbfnModel model3 = createRbfnModel("Model 3 Name");
		sut.addRbfnModel(model1);
		sut.addRbfnModel(model2);
		sut.addRbfnModel(model3);
		sut.deleteRbfnModel(model1);
		sut.deleteRbfnModel(model2);

		// Act & Assert
		assertEquals(1, sut.getNumberOfRbfnModels());
	}

	@Test
	public void test_deleteRbfnModel_indexIsLessThanZero_doesNotRemoveAnyModel() {
		// Arrange
		NolRbfnModel model = createRbfnModel("Model Name");
		sut.addRbfnModel(model);

		// Act
		sut.deleteRbfnModel(-1);

		// Assert
		assertTrue(sut.getRbfnModels().contains(model));
	}

	@Test
	public void test_getRbfnModelIndexByName_modelExists_ReturnsModelIndex() {
		// Arrange
		NolRbfnModel model1 = createRbfnModel("Model 1 Name");
		NolRbfnModel model2 = createRbfnModel("Model 2 Name");
		NolRbfnModel model3 = createRbfnModel("Model 3 Name");
		sut.addRbfnModel(model1);
		sut.addRbfnModel(model2);
		sut.addRbfnModel(model3);

		// Act & Assert
		assertEquals(0, sut.getRbfnModelIndexByName(model1.getName()));
		assertEquals(1, sut.getRbfnModelIndexByName(model2.getName()));
		assertEquals(2, sut.getRbfnModelIndexByName(model3.getName()));
	}

	@Test
	public void test_getRbfnModelIndexByName_modelDoesNotExist_returnsMinusOne() {
		// Arrange
		NolRbfnModel existingModel = createRbfnModel("Existing Model Name");
		NolRbfnModel missingModel = createRbfnModel("Missing Model Name");
		sut.addRbfnModel(existingModel);

		// Act & Assert
		assertEquals(-1, sut.getRbfnModelIndexByName(missingModel.getName()));
	}

	// Assert
	@Test(expected = IndexOutOfBoundsException.class)
	public void test_getRbfnModel_indexIsInvalid_throwsIndexOutOfBoundsException() {
		// Arrange
		// No arrangements

		// Act
		sut.getRbfnModel(0);
	}

	@Test
	public void test_getRbfnModel_indexIsValid_returnsModelOnSpecifiedIndex() {
		// Arrange
		NolRbfnModel model1 = createRbfnModel("Model 1 Name");
		NolRbfnModel model2 = createRbfnModel("Model 2 Name");
		NolRbfnModel model3 = createRbfnModel("Model 3 Name");
		sut.addRbfnModel(model1);
		sut.addRbfnModel(model2);
		sut.addRbfnModel(model3);

		// Act & Assert
		assertEquals(model1, sut.getRbfnModel(0));
		assertEquals(model2, sut.getRbfnModel(1));
		assertEquals(model3, sut.getRbfnModel(2));
	}

	@Test
	public void test_addRhoModel_modelDoesNotExist_addsModel() {
		// Arrange
		NolRhoModel existingModel = createRhoModel("Existing Model Name");
		NolRhoModel missingModel = createRhoModel("Non Existing Model Name");
		sut.addRhoModel(existingModel);

		// Act
		sut.addRhoModel(missingModel);

		// Assert
		assertTrue(sut.getRhoModels().contains(existingModel));
		assertTrue(sut.getRhoModels().contains(missingModel));
	}

	@Test
	public void test_addRhoModel_modelAlreadyExists_updatesModel() {
		// Arrange
		NolRhoModel oldModel = createRhoModel("Same Model Name");
		sut.addRhoModel(oldModel);
		NolRhoModel newModel = createRhoModel("Same Model Name");

		// Act
		sut.addRhoModel(newModel);

		// Assert
		assertTrue(sut.getRhoModels().contains(newModel));
		assertFalse(sut.getRhoModels().contains(oldModel));
	}

	@Test
	public void test_deleteRhoModel_indexIsOutOfBound_doesNotRemoveAnyModel() {
		// Arrange
		NolRhoModel model = createRhoModel("Model Name");
		sut.addRhoModel(model);

		// Act
		sut.deleteRhoModel(1);

		// Assert
		assertTrue(sut.getRhoModels().contains(model));
	}

	@Test
	public void test_deleteRhoModel_indexIsValid_removesModelFromSpecifiedIndex() {
		// Arrange
		NolRhoModel model1 = createRhoModel("Model 1 Name");
		NolRhoModel model2 = createRhoModel("Model 2 Name");
		NolRhoModel model3 = createRhoModel("Model 3 Name");
		sut.addRhoModel(model1);
		sut.addRhoModel(model2);
		sut.addRhoModel(model3);

		// Act
		sut.deleteRhoModel(1);

		// Assert
		assertTrue(sut.getRhoModels().contains(model1));
		assertFalse(sut.getRhoModels().contains(model2));
		assertTrue(sut.getRhoModels().contains(model3));
	}

	@Test
	public void test_deleteRhoModel_modelIsInvalid_doesNotRemoveAnyModel() {
		// Arrange
		NolRhoModel model1 = createRhoModel("Model 1 Name");
		NolRhoModel model2 = createRhoModel("Model 2 Name");
		NolRhoModel model3 = createRhoModel("Model 3 Name");
		sut.addRhoModel(model1);
		sut.addRhoModel(model2);

		// Act
		sut.deleteRhoModel(model3);

		// Assert
		assertTrue(sut.getRhoModels().contains(model1));
		assertTrue(sut.getRhoModels().contains(model2));
	}

	@Test
	public void test_deleteRhoModel_modelIsValid_removesSpecifiedModel() {
		// Arrange
		NolRhoModel model1 = createRhoModel("Model 1 Name");
		NolRhoModel model2 = createRhoModel("Model 2 Name");
		NolRhoModel model3 = createRhoModel("Model 3 Name");
		sut.addRhoModel(model1);
		sut.addRhoModel(model2);
		sut.addRhoModel(model3);

		// Act
		sut.deleteRhoModel(model3);

		// Assert
		assertTrue(sut.getRhoModels().contains(model1));
		assertTrue(sut.getRhoModels().contains(model2));
		assertFalse(sut.getRhoModels().contains(model3));
	}

	@Test
	public void test_deleteRhoModel_modelIsRemovedMoreThanOnce_removesModelOnceAndIgnoresOtherCalls() {
		// Arrange
		NolRhoModel model1 = createRhoModel("Model 1 Name");
		NolRhoModel model2 = createRhoModel("Model 2 Name");
		NolRhoModel model3 = createRhoModel("Model 3 Name");
		sut.addRhoModel(model1);
		sut.addRhoModel(model2);
		sut.addRhoModel(model3);

		// Act
		sut.deleteRhoModel(model3);
		sut.deleteRhoModel(model3);

		// Assert
		assertTrue(sut.getRhoModels().contains(model1));
		assertTrue(sut.getRhoModels().contains(model2));
		assertFalse(sut.getRhoModels().contains(model3));
	}

	@Test
	public void test_getNumberOfRhoModels_always_returnsNumberOfAddedRhoModels() {
		// Arrange
		NolRhoModel model1 = createRhoModel("Model 1 Name");
		NolRhoModel model2 = createRhoModel("Model 2 Name");
		NolRhoModel model3 = createRhoModel("Model 3 Name");
		sut.addRhoModel(model1);
		sut.addRhoModel(model2);
		sut.addRhoModel(model3);

		// Act & Assert
		assertEquals(3, sut.getNumberOfRhoModels());
	}

	@Test
	public void test_getNumberOfRhoModels_modelsAreAddedAndDeleted_returnsCorrectNumberOfRhoModels() {
		// Arrange
		NolRhoModel model1 = createRhoModel("Model 1 Name");
		NolRhoModel model2 = createRhoModel("Model 2 Name");
		NolRhoModel model3 = createRhoModel("Model 3 Name");
		sut.addRhoModel(model1);
		sut.addRhoModel(model2);
		sut.addRhoModel(model3);
		sut.deleteRhoModel(model1);
		sut.deleteRhoModel(model2);

		// Act & Assert
		assertEquals(1, sut.getNumberOfRhoModels());
	}

	@Test
	public void test_deleteRhoModel_indexIsLessThanZero_doesNotRemoveAnyModel() {
		// Arrange
		NolRhoModel model = createRhoModel("Model Name");
		sut.addRhoModel(model);

		// Act
		sut.deleteRhoModel(-1);

		// Assert
		assertTrue(sut.getRhoModels().contains(model));
	}

	@Test
	public void test_getRhoModelIndexByName_modelExists_ReturnsModelIndex() {
		// Arrange
		NolRhoModel model1 = createRhoModel("Model 1 Name");
		NolRhoModel model2 = createRhoModel("Model 2 Name");
		NolRhoModel model3 = createRhoModel("Model 3 Name");
		sut.addRhoModel(model1);
		sut.addRhoModel(model2);
		sut.addRhoModel(model3);

		// Act & Assert
		assertEquals(0, sut.getRhoModelIndexByName(model1.getName()));
		assertEquals(1, sut.getRhoModelIndexByName(model2.getName()));
		assertEquals(2, sut.getRhoModelIndexByName(model3.getName()));
	}

	@Test
	public void test_getRhoModelIndexByName_modelDoesNotExist_returnsMinusOne() {
		// Arrange
		NolRhoModel existingModel = createRhoModel("Existing Model Name");
		NolRhoModel missingModel = createRhoModel("Missing Model Name");
		sut.addRhoModel(existingModel);

		// Act & Assert
		assertEquals(-1, sut.getRhoModelIndexByName(missingModel.getName()));
	}

	// Assert
	@Test(expected = IndexOutOfBoundsException.class)
	public void test_getRhoModel_indexIsInvalid_throwsIndexOutOfBoundsException() {
		// Arrange
		// No arrangements

		// Act
		sut.getRhoModel(0);
	}

	@Test
	public void test_getRhoModel_indexIsValid_returnsModelOnSpecifiedIndex() {
		// Arrange
		NolRhoModel model1 = createRhoModel("Model 1 Name");
		NolRhoModel model2 = createRhoModel("Model 2 Name");
		NolRhoModel model3 = createRhoModel("Model 3 Name");
		sut.addRhoModel(model1);
		sut.addRhoModel(model2);
		sut.addRhoModel(model3);

		// Act & Assert
		assertEquals(model1, sut.getRhoModel(0));
		assertEquals(model2, sut.getRhoModel(1));
		assertEquals(model3, sut.getRhoModel(2));
	}

	@Test
	public void test_addPlsModel_modelDoesNotExist_addsModel() {
		// Arrange
		NolPlsModel existingModel = createPlsModel("Existing Model Name");
		NolPlsModel missingModel = createPlsModel("Non Existing Model Name");
		sut.addPlsModel(existingModel);

		// Act
		sut.addPlsModel(missingModel);

		// Assert
		assertTrue(sut.getPlsModels().contains(existingModel));
		assertTrue(sut.getPlsModels().contains(missingModel));
	}

	@Test
	public void test_addPlsModel_modelAlreadyExists_updatesModel() {
		// Arrange
		NolPlsModel oldModel = createPlsModel("Same Model Name");
		sut.addPlsModel(oldModel);
		NolPlsModel newModel = createPlsModel("Same Model Name");

		// Act
		sut.addPlsModel(newModel);

		// Assert
		assertTrue(sut.getPlsModels().contains(newModel));
		assertFalse(sut.getPlsModels().contains(oldModel));
	}

	@Test
	public void test_deletePlsModel_indexIsOutOfBound_doesNotRemoveAnyModel() {
		// Arrange
		NolPlsModel model = createPlsModel("Model Name");
		sut.addPlsModel(model);

		// Act
		sut.deletePlsModel(1);

		// Assert
		assertTrue(sut.getPlsModels().contains(model));
	}

	@Test
	public void test_deletePlsModel_indexIsValid_removesModelFromSpecifiedIndex() {
		// Arrange
		NolPlsModel model1 = createPlsModel("Model 1 Name");
		NolPlsModel model2 = createPlsModel("Model 2 Name");
		NolPlsModel model3 = createPlsModel("Model 3 Name");
		sut.addPlsModel(model1);
		sut.addPlsModel(model2);
		sut.addPlsModel(model3);

		// Act
		sut.deletePlsModel(1);

		// Assert
		assertTrue(sut.getPlsModels().contains(model1));
		assertFalse(sut.getPlsModels().contains(model2));
		assertTrue(sut.getPlsModels().contains(model3));
	}

	@Test
	public void test_deletePlsModel_modelIsInvalid_doesNotRemoveAnyModel() {
		// Arrange
		NolPlsModel model1 = createPlsModel("Model 1 Name");
		NolPlsModel model2 = createPlsModel("Model 2 Name");
		NolPlsModel model3 = createPlsModel("Model 3 Name");
		sut.addPlsModel(model1);
		sut.addPlsModel(model2);

		// Act
		sut.deletePlsModel(model3);

		// Assert
		assertTrue(sut.getPlsModels().contains(model1));
		assertTrue(sut.getPlsModels().contains(model2));
	}

	@Test
	public void test_deletePlsModel_modelIsValid_removesSpecifiedModel() {
		// Arrange
		NolPlsModel model1 = createPlsModel("Model 1 Name");
		NolPlsModel model2 = createPlsModel("Model 2 Name");
		NolPlsModel model3 = createPlsModel("Model 3 Name");
		sut.addPlsModel(model1);
		sut.addPlsModel(model2);
		sut.addPlsModel(model3);

		// Act
		sut.deletePlsModel(model3);

		// Assert
		assertTrue(sut.getPlsModels().contains(model1));
		assertTrue(sut.getPlsModels().contains(model2));
		assertFalse(sut.getPlsModels().contains(model3));
	}

	@Test
	public void test_deletePlsModel_modelIsRemovedMoreThanOnce_removesModelOnceAndIgnoresOtherCalls() {
		// Arrange
		NolPlsModel model1 = createPlsModel("Model 1 Name");
		NolPlsModel model2 = createPlsModel("Model 2 Name");
		NolPlsModel model3 = createPlsModel("Model 3 Name");
		sut.addPlsModel(model1);
		sut.addPlsModel(model2);
		sut.addPlsModel(model3);

		// Act
		sut.deletePlsModel(model3);
		sut.deletePlsModel(model3);

		// Assert
		assertTrue(sut.getPlsModels().contains(model1));
		assertTrue(sut.getPlsModels().contains(model2));
		assertFalse(sut.getPlsModels().contains(model3));
	}

	@Test
	public void test_getNumberOfPlsModels_always_returnsNumberOfAddedPlsModels() {
		// Arrange
		NolPlsModel model1 = createPlsModel("Model 1 Name");
		NolPlsModel model2 = createPlsModel("Model 2 Name");
		NolPlsModel model3 = createPlsModel("Model 3 Name");
		sut.addPlsModel(model1);
		sut.addPlsModel(model2);
		sut.addPlsModel(model3);

		// Act & Assert
		assertEquals(3, sut.getNumberOfPlsModels());
	}

	@Test
	public void test_getNumberOfPlsModels_modelsAreAddedAndDeleted_returnsCorrectNumberOfPlsModels() {
		// Arrange
		NolPlsModel model1 = createPlsModel("Model 1 Name");
		NolPlsModel model2 = createPlsModel("Model 2 Name");
		NolPlsModel model3 = createPlsModel("Model 3 Name");
		sut.addPlsModel(model1);
		sut.addPlsModel(model2);
		sut.addPlsModel(model3);
		sut.deletePlsModel(model1);
		sut.deletePlsModel(model2);

		// Act & Assert
		assertEquals(1, sut.getNumberOfPlsModels());
	}

	@Test
	public void test_deletePlsModel_indexIsLessThanZero_doesNotRemoveAnyModel() {
		// Arrange
		NolPlsModel model = createPlsModel("Model Name");
		sut.addPlsModel(model);

		// Act
		sut.deletePlsModel(-1);

		// Assert
		assertTrue(sut.getPlsModels().contains(model));
	}

	@Test
	public void test_getPlsModelIndexByName_modelExists_ReturnsModelIndex() {
		// Arrange
		NolPlsModel model1 = createPlsModel("Model 1 Name");
		NolPlsModel model2 = createPlsModel("Model 2 Name");
		NolPlsModel model3 = createPlsModel("Model 3 Name");
		sut.addPlsModel(model1);
		sut.addPlsModel(model2);
		sut.addPlsModel(model3);

		// Act & Assert
		assertEquals(0, sut.getPlsModelIndexByName(model1.getName()));
		assertEquals(1, sut.getPlsModelIndexByName(model2.getName()));
		assertEquals(2, sut.getPlsModelIndexByName(model3.getName()));
	}

	@Test
	public void test_getPlsModelIndexByName_modelDoesNotExist_returnsMinusOne() {
		// Arrange
		NolPlsModel existingModel = createPlsModel("Existing Model Name");
		NolPlsModel missingModel = createPlsModel("Missing Model Name");
		sut.addPlsModel(existingModel);

		// Act & Assert
		assertEquals(-1, sut.getPlsModelIndexByName(missingModel.getName()));
	}

	// Assert
	@Test(expected = IndexOutOfBoundsException.class)
	public void test_getPlsModel_indexIsInvalid_throwsIndexOutOfBoundsException() {
		// Arrange
		// No arrangements

		// Act
		sut.getPlsModel(0);
	}

	@Test
	public void test_getPlsModel_indexIsValid_returnsModelOnSpecifiedIndex() {
		// Arrange
		NolPlsModel model1 = createPlsModel("Model 1 Name");
		NolPlsModel model2 = createPlsModel("Model 2 Name");
		NolPlsModel model3 = createPlsModel("Model 3 Name");
		sut.addPlsModel(model1);
		sut.addPlsModel(model2);
		sut.addPlsModel(model3);

		// Act & Assert
		assertEquals(model1, sut.getPlsModel(0));
		assertEquals(model2, sut.getPlsModel(1));
		assertEquals(model3, sut.getPlsModel(2));
	}

	@Test
	public void test_addPcaModel_modelDoesNotExist_addsModel() {
		// Arrange
		NolPcaModel existingModel = createPcaModel("Existing Model Name");
		NolPcaModel missingModel = createPcaModel("Non Existing Model Name");
		sut.addPcaModel(existingModel);

		// Act
		sut.addPcaModel(missingModel);

		// Assert
		assertTrue(sut.getPcaModels().contains(existingModel));
		assertTrue(sut.getPcaModels().contains(missingModel));
	}

	@Test
	public void test_addPcaModel_modelAlreadyExists_updatesModel() {
		// Arrange
		NolPcaModel oldModel = createPcaModel("Same Model Name");
		sut.addPcaModel(oldModel);
		NolPcaModel newModel = createPcaModel("Same Model Name");

		// Act
		sut.addPcaModel(newModel);

		// Assert
		assertTrue(sut.getPcaModels().contains(newModel));
		assertFalse(sut.getPcaModels().contains(oldModel));
	}

	@Test
	public void test_deletePcaModel_indexIsOutOfBound_doesNotRemoveAnyModel() {
		// Arrange
		NolPcaModel model = createPcaModel("Model Name");
		sut.addPcaModel(model);

		// Act
		sut.deletePcaModel(1);

		// Assert
		assertTrue(sut.getPcaModels().contains(model));
	}

	@Test
	public void test_deletePcaModel_indexIsValid_removesModelFromSpecifiedIndex() {
		// Arrange
		NolPcaModel model1 = createPcaModel("Model 1 Name");
		NolPcaModel model2 = createPcaModel("Model 2 Name");
		NolPcaModel model3 = createPcaModel("Model 3 Name");
		sut.addPcaModel(model1);
		sut.addPcaModel(model2);
		sut.addPcaModel(model3);

		// Act
		sut.deletePcaModel(1);

		// Assert
		assertTrue(sut.getPcaModels().contains(model1));
		assertFalse(sut.getPcaModels().contains(model2));
		assertTrue(sut.getPcaModels().contains(model3));
	}

	@Test
	public void test_deletePcaModel_modelIsInvalid_doesNotRemoveAnyModel() {
		// Arrange
		NolPcaModel model1 = createPcaModel("Model 1 Name");
		NolPcaModel model2 = createPcaModel("Model 2 Name");
		NolPcaModel model3 = createPcaModel("Model 3 Name");
		sut.addPcaModel(model1);
		sut.addPcaModel(model2);

		// Act
		sut.deletePcaModel(model3);

		// Assert
		assertTrue(sut.getPcaModels().contains(model1));
		assertTrue(sut.getPcaModels().contains(model2));
	}

	@Test
	public void test_deletePcaModel_modelIsValid_removesSpecifiedModel() {
		// Arrange
		NolPcaModel model1 = createPcaModel("Model 1 Name");
		NolPcaModel model2 = createPcaModel("Model 2 Name");
		NolPcaModel model3 = createPcaModel("Model 3 Name");
		sut.addPcaModel(model1);
		sut.addPcaModel(model2);
		sut.addPcaModel(model3);

		// Act
		sut.deletePcaModel(model3);

		// Assert
		assertTrue(sut.getPcaModels().contains(model1));
		assertTrue(sut.getPcaModels().contains(model2));
		assertFalse(sut.getPcaModels().contains(model3));
	}

	@Test
	public void test_deletePcaModel_modelIsRemovedMoreThanOnce_removesModelOnceAndIgnoresOtherCalls() {
		// Arrange
		NolPcaModel model1 = createPcaModel("Model 1 Name");
		NolPcaModel model2 = createPcaModel("Model 2 Name");
		NolPcaModel model3 = createPcaModel("Model 3 Name");
		sut.addPcaModel(model1);
		sut.addPcaModel(model2);
		sut.addPcaModel(model3);

		// Act
		sut.deletePcaModel(model3);
		sut.deletePcaModel(model3);

		// Assert
		assertTrue(sut.getPcaModels().contains(model1));
		assertTrue(sut.getPcaModels().contains(model2));
		assertFalse(sut.getPcaModels().contains(model3));
	}

	@Test
	public void test_getNumberOfPcaModels_always_returnsNumberOfAddedPcaModels() {
		// Arrange
		NolPcaModel model1 = createPcaModel("Model 1 Name");
		NolPcaModel model2 = createPcaModel("Model 2 Name");
		NolPcaModel model3 = createPcaModel("Model 3 Name");
		sut.addPcaModel(model1);
		sut.addPcaModel(model2);
		sut.addPcaModel(model3);

		// Act & Assert
		assertEquals(3, sut.getNumberOfPcaModels());
	}

	@Test
	public void test_getNumberOfPcaModels_modelsAreAddedAndDeleted_returnsCorrectNumberOfPcaModels() {
		// Arrange
		NolPcaModel model1 = createPcaModel("Model 1 Name");
		NolPcaModel model2 = createPcaModel("Model 2 Name");
		NolPcaModel model3 = createPcaModel("Model 3 Name");
		sut.addPcaModel(model1);
		sut.addPcaModel(model2);
		sut.addPcaModel(model3);
		sut.deletePcaModel(model1);
		sut.deletePcaModel(model2);

		// Act & Assert
		assertEquals(1, sut.getNumberOfPcaModels());
	}

	@Test
	public void test_deletePcaModel_indexIsLessThanZero_doesNotRemoveAnyModel() {
		// Arrange
		NolPcaModel model = createPcaModel("Model Name");
		sut.addPcaModel(model);

		// Act
		sut.deletePcaModel(-1);

		// Assert
		assertTrue(sut.getPcaModels().contains(model));
	}

	@Test
	public void test_getPcaModelIndexByName_modelExists_ReturnsModelIndex() {
		// Arrange
		NolPcaModel model1 = createPcaModel("Model 1 Name");
		NolPcaModel model2 = createPcaModel("Model 2 Name");
		NolPcaModel model3 = createPcaModel("Model 3 Name");
		sut.addPcaModel(model1);
		sut.addPcaModel(model2);
		sut.addPcaModel(model3);

		// Act & Assert
		assertEquals(0, sut.getPcaModelIndexByName(model1.getName()));
		assertEquals(1, sut.getPcaModelIndexByName(model2.getName()));
		assertEquals(2, sut.getPcaModelIndexByName(model3.getName()));
	}

	@Test
	public void test_getPcaModelIndexByName_modelDoesNotExist_returnsMinusOne() {
		// Arrange
		NolPcaModel existingModel = createPcaModel("Existing Model Name");
		NolPcaModel missingModel = createPcaModel("Missing Model Name");
		sut.addPcaModel(existingModel);

		// Act & Assert
		assertEquals(-1, sut.getPcaModelIndexByName(missingModel.getName()));
	}

	// Assert
	@Test(expected = IndexOutOfBoundsException.class)
	public void test_getPcaModel_indexIsInvalid_throwsIndexOutOfBoundsException() {
		// Arrange
		// No arrangements

		// Act
		sut.getPcaModel(0);
	}

	@Test
	public void test_getPcaModel_indexIsValid_returnsModelOnSpecifiedIndex() {
		// Arrange
		NolPcaModel model1 = createPcaModel("Model 1 Name");
		NolPcaModel model2 = createPcaModel("Model 2 Name");
		NolPcaModel model3 = createPcaModel("Model 3 Name");
		sut.addPcaModel(model1);
		sut.addPcaModel(model2);
		sut.addPcaModel(model3);

		// Act & Assert
		assertEquals(model1, sut.getPcaModel(0));
		assertEquals(model2, sut.getPcaModel(1));
		assertEquals(model3, sut.getPcaModel(2));
	}

	@Test
	public void test_addGenOptimization_optimizationDoesNotExist_addsOptimization() {
		// Arrange
		NolGenOptimization existingOptimization = createNolGenOptimization("Existing Optimization Name");
		NolGenOptimization missingOptimization = createNolGenOptimization("Non Existing Optimization Name");
		sut.addGenOptimization(existingOptimization);

		// Act
		sut.addGenOptimization(missingOptimization);

		// Assert
		assertTrue(sut.getGenOptimizations().contains(existingOptimization));
		assertTrue(sut.getGenOptimizations().contains(missingOptimization));
	}

	@Test
	public void test_addGenOptimization_optimizationAlreadyExists_updatesOptimization() {
		// Arrange
		NolGenOptimization oldOptimization = createNolGenOptimization("Same Optimization Name");
		sut.addGenOptimization(oldOptimization);
		NolGenOptimization newOptimization = createNolGenOptimization("Same Optimization Name");

		// Act
		sut.addGenOptimization(newOptimization);

		// Assert
		assertTrue(sut.getGenOptimizations().contains(newOptimization));
		assertFalse(sut.getGenOptimizations().contains(oldOptimization));
	}

	@Test
	public void test_deleteGenOptimization_indexIsOutOfBound_doesNotRemoveAnyOptimization() {
		// Arrange
		NolGenOptimization optimization = createNolGenOptimization("Optimization Name");
		sut.addGenOptimization(optimization);

		// Act
		sut.deleteGenOptimization(1);

		// Assert
		assertTrue(sut.getGenOptimizations().contains(optimization));
	}

	@Test
	public void test_deleteGenOptimization_indexIsValid_removesOptimizationFromSpecifiedIndex() {
		// Arrange
		NolGenOptimization optimization1 = createNolGenOptimization("Optimization 1 Name");
		NolGenOptimization optimization2 = createNolGenOptimization("Optimization 2 Name");
		NolGenOptimization optimization3 = createNolGenOptimization("Optimization 3 Name");
		sut.addGenOptimization(optimization1);
		sut.addGenOptimization(optimization2);
		sut.addGenOptimization(optimization3);

		// Act
		sut.deleteGenOptimization(1);

		// Assert
		assertTrue(sut.getGenOptimizations().contains(optimization1));
		assertFalse(sut.getGenOptimizations().contains(optimization2));
		assertTrue(sut.getGenOptimizations().contains(optimization3));
	}

	@Test
	public void test_deleteGenOptimization_optimizationIsInvalid_doesNotRemoveAnyOptimization() {
		// Arrange
		NolGenOptimization optimization1 = createNolGenOptimization("Optimization 1 Name");
		NolGenOptimization optimization2 = createNolGenOptimization("Optimization 2 Name");
		NolGenOptimization optimization3 = createNolGenOptimization("Optimization 3 Name");
		sut.addGenOptimization(optimization1);
		sut.addGenOptimization(optimization2);

		// Act
		sut.deleteGenOptimization(optimization3);

		// Assert
		assertTrue(sut.getGenOptimizations().contains(optimization1));
		assertTrue(sut.getGenOptimizations().contains(optimization2));
	}

	@Test
	public void test_deleteGenOptimization_optimizationIsValid_removesSpecifiedOptimization() {
		// Arrange
		NolGenOptimization optimization1 = createNolGenOptimization("Optimization 1 Name");
		NolGenOptimization optimization2 = createNolGenOptimization("Optimization 2 Name");
		NolGenOptimization optimization3 = createNolGenOptimization("Optimization 3 Name");
		sut.addGenOptimization(optimization1);
		sut.addGenOptimization(optimization2);
		sut.addGenOptimization(optimization3);

		// Act
		sut.deleteGenOptimization(optimization3);

		// Assert
		assertTrue(sut.getGenOptimizations().contains(optimization1));
		assertTrue(sut.getGenOptimizations().contains(optimization2));
		assertFalse(sut.getGenOptimizations().contains(optimization3));
	}

	@Test
	public void test_deleteGenOptimization_optimizationIsRemovedMoreThanOnce_removesOptimizationOnceAndIgnoresOtherCalls() {
		// Arrange
		NolGenOptimization optimization1 = createNolGenOptimization("Optimization 1 Name");
		NolGenOptimization optimization2 = createNolGenOptimization("Optimization 2 Name");
		NolGenOptimization optimization3 = createNolGenOptimization("Optimization 3 Name");
		sut.addGenOptimization(optimization1);
		sut.addGenOptimization(optimization2);
		sut.addGenOptimization(optimization3);

		// Act
		sut.deleteGenOptimization(optimization3);
		sut.deleteGenOptimization(optimization3);

		// Assert
		assertTrue(sut.getGenOptimizations().contains(optimization1));
		assertTrue(sut.getGenOptimizations().contains(optimization2));
		assertFalse(sut.getGenOptimizations().contains(optimization3));
	}

	@Test
	public void test_getNumberOfGenOptimizations_always_returnsNumberOfAddedGenOptimizations() {
		// Arrange
		NolGenOptimization optimization1 = createNolGenOptimization("Optimization 1 Name");
		NolGenOptimization optimization2 = createNolGenOptimization("Optimization 2 Name");
		NolGenOptimization optimization3 = createNolGenOptimization("Optimization 3 Name");
		sut.addGenOptimization(optimization1);
		sut.addGenOptimization(optimization2);
		sut.addGenOptimization(optimization3);

		// Act & Assert
		assertEquals(3, sut.getNumberOfGenOptimizations());
	}

	@Test
	public void test_getNumberOfGenOptimizations_optimizationsAreAddedAndDeleted_returnsCorrectNumberOfGenOptimizations() {
		// Arrange
		NolGenOptimization optimization1 = createNolGenOptimization("Optimization 1 Name");
		NolGenOptimization optimization2 = createNolGenOptimization("Optimization 2 Name");
		NolGenOptimization optimization3 = createNolGenOptimization("Optimization 3 Name");
		sut.addGenOptimization(optimization1);
		sut.addGenOptimization(optimization2);
		sut.addGenOptimization(optimization3);
		sut.deleteGenOptimization(optimization1);
		sut.deleteGenOptimization(optimization2);

		// Act & Assert
		assertEquals(1, sut.getNumberOfGenOptimizations());
	}

	@Test
	public void test_deleteGenOptimization_indexIsLessThanZero_doesNotRemoveAnyOptimization() {
		// Arrange
		NolGenOptimization optimization = createNolGenOptimization("Optimization Name");
		sut.addGenOptimization(optimization);

		// Act
		sut.deleteGenOptimization(-1);

		// Assert
		assertTrue(sut.getGenOptimizations().contains(optimization));
	}

	@Test
	public void test_getGenOptimizationIndexByName_optimizationExists_ReturnsOptimizationIndex() {
		// Arrange
		NolGenOptimization optimization1 = createNolGenOptimization("Optimization 1 Name");
		NolGenOptimization optimization2 = createNolGenOptimization("Optimization 2 Name");
		NolGenOptimization optimization3 = createNolGenOptimization("Optimization 3 Name");
		sut.addGenOptimization(optimization1);
		sut.addGenOptimization(optimization2);
		sut.addGenOptimization(optimization3);

		// Act & Assert
		assertEquals(0, sut.getGenOptimizationIndexByName(optimization1.getName()));
		assertEquals(1, sut.getGenOptimizationIndexByName(optimization2.getName()));
		assertEquals(2, sut.getGenOptimizationIndexByName(optimization3.getName()));
	}

	@Test
	public void test_getGenOptimizationIndexByName_optimizationDoesNotExist_returnsMinusOne() {
		// Arrange
		NolGenOptimization existingOptimization = createNolGenOptimization("Existing Optimization Name");
		NolGenOptimization missingOptimization = createNolGenOptimization("Missing Optimization Name");
		sut.addGenOptimization(existingOptimization);

		// Act & Assert
		assertEquals(-1, sut.getGenOptimizationIndexByName(missingOptimization.getName()));
	}

	// Assert
	@Test(expected = IndexOutOfBoundsException.class)
	public void test_getGenOptimization_indexIsInvalid_throwsIndexOutOfBoundsException() {
		// Arrange
		// No arrangements

		// Act
		sut.getGenOptimization(0);
	}

	@Test
	public void test_getGenOptimization_indexIsValid_returnsOptimizationOnSpecifiedIndex() {
		// Arrange
		NolGenOptimization optimization1 = createNolGenOptimization("Optimization 1 Name");
		NolGenOptimization optimization2 = createNolGenOptimization("Optimization 2 Name");
		NolGenOptimization optimization3 = createNolGenOptimization("Optimization 3 Name");
		sut.addGenOptimization(optimization1);
		sut.addGenOptimization(optimization2);
		sut.addGenOptimization(optimization3);

		// Act & Assert
		assertEquals(optimization1, sut.getGenOptimization(0));
		assertEquals(optimization2, sut.getGenOptimization(1));
		assertEquals(optimization3, sut.getGenOptimization(2));
	}

	@Test
	public void test_initDataTreeForTransientField_always_invokesInitTransientForBpnModels() {
		// Arrange
		NolBpnModel[] models = new NolBpnModel[] { createBpnModel("Model 1 Name"), createBpnModel("Model 2 Name") };
		for (NolBpnModel model : models) {
			sut.addBpnModel(model);
		}

		// Act
		sut.initDataTreeForTransientField();

		// Assert
		for (NolBpnModel model : models) {
			verify(model).initTransient(sut);
		}
	}

	@Test
	public void test_initDataTreeForTransientField_always_invokesInitTransientForAnnModels() {
		// Arrange
		NolAnnModel[] models = new NolAnnModel[] { createAnnModel("Model 1 Name"), createAnnModel("Model 2 Name") };
		for (NolAnnModel model : models) {
			sut.addAnnModel(model);
		}

		// Act
		sut.initDataTreeForTransientField();

		// Assert
		for (NolAnnModel model : models) {
			verify(model).initTransient(sut);
		}
	}

	@Test
	public void test_initDataTreeForTransientField_always_invokesInitTransientForRbfnModels() {
		// Arrange
		NolRbfnModel[] models = new NolRbfnModel[] { createRbfnModel("Model 1 Name"), createRbfnModel("Model 2 Name") };
		for (NolRbfnModel model : models) {
			sut.addRbfnModel(model);
		}

		// Act
		sut.initDataTreeForTransientField();

		// Assert
		for (NolRbfnModel model : models) {
			verify(model).initTransient(sut);
		}
	}

	@Test
	public void test_initDataTreeForTransientField_always_invokesInitTransientForRhoModels() {
		// Arrange
		NolRhoModel[] models = new NolRhoModel[] { createRhoModel("Model 1 Name"), createRhoModel("Model 2 Name") };
		for (NolRhoModel model : models) {
			sut.addRhoModel(model);
		}

		// Act
		sut.initDataTreeForTransientField();

		// Assert
		for (NolRhoModel model : models) {
			verify(model).initTransient(sut);
		}
	}

	@Test
	public void test_initDataTreeForTransientField_always_invokesInitTransientForPlsModels() {
		// Arrange
		NolPlsModel[] models = new NolPlsModel[] { createPlsModel("Model 1 Name"), createPlsModel("Model 2 Name") };
		for (NolPlsModel model : models) {
			sut.addPlsModel(model);
		}

		// Act
		sut.initDataTreeForTransientField();

		// Assert
		for (NolPlsModel model : models) {
			verify(model).initTransient(sut);
		}
	}

	@Test
	public void test_initDataTreeForTransientField_always_invokesInitTransientForGenOptimizations() {
		// Arrange
		NolGenOptimization[] models = new NolGenOptimization[] { createNolGenOptimization("Optimization 1 Name"),
				createNolGenOptimization("Optimization 2 Name") };
		for (NolGenOptimization model : models) {
			sut.addGenOptimization(model);
		}

		// Act
		sut.initDataTreeForTransientField();

		// Assert
		for (NolGenOptimization model : models) {
			verify(model).initTransient(sut);
		}
	}

	@Test
	public void test_initDataTreeForTransientField_always_invokesInitTransientForPcaModels() {
		// Arrange
		NolPcaModel[] models = new NolPcaModel[] { createPcaModel("Model 1 Name"), createPcaModel("Model 2 Name") };
		for (NolPcaModel model : models) {
			sut.addPcaModel(model);
		}

		// Act
		sut.initDataTreeForTransientField();

		// Assert
		for (NolPcaModel model : models) {
			verify(model).initTransient(sut);
		}
	}

	@Test
	public void test_initializeHardBounds_always_invokesInitializeHardBoundsForProcessedData() {
		// Arrange
		DataSeries[] processedData = new DataSeries[] { createDataSeries("Data Series 1"),
				createDataSeries("Data Series 2") };
		for (DataSeries dataSeries : processedData) {
			sut.addProcessedDataSeries(dataSeries);
		}

		// Act
		sut.initializeHardBounds();

		// Assert
		for (DataSeries dataSeries : processedData) {
			verify(dataSeries).initializeHardBounds();
		}
	}

	@Test
	public void test_initializeHardBounds_always_invokesInitializeHardBoundsForRawData() {
		// Arrange
		DataSeries[] rawData = new DataSeries[] { createDataSeries("Data Series 1"),
				createDataSeries("Data Series 2") };
		for (DataSeries dataSeries : rawData) {
			sut.addDataSeries(dataSeries);
		}

		// Act
		sut.initializeHardBounds();

		// Assert
		for (DataSeries dataSeries : rawData) {
			verify(dataSeries).initializeHardBounds();
		}
	}

	private NolAnnModel createAnnModel(String name) {
		NolAnnModel annModel = mock(NolAnnModel.class);
		when(annModel.getName()).thenReturn(name);
		return annModel;
	}

	private NolBpnModel createBpnModel(String name) {
		NolBpnModel bpnModel = mock(NolBpnModel.class);
		when(bpnModel.getName()).thenReturn(name);
		return bpnModel;
	}

	private DataSeries createDataSeries(String name) {
		DataSeries dataSeries = mock(DataSeries.class);
		when(dataSeries.getName()).thenReturn(name);
		return dataSeries;
	}

	private NolGenOptimization createNolGenOptimization(String name) {
		NolGenOptimization nolGenOptimization = mock(NolGenOptimization.class);
		when(nolGenOptimization.getName()).thenReturn(name);
		return nolGenOptimization;
	}

	private NolPcaModel createPcaModel(String name) {
		NolPcaModel pcaModel = mock(NolPcaModel.class);
		when(pcaModel.getName()).thenReturn(name);
		return pcaModel;
	}

	private NolPlsModel createPlsModel(String name) {
		NolPlsModel plsModel = mock(NolPlsModel.class);
		when(plsModel.getName()).thenReturn(name);
		return plsModel;
	}

	private NolRbfnModel createRbfnModel(String name) {
		NolRbfnModel rbfnModel = mock(NolRbfnModel.class);
		when(rbfnModel.getName()).thenReturn(name);
		return rbfnModel;
	}

	private NolRhoModel createRhoModel(String name) {
		NolRhoModel rhoModel = mock(NolRhoModel.class);
		when(rhoModel.getName()).thenReturn(name);
		return rhoModel;
	}
}
