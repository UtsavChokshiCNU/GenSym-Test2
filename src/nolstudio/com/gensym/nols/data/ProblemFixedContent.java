package com.gensym.nols.data;
import java.util.*;
import java.io.*;

public class ProblemFixedContent implements Serializable {
	static final long serialVersionUID = 1L;

	private static String includes = "#include \"OptProb.h\"\n#include <stdio.h>\n#include <string.h>\n#include <stdlib.h>\n";
	private static String funceval = "INTARG _CC funceval (HPROBLEM lp, INTARG numcols, INTARG numrows, LPREALARG objval, LPREALARG lhs, LPREALARG var, INTARG varone, INTARG vartwo){\n";
	private static String jacobian = "INTARG _CC jacobian (HPROBLEM lp,INTARG numcols,INTARG numrows,INTARG nzspace,LPREALARG objval,LPREALARG obj, LPINTARG matbeg,LPINTARG matcnt,HPINTARG matind,HPREALARG matval,LPREALARG var,LPBYTEARG objtype, LPBYTEARG matvaltype){\n";
	private static String solvenlp = "__declspec(dllexport) void __stdcall solvenlp(LPINTARG pstat, LPREALARG pobj,LPREALARG finalx, LPREALARG initx, LPREALARG lb, LPREALARG ub, LPREALARG exog){\n";
	private static String jsolveNLP = "JNIEXPORT jdoubleArray JNICALL Java_com_gensym_gos_deploy_OnlineManager_jsolveNLP(JNIEnv * env, jobject this, jdoubleArray x, jdoubleArray lb, jdoubleArray ub , jdoubleArray exog){\n";


 	public ProblemFixedContent(){}


	public static String getIncludes(){
		return includes;
	}

	public static String getFuncevalSyn(){
		return funceval;
	}

	public static String getJacobianSyn(){
		return jacobian;
	}

	public static String getSolvenlpSyn(){
		return solvenlp;
	}

	public static String getSolvenlpFinishedContent(int constraintNumber, boolean useJacobian){
		StringBuffer sb = new StringBuffer (1000);
		String jaco = "NULL";
		if(useJacobian){
			jaco = "jacobian";
		}
		if(constraintNumber >0){
			sb.append ("lp = loadnlp (PROBNAME, numcols, numrows, objsen, obj, rhs, sense, matbeg, matcnt, matind, matval, initx, lb, ub, rngval, nzspace, funceval, "+jaco+");\n");
		}else{
			sb.append ("lp = loadnlp (PROBNAME, numcols, numrows, objsen, obj, NULL, NULL, matbeg, matcnt, matind, NULL, initx, lb, ub, rngval, nzspace, funceval, "+jaco+");\n");
		}
		sb.append ("if (!lp){\n");
		sb.append ("printf(\"No optimization object\");\n");
		sb.append ("return;\n");
		sb.append ("}\n");
		sb.append ("setintparam (lp, PARAM_DERIV, derivflag);\n");
		sb.append ("optimize (lp);\n");
		if(constraintNumber >0){
			sb.append ("solution (lp, pstat, pobj, finalx, piout, slack, dj);\n");
		}else{
			sb.append ("solution (lp, pstat, pobj, finalx, NULL, NULL, dj);\n");
		}
		sb.append ("setlpcallbackfunc (lp, NULL);\n");
		sb.append ("setintparam (lp, PARAM_DERIV, 0);\n");
		sb.append ("unloadprob (&lp);\n");
		sb.append ("}\n");
		return sb.toString();
	}

	public static String getJsolveNLPSyn(){
		return jsolveNLP;
	}

	public static String getJsolveNLPContent(){
		StringBuffer sb = new StringBuffer (1000);
		sb.append ("jdouble *xp;\n");
		sb.append ("jdouble *lbp;\n");
		sb.append ("jdouble *ubp;\n");
		sb.append ("jdouble *exogp;\n");
		sb.append ("jdoubleArray results;\n");
		sb.append ("jdouble temp[2];\n");
		sb.append ("jint size;\n");
		sb.append ("long stat; double objval;\n");
		sb.append ("xp = (*env)->GetDoubleArrayElements(env, x, NULL);\n");
		sb.append ("if (xp == NULL) {\n");
		sb.append ("printf(\"Exception occurred!\");\n");
		sb.append ("return NULL; /* exception occurred */\n");
		sb.append ("}\n");
		sb.append ("lbp = (*env)->GetDoubleArrayElements(env, lb, NULL);\n");
		sb.append ("if (lbp == NULL) {\n");
		sb.append ("printf(\"Exception occurred!\");\n");
		sb.append ("return NULL; /* exception occurred */\n");
		sb.append ("}\n");
		sb.append ("ubp = (*env)->GetDoubleArrayElements(env, ub, NULL);\n");
		sb.append ("if (ubp == NULL) { \n");
		sb.append ("printf(\"Exception occurred!\");\n");
		sb.append ("return NULL; /* exception occurred */\n");
		sb.append ("}\n");
		sb.append ("exogp = (*env)->GetDoubleArrayElements(env, exog, NULL);\n");
		sb.append ("if (exogp == NULL) {\n");
		sb.append ("printf(\"Exception occurred!\");\n");
		sb.append ("return NULL; /* exception occurred */\n");
		sb.append ("}\n");
		sb.append ("solvenlp ( &stat, &objval, xp, xp, lbp, ubp, exogp);\n");
		sb.append ("size = (*env)->GetArrayLength(env, x);\n");
		sb.append ("results = (*env)->NewDoubleArray(env, size+2);\n");
		sb.append ("temp[0] = (jdouble)stat;\n");
		sb.append ("temp[1] = (jdouble)objval;\n");
		sb.append ("(*env)->SetDoubleArrayRegion(env, results, 0, 2, temp);\n");
		sb.append ("(*env)->SetDoubleArrayRegion(env, results, 2, size, xp);\n");

		sb.append ("(*env)->ReleaseDoubleArrayElements(env, x, xp, 0);\n");
		sb.append ("(*env)->ReleaseDoubleArrayElements(env, lb, lbp, 0);\n");
		sb.append ("(*env)->ReleaseDoubleArrayElements(env, ub, ubp, 0);\n");
		sb.append ("(*env)->ReleaseDoubleArrayElements(env, exog, exogp, 0);\n");
		sb.append ("return results;\n");
		return sb.toString();
	}



}
