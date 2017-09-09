/* TODO: describe
 * Subsystem:
 * Tags:
 *   - g2nke - native KB extensions
 * Used In:
 *   - 
 * 
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#ifndef COUNT_HISTORY_DATAPOINTS_H
#define COUNT_HISTORY_DATAPOINTS_H

#include "common_config.h"
#include "runtime.h"

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
	Object compareOperator);

Object XANALYS_API g2nke_count_history_datapoints_matching_op_and_eventflag(
	Object o_subjVar, // the KB variable subject to history retrieval
	Object o_N, 
	Object o_nStart, 
	Object o_fellow, // the fellow value to compare to
	Object o_eventFlag,
	Object o_eventBitPos,
	Object o_requiredGoodSize, 
	Object o_compareOperator);

#endif /* COUNT_HISTORY_DATAPOINTS_H */