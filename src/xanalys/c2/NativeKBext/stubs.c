/* TODO: desctibe / Stubs for compiling in Xanalys
 * Subsystem:
 * Tags:
 *   - g2nke - native KB extensions
 * Used In:
 *   - 
 * 
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "g2ss/NativeKBext/Specific/SmartSignal/CountHistoryDatapoints.h"

Object XANALYS_API g2nke_count_history_datapoints_matching_op(
	Object subjVar, // the KB variable subject to history retrieval
	Object valueHistoryCascadedRingBuffer,
	Object valueHistoryRingBufferOrCascade,
	Object valueRequestedBySimulator_qm,
	Object referencingSimulationHistory_qm,
	Object N, 
	Object nStart, 
	Object fellow, // the fellow value to compare to
	Object requiredGoodSize, 
	Object compareOperator) 
{
	//TODO: report error "not implemented"
	return NIL;
}

Object XANALYS_API g2nke_count_history_datapoints_matching_op_and_eventflag(
	Object o_subjVar, // the KB variable subject to history retrieval
	Object o_N, 
	Object o_nStart, 
	Object o_fellow, // the fellow value to compare to
	Object o_eventFlag,
	Object o_eventBitPos,
	Object o_requiredGoodSize, 
	Object o_compareOperator) 
{
	//TODO: report error "not implemented"
	return NIL;
}

Object XANALYS_API c2_scalar_multiply(
    Object g2_array1,
    Object g2_array2,
    Object x)
{
	return NIL;
}


Object XANALYS_API c2_matrix_vector_to_vector_multiply(
    Object matrix_vector,
    Object vector1,
    Object vector2,
    Object index_1)
{
	return NIL;
}

Object XANALYS_API c2_initialize_matrix_multiply(
    Object  matrix1,
    Object matrix2,
    Object matrix3)
{
	return NIL;
}

Object XANALYS_API c2_matrix_to_matrix_multiply(
    Object j,
    Object m2,
    Object type,
    Object matrix1_vector,
    Object matrix2,
    Object matrix3_vector)
{
	return NIL;
}

Object XANALYS_API c2_array_multiply(
    Object g2_array1,
    Object g2_array2)
{
    return NIL;
}

Object XANALYS_API c2_array_add(
    Object g2_array1,
    Object g2_array2,
    Object g2_array3)
{
	return NIL;
}
