/** Accelerating functioality for Continental KB
 * It involevs improving statistical functions used in KB level or even in lisp level
 * Subsystem: G2.Subsystems.NativeKBext.Specific.Continental
 * Tags:
 *   - g2nke - native KB extensions
 * Used In:
 *   - The KB code of Continental
 * 
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */



#include "g2ss/NativeKBext/Specific/Continental/StatisticalProcedures.h"

/*****************************************************************************
 *   The following portion is copied from CountHisotryDatapoint.c            *
 *****************************************************************************/
// interop.lisp, C2-GET-TOTAL-LENGTH-OF-RING-BUFFER-OR-CASCADE
Object c2_get_total_length_of_ring_buffer_or_cascade(Object o_ring_buffer_or_cascade); 

// interop.lisp, C2-GET-HISTORY-SPEC
Object c2_get_history_spec(Object o_variable, Object o_valueRequestedBySimulator_qm);

// histories.lisp, GET-HISTORY-VALUE-FOR-RING-BUFFER-OR-CASCADE-FUNCTION
Object get_history_value_for_ring_buffer_or_cascade_function(
	Object o_ring_buffer_or_cascaded_ring_buffer,
	Object o_element_index);

// histories.lisp, COMPUTE-INDEX-FOR-PREVIOUS-DATA-POINT
Object compute_index_for_previous_data_point(
	Object o_ring_buffer_or_cascade, Object o_nPointsAgo);

// stack-eval2.lisp, EVAL-BITWISE-TEST-FUNCALLED
Object eval_bitwise_test_funcalled(Object value,Object location);

// types.lisp, look for (defparameter evaluation-true-value (cons truth 'truth-value))
extern Object Evaluation_true_value;

// rtl/c/values.c, prefixed with "g2rtl_" by librtl.h
#include <librtl.h>
extern Object Values[];
////// END - Translated Prototypes

//TODO: Create a header with RTL prototypes and move these there
extern double object_to_cdouble(Object o_x);
extern Object cdouble_to_double(double x);



// When we have a header structure and a stabilized design for moving into C++,
//   we can get rid of these hacks and use STL stuff
static int l_min(int a, int b) {
	if( a < b ) return a;
	else return b;
}




/*****************************************************************************
 *       The above  portion is copied from CountHisotryDatapoint.c           *
 *****************************************************************************/

// subject Kb method that is convertd to C

// cache mechinasm

Object cached_history_1;
Object cached_window_size_1;
Object cached_start_index_1;
Object cached_serial_number_1;
double cached_result_1;

double cached_CV1[100000];
int cached_Vend1 = -1;

Object XANALYS_API g2nke_historical_mean(
	Object o_history, 
	Object o_window_size, 
	Object o_start_index)
{
	// Inverse FIX for integer.
	int nWindow = IFIX(o_window_size);
	int nStart = IFIX(o_start_index);
	int nEnd;

	Object o_nHistoryDatapoints; // = c2_get_total_length_of_ring_buffer_or_cascade( o_valueHistoryRingBufferOrCascade );
	
	int nHistoryDatapoints; // = IFIX( o_nHistoryDatapoints );

	// element index of historical value
	Object o_elmIndex;

	// to store historical mean
	double mean = 0;
	// to store historical mean for returning
	Object o_historical_mean = NIL;

	double sum = 0;
	Object o_value = NIL;
	double value = 0;
	int i, use_CV = 0;

	// history object values
	HistorySpec hsSpec;

	// populating the history specs from history container
	(void)populateHistorySpec(o_history, &hsSpec);

	if (cached_history_1 == o_history &&
	    cached_serial_number_1 == hsSpec.o_ringBufferSerialNumber)
		use_CV = 1;

	if (use_CV &&
		cached_window_size_1 == o_window_size &&
	    cached_start_index_1 == o_start_index)
		return cdouble_to_double(cached_result_1);

	// calculating the total number of data points in ring buffer or cacade a.k.a. history
	o_nHistoryDatapoints = c2_get_total_length_of_ring_buffer_or_cascade(hsSpec.o_valueHistoryRingBufferOrCascade);
	nHistoryDatapoints = IFIX( o_nHistoryDatapoints );



	/*******************************************
	 *            Business Logic               *
	 *******************************************
		NEnd = NWindow +NStart - 1;
    
		for i = NStart to NEnd do
			Val = the value of Var as of i datapoints ago;
			Sum1 = Sum1 + Val;
		end;
    
		Mean = Sum1 / NWindow;
	*******************************************/

	
	nEnd = l_min( nStart+ nWindow, nHistoryDatapoints ) -1;
	
	for(i=nStart; i<=nEnd; i++)
	{
		if (use_CV && i <= cached_Vend1)
			value = cached_CV1[i];
		else {
			o_elmIndex = compute_index_for_previous_data_point(hsSpec.o_valueHistoryRingBufferOrCascade, FIX(i));
			o_value = get_history_value_for_ring_buffer_or_cascade_function(hsSpec.o_valueHistoryRingBufferOrCascade, o_elmIndex);
			value  = object_to_cdouble(o_value);
			cached_CV1[i] = value;
			if (i > cached_Vend1) cached_Vend1 = i;
			// if its not a number we dont need to use it
			if( (value) != (value)){
				continue;
			}
		}
		sum+=value;
	}
	mean = sum/(double)nWindow;

	o_historical_mean = cdouble_to_double(mean);
	cached_history_1 = o_history;
	cached_window_size_1 = o_window_size;
	cached_start_index_1 = o_start_index;
	cached_serial_number_1 = hsSpec.o_ringBufferSerialNumber;
	cached_result_1 = mean;
	return o_historical_mean;
}


// Subject kb level procedure

Object cached_history_2;
Object cached_window_size_2;
Object cached_start_index_2;
Object cached_serial_number_2;
double cached_result_2;

Object XANALYS_API g2nke_historical_variance(
	Object o_history, 
	Object o_window_size, 
	Object o_start_index)
{
		// Inverse FIX for integer.
	int nWindow = IFIX(o_window_size);
	int nStart = IFIX(o_start_index);
	int nEnd;

	
	Object o_nHistoryDatapoints; 
	
	int nHistoryDatapoints; 

	// element index of historical value
	Object o_elmIndex;

	double mean = 0;
	double variance = 0;
	double sum = 0;
	Object o_value = NIL;
	double historical_value = 0;
	int i;
	Object o_variance=NIL;
	// history object values
	HistorySpec hsSpec;

	// populating the history specs from history container
	(void)populateHistorySpec(o_history, &hsSpec);

	if (cached_history_2 == o_history &&
            cached_window_size_2 == o_window_size &&
	    cached_start_index_2 == o_start_index &&
	    cached_serial_number_2 == hsSpec.o_ringBufferSerialNumber)
		return cdouble_to_double(cached_result_2);

	// calculating the total number of data points in ring buffer or cacade a.k.a. history
	o_nHistoryDatapoints = c2_get_total_length_of_ring_buffer_or_cascade(hsSpec.o_valueHistoryRingBufferOrCascade);
	nHistoryDatapoints = IFIX( o_nHistoryDatapoints );

	
	nEnd = l_min( nStart+ nWindow, nHistoryDatapoints ) -1;
	
	// creating dynamic array to store history variables

	// calculating average
	for(i=nStart; i<=nEnd; i++)
	{
		o_elmIndex = compute_index_for_previous_data_point(hsSpec.o_valueHistoryRingBufferOrCascade, FIX(i));
		o_value = get_history_value_for_ring_buffer_or_cascade_function(hsSpec.o_valueHistoryRingBufferOrCascade, o_elmIndex);

		historical_value = object_to_cdouble(o_value);

		// if its not a number we dont need to use it
		if( (historical_value) != (historical_value)){
			continue;
		}
		sum += historical_value;
	}

	mean = sum/(double)nWindow;
	
	// calculating variance
	sum = 0;
	for(i=nStart; i<=nEnd; i++)
	{
		o_elmIndex = compute_index_for_previous_data_point(hsSpec.o_valueHistoryRingBufferOrCascade, FIX(i));
		o_value = get_history_value_for_ring_buffer_or_cascade_function(hsSpec.o_valueHistoryRingBufferOrCascade, o_elmIndex);

		historical_value = object_to_cdouble(o_value);

		// if its not a number we dont need to use it
		if( (historical_value) != (historical_value)){
			continue;
		}

		sum += (historical_value - mean)*(historical_value - mean);
	}

	// clear the allocated memory
	variance = sum/(double)nWindow;
	o_variance = cdouble_to_double(variance);
	cached_history_2 = o_history;
	cached_window_size_2 = o_window_size;
	cached_start_index_2 = o_start_index;
	cached_serial_number_2 = hsSpec.o_ringBufferSerialNumber;
	cached_result_2 = variance;
	return o_variance;
}
