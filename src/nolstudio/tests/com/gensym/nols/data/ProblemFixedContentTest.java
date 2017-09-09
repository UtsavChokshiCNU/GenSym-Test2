package com.gensym.nols.data;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import org.junit.Test;

public class ProblemFixedContentTest
{

	/**
	 * Method to test getFuncevalSyn()
	 */
	@Test
	public void testGetFuncevalSyn()
	{
		final String funceval = "INTARG _CC funceval (HPROBLEM lp, INTARG numcols, INTARG numrows, LPREALARG objval, "
				+ "LPREALARG lhs, LPREALARG var, INTARG varone, INTARG vartwo){\n";
		assertEquals(funceval, ProblemFixedContent.getFuncevalSyn());
	}

	/**
	 * Method to test getJacobianSyn()
	 */
	@Test
	public void testGetJacobianSyn()
	{
		final String jacobian = "INTARG _CC jacobian (HPROBLEM lp,INTARG numcols,INTARG numrows,INTARG nzspace,"
				+ "LPREALARG objval,LPREALARG obj, LPINTARG matbeg,LPINTARG matcnt,HPINTARG matind,"
				+ "HPREALARG matval,LPREALARG var,LPBYTEARG objtype, LPBYTEARG matvaltype){\n";
		assertEquals(jacobian, ProblemFixedContent.getJacobianSyn());

	}

	/**
	 * Method to test getJacobianSyn()
	 */
	@Test
	public void testGetSolvenlpSyn()
	{
		final String solvenlp = "__declspec(dllexport) void __stdcall solvenlp(LPINTARG pstat, LPREALARG pobj,"
				+ "LPREALARG finalx, LPREALARG initx, LPREALARG lb, LPREALARG ub, LPREALARG exog){\n";
		assertEquals(solvenlp, ProblemFixedContent.getSolvenlpSyn());
	}

	/**
	 * Method to test getSolvenlpFinishedContent()
	 */
	@Test
	public void testGetSolvenlpFinishedContent()
	{
		// tests constraintNumber == 0 case
		String returnVal = ProblemFixedContent.getSolvenlpFinishedContent(0, true);
		assertTrue(returnVal.contains("lp = loadnlp (PROBNAME, numcols, numrows, objsen, obj, NULL, NULL, matbeg, "
				+ "matcnt, matind, NULL, initx, lb, ub, rngval, nzspace, funceval, jacobian);"));
		assertTrue(returnVal.contains("if (!lp){"));
		assertTrue(returnVal.contains("printf(\"No optimization object\");"));
		assertTrue(returnVal.contains("return;"));
		assertTrue(returnVal.contains("}"));
		assertTrue(returnVal.contains("setintparam (lp, PARAM_DERIV, derivflag);"));
		assertTrue(returnVal.contains("optimize (lp);"));
		assertTrue(returnVal.contains("solution (lp, pstat, pobj, finalx, NULL, NULL, dj);"));
		assertTrue(returnVal.contains("setlpcallbackfunc (lp, NULL);"));
		assertTrue(returnVal.contains("setintparam (lp, PARAM_DERIV, 0);"));
		assertTrue(returnVal.contains("unloadprob (&lp);"));
		assertTrue(returnVal.contains("}"));

		//for constraintNumber > 0 case
		returnVal = ProblemFixedContent.getSolvenlpFinishedContent(1, true);
		assertTrue(returnVal.contains("lp = loadnlp (PROBNAME, numcols, numrows, objsen, obj, rhs, sense, matbeg, "
				+ "matcnt, matind, matval, initx, lb, ub, rngval, nzspace, funceval, jacobian);"));
		assertTrue(returnVal.contains("if (!lp){"));
		assertTrue(returnVal.contains("printf(\"No optimization object\");"));
		assertTrue(returnVal.contains("return;"));
		assertTrue(returnVal.contains("}"));
		assertTrue(returnVal.contains("setintparam (lp, PARAM_DERIV, derivflag);"));
		assertTrue(returnVal.contains("optimize (lp);"));
		assertTrue(returnVal.contains("solution (lp, pstat, pobj, finalx, piout, slack, dj);"));
		assertTrue(returnVal.contains("setlpcallbackfunc (lp, NULL);"));
		assertTrue(returnVal.contains("setintparam (lp, PARAM_DERIV, 0);"));
		assertTrue(returnVal.contains("unloadprob (&lp);"));
		assertTrue(returnVal.contains("}"));
	}

	/**
	 * Method to test getJsolveNLPSyn()
	 */
	@Test
	public void testGetJsolveNLPSyn()
	{
		final String jsolveNLP = "JNIEXPORT jdoubleArray JNICALL Java_com_gensym_gos_deploy_OnlineManager_jsolveNLP(JNIEnv * "
				+ "env, jobject this, jdoubleArray x, jdoubleArray lb, jdoubleArray ub , jdoubleArray exog){\n";
		assertEquals(jsolveNLP, ProblemFixedContent.getJsolveNLPSyn());
	}

	/**
	 * Method to test getJsolveNLPContent()
	 */
	@Test
	public void testGetJsolveNLPContent()
	{
		final String returnVal = ProblemFixedContent.getJsolveNLPContent();
		assertTrue(returnVal.contains("if (exogp == NULL) {"));
		assertTrue(returnVal.contains("printf(\"Exception occurred!\");"));
		assertTrue(returnVal.contains("return NULL; /* exception occurred */"));
		assertTrue(returnVal.contains("}"));
		assertTrue(returnVal.contains("solvenlp ( &stat, &objval, xp, xp, lbp, ubp, exogp);"));
		assertTrue(returnVal.contains("size = (*env)->GetArrayLength(env, x);"));
		assertTrue(returnVal.contains("results = (*env)->NewDoubleArray(env, size+2);"));
		assertTrue(returnVal.contains("temp[0] = (jdouble)stat;"));
		assertTrue(returnVal.contains("temp[1] = (jdouble)objval;"));
		assertTrue(returnVal.contains("(*env)->SetDoubleArrayRegion(env, results, 0, 2, temp);"));
		assertTrue(returnVal.contains("(*env)->SetDoubleArrayRegion(env, results, 2, size, xp);"));
		assertTrue(returnVal.contains("(*env)->ReleaseDoubleArrayElements(env, x, xp, 0);"));
		assertTrue(returnVal.contains("(*env)->ReleaseDoubleArrayElements(env, lb, lbp, 0);"));
		assertTrue(returnVal.contains("(*env)->ReleaseDoubleArrayElements(env, ub, ubp, 0);"));
		assertTrue(returnVal.contains("(*env)->ReleaseDoubleArrayElements(env, exog, exogp, 0);"));
		assertTrue(returnVal.contains("return results;"));
	}
}
