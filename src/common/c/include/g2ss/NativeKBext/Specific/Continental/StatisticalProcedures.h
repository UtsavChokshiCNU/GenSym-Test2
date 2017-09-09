/**
 * Header file for StatisticalProcedures.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */



#ifndef STATISTICAL_PROCEDURES_H
#define STATISTICAL_PROCEDURES_H

#include "common_config.h"
#include "runtime.h"

typedef struct tagHistorySpec {
	Object o_valueHistoryCascadedRingBuffer;
	Object o_valueHistoryRingBufferOrCascade;
	Object o_valueRequestedBySimulator_qm;
	Object o_referencingSimulationHistory_qm;
	Object o_ringBufferSerialNumber;
} HistorySpec;

extern int populateHistorySpecFromList(Object o_historySpec, HistorySpec *pDest);
extern int populateHistorySpec(Object o_variable, HistorySpec *pDest);



Object XANALYS_API g2nke_historical_mean(
	Object o_history, 
	Object o_window_size, 
	Object o_start_index);

Object XANALYS_API g2nke_historical_variance_from_mean(
	Object o_history, 
	Object o_window_size, 
	Object o_start_index,
	Object o_mean);

#endif // STATISTICAL_PROCEDURES_H

