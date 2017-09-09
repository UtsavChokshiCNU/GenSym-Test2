/**
 * Header file for StatisticalProcedures.c
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */



#ifndef STATISTICAL_PROCEDURES_H
#define STATISTICAL_PROCEDURES_H

#include "common_config.h"
#include "runtime.h"


Object XANALYS_API g2nke_historical_mean(
	Object o_history, 
	Object o_window_size, 
	Object o_start_index);

Object XANALYS_API g2nke_historical_variance(
	Object o_history, 
	Object o_window_size, 
	Object o_start_index);

#endif // STATISTICAL_PROCEDURES_H

