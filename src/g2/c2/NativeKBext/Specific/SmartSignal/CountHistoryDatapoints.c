/* Accelerating functioality for Smart Signal KB
 * Subsystem: G2.Subsystems.NativeKBext.Specific.SmartSignal
 * Tags:
 *   - g2nke - native KB extensions
 * Used In:
 *   - The KB code of Smart Signal database
 * 
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "g2ss/NativeKBext/Specific/SmartSignal/CountHistoryDatapoints.h"
#include <math.h>

//TODO: Move the prototypes of the translated functions into a separate header
////// BEGIN - Translated Prototypes
// interop.lisp, C2-GET-TOTAL-LENGTH-OF-RING-BUFFER-OR-CASCADE
// @param o_ring_buffer_or_cascade actual history object
// @returns Object the total number of data points in history
Object c2_get_total_length_of_ring_buffer_or_cascade(Object o_ring_buffer_or_cascade); 

// interop.lisp, C2-GET-HISTORY-SPEC 
// @param o_variable history container
// @returns Obejct the references that is needed to work with history
Object c2_get_history_spec(Object o_variable, Object o_valueRequestedBySimulator_qm);

// histories.lisp, GET-HISTORY-VALUE-FOR-RING-BUFFER-OR-CASCADE-FUNCTION
// @param o_ring_buffer_or_cascade actual history object
// @param o_element_index index of the element
// @returns Object A value at an index in the history
Object get_history_value_for_ring_buffer_or_cascade_function(
	Object o_ring_buffer_or_cascaded_ring_buffer,
	Object o_element_index);

// histories.lisp, COMPUTE-INDEX-FOR-PREVIOUS-DATA-POINT
// @param o_ring_buffer_or_cascade actual history object
// @param o_nPointsAgo number of points ago the datapoint resides
// @returns Object index of the datapoint in the history
Object compute_index_for_previous_data_point(
	Object o_ring_buffer_or_cascade, Object o_nPointsAgo);

// stack-eval2.lisp, EVAL-BITWISE-TEST-FUNCALLED
Object eval_bitwise_test_funcalled(Object value,Object location);

// types.lisp, look for (defparameter evaluation-true-value (cons truth 'truth-value))
extern Object Evaluation_true_value;

// rtl/c/values.c, prefixed with "g2rtl_" by librtl.h
#include <librtl.h>
extern TLS Object Values[];
////// END - Translated Prototypes

//TODO: Create a header with RTL prototypes and move these there
// converts a kb level double (object in c level) to c level double
extern double object_to_cdouble(Object o_x);
// converts a c level double to kb level double (object in c level)
extern Object cdouble_to_double(double x);


// When we have a header structure and a stabilized design for moving into C++,
//   we can get rid of these hacks and use STL stuff
static int l_min(int a, int b) {
	if( a < b ) return a;
	else return b;
}

// history data specification.
// stores all the data that is usefull to work with history
typedef struct tagHistorySpec {
	Object o_valueHistoryCascadedRingBuffer;
	Object o_valueHistoryRingBufferOrCascade;
	Object o_valueRequestedBySimulator_qm;
	Object o_referencingSimulationHistory_qm;
	Object o_ringBufferSerialNumber;
} HistorySpec;
// Arghh! Plain C, no++ .


int populateHistorySpecFromList(Object o_historySpec, HistorySpec *pDest) { // bool, indeed
	Object *fields[] = { 
		&(pDest->o_valueHistoryCascadedRingBuffer),
		&(pDest->o_valueHistoryRingBufferOrCascade),
		&(pDest->o_valueRequestedBySimulator_qm),
		&(pDest->o_referencingSimulationHistory_qm)
	};
	Object o_hsCur = o_historySpec;
	int i;

	for(i=0; i<sizeof(fields)/sizeof(fields[0]); i++) {
		// see function get_property_value() for a reference on using lists
		*fields[i] = M_CAR(o_hsCur);
		o_hsCur = M_CDR(o_hsCur);
		//TODO: test o_hsCur for NIL
	}
	//pDest->o_valueHistoryCascadedRingBuffer = M_CAR(o_hsCur);
	//o_hsCur = M_CDR(o_hsCur);
	//pDest->o_valueHistoryRingBufferOrCascade = M_CAR(o_hsCur);
	//o_hsCur = M_CDR(o_hsCur);
	//pDest->o_valueRequestedBySimulator_qm = M_CAR(o_hsCur);
	//o_hsCur = M_CDR(o_hsCur);
	//pDest->o_referencingSimulationHistory_qm = M_CAR(o_hsCur);

	return 1; // true
}


// populate history spec fom History container
// @param o_variable history container object
// @param History spec buffer where it should be copied
// @return always returns 1
int populateHistorySpec(Object o_variable, HistorySpec *pDest) { // bool, indeed
	// This was causing G2 allocation inconsistency
	//Object o_historySpec = c2_get_history_spec(o_variable
	//	, NIL // For now, we set value-requested-by-simulator? to false
	//);
	//return populateHistorySpecFromList(o_historySpec, pDest);
	Object o_ret = c2_get_history_spec(o_variable
		, NIL // For now, we set value-requested-by-simulator? to false
	);
	//TODO: check whether less values, or NIL (0 values) is returned
	MVS_5( o_ret
		, pDest->o_valueHistoryCascadedRingBuffer
		, pDest->o_valueHistoryRingBufferOrCascade
		, pDest->o_valueRequestedBySimulator_qm
		, pDest->o_referencingSimulationHistory_qm
		, pDest->o_ringBufferSerialNumber);
	return 1;
}


// the subject kb procedure that is converted to C
Object XANALYS_API g2nke_count_history_datapoints_matching_op(
	Object o_subjVar, // the KB variable subject to history retrieval
	Object o_valueHistoryCascadedRingBuffer,
	Object o_valueHistoryRingBufferOrCascade,
	Object o_valueRequestedBySimulator_qm,
	Object o_referencingSimulationHistory_qm,
	Object o_N, 
	Object o_nStart, 
	Object o_fellow, // the fellow value to compare to
	Object o_requiredGoodSize, 
	Object o_compareOperator) 
{
	int N = IFIX( o_N );
	int nStart = IFIX( o_nStart );

	Object o_nHistoryDatapoints = c2_get_total_length_of_ring_buffer_or_cascade( 
		o_valueHistoryRingBufferOrCascade );
	int nHistoryDatapoints = IFIX( o_nHistoryDatapoints );
	int nEnd = l_min(nStart+N, nHistoryDatapoints) - 1;
	int i;
	Object o_elmIndex;
	Object o_V; // historical values
	double V;
	int goodDataCount = 0;
	int matchedDataCount = 0;
	int compareOperator = IFIX(o_compareOperator);
	double fellow;
	int requiredGoodSize = IFIX(o_requiredGoodSize);
	double ans = 0;
	Object o_ans = NIL;
	//Not sure whether KB-level "value"-s are just DOUBLE_FLOATs
	if (!SI_IMMEDIATEP(o_fellow) && SI_PRIMITIVE_VECTOR_TYPE == SI_STORED_OBJECT_TYPE(o_fellow))
	{
		fellow = DOUBLE_FLOAT_TO_DOUBLE(o_fellow);
	}
	else
	{
		fellow = object_to_cdouble(o_fellow);
	}

	for(i=nStart; i<=nEnd; i++) {
		o_elmIndex = compute_index_for_previous_data_point(
			o_valueHistoryRingBufferOrCascade, FIX(i) );
		o_V = get_history_value_for_ring_buffer_or_cascade_function(o_valueHistoryRingBufferOrCascade,
			o_elmIndex );
		// now we need to convert o_V to C double type
		// Not sure whether the historical values of KB-level
		//   "quantitative-parameter" are just DOUBLE_FLOATs
		// V = DOUBLE_FLOAT_TO_DOUBLE(o_V);
		V = object_to_cdouble(o_V);
		// a test for NaN, http://stackoverflow.com/questions/570669/checking-if-a-double-or-float-is-nan-in-c
		if( (V) != (V) ) { 
			continue;
		}
		goodDataCount++;
		switch( compareOperator ) {
		case 1: // "GT_EQ"
			if( V >= fellow ) matchedDataCount++;
			break;
		case 2: // "GT"
			if( V > fellow ) matchedDataCount++;
			break;
		case 3: // "LT_EQ"
			if( V <= fellow ) matchedDataCount++;
			break;
		case 4: // "LT"
			if( V < fellow ) matchedDataCount++;
			break;
		case 5: // "EQ"
			if( V == fellow ) matchedDataCount++;
			break;
		case 6: // "NOT_EQ"
			if( V != fellow ) matchedDataCount++;
			break;
		}
	}

	if( goodDataCount >= requiredGoodSize && goodDataCount > 0 ) {
		ans = matchedDataCount / (double)goodDataCount;
	} else {
		ans = 0;
	}

	o_ans = cdouble_to_double(ans);
	return o_ans;
}

//Cached the result of next function
Object cached_subjVar;
Object cached_eventFlag;
Object cached_eventBitPos;
Object cached_N;
Object cached_nStart;
Object cached_compareOperator;
Object cached_requiredGoodSize;
Object cached_fellow;
Object cached_result;
Object cached_subjVarSnum;
Object cached_eventFlagSnum;

double cached_V[100000];
Object cached_H[100000];
int cached_Vend = -1;

// subject Kb method that is convertd to C
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
	// Inverse FIX for integer.
	// Or converting KB/Lisp level interger to C level interger - Shiplu Mokaddim, Wednesday, January 12, 2011 1:46:41 AM
	int N = IFIX( o_N ); 
	int nStart = IFIX( o_nStart );
	int compareOperator = IFIX(o_compareOperator);

	//Not sure whether KB-level "value"-s are just DOUBLE_FLOATs
	// double fellow = DOUBLE_FLOAT_TO_DOUBLE(o_fellow);
	double fellow = object_to_cdouble(o_fellow);
	int requiredGoodSize = IFIX(o_requiredGoodSize);
	
	int nEnd, mEnd;

	Object o_V; // historical values of the subject variable
	Object o_historicalEF; // historical values of the eventFlag
	double V;

	Object o_nHistoryDatapoints; // = c2_get_total_length_of_ring_buffer_or_cascade( o_valueHistoryRingBufferOrCascade );
	int nHistoryDatapoints; // = IFIX( o_nHistoryDatapoints );
	Object o_elmIndex;
	Object o_isOutlier;
	
	double ans = 0;
	Object o_ans = NIL;
	int goodDataCount = 0;
	int matchedDataCount = 0;
	int i;
	int use_CV = 0;

	HistorySpec hsSubj;
	HistorySpec hsEventFlag;

	//TODO: look at the return values
	// populating the history specs from history container
	(void)populateHistorySpec( o_subjVar, &hsSubj );
	(void)populateHistorySpec( o_eventFlag, &hsEventFlag );

	if (cached_subjVar == o_subjVar &&
	    cached_fellow == o_fellow &&
	    cached_eventFlag == o_eventFlag &&
	    cached_eventBitPos == o_eventBitPos &&
	    cached_requiredGoodSize == o_requiredGoodSize &&
	    cached_compareOperator == o_compareOperator &&
	    cached_subjVarSnum == hsSubj.o_ringBufferSerialNumber &&
	    cached_eventFlagSnum == hsEventFlag.o_ringBufferSerialNumber)
	    use_CV = 1;

	if (use_CV &&
		cached_N == o_N &&
		cached_nStart == o_nStart)
	    return cached_result;

	//// Calculating nEnd
	// calculating the total number of data points in ring buffer or cacade a.k.a. history
	o_nHistoryDatapoints = c2_get_total_length_of_ring_buffer_or_cascade( 
		hsSubj.o_valueHistoryRingBufferOrCascade );
	nHistoryDatapoints = IFIX( o_nHistoryDatapoints );
	nEnd = l_min( nStart+N, nHistoryDatapoints ) - 1;
	//// Calculating mEnd
	// calculating the total number of data points in ring buffer or cacade a.k.a. history
	o_nHistoryDatapoints = c2_get_total_length_of_ring_buffer_or_cascade( 
		hsEventFlag.o_valueHistoryRingBufferOrCascade );
	nHistoryDatapoints = IFIX( o_nHistoryDatapoints );
	mEnd = l_min( nStart+N, nHistoryDatapoints ) - 1;

	// Iterating through all the history element
	for(i=nStart; i<=nEnd; i++) {
		if (use_CV && i<=cached_Vend)
			V = cached_V[i];
		else {
		// here compute_index_for_previous_data_point() method returns the actual index of the history element
		// history elements are not stored as an 0 indexed array.  The data structure is complex
		// any data at i datapoint ago is not at 0/1 index.  Here we find that index. 
		// Shiplu Mokaddim, Wednesday, January 12, 2011 1:56:14 AM
		o_elmIndex = compute_index_for_previous_data_point(
			hsSubj.o_valueHistoryRingBufferOrCascade, FIX(i) );

		// When we know the index of the history value. We just retrive it using a c level lisp function.
		o_V = get_history_value_for_ring_buffer_or_cascade_function(hsSubj.o_valueHistoryRingBufferOrCascade,
			o_elmIndex );

		// now we need to convert history value (o_V) to C double type
		// Not sure whether the historical values of KB-level
		//   "quantitative-parameter" are just DOUBLE_FLOATs
		// V = DOUBLE_FLOAT_TO_DOUBLE(o_V);
		V = object_to_cdouble(o_V);
			cached_V[i] = V;
			if (cached_Vend < i) cached_Vend = i;
		}
		// a test for NaN, http://stackoverflow.com/questions/570669/checking-if-a-double-or-float-is-nan-in-c
		if( (V) != (V) ) { 
			continue;
		}


		/// Following is the C-Level implementation of KB level business function
#pragma region Test for outlier
		if( i <= mEnd ) {
			if (use_CV && i<=cached_Vend)
				o_historicalEF = cached_H[i];
			else {
				o_elmIndex = compute_index_for_previous_data_point(
					hsEventFlag.o_valueHistoryRingBufferOrCascade, FIX(i) );
				o_historicalEF = get_history_value_for_ring_buffer_or_cascade_function(
					hsEventFlag.o_valueHistoryRingBufferOrCascade,
					o_elmIndex );
				cached_H[i] = o_historicalEF;
				if (cached_Vend < i)
					cached_Vend = i;
			}
			// Not sure whether this is a proper and sufficient way of handling the return
			//   value from a *_funcalled
			MVS_1(
				eval_bitwise_test_funcalled( o_historicalEF, o_eventBitPos ),
				o_isOutlier ); // assign to o_isOutlier
			if( EQ(o_isOutlier, Evaluation_true_value) ) {
				continue;
			}
		}
#pragma endregion

		goodDataCount++;
		switch( compareOperator ) {
		case 1: // "GT_EQ"
			if( V >= fellow ) matchedDataCount++;
			break;
		case 2: // "GT"
			if( V > fellow ) matchedDataCount++;
			break;
		case 3: // "LT_EQ"
			if( V <= fellow ) matchedDataCount++;
			break;
		case 4: // "LT"
			if( V < fellow ) matchedDataCount++;
			break;
		case 5: // "EQ"
			if( V == fellow ) matchedDataCount++;
			break;
		case 6: // "NOT_EQ"
			if( V != fellow ) matchedDataCount++;
			break;
		}
	}

	if( goodDataCount >= requiredGoodSize && goodDataCount > 0 ) {
		ans = matchedDataCount / (double)goodDataCount;
	} else {
		ans = 0;
	}
	cached_subjVar = o_subjVar;
	cached_N = o_N;
	cached_nStart = o_nStart;
	cached_fellow = o_fellow;
	cached_eventFlag = o_eventFlag;
	cached_eventBitPos = o_eventBitPos;
	cached_requiredGoodSize = o_requiredGoodSize;
	cached_compareOperator = o_compareOperator;
	cached_subjVarSnum = hsSubj.o_ringBufferSerialNumber;
	cached_eventFlagSnum = hsEventFlag.o_ringBufferSerialNumber;
	// The result is found.
	// converting it back to lisp/kb level double type before returning
	o_ans = cdouble_to_double(ans);
	cached_result = o_ans;

	return o_ans;
}
