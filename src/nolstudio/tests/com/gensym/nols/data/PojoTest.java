package com.gensym.nols.data;

import java.util.Arrays;
import java.util.List;

import org.junit.Test;

import com.openpojo.reflection.impl.PojoClassFactory;
import com.openpojo.validation.Validator;
import com.openpojo.validation.ValidatorBuilder;
import com.openpojo.validation.test.impl.GetterTester;
import com.openpojo.validation.test.impl.SetterTester;

public class PojoTest {
	@Test
	public void testOpenPojo() {
		final Validator validator = ValidatorBuilder.create()
				.with(new SetterTester())
				.with(new GetterTester())
				.build();

		final List<Class> classes = Arrays.asList(Prediction.class,
				RawDataEvent.class,
				Constraint.class,
				DataSource.class,
				//NolLabel.class,
				NolSimulation.class,
				Objective.class,
				OptimizationVariable.class,
				PreprocessorEvent.class,
				ProblemFixedContent.class,
				ProjectEvent.class,
				RawDataEvent.class,
				Variable.class);

		for(final Class clazz:classes){
			validator.validate(PojoClassFactory.getPojoClass(clazz));
		}
	}
}
